#include<errno.h> 
#include<unistd.h>
#include<fcntl.h>   
#include<stdio.h>    
#include<stdlib.h>    
#include<string.h>

int main(int argc,char* argv[]){
   char* token=strtok(argv[1],".");
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

   printf("%s\n",mimeType);
   return 0;
}
