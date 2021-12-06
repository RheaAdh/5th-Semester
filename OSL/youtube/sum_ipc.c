#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int arrSize = sizeof(arr) / sizeof(int);
    int start, end;
    int fd[2];
    if (pipe(fd) == -1)
    {
        printf("cannot open file\n");
        exit(0);
    }
    int id = fork();
    if (id == 0)
    {
        start = 0;
        end = arrSize / 2;
    }
    else
    {
        start = arrSize / 2;
        end = arrSize;
    }

    int sum = 0;

    for (int i = start; i < end; i++)
    {
        sum += arr[i];
    }
    if (id == 0)
    {
        close(fd[0]);
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);
    }
    else
    {
        int sumfrmchild = 0;
        close(fd[1]);
        read(fd[0], &sumfrmchild, sizeof(sumfrmchild));
        close(fd[0]);

        int totsum = sum + sumfrmchild;
        printf("totsum=%d\n", totsum);
        wait(NULL);
    }
}