#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;
int cnt = 0;

void *routine(void *param)
{
    int idx = param;
    printf("Thread %d : ", idx);
    for (int i = 0; i < 20; i++)
    {
        pthread_mutex_lock(&mutex);
        cnt++;
        printf("count = %d\n", cnt);
        pthread_mutex_unlock(&mutex);
    }
}
int main()
{
    pthread_t threads[10];
    pthread_mutex_init(&mutex, 0);
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&threads[i], 0, &routine, (void *)i);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
}
