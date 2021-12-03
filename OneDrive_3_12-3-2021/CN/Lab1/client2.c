#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 5004
#define MAXLINE 1000

int main()
{
	int sd,nd,n,len,result;
	struct sockaddr_in seraddress, cliaddress;
	char buf[256],buf1[256];

	sd=socket(AF_INET,SOCK_STREAM,0);

	seraddress.sin_port=htons(PORT);
	seraddress.sin_family=AF_INET;
	seraddress.sin_addr.s_addr=inet_addr("127.0.0.1");

	len=sizeof(seraddress);
	connect(sd,(struct sockaddr*)&seraddress,len);
	printf("Connected to server...");
	printf("Enter message to send to server");

	scanf("%s",buf);
	printf(" \n Message sent to server");
	
	n=write(sd,buf,strlen(buf));
	getchar();
	close(nd);
	close(sd);
}