#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAXLINE 1000
#define PORT 5000
#define SA struct sockaddr

int main()
{
    char buff[100];
    char *msg = "Hi client";
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bind(sockfd, (SA *)&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int n;
    n = recvfrom(sockfd, buff, sizeof(buff), 0, (SA *)&cliaddr, sizeof(cliaddr));

    buff[n] = '\n';
    printf("recvfrom client:");
    puts(buff);

    sendto(sockfd, msg, MAXLINE, 0, (SA *)&cliaddr, sizeof(cliaddr));

    getchar();
    close(sockfd);
}
