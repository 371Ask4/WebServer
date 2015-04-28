#include<errno.h> 
#include<unistd.h>
#include<fcntl.h>   
#include<stdio.h>    
#include<stdlib.h>    
#include<string.h>
#include"../include/http.h"
#include"../include/config.h"

int length(const char** array) {
   int count = 0;
   while(array[count]) count++;
   return count;
}

int getFileSize(char* filename){
   struct stat buf;
   int n;
   
   n=stat(filename,&buf);
   if(n<0){
      perror("Error in lstat().");
      exit(-1);
   }   
   
   return buf.st_size;
}

void printContentType(int new_socket,char * path){
      write(new_socket, "Content-Type: ", 14);

      char* token=strtok(path,".");
      char* extension;
      //char* mimeType;
      
      while(token!=NULL){
         extension=strdup(token);
         token=strtok(NULL,".");
      }
      

      if(strcmp(extension,"txt")==0){
         //mimeType="text/plain";
         write(new_socket, "text/plain", 10);
      }else if(strcmp(extension,"sed")==0){
         //mimeType="text/plain";
         write(new_socket, "text/plain", 10);
      }else if(strcmp(extension,"awk")==0){
         //mimeType="text/plain";
         write(new_socket, "text/plain", 10);
      }else if(strcmp(extension,"c")==0){
         //mimeType="text/plain";
         write(new_socket, "text/plain", 10);
      }else if(strcmp(extension,"h")==0){
         //mimeType="text/plain";
         write(new_socket, "text/plain", 10);
      }else if(strcmp(extension,"html")==0){
         //mimeType="text/html";
         write(new_socket, "text/html", 9);
      }else if(strcmp(extension,"htm")==0){
         //mimeType="text/html";
         write(new_socket, "text/html", 9);
      }else if(strcmp(extension,"jpeg")==0){
         //mimeType="text/jpeg";
         write(new_socket, "text/jpeg", 9);
      }else if(strcmp(extension,"jpg")==0){
         //mimeType="text/jpeg";
         write(new_socket, "text/jpg", 8);
      }else if(strcmp(extension,"gif")==0){
         //mimeType="text/gif";
         write(new_socket, "text/gif", 8);
      }else if(strcmp(extension,"pdf")==0){
         //mimeType="application/pdf";
         write(new_socket, "text/pdf", 8);
      }else{
         //mimeType="application/octet-stream";
         write(new_socket, "application/octet-stream", 24);
      }

      //write(new_socket, mimeType, strlen(mimeType));
      write(new_socket, "\r\n", 2);
}

char* getMIME(char* path){
   char* token=strtok(path,".");
   char* extension;
   char* mimeType;

   while(token!=NULL){
      strcpy(extension,token);
      token=strtok(NULL,".");
   }
   
   if(strcmp(extension,"txt")==0){
      mimeType="text/plain";
   }else if(strcmp(extension,"sed")==0){
      mimeType="text/plain";
   }else if(strcmp(extension,"awk")==0){
      mimeType="text/plain";
   }else if(strcmp(extension,"c")==0){
      mimeType="text/plain";
   }else if(strcmp(extension,"h")==0){
      mimeType="text/plain";
   }else if(strcmp(extension,"html")==0){
      mimeType="text/html";
   }else if(strcmp(extension,"htm")==0){
      mimeType="text/html";
   }else if(strcmp(extension,"jpeg")==0){
      mimeType="text/jpeg";
   }else if(strcmp(extension,"jpg")==0){
      mimeType="text/jpeg";
   }else if(strcmp(extension,"gif")==0){
      mimeType="text/gif";
   }else if(strcmp(extension,"pdf")==0){
      mimeType="application/pdf";
   }else{
      mimeType="application/octet-stream";
   }

   return mimeType;
}

int executeHEAD(char* path,int new_socket){
   
   printf("\r\n");

   int fd,bytes;
   char buffer[MAX_SOCK];
   char with_dot[strlen(path)+1];
   char* end=(char*)malloc(sizeof(char)*2);

   end[0]=3;
   end[1]='\0';

   with_dot[0]='.';
   strcat(with_dot,path);
   if(path[0]=='.')
      fd=open(path,O_RDWR, 0400);
   else
      fd=open(with_dot,O_RDWR, 0400);

   if(fd<0){
      write(new_socket, "HTTP/1.1 404 File not found\r\n", 29);
      write(new_socket, "Content-length: 52\r\n", 20);
      write(new_socket, "Content-Type: text/html\r\n\r\n", 27);
      write(new_socket, "<html><body><h1>File not found.</h1></body></html>\r\n",52);
   }else{
     //char* mimeType=(char*)malloc(sizeof(char)*MAX_SOCK);
      //mimeType=getMIME(path);
      write(new_socket, "HTTP/1.1 200 OK\r\n", 17);
      write(new_socket, "Content-length: 45\r\n", 20);
      write(new_socket, "Content-Type: ", 14);

      char* token=strtok(path,".");
      char* extension;
      //char* mimeType;
      
      
      while(token!=NULL){
         extension=strdup(token);
         token=strtok(NULL,".");
      }
      

      if(strcmp(extension,"txt")==0){
         //mimeType="text/plain";
         write(new_socket, "text/plain", 10);
      }else if(strcmp(extension,"sed")==0){
         //mimeType="text/plain";
         write(new_socket, "text/plain", 10);
      }else if(strcmp(extension,"awk")==0){
         //mimeType="text/plain";
         write(new_socket, "text/plain", 10);
      }else if(strcmp(extension,"c")==0){
         //mimeType="text/plain";
         write(new_socket, "text/plain", 10);
      }else if(strcmp(extension,"h")==0){
         //mimeType="text/plain";
         write(new_socket, "text/plain", 10);
      }else if(strcmp(extension,"html")==0){
         //mimeType="text/html";
         write(new_socket, "text/html", 9);
      }else if(strcmp(extension,"htm")==0){
         //mimeType="text/html";
         write(new_socket, "text/html", 9);
      }else if(strcmp(extension,"jpeg")==0){
         //mimeType="text/jpeg";
         write(new_socket, "text/jpeg", 9);
      }else if(strcmp(extension,"jpg")==0){
         //mimeType="text/jpeg";
         write(new_socket, "text/jpg", 8);
      }else if(strcmp(extension,"gif")==0){
         //mimeType="text/gif";
         write(new_socket, "text/gif", 8);
      }else if(strcmp(extension,"pdf")==0){
         //mimeType="application/pdf";
         write(new_socket, "text/pdf", 8);
      }else{
         //mimeType="application/octet-stream";
         write(new_socket, "application/octet-stream", 24);
      }

      //write(new_socket, mimeType, strlen(mimeType));
      write(new_socket, "\r\n", 2);
      write(new_socket, "<html><body><h1>Success.</h1></body></html>\r\n",45); 

      //printf("\n%s\n",extension);
   }
  
   //write(new_socket, path,strlen(path));
   write(new_socket, end,2);
   return 1;
}

int executeGET(char* path,int new_socket){
   
   printf("\r\n");

   int fd,bytes;
   char buffer[MAX_SOCK];
   char with_dot[strlen(path)+1];
   char* end=(char*)malloc(sizeof(char)*2);
   
   end[0]=3;
   end[1]='\0';

   with_dot[0]='.';
   strcat(with_dot,path);
   if(path[0]=='.')
      fd=open(path,O_RDWR, 0400);
   else
      fd=open(with_dot,O_RDWR, 0400);

   if(fd<0){
      write(new_socket, "HTTP/1.1 401 File not found\n", 28);
      write(new_socket, "Content-length: 50\r\n", 19);
      write(new_socket, "Content-Type: text/html\r\n", 25);
      write(new_socket, "<html><body><h1>File not found.</h1></body></html>\r\n",50);
      write(new_socket, end,2);
   }else{
      write(new_socket, "HTTP/1.1 200 OK\r\n", 16);
      int fileSize = getFileSize(path);

      char fileSizeString[MAX_SOCK];
      sprintf(fileSizeString,"%d",fileSize);

      write(new_socket, "Content-length: ", 16);
      write(new_socket, fileSizeString, strlen(fileSizeString));
      write(new_socket, "\r\n",2);
      printContentType(new_socket,path);
      
      write(new_socket, "\r\n",2);
      
      do {
         bytes = read(fd, buffer, MAX_SOCK);
         write(new_socket,buffer,bytes);
      }while(bytes!=0);

      write(new_socket, end,2);
      
   }
   return 1;
}

int executeDELETE(char* path,int new_socket){
   printf("\r\n");
   
   int fd,bytes;
   char buffer[MAX_SOCK];
   char with_dot[strlen(path)+1];
   char* end=(char*)malloc(sizeof(char)*2);

   end[0]=3;
   end[1]='\0';

   with_dot[0]='.';
   strcat(with_dot,path);
   if(path[0]=='.')
      fd=open(path,O_RDWR, 0400);
   else{
      fd=open(with_dot,O_RDWR, 0400);
      path=with_dot;
   }

   if((fd<0)||(remove(path)<0)){
      write(new_socket, "HTTP/1.1 401 File not found\n", 28);
      write(new_socket, "Content-length: 45\r\n", 19);
      write(new_socket, "Content-Type: text/html\r\n", 25);
      write(new_socket, "<html><body><h1>File not found.</h1></body></html>",50);
   }else{
      write(new_socket, "HTTP/1.1 200 OK\r\n", 15);
      write(new_socket, "Content-length: 46\r\n", 19);
      write(new_socket, "Content-Type: text/html\r\n", 25);
      write(new_socket, "<html><body><h1>Success.</h1></body></html>\r\n",45);
   }
   
   write(new_socket, end,2);
   return 1;
}

char* convertToUpperCase(char *sPtr){
      while(*sPtr != '\0')
      {
         if (islower(*sPtr))
              *sPtr = toupper(*sPtr);
       }
}

int executeRequest(REQUEST request,int new_socket){
      
   if(strcmp(request.type->method,GET)==0){
      executeGET(request.type->path,new_socket);
      /*
      //////////////////////////////////
      printf("\nPATH: ");
      printf("%s\n",request.type->path);
      //////////////////////////////////

      write(new_socket, "HTTP/1.1 200 OK\n", 15);
      write(new_socket, "Content-length: 46\n", 19);
      write(new_socket, "Content-Type: text/html\n\n", 25);
      write(new_socket, "<html><body><H1>",16);
      write(new_socket, request.type->method, strlen(request.type->method));
      write(new_socket, " ",1);
      write(new_socket, request.type->path, strlen(request.type->path));
      write(new_socket, "</H1></body></html>",19);
      */
   }else if(strcmp(request.type->method,HEAD)==0){
      executeHEAD(request.type->path,new_socket);
      /*
      write(new_socket, "HTTP/1.1 200 OK\n", 15);
      write(new_socket, "Content-length: 46\n", 19);
      write(new_socket, "Content-Type: text/html\n\n", 25);
      write(new_socket, "<html><body><H1>",16);
      write(new_socket, request.type->method, strlen(request.type->method));
      write(new_socket, " ",1);
      write(new_socket, request.type->path, strlen(request.type->path));
      write(new_socket, "</H1></body></html>",19);
      */
   }else if(strcmp(request.type->method,DELETE)==0){
      executeDELETE(request.type->path,new_socket);
      /*
      write(new_socket, "HTTP/1.1 200 OK\n", 15);
      write(new_socket, "Content-length: 46\n", 19);
      write(new_socket, "Content-Type: text/html\n\n", 25);
      write(new_socket, "<html><body><H1>",16);
      write(new_socket, request.type->method, strlen(request.type->method));
      write(new_socket, " ",1);
      write(new_socket, request.type->path, strlen(request.type->path));
      write(new_socket, "</H1></body></html>",19);
      */
   }else{
      write(new_socket, "HTTP/1.1 500 OK\n", 15);
      write(new_socket, "Content-length: 46\n", 19);
      write(new_socket, "Content-Type: text/html\n\n", 25);
      write(new_socket, "<html><body><H1>",16);
      write(new_socket, "Method not implemented",22);
      write(new_socket, "</H1></body></html>",19);
   }
   return 1;
}

char* toString(REQUEST request){
   char* req_string=(char*)malloc(sizeof(char)*((
      strlen(request.type->method)+
      strlen(request.type->path)+
      strlen(request.type->protocol)+
      strlen(request.head->user_agent)+
      strlen(request.head->host)+
      strlen(request.head->connection))
   ));

   strcat(req_string,strcat(request.type->method," "));
   strcat(req_string,strcat(request.type->path," "));
   strcat(req_string,strcat(request.type->protocol," \r\n"));

   strcat(req_string,strcat(request.head->host,"\r\n"));
   strcat(req_string,strcat(request.head->user_agent,"\r\n"));
   strcat(req_string,strcat(request.head->connection,"\r\n\n"));
   return req_string;
}

REQUEST* parseRequest(char* req_ptr){
   char* req=(char*)malloc(sizeof(char)*MAX_SOCK);
   strcpy(req,req_ptr);

   //char req[MAX_SOCK]="GET / HTTP/1.1\r\nHost: localhost:10000\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:31.0) Gecko/20100101 Firefox/31.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\nConnection: keep-alive\r\nCache-Control: max-age=0\r\n\r\n\r\n";

   REQUEST* request=(REQUEST*)malloc(sizeof(REQUEST));
   REQUEST_HEAD* head=(REQUEST_HEAD*)malloc(sizeof(REQUEST_HEAD));
   TYPE* type=(TYPE*)malloc(sizeof(TYPE));
   
   char* req_token;
   char* host_token;
   char* user_token;
   char* connection_token;
   const char del[3] = "\r\n";

   char method[MAX_SOCK];
   char path[MAX_SOCK];
   char protocol[MAX_SOCK];
   char user_agent[MAX_SOCK];
   char host[MAX_SOCK];
   char connection[MAX_SOCK];

   req_token=strtok(req,del);
   host_token=strtok(NULL,del);
   user_token=strtok(NULL,del);

   connection_token=strtok(NULL,del);
   while(connection_token!=NULL){
      strcpy(connection,connection_token);
      connection[strlen(connection)]='\0';
      head->connection=connection;
      connection_token=strtok(NULL,del);
   }
   /*
   if(strcmp(method,GET)==0){
      printf("%s %s\n",GET,strtok(NULL," "));
   }else if(strcmp(method,HEAD)==0){
      printf("%s %s\n",HEAD,strtok(NULL," "));
   }else if(strcmp(method,DELETE)==0){
      printf("%s %s\n",DELETE,strtok(NULL," "));
   }else{
      printf("%s %s\n",NOT_IMPLEMENTED,strtok(NULL," "));
   }
   */
   
   strcpy(method,strtok(req_token," "));
   method[strlen(method)]='\0';
   type->method=method;

   strcpy(path,config[PATH]);
   strcat(path,strtok(NULL," "));
   path[strlen(path)]='\0';
   type->path=path;

   strcpy(protocol,strtok(NULL," "));
   protocol[strlen(protocol)]='\0';
   type->protocol=protocol;

   strcpy(user_agent,user_token);
   user_agent[strlen(user_agent)]='\0';
   head->user_agent=user_agent;

   strcpy(host,host_token);
   host[strlen(host)]='\0';
   head->host=host;

   request->type=type;
   request->head=head;


   return request;
}
