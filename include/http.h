#ifndef __HTTP__H_
#define __HTTP__H_

#define MAX_SOCK 1024
#define GET "GET"
#define HEAD "HEAD"
#define DELETE "DELETE"
#define NOT_IMPLEMENTED "Not Implemented"

#define CLOSE "close"
#define KEEP_ALIVE "keep-alive"

   typedef struct response_head{
      char* connection;
      char* server;
      char* content_length;
      char* content_type;
   }RESPONSE_HEAD;

   typedef struct request_head{
      char* user_agent;
      char* host;
      char* connection;
   }REQUEST_HEAD;

   typedef struct type{
      char* method;
      char* path;
      char* protocol;
   }TYPE;

   typedef struct request{
      struct type* type;
      struct request_head* head;
   }REQUEST;

   typedef struct response{
      struct response_head* head;
      char* protocol;
      int code;
      char* status;
      char* body;
   }RESPONSE;

   REQUEST* parseRequest(char*);
   int executeRequest(REQUEST,int);
   int executeHEAD(char*,int);
   int executeGET(char*,int);
   int executeDELETE(char*,int);
   char* toString(REQUEST);
   int length(const char**);
   char* getMIME(char*);
   char* convertToUpperCase(char *);
#endif
