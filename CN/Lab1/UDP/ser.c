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
	char buffer[100]; //msg from client
	int sockfd, len, n;
	struct sockaddr_in servaddr, cliaddr;

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	// STEP1
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	// STEP2
	bind(sockfd, (SA *)&servaddr, sizeof(servaddr));

	// STEP3
	n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (SA *)&cliaddr, sizeof(cliaddr));

	buffer[n] = '\0';
	puts(buffer);

	// STEP4
	sendto(sockfd, msg, sizeof(msg), 0, (SA *)&cliaddr, sizeof(cliaddr));
	getchar();

	// STEP5
	close(sockfd);
}

// Server
// socket->bind->recvfrom->sendto->close
