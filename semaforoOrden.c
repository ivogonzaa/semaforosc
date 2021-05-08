#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

void* printA();
void* printB();
void* printC();

char result[100] = "";
sem_t semA, semB, semC;

int main (int argc, char* args[]){
    printf("///////////////////////\n\n");

    sem_init(&semA, 0, 0);
    sem_init(&semB, 0, 1);
    sem_init(&semC, 0, 0);

    pthread_t ta, tb, tc;
    pthread_create(&ta, NULL, printA, NULL);
    pthread_create(&tb, NULL, printB, NULL);
    pthread_create(&tc, NULL, printC, NULL);

    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    pthread_join(tc, NULL);

    printf("\n///////////////////////\n");
}

void* printA(){
    int i;
    for(i = 0; i < 6; i++ ){
        sem_wait(&semA);
        strcat(result, "A");
        printf("%s\n", result);
        sem_post(&semC);
        
        sem_wait(&semA);
        strcat(result, "A");
        printf("%s\n", result);
        sem_post(&semB);
    }
}

void* printB(){
    int i;
    for(i = 0; i < 6; i++ ){
        sem_wait(&semB);
        strcat(result, "B");
        printf("%s\n", result);
        sem_post(&semA);
    }
}

void* printC(){
    int i;
    for(i = 0; i < 6; i++ ){
        sem_wait(&semC);
        strcat(result, "C");
        printf("%s\n", result);
        sem_post(&semA);
    }
}
