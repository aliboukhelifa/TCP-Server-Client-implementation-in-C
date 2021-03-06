// Mise en oeuvre du client à partir de la phase d'écoute du server
// Ensemble des bibliothèques (Headers) nécessaires pour la mise en oeuvre du programme 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<ctype.h>

// Définir un port de communication Client-Server
// de préférence qu'il soit déclaré en variable globale (ne change pas dans le programme)
// comme la valeur pi en trigonomitrie pi = 3.14
#define PORT 4444

int main(){

		// Phase déclarative
		// Déclaration et initialisation de la socket côté CLIENT
		int clientSocket;
		// Décrire la structure du client
		struct sockaddr_in serverAddr; 
		// Initialisation d'un Buffer
		char buffer[1024];
		// Créer la socket côté Client
		clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		printf("[+] Client Socket Created Successfully\n");
		
		
		// Phase de Paramétrage
		// Consiste à définir les différents paramètre de la communication que doit contenir la socket "sockfd"
		// ANYDDR_ANY : Any adress du réseau Server
		// Port de communication "PORT" faire appel à la fonction htons
	
		// Il se trouve des fois qu'il faille initialiser la structure du server (idem pour celle du client)
		// appel d'une fonction "memset" pour juste des précautions à prendre
		memset(&serverAddr, '\0', sizeof(serverAddr));
		
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(PORT); // conversion en octets
		serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // adresse du server
		
		// Etablissement de la connexion à partir du client
		// une fois le 3 handshack est approuvé
		// Faire appel à la fonction "connect()"
		connect(clientSocket , (struct sockaddr *)&serverAddr , sizeof(serverAddr));
		printf("[+] Client Connected to Server Successfully\n");
		
		// Phase de communication Client_Server
		// Comme on est dans le mode TCP, les fonctions utilisées pour écrire et lire 
		// dans les buffer sont : "read()" et "write()"
	
		// si le client souhaite envoyer un message, il doit l'écrire
		// sur la mémoire tampon "Buffer"
		
		printf("\n Entrer un entier pour que le Server calcul la factorielle: \n");
		
		// Chaine de type pointeur, taille, flot de données pointe vers le fichier
		fgets(buffer, 1024, stdin);
		// Ecrire le message en spécifiant le nombre d'octets dans le buffer "write()"
		
		int monNombre = atoi(buffer);
		// printf("Buffer : %s", buffer);
		
		//printf("Mon nombre au en int au carré : %d", monNombre*monNombre);
		write(clientSocket, buffer, strlen(buffer));
		
		// Le client va faire appel à la fonction de lecture "read()"
		read(clientSocket, buffer, 1024);
		printf("\n (Server) message : %s\n",buffer);
		int n;
		char msg[1024];
		int servLen = sizeof(serverAddr);

		n = recvfrom(clientSocket,msg,1024,0,(struct sockaddr *)&serverAddr , &servLen);
		printf("Fichier lu : %s\n", msg);
		FILE* fichierRecu = NULL;
		fichierRecu = fopen("factRecu.txt","w+");
		fprintf(fichierRecu,"%s",msg);
		fclose(fichierRecu);

	printf("[+]OK.\n");
	printf("[+]SEE YOU\n");


	return 0;

}