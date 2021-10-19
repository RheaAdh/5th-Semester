#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 5000
#define MAXLINE 1000
//server
int main()
{
    char buffer[100];
    int arr[50];
    int servsockfd, len, n;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    //UDP socket
    servsockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;
    //bind server
    bind(servsockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Server Running\n");
    //receive the datagram
    len = sizeof(cliaddr);
    n = recvfrom(servsockfd, arr, sizeof(arr), 0, (struct sockaddr *)&cliaddr, &len);
    //puts(buffer);
    int counter = 0;
    int x, y;
    printf("Enter row and column\n");
    scanf("%d %d", &x, &y);
    printf("The array is: \n");
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            printf("%d ", arr[counter]);
            counter++;
        }
        printf("\n");
    }
    printf("\n");
    //buffer = "printed elements\n";
    //echoing back
    sendto(servsockfd, buffer, n, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    getchar();
    //close the descriptor
    close(servsockfd);
}