#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <netdb.h>
#include "defobj.h"
#define SO_MAXCONN 5

int main(int argc, char* argv[])
{
	struct sockaddr_in sin;

	int sd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sd == -1)
	{
		perror("Erreur de socket :");
		exit(-1);
	}
else 
{
	bzero(&sin,sizeof(sin));
	sin.sin_family= AF_INET;
	sin.sin_port = htons(atoi(argv[1]));

	 int b = bind(sd,(const struct sockaddr*)&sin,sizeof(sin));
	if(b == -1)
	{
		perror("Erreur de bind() :");
		exit(-1);
	}
	
	while(1)
	{
		int l = listen(sd,SO_MAXCONN);
	if(l == -1)
	{
		perror("Erreur de listen :");
		exit(-1);
	}
	
	int newsd = accept(sd,0,0);
	if(newsd == -1)
	{
		perror("Erreur de socket :");
		exit(-1);
	}
	pid_t pid = fork();
	
		if(pid == -1)
		{
			perror("fork :");
			exit(-1);
		}
		else if(pid == 0)//pere	
		{
			waitpid();
		}
		else
		{
			void* objet;
			int* taille;			
			size_t rec =recv(newsd,objet,taille,0);
			struct obj* convert = (struct obj*) objet;
			printf("quelque chose j'ai recu !\n");
			printf("%s\n",&(convert->id));
		}
	}			
}
	
}
