#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

// pthread_mutex_t mutex;
sem_t semaphore;

int cnt = 0;

void *routine(void *param)
{
    int idx = param;
    printf("Thread %d : ", idx);
    for (int i = 0; i < 20; i++)
    {
        // pthread_mutex_lock(&mutex);
        sem_wait(&semaphore);
        cnt++;
        printf("count = %d\n", cnt);
        // pthread_mutex_unlock(&mutex);
    }
}
void *routine2(void *param)
{
    int idx = param;
    printf("Thready %d : ", idx);
    for (int i = 0; i < 20; i++)
    {
        // pthread_mutex_lock(&mutex);

        cnt++;
        printf("count = %d\n", cnt);
        sem_post(&semaphore);
        // pthread_mutex_unlock(&mutex);
    }
}
int main()
{
    pthread_t threads[2];
    // pthread_mutex_init(&mutex, 0);
    sem_init(&semaphore, 0, 1);

    pthread_create(&threads[0], 0, &routine, 0);

    pthread_create(&threads[1], 0, &routine2, 1);

    pthread_join(threads[0], NULL);

    pthread_join(threads[1], NULL);

    // pthread_mutex_destroy(&mutex);
    sem_destroy(&semaphore);
}
