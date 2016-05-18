#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h> 

#define BUFERSIZE 2048
#define PORT_NO 1234
#define error(a,b) fprintf(stderr, a, b)  // error 'function'


int main(int argc,char *argv[]){

	int fd;	        	           		// socket endpt
   int flags;                      	// rcv flags
   struct sockaddr_in server;      	// socket name (addr) of server
   struct sockaddr_in client;	     	// socket name of client
   int server_size;                	// length of the socket addr. server
   int client_size;                	// length of the socket addr. client
   int bytes;		           					// length of buffer 
   int rcvsize;                    	// received bytes
   int trnmsize;                   	// transmitted bytes
   int err;                        	// error code
   char on;                        	// 
   char buffer[BUFERSIZE+1];	     		// datagram dat buffer area   
   int valasz;

	on                     = 1;
   flags                  = 0;
   bytes                  = BUFERSIZE;
   server_size            = sizeof server;
   client_size            = sizeof client;
   server.sin_family      = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port        = htons(PORT_NO);


   fd = socket(AF_INET, SOCK_STREAM,0);
   if(fd < 0){
      error("%s:Socket creation error.",argv[0]);
      exit(1);
   }

   setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on,sizeof on);
   setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on,sizeof on);

   err = connect(fd, (struct sockaddr *)&server, server_size);
   if(err < 0){
      error("%s:Cannot connect to the socket\n", argv[0]);
      exit(2);
   }

   rcvsize = recv(fd, buffer, bytes, flags);
   if(rcvsize < 0){
      error("%s:Cannot recieve from the socket.\n",argv[0]);
      exit(4);
   }
   printf("%s\n", buffer);
   while(1){
      rcvsize = recv(fd, buffer, bytes, flags);
      if(rcvsize < 0){
         error("%s:Cannot recieve from the socket.\n",argv[0]);
         exit(4);
      }

      if(!strcmp(buffer, "Te nyertél. Gratulálok!\n") || !strcmp(buffer, "Nem te nyertél. Majd legközelebb!\n")){
         printf("%s\n",buffer);
         close(fd);
         exit(0);
      }

      printf("%s\n", buffer);
      scanf("%s",buffer);

      trnmsize = send(fd, buffer, bytes, flags);
      if(trnmsize < 0){
         error("%s:Cannot recieve from the socket.\n",argv[0]);
         exit(3);
      }
      rcvsize = recv(fd, buffer, bytes, flags);
      if(rcvsize < 0){
         error("%s:Cannot recieve from the socket.\n",argv[0]);
         exit(4);
      }
      if(strcmp(buffer,"tovabb")){
         printf("%s\n",buffer );
         close(fd);
         exit(0);
      }
      rcvsize = recv(fd, buffer, bytes, flags);
      if(rcvsize < 0){
         error("%s:Cannot recieve from the socket.\n",argv[0]);
         exit(4);
      }
      printf("%s\n",buffer);
   }
   close(fd);
}










