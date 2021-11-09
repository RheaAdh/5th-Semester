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
#define SA struct sockaddr
#define PORT 5000

int main()
{
    char buff[100], buff1[100];
    int sockfd, nd;
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    len = sizeof(servaddr);
    connect(sockfd, (SA *)&servaddr, sizeof(servaddr));
    int n, n1;
    printf("enter string");
    gets(buff);
    n = write(sockfd, buff, sizeof(buff));
    n1 = read(sockfd, buff1, sizeof(buff));
    printf("msg from server is %s", buff1);
    getchar();
}