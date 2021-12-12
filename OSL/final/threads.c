#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <pthread.h>
void *evensum(void *param)
{
    printf("hibye");
    int *arr = (int *)param;
    int sum = 0;
    for (int i = 0; i <= 6; i++)
    {
        if (arr[i] % 2 == 0)
            sum += arr[i];
    }
    return (void *)sum;
}
void *oddsum(void *param)
{
    int *arr = (int *)param;
    int sum = 0;
    for (int i = 0; i <= 6; i++)
    {
        printf("hi");
        if (arr[i] % 2 != 0)
            sum += arr[i];
    }
    return (void *)sum;
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = 7;
    pthread_t th1, th2;

    pthread_create(&th1, 0, &oddsum, (void *)arr);
    pthread_create(&th2, 0, &evensum, (void *)arr);
    int evensum = 0;
    int oddsum = 0;
    pthread_join(th1, (void **)&oddsum);
    pthread_join(th2, (void **)&evensum);

    printf("even sum =%d\n oddsum= %d \n", evensum, oddsum);
}