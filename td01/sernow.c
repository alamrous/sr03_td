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
	            struct obj objet;
	            size_t rec;
    pid_t ppid;
//Creation de la socket
	int sd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sd == -1)
	{
		perror("Erreur de socket :");
		exit(-1);
	}

	//initialisation de la structure de la socket
	bzero(&sin,sizeof(sin));
	sin.sin_family= AF_INET;
	sin.sin_port = htons(atoi(argv[1]));
//bind de la socket avec la structure de socket
	 int b = bind(sd,(const struct sockaddr*)&sin,sizeof(sin));
	if(b == -1)
	{
		perror("Erreur de bind() :");
		exit(-1);
	}

	while(1)
	{
    //On met la socket en attente de connexion
    int l = listen(sd,SO_MAXCONN);

	if(l == -1)
	{
		perror("Erreur de listen :");
		exit(-1);
	}
    //On accepte la connexion
	int newsd = accept(sd,0,0);
	if(newsd == -1)
	{
		perror("Erreur de socket :");
		exit(-1);
	}
	//On crée un processus fils
	pid_t pid = fork();
    //On fait un switch sur la valeur du fork
    switch((int)pid)
    {
    //Cas où on est dans le fils
    case 0:
			 rec =recv(newsd,&objet,sizeof(objet),0);
			while(rec != 0){
			if(rec==-1)
				{
					printf("Erreur recv");
					exit( -1);
				}
			else
				{

						printf("quelque chose j'ai recu !\n");
						printf("%s \n",objet.id);
					rec =recv(newsd,&objet,sizeof(objet),0);

				}

                }
                break;
   //cas de problème de fork
    case -1:
    	perror("fork :");
			exit(-1);
			break;
    //on est dans le pere
    default :
    newsd =accept(sd,0,0);
		if(newsd==-1)
		{
		printf("ERREUR accept");
		exit( -1);
		}
	ppid = fork();
    break;


    }



	}


}

