#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>

sem_t semA, semB, mutex;


void* printA();
void* printB();


int main (int argc, char* args[]){
    printf("\n////////////////////\n");

    sem_init(&semA, 0, 1);
    sem_init(&mutex, 0, 1);
    sem_init(&semB, 0, 0);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, printA, NULL);
    pthread_create(&t2, NULL, printB, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\n////////////////////\n");
}

void* printA(){
    sem_wait(&semA);
    sem_wait(&mutex);
    printf("A");
    sem_post(&mutex);
    sem_post(&semB);
}

void* printB() {
    sem_wait(&mutex);
    sem_wait(&semB);
    printf("B");
    sem_post(&mutex);
    sem_post(&semA);
}