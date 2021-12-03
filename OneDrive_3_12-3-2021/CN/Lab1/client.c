#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 5004
#define MAXLINE 1000

int main()
{
	char buffer[100];
	char *message="Hello from client";
	int listenfd, len,n;
	struct sockaddr_in servaddr,cliaddr;

	servaddr.sin_port=htons(PORT);
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	sendto(listenfd,message,sizeof(message),0,(struct sockaddr*)&servaddr, len);
	len=sizeof(cliaddr);
	n=recvfrom(listenfd,buffer,sizeof(buffer),0,(struct sockaddr*)&servaddr,&len);

	buffer[n]='\0';
	puts(buffer);

	printf("The hello message is sent to server\n");
	close(listenfd);

	return 0;
}