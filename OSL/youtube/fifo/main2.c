#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int fd = open("sum", O_WRONLY);
    if (fd == -1)
    {
        printf("cant open");
        exit(0);
    }
    for (int i = 0; i < 9; i++)
    {
        if (write(fd, &arr[i], sizeof(int)) == -1)
        {
            printf("cant write");
            exit(0);
        }
        printf("Wrote %d\n", arr[i]);
    }
    close(fd);
    return 0;
}