#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

//pthread_mutex_t even_lock, odd_lock;
sem_t even_lock,odd_lock;
void *evenFunc(void *args)
{
    int index = 0;
    while(index < 10)
    {
        //pthread_mutex_lock(&even_lock);
        sem_wait(&even_lock);
        sleep(random()%3);
        printf("%d\n ",index );
        index +=2;
        sem_post(&odd_lock);
        //pthread_mutex_unlock(&odd_lock);
    }
    pthread_exit(0);
}

void *oddFunc(void *args)
{
    int index = 1;
    while(index < 10)
    {
        //pthread_mutex_lock(&odd_lock);
        sem_wait(&odd_lock);
        sleep(random()%4);
        printf("%d\n ",index );
        index +=2;
        sem_post(&even_lock);
        //pthread_mutex_unlock(&even_lock);
    }
    pthread_exit(0);
}

int main()
{
    pthread_t evenThread;
    pthread_t oddThread;
    int ret1 = 0;
    int ret2 = 0;

    //pthread_mutex_init(&even_lock,NULL);
    //pthread_mutex_init(&odd_lock,NULL);
    sem_init(&even_lock,0,1);
    sem_init(&odd_lock,0,0);

    ret1 = pthread_create(&evenThread,NULL,evenFunc,NULL);
    if(ret1 != 0)
    {
        perror("Thread Even Creation Failed\n");
        exit(1);
    }
    ret2 = pthread_create(&oddThread,NULL,oddFunc,NULL);
    if(ret2 !=0)
    {
        perror("Thread odd Creation Failed\n");
        exit(1);
    }
    pthread_join(evenThread,NULL);
    pthread_join(oddThread,NULL);


    sem_destroy(&even_lock);
    sem_destroy(&odd_lock);
   // pthread_mutex_destroy(&even_lock);
   // pthread_mutex_destroy(&odd_lock);
    return 0;
}
