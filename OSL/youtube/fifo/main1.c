#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
    int arr[9];
    int fd = open("sum", O_RDONLY);
    if (fd == -1)
    {
        printf("cant read");
        exit(0);
    }
    int i;
    int sum = 0;
    for (i = 0; i < 9; i++)
    {
        if (read(fd, &arr[i], sizeof(int)) == -1)
        {
            printf("oops cant read");
            exit(0);
        }
        sum += arr[i];
        printf("Read %d\n", arr[i]);
    }
    printf("sum=%d\n", sum);
    return 0;
}