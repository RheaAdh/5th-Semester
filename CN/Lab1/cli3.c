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
int main()
{
    char buffer[100];
    //char *message = "Hello Server";
    int sockfd, n, len;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;
    printf("Enter num\n");
    int num;
    scanf("%d", &num);
    int arr[10];
    printf("Enter array elements\n");
    for (int i = 0; i < num; i++)
    {
        scanf("%d", &arr[i]);
    }
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    sendto(sockfd, arr, MAXLINE, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
    len = sizeof(cliaddr);
    // waiting for response
    n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';
    printf("message fromseris %s \n", buffer);
    getchar();
    close(sockfd);
}