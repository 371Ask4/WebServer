#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include"include/http.h"

char* toString(REQUEST);

int main(int argc,char* argv[]){
   int port,sock,serverlen;
   int bytes;
   char buf[MAX_SOCK];
   struct sockaddr_in server;
   struct sockaddr* serverptr;
   struct hostent* rem;
   char connection[MAX_SOCK];

   if(argc<3){
      printf("Please give host name and port number.\n");
      exit(-1);
   }

   if((sock=socket(PF_INET,SOCK_STREAM,0))<0){
      perror("Error in socket().");
      exit(-1);
   }

   if((rem=gethostbyname(argv[1]))==NULL){
      perror("Error in gethosbyname().");
      exit(-1);
   }

   port=atoi(argv[2]);
   server.sin_family=PF_INET;
   bcopy((char*)rem->h_addr,(char*)&server.sin_addr,rem->h_length);
   server.sin_port=htons(port);
   serverptr=(struct sockaddr*) &server;
   serverlen=sizeof(server);

   if(connect(sock,serverptr,serverlen)<0){
      perror("Error in connect().");
      exit(-1);
   }
   printf("Requested connection to %s on %d\n",argv[1],port);

      REQUEST request;
      REQUEST_HEAD* head=(REQUEST_HEAD*)malloc(sizeof(REQUEST_HEAD));
      TYPE* type=(TYPE*)malloc(sizeof(TYPE));
      char req_string[MAX_SOCK];
      char method[MAX_SOCK];
      char path[MAX_SOCK];
      char host[MAX_SOCK];
      char user_agent[MAX_SOCK];

      if(argv[3]==NULL){
         strcpy(connection,"keep-alive");
      }else if(strcmp(argv[3],"-c")==0){
         strcpy(connection,"close");
      }else{   
         printf("Wrong option.\n");
         exit(-1);
      }

   do{
      printf("METHOD:");
      fgets(method,MAX_SOCK,stdin);
      method[strlen(method)-1]='\0';
      type->method=method;
      
      strcat(req_string,method);
      strcat(req_string," ");

      printf("FILE:");
      fgets(path,MAX_SOCK,stdin);
      path[strlen(path)-1]='\0';
      type->path=path;

      strcat(req_string,path);
      strcat(req_string," ");

      type->protocol="HTTP/1.1";
      
      strcat(req_string,"HTTP/1.1\r\n");

      
      /*
      printf("HOST:");
      fgets(host,MAX_SOCK,stdin);
      host[strlen(host)-1]='\0';
      */
      strcpy(host,argv[1]);
      strcat(host,":");
      strcat(host,argv[2]);
      head->host=host;
      
      strcat(req_string,"Host: ");
      strcat(req_string,host);
      strcat(req_string,"\r\n");
      
      strcpy(user_agent,"GNU bash, version 4.1.2(1)-release (x86_64-redhat-linux-gnu)");
      user_agent[strlen(user_agent)]='\0';
      head->user_agent=user_agent;

      strcat(req_string,"User-Agent: ");
      strcat(req_string,user_agent);
      strcat(req_string,"\r\n");
      
      connection[strlen(connection)]='\0';
      head->connection=connection;

      strcat(req_string,"Connection: ");
      strcat(req_string,connection);      
      strcat(req_string,"\r\n");

      strcat(req_string,"Cache-Control: max-age=0"); 
      strcat(req_string,"\r\n");

      request.type=type;
      request.head=head;
      
      //char* req_string=toString(request);      
      //printf("%s\n",req_string);
      
      if(write(sock,req_string,strlen(req_string))<0){
         perror("Error in write().");
         exit(-1);
      }

      bzero(buf,sizeof(buf));
      bzero(req_string,sizeof(req_string));
      
      do {
         bzero(buf,sizeof(buf));
         bytes=read(sock,buf,sizeof(buf));
         if(bytes<0){
            perror("Error in read().");
            exit(-1);
         }
         printf("%s\n",buf);
      }while(buf[bytes-2]!=3);
      bzero(buf,sizeof(buf));
      
      
      free(request.head);
      free(request.type);
      bzero((void *)&request,sizeof(request));

      bzero(req_string,sizeof(req_string));
      bzero(method,sizeof(method));
      bzero(path,sizeof(path));
      bzero(host,sizeof(host));
      bzero(user_agent,sizeof(user_agent));
      
      
   }while(strcmp(connection,KEEP_ALIVE)==0);
   close(sock);
   exit(0);
}


char* toString(REQUEST request){
   
   char* req_string=(char*)malloc(sizeof(char)*((
      strlen(request.type->method)+
      strlen(request.type->path)+
      strlen(request.type->protocol)+
      strlen(request.head->user_agent)+
      strlen(request.head->host)+
      strlen(request.head->connection)+18)
   ));

   char method[MAX_SOCK];
   strcpy(method,request.type->method);
   strcat(method," ");
   
   char path[MAX_SOCK];
   strcpy(path,request.type->path);
   strcat(path," ");

   char protocol[MAX_SOCK];
   strcpy(protocol,request.type->protocol);
   strcat(protocol,"\r\n");

   strcat(req_string,method);
   strcat(req_string,path);
   strcat(req_string,protocol);
   /*
   strcat(req_string,strcat(request.head->host,"\r\n"));
   strcat(req_string,strcat(request.head->user_agent,"\r\n"));
   strcat(req_string,strcat(request.head->connection,"\r\n\n"));
   */
   return req_string;
}

