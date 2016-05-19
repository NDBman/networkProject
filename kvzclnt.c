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

   //megkapjuk az első üzenetet (vagy várakozás vagy indulhat is a játék)
   rcvsize = recv(fd, buffer, bytes, flags);
   if(rcvsize < 0){
      error("%s:Cannot recieve from the socket.\n",argv[0]);
      exit(4);
   }
   printf("%s\n", buffer);
   while(1){
      //megkapjuk a kérdést
      rcvsize = recv(fd, buffer, bytes, flags);
      if(rcvsize < 0){
         error("%s:Cannot recieve from the socket.\n",argv[0]);
         exit(4);
      }
      //Ha már vége a játéknak akkor nem kérdést kapunk hanem erről értesítést.
      if(!strcmp(buffer,"break")){
         break;
      }
      //Kérdés kiírása, válasz beolvasása
      printf("%s\n", buffer);
      scanf("%s",buffer);

      //Választ elküldjük
      trnmsize = send(fd, buffer, bytes, flags);
      if(trnmsize < 0){
         error("%s:Cannot recieve from the socket.\n",argv[0]);
         exit(3);
      }
      //Megkapjuk, hogy feladta-e a másik játékos vagy mehet tovább a játék
      rcvsize = recv(fd, buffer, bytes, flags);
      if(rcvsize < 0){
         error("%s:Cannot recieve from the socket.\n",argv[0]);
         exit(4);
      }
      //Ha feladta itt kilépünk
      if(strcmp(buffer,"tovabb")){
         printf("%s\n",buffer );
         close(fd);
         exit(0);
      }
      //Megkapjuk a jelenlegi kör eredményét
      rcvsize = recv(fd, buffer, bytes, flags);
      if(rcvsize < 0){
         error("%s:Cannot recieve from the socket.\n",argv[0]);
         exit(4);
      }
      printf("%s\n",buffer);
   }
   rcvsize = recv(fd,buffer,bytes,flags);
   if(rcvsize < 0){
      error("%s:Cannot recieve from the socket.\n",argv[0]);
      exit(4);
   }
   printf("%s\n", buffer);
   sprintf(buffer,"vége");
   trnmsize = send(fd, buffer,bytes,flags);
   if(trnmsize < 0){
      error("%s:Cannot send to the socket.\n", argv[0]);
      exit(5);
   }
   close(fd);
}