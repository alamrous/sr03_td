#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <netdb.h>
#include "iniobj.h"



int main(int argc, char* argv[])
{
	struct sockaddr_in sin;
	struct hostent *hp;
	
	int sd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sd == -1)
		perror("Erreur sur socket() : ");
	hp= gethostbyname(argv[1]) ;
	bzero(&sin,sizeof(sin));
	//Adresse socket serveur 
	sin.sin_family= hp->h_addrtype;
	bcopy(hp->h_addr,&(sin.sin_addr),hp->h_length);
	sin.sin_port = htons(atoi(argv[2]));
	
	connect(sd,(struct sockaddr*)&sin,sizeof(sin));

	//char* message = argv[3];
	//printf("%s",message);
	int i = 0; 
	for (i=0; i<3; i++)
	{
		send(sd,table[i],sizeof(table[i]),0);	
	}
	//printf("%s",table[0].id);
	//send(sd,message,strlen(message),0);
	
		
return -1;	
}
