#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<signal.h>
#include<pthread.h>
#include"../include/http.h"
#include"../include/config.h"

#define MAX_QUEUED 5

void*handle_requests_loop(void* data);

int sockets[THREADS];
pthread_mutex_t *mutexes;
pthread_cond_t *conditions;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int main(int argc,char* argv[]){
   int port,sock,serverlen,clientlen;
   struct sockaddr_in server,client;
   struct sockaddr* serverptr;
   struct sockaddr* clientptr;
   struct hostent* rem;
   int        i=0;                               
   int        thr_id[THREADS];      
   pthread_t  p_threads[THREADS];   	
   mutexes = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * THREADS);
   conditions = (pthread_cond_t *) malloc(sizeof(pthread_cond_t) * THREADS);

   config[PORT]=(char*)malloc(sizeof(char*)*MAX_CONFIG_LINE);
   config[PATH]=(char*)malloc(sizeof(char*)*MAX_CONFIG_LINE);
   config[THREADS]=(char*)malloc(sizeof(char*)*MAX_CONFIG_LINE);
   initFromConfig(config);

   if((sock=socket(PF_INET,SOCK_STREAM,0))<0){
      perror("Error in socket().");
      exit(-1);
   }

   port=atoi(config[PORT]);

   server.sin_family=PF_INET;
   server.sin_addr.s_addr=htonl(INADDR_ANY);
   server.sin_port=htons(port);
   
   serverptr=(struct sockaddr*) &server;
   serverlen=sizeof(server);

   if(bind(sock,serverptr,serverlen)<0){
      perror("Error in bind().");
      exit(-1);
   }
   
   if(listen(sock,MAX_QUEUED)){
      perror("Error in listen()");
      exit(-1);      
   }
   printf("Now listening on %d\n",port);
	
	for (i=0; i<THREADS; i++) {
		thr_id[i] = i;
		sockets[i]=0;
		pthread_create(&p_threads[i], NULL, &handle_requests_loop, (void*)&thr_id[i]);
		pthread_mutex_init(&mutexes[i], NULL);
		pthread_cond_init(&conditions[i], NULL);
   }
	
   while(1){
	   i = 0;
		while (sockets[i] != 0) {
			i++;
			if (i == THREADS)
				i = 0;
		}
	   
      clientptr=(struct sockaddr*) &client;
      clientlen=sizeof(client);
	
      if((sockets[i]=accept(sock,clientptr,&clientlen))<0){
         perror("Error in accept().");
         exit(-1);
      }

      if((rem=gethostbyaddr((char*)&client.sin_addr.s_addr,sizeof(client.sin_addr.s_addr),client.sin_family))==NULL){
         herror("Error in gethostbyadd()");
         
exit(-1);
      }
      
      pthread_cond_signal(&conditions[i]);
		
		
      /*
      char* req_token; 
      char method[MAX_SOCK];
      char path[MAX_SOCK];
      const char del[3] = "\r\n";
      char klakla[MAX_SOCK];

      strcpy(klakla,buffer);
      req_token=strtok(klakla,del);
      
      strcpy(method,strtok(req_token," "));
      method[strlen(method)]='\0';

      strcpy(path,strtok(NULL," "));
      path[strlen(path)]='\0';
      
      write(new_socket, "HTTP/1.1 200 OK\n", 15);
      write(new_socket, "Content-length: 46\n", 19);
      write(new_socket, "Content-Type: text/html\n\n", 25);
      write(new_socket, "<html><body><H1>",16);
      write(new_socket, method, strlen(method));
      write(new_socket, " ",1);
      write(new_socket, path, strlen(path));
      write(new_socket, "</H1></body></html>",19);
      */
   }
   close(sock);
}

void*
handle_requests_loop(void* data)
{
	pthread_mutex_lock(&mutex);
    int thread_id = *((int*)data);
    int error;
    int recval;
    pthread_mutex_unlock(&mutex);
    REQUEST* request;
	char buf[MAX_SOCK];
    while (1) {
		pthread_mutex_lock(&mutexes[thread_id]);
		pthread_cond_wait(&conditions[thread_id], &mutexes[thread_id]);
		request=NULL;
	    do{
				  error=0;
                  socklen_t len=sizeof(error);              

                  if((recval=recv(sockets[thread_id], buf, MAX_SOCK, 0))==0){
					break;  
			      }
                  printf("%s",buf);
                  request=parseRequest(buf); 
                   
                  executeRequest(*request,sockets[thread_id]);
                  free(request);
                  bzero(buf,sizeof(buf));
        }while(1);
        
        if(sockets[thread_id] !=0){
			close(sockets[thread_id]);
			sockets[thread_id] = 0;
		}
		pthread_mutex_unlock(&mutexes[thread_id]);
	}
  }
