#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 5000
#define MAXLINE 1000
#define SA struct sockaddr

int main()
{
	char buffer[100]; //msg from server

	int sockfd, n, len;
	struct sockaddr_in servaddr, cliaddr;

	char *message = "Hello Server";

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_addr.s_addr = inet_addr("10.70.0.51");
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	// STEP1
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	// STEP2
	sendto(sockfd, message, MAXLINE, 0, (SA *)&servaddr, sizeof(servaddr));

	// STEP3
	n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (SA *)&servaddr, sizeof(servaddr));

	buffer[n] = '\0';
	printf("Message from server is : %s \n", buffer);
	getchar();

	// STEP4
	close(sockfd);
}

// Client
// socket->sendto->recvfrom->close