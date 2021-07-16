#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#define Maxproducer 2
#define Maxconsumer 4
#define cons 2
#define prod 4
#define BufferSize 4
sem_t empty,full,mutex;
int in = 0,out = 0;
int buffer[BufferSize];
void *producer(void *pno)
{
    for(int i = 0; i < prod; i++) {
        sem_wait(&empty);//Waits if the buffer is full
        sem_wait(&mutex);
        buffer[in] = rand();// Produce an random item
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno),buffer[in],in);
        in = (in+1)%BufferSize;
        sem_post(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *cno)
{
    for(int i = 0; i < cons; i++)
        {
        sem_wait(&full);//Waits if buffer is empty
        sem_wait(&mutex);
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n",*((int *)cno),item, out);
        out = (out+1)%BufferSize;
        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main()
{
    system("clear");
    printf("SEMAPHORE\n\n");
    pthread_t pro[2],con[4];
    sem_init(&mutex, 0,1);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);
    int a[4] = {1,2,3,4};
    printf("In this case,\n There are 4 producers and each producer can produce 2 items\n There are 2 consumers and each consumer can consume 4 items\n\n\n");
    for(int i = 0; i < Maxproducer; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < Maxconsumer; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }
    for(int i = 0; i < Maxproducer; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i=0;i< Maxconsumer;i++){
        pthread_join(con[i],NULL);
    }

    sem_destroy(&mutex);//Destroy
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}