#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
sem_t mutex;
sem_t empty;
sem_t full;
int buf[5], f, r;
void *produce(void *param)
{
    // wait,empty wait,m areo post,m post,f
    //
    int item, i;
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        //
        printf("produced item is %d\n", i);
        buf[(++r) % 5] = i;
        sem_post(&mutex);
        sem_post(&full);
    }
}
void *consume(void *param)
{
    //
    int item, i;
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        //
        printf("consumed item is %d\n", i);
        buf[(++f) % 5] = i;
        sem_post(&mutex);
        sem_post(&empty);
    }
}
int main()
{
    pthread_t th1;
    pthread_t th2;

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 1);
    sem_init(&empty, 0, 5);

    pthread_create(&th1, NULL, produce, NULL);
    pthread_create(&th2, NULL, consume, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
}