#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#define PORT 5555
#define SA struct sockaddr

struct Person{
	int age;
	char name[100];
};

// CLIENT IN TCP
// socket , connect , close

int main()
{
	int sockfd, len, n;
	struct sockaddr_in seraddr, cliaddr;

	struct Person p,temp;

	//Create socket 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd==-1){
		printf("No socket created.\n");
		exit(0);
	}
	else{
		printf("Socket created!\n");
	}

	// Assignment
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = inet_addr("172.16.57.36");
	seraddr.sin_port = htons(PORT);

	len = sizeof(seraddr);

	// Establishing connection.
	int connfd;
	connfd=connect(sockfd, (SA*)&seraddr, len);

	if(connfd<0){
		printf("No connection.\n");
		exit(0);
	}
	else{
		printf("Connected!\n");
	}


	printf("Enter name of person: ");
	scanf("%s", (p.name));

	printf("Enter age of person: ");
	scanf("%d", &(p.age));

	printf("Values are being read properly in client :\n");
	printf("Name of person: %s\n",p.name);
	printf("Age of person: %d \n",p.age);

	// Send structure to server = p

	n = write(sockfd, &p, sizeof(struct Person));

	//Receive structure from server = temp
	n = read(sockfd, &temp, sizeof(struct Person));

	printf("\nPerson Details received from server: ");

	printf("Name of person: %s\n",temp.name);
	printf("Age of person: %d \n",temp.age);

	getchar();

	// close(sockfd);	
}