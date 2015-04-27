#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<signal.h>
#include"../include/http.h"

int sock;

void signal_handler(int sig){
   close(sock);
   exit(0);
}

int main(int argc,char* argv[]){
   int port,serverlen;
   char buf[MAX_SOCK];
   struct sockaddr_in server;
   struct sockaddr* serverptr;
   struct hostent* rem;

   signal(SIGINT,signal_handler);

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

   char enter[MAX_SOCK];
   fgets(enter,MAX_SOCK,stdin);
  
   char req_string[MAX_SOCK]="DELETE /fd.txt HTTP/1.1\r\nHost: localhost:10000\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:31.0) Gecko/20100101 Firefox/31.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\nConnection: keep-alive\r\nCache-Control: max-age=0\r\n\r\n\r\n";;      

   if(write(sock,req_string,MAX_SOCK)<0){
      perror("Error in write().");
      exit(-1);
   }

   bzero(buf,sizeof(buf));
         
   if(read(sock,buf,sizeof(buf))<0){
      perror("Error in read().");
      exit(-1);
   }

   printf("%s\n",buf);

   close(sock);
   exit(0);
}

