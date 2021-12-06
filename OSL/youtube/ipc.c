#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        printf("cannot open file\n");
        exit(0);
    }
    int id = fork();
    if (id == 0)
    {
        close(fd[0]);
        int x;
        printf("Input number:\n");
        scanf("%d", &x);
        if (write(fd[1], &x, sizeof(int)) == -1)
        {
            printf("err in writing\n");
            exit(0);
        }
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1)
        {
            printf("err in reading\n");
            exit(0);
        }
        close(fd[0]);
        printf("Got from child process %d", y);
    }
}