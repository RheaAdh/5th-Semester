#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    FILE *fptr;
    int status = 0;
    int n;
    printf("enter n:\n");
    scanf("%d", &n);
    int pid = fork();
    if (pid == -1)
    {
        printf("err\n");
    }
    else if (pid == 0)
    {
        fptr = fopen("sum.txt", "w+");
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            sum += i;
        }
        fwrite(&sum, sizeof(int), 1, fptr);
        fclose(fptr);
    }
    else
    {
        wait(&status);
        fptr = fopen("sum.txt", "r");
        int sum = 0;
        fread(&sum, sizeof(int), 1, fptr);
        printf("%d\n", sum);
        fclose(fptr);
    }
    exit(0);
}