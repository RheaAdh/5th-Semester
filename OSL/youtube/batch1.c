#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // FILE *fptr;
    int fp;
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
        // fptr = fopen("sum.txt", "w+");
        fp = open("sum.txt", O_WRONLY);
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            sum += i;
        }
        // fwrite(&sum, sizeof(int), 1, fptr);
        // fclose(fptr);
        write(fp, &sum, sizeof(int));
        close(fp);
    }
    else
    {
        wait(&status);
        // fptr = fopen("sum.txt", "r");
        fp = open("sum.txt", O_RDONLY);
        int sum = 0;
        // fread(&sum, sizeof(int), 1, fptr);
        read(fp, &sum, sizeof(int));
        printf("%d\n", sum);
        close(fp);
        // fclose(fptr);
    }

    exit(0);
}