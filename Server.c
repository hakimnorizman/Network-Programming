#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
	{
		int sockfd, newsockfd, portno;
		socklen_t clilen;
		char buffer[255];
		struct sockaddr_in serv_addr, cli_addr;
		int n;

		if (argc < 2)
		{
			fprintf(stderr, "ERROR!, no port provided\n");
			exit(1);
		}

		sockfd = socket(AF_INET, SOCK_STREAM, 0);//INET is for IP address, SOCK is for TCP

		if (sockfd < 0)
 			error("ERROR in opening socket!\n");

		bzero((char *) &serv_addr, sizeof(serv_addr));//to clear the server address

		portno = atoi(argv[1]);//use atoi to convert char into int, and store in portno

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(portno);//convert int to network format

		if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
			error("ERROR in binding!\n");

		listen(sockfd,5);//5 clients only can bind, this is the listen method to listen to clients
		clilen = sizeof(cli_addr);

		newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen); //to accept the connection from the client

		if (newsockfd < 0)
			error("ERROR on accept!\n");

		while(1) //loop for connection of client
		{
			bzero(buffer,255);

			n = read(newsockfd,buffer,255); //read the message from the client
			if (n < 0)
			   error("ERROR reading from socket!\n");

			printf("Someone say: %s \n",buffer); //display the message from the client by passing value of the string

			bzero(buffer,255); 
			fgets(buffer,255,stdin);
			
			n = write(newsockfd,buffer,strlen(buffer)); //to send message back to client

			if (n < 0)
				error("ERROR writing to socket!\n");

			int i = strncmp("See you next time!\n", buffer, 18);

			if(i == 0)
				break;
		}
		close(newsockfd);
		close(sockfd);
		return 0;

	}
