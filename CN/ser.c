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
    char buff[100];
    int sockfd, nd;
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(sockfd, (SA *)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    listen(sockfd, 5);
    len = sizeof(cliaddr);
    int n;
    while (1)
    {
        int nd;

        if (fork() == 0)
        {
            close(sockfd);
            accept(nd, (SA *)&cliaddr, sizeof(cliaddr));
            n = read(sockfd, buff, sizeof(buff));
            printf("client says : %s", buff);
            getchar();
        }
        close(nd);
    }
}