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
    }
    else
    {
    }
}