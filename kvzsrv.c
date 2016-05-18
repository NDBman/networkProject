
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <time.h>

#define BUFERSIZE 2048
#define PORT_NO 1234
#define error(a,b) fprintf(stderr, a, b)  // error 'function'


int main(int argc,char *argv[]){

	srand(time(NULL));

	int fd;	        	           		// socket endpt
   	int fdc;                        	// socket endpt
   	int fdc2;
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
   	int jatszmaSzam = 1;
   	int i,j,sorSzam;
   	int voltMar[15];
   	int valasz1, valasz2, valasz;
   	int eredmeny1, eredmeny2;
   	int volt;

	jatszmaSzam = atoi(argv[1]);

   	

	on                     = 1;
   	flags                  = 0;
   	bytes                  = BUFERSIZE;
   	server_size            = sizeof server;
   	client_size            = sizeof client;
   	server.sin_family      = AF_INET;
   	server.sin_addr.s_addr = INADDR_ANY;
   	server.sin_port        = htons(PORT_NO);

   	if(jatszmaSzam > 0 && jatszmaSzam < 16){

	   	fd = socket(AF_INET, SOCK_STREAM, 0);
	   	if(fd < 0){
	   		error("%s: Socket creation error\n",argv[0]);
	      	exit(1);
	   	}

	   	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*) &on, sizeof on);
	   	setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char*) &on, sizeof on);

	   	err = bind(fd, (struct sockaddr *)&server,server_size);
	   	if(err < 0){
	   		error("%s:Cannot bind socket.\n",argv[0]);
	   		exit(2);
	   	}

	   	err = listen(fd, 10);
	   	if(err < 0){
	   		error("%s:Cannot listen to the socket.\n",argv[0]);
	   		exit(2);
	   	}

	   	fdc = accept(fd, (struct sockaddr *)&client, &client_size);
	   	if(fdc < 0){
	   		error("%s:Cannot accept the socket.\n", argv[0]);
	   		exit(3);
	   	}
	   	sprintf(buffer,"Várakozás a másik játékosra");
	   	trnmsize = send(fdc, buffer, bytes, flags);
	   	if(trnmsize < 0){
	   		error("%s:Cannot send to the socket.\n", argv[0]);
	   		exit(5);
	   	}

	   	fdc2 = accept(fd, (struct sockaddr*)&client,&client_size);
	   	if(fdc2 < 0){
	   		error("%s:Cannot accept the socket.\n", argv[0]);
	   		exit(3);
	   	}

	   	sprintf(buffer,"indulhat a játék.");
	   	trnmsize = send(fdc2, buffer, bytes, flags);
	   	if(trnmsize < 0){
	   		error("%s:Cannot send to the socket.\n", argv[0]);
	   		exit(5);
	   	}

	   	for(i = 0;i < jatszmaSzam;i++){
	   		volt = 1;
	   		while(volt){
	   			volt = 0;
	   			sorSzam = rand() % 14;
	   			for(j = 0;j < i;j++){
	   				if(sorSzam == voltMar[j]){
	   					volt = 1;
	   				}
	   			}
	   		}
	   		voltMar[i] = sorSzam;
	   		switch(sorSzam){
	   			case 0:
	   				sprintf(buffer,"Hány oldala van a négyszögnek?");
	   				valasz= 4;
	   				break;
	   			case 1:
	   				sprintf(buffer,"Hány darab kiskockából áll a Rubik kocka?");
	   				valasz=20;
	   				break;
	   			case 2:
	   				sprintf(buffer,"Hány perc egy óra?");
	   				valasz=60;
	   				break;
	   			case 3:
	   				sprintf(buffer,"Hány dalmata van a híres kutyás filmben?");
	   				valasz=100;
	   				break;
	   			case 4:
	   				sprintf(buffer,"Hány kívánságot teljesít a dzsinn");
	   				valasz= 3;
	   				break;
	   			case 5:
	   				sprintf(buffer,"Hány pöttye van a katicabogárnak?");
	   				valasz = 7;
	   				break;
	   			case 6:
	   				sprintf(buffer,"Mi az ördög száma?");
	   				valasz = 666;
	   				break;
	   			case 7:
	   				sprintf(buffer,"Hány ágra süt a nap?");
	   				valasz = 7;
	   				break;
	   			case 8:
	   				sprintf(buffer,"Mikor volt a Holdra szállás?");
	   				valasz = 1969;
	   				break;
	   			case 9:
	   				sprintf(buffer,"Mikor fedezték fel Amerikát?");
	   				valasz = 1492;
	   				break;
	   			case 10:
	   				sprintf(buffer,"Hány nagyszülőnk van?");
	   				valasz = 4;
	   				break;
	   			case 11:
	   				sprintf(buffer,"Hanyadika a szerencsétlen pénteki nap?");
	   				valasz = 13;
	   				break;
	   			case 12:
	   				sprintf(buffer,"Mi a legkisebb prímszám?");
	   				valasz = 2;
	   				break;
	   			case 13:
	   				sprintf(buffer,"Hanyas verziószámú a legújabb Windows?");
	   				valasz = 10;
	   				break;
	   			case 14:
	   				sprintf(buffer,"Számítógépek ezt a számrendszert használják.");
	   				valasz = 2;
	   				break;

	   		}
	   		trnmsize = send(fdc, buffer,bytes, flags);
	   		if(trnmsize < 0){
	   			error("%s:Cannot send to the socket.\n", argv[0]);
	   			exit(5);
	   		}
	   		trnmsize = send(fdc2, buffer,bytes, flags);
	   		if(trnmsize < 0){
	   			error("%s:Cannot send to the socket.\n", argv[0]);
	   			exit(5);
	   		}

	   		rcvsize = recv(fdc, buffer,bytes,flags);
	   		if(rcvsize < 0){
	   			error("%s:Cannot recieve from the socket.\n",argv[0]);
      			exit(4);
	   		}
	   		valasz1 = atoi(buffer);
	   		if(!strcmp(buffer,"feladom")){
	   			rcvsize = recv(fdc2, buffer,bytes,flags);
		   		if(rcvsize < 0){
		   			error("%s:Cannot recieve from the socket.\n",argv[0]);
	      			exit(4);
		   		}
	   			sprintf(buffer,"1-es játékos feladta.Te nyertél!\n");
	   			trnmsize = send(fdc2,buffer,bytes,flags);
	   			if(trnmsize < 0){
	   				error("%s:Cannot send to the socket.\n", argv[0]);
	   				exit(5);
	   			}
	   			sprintf(buffer, "Játék vége. Veszítettél!");
	   			trnmsize = send(fdc,buffer,bytes,flags);
	   			if(trnmsize < 0){
	   				error("%s:Cannot send to the socket.\n", argv[0]);
	   				exit(5);
	   			}
	   			close(fdc2);
	   			close(fdc);
	   			close(fd);
	   			exit(0);
	   		}else{
	   			rcvsize = recv(fdc2, buffer,bytes,flags);
		   		if(rcvsize < 0){
		   			error("%s:Cannot recieve from the socket.\n",argv[0]);
	      			exit(4);
		   		}
		   		
		   		valasz2= atoi(buffer);
		   		if(!strcmp(buffer,"feladom")){
		   			sprintf(buffer,"2-es játékos feladta.Te nyertél!\n");
		   			trnmsize = send(fdc,buffer,bytes,flags );
		   			if(trnmsize < 0){
	   					error("%s:Cannot send to the socket.\n", argv[0]);
	   					exit(5);
	   				}
	   				sprintf(buffer, "Játék vége. Veszítettél!");
	   				trnmsize = send(fdc2,buffer,bytes,flags);
	   				if(trnmsize < 0){
	   					error("%s:Cannot send to the socket.\n", argv[0]);
	   					exit(5);
	   				}
	   				close(fdc2);
	   				close(fdc);
	   				close(fd);
	   				exit(0);
		   		}else{
		   			sprintf(buffer,"tovabb");
		   			trnmsize = send(fdc,buffer,bytes,flags );
		   			if(trnmsize < 0){
	   					error("%s:Cannot send to the socket.\n", argv[0]);
	   					exit(5);
	   				}
	   				trnmsize = send(fdc2,buffer,bytes,flags);
	   				if(trnmsize < 0){
	   					error("%s:Cannot send to the socket.\n", argv[0]);
	   					exit(5);
	   				}
		   		}
	   		}

	   		
	   		if(abs(valasz - valasz1) < abs(valasz - valasz2)){
	   			sprintf(buffer,"Te nyerted ezt a  kört\n");
	   			trnmsize = send(fdc,buffer,bytes,flags);
	   			if(trnmsize < 0){
	   				error("%s:Cannot send to the socket.\n", argv[0]);
	   				exit(5);
	   			}
	   			sprintf(buffer,"Nem te nyerted ezt a kört.\n");
	   			trnmsize = send(fdc2,buffer,bytes,flags);
	   			if(trnmsize < 0){
	   				error("%s:Cannot send to the socket.\n", argv[0]);
	   				exit(5);
	   			}
	   			eredmeny1++;

	   		}else if(abs(valasz - valasz1) > abs(valasz - valasz2)){
	   			sprintf(buffer,"Nem te nyerted ezt a kört.\n");
	   			trnmsize = send(fdc,buffer,bytes,flags);
	   			if(trnmsize < 0){
	   				error("%s:Cannot send to the socket.\n", argv[0]);
	   				exit(5);
	   			}
	   			sprintf(buffer,"Te nyerted ezt a kört.\n");
	   			trnmsize = send(fdc2,buffer,bytes,flags);
	   			if(trnmsize < 0){
	   				error("%s:Cannot send to the socket.\n", argv[0]);
	   				exit(5);
	   			}
	   			eredmeny2++;

	   		}else{
	   			sprintf(buffer,"Ez a kör döntetlen.\n");
	   			trnmsize = send(fdc,buffer,bytes,flags);
	   			if(trnmsize < 0){
	   				error("%s:Cannot send to the socket.\n", argv[0]);
	   				exit(5);
	   			}
	   			trnmsize = send(fdc2,buffer,bytes,flags);
	   			if(trnmsize < 0){
	   				error("%s:Cannot send to the socket.\n", argv[0]);
	   				exit(5);
	   			}
	   		}

	   	}

	   	if(eredmeny1 > eredmeny2){
	   		sprintf(buffer, "Te nyertél. Gratulálok!\n");
	   		trnmsize = send(fdc,buffer,bytes,flags);
	   		if(trnmsize < 0){
	   			error("%s:Cannot send to the socket.\n", argv[0]);
	   			exit(5);
	   		}
	   		sprintf(buffer, "Nem te nyertél. Majd legközelebb!\n");
	   		trnmsize = send(fdc2,buffer,bytes,flags);
	   		if(trnmsize < 0){
	   			error("%s:Cannot send to the socket.\n", argv[0]);
	   			exit(5);
	   		}
	   	}else if(eredmeny1 < eredmeny2){
	   		sprintf(buffer, "Te nyertél. Gratulálok!\n");
	   		trnmsize = send(fdc2,buffer,bytes,flags);
	   		if(trnmsize < 0){
	   			error("%s:Cannot send to the socket.\n", argv[0]);
	   			exit(5);
	   		}
	   		sprintf(buffer, "Nem te nyertél. Majd legközelebb!\n");
	   		trnmsize = send(fdc,buffer,bytes,flags);
	   		if(trnmsize < 0){
	   			error("%s:Cannot send to the socket.\n", argv[0]);
	   			exit(5);
	   		}
	   	}else{
	   		sprintf(buffer, "Döntetlen.\n");
	   		trnmsize = send(fdc2,buffer,bytes,flags);
	   		if(trnmsize < 0){
	   			error("%s:Cannot send to the socket.\n", argv[0]);
	   			exit(5);
	   		}

	   		trnmsize = send(fdc,buffer,bytes,flags);
	   		if(trnmsize < 0){
	   			error("%s:Cannot send to the socket.\n", argv[0]);
	   			exit(5);
	   		}
	   	}

	   	close(fdc);
	   	close(fd);
   	}else{
		printf("1-től 15-ig adjon meg számot.\n");
		exit(6);
   	}

   	



}

























