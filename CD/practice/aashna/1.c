#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>
#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 1000

int main(int argc, char *argv[])

{
    int pipe_fd2;
    int res;
    int open_mode = O_WRONLY;
    int n = 0;
    char buffer[BUFFER_SIZE + 1];
    if (access(FIFO_NAME, F_OK) == -1)
    {
        res = mkfifo(FIFO_NAME, 0777);

        if (res != 0)
        {
            fprintf(stderr, "Could not create file %s\n", FIFO_NAME);

            exit(EXIT_FAILURE);
        }
    }

    printf("Process %d opening FIFO write only\n", getpid());

    pipe_fd2 = open(FIFO_NAME, open_mode);

    printf(pipe_fd2);

    printf("Process %d result %d\n", getpid(), pipe_fd2);

    if (pipe_fd2 != -1)
    {

        printf("Enter 4 Numbers: \n");
        while (n < 4)
        {

            scanf("%s", buffer);
            res = write(pipe_fd2, buffer, BUFFER_SIZE);
            if (res == -1)
            {
                fprintf(stderr, "Write Error on Pipe.\n");

                exit(EXIT_FAILURE);
            }

            n++;
        }

        (void)close(pipe_fd2);
    }
    else
    {
        printf("failing");
        exit(EXIT_FAILURE);
    }
    printf("Process %d Finished.\n", getpid());

    exit(EXIT_SUCCESS);

    return 0;
}