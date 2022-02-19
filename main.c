#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_NUM 3

static int waterCreations = 0, waterStall = 0;
int hydrogen = 0, oxygen = 0;

pthread_mutex_t mutex;

_Noreturn void* hydrogenProducer(){
    while(1){
        pthread_mutex_lock(&mutex);
        if(hydrogen < 2){
            //printf("Creating hydrogen...\n");
            hydrogen++;
        }else{
            //printf("Hydrogen waiting...\n");
        }
        pthread_mutex_unlock(&mutex);
    }
}

_Noreturn void* oxygenProducer(){
    while(1) {
        pthread_mutex_lock(&mutex);
        if (oxygen < 1 && hydrogen == 2) {
            //printf("Creating oxygen...\n");
            oxygen++;
        } else {
            //printf("Oxygen waiting...\n");
        }
        pthread_mutex_unlock(&mutex);
    }
}

_Noreturn void* waterCreation(){
    while(1) {
        pthread_mutex_lock(&mutex);
        if (hydrogen == 2 && oxygen == 1) {
            hydrogen = 0;
            oxygen = 0;
            waterCreations++;
            printf("Water has been created!\n");
            printf("Total water particles: %d\n\n", waterCreations);
        } else {
            waterStall++;
            printf("Water waiting to be created...\n");
            printf("Stall counter: %d\n\n", waterStall);
        }
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutex, NULL);
    int iterator;

    if(pthread_create(th ,NULL ,&hydrogenProducer ,NULL ) != 0 ){
        perror("Thread could not be created\n");
    }
    if(pthread_create(th + 1 ,NULL ,&oxygenProducer ,NULL ) != 0 ){
        perror("Thread could not be created\n");
    }
    if(pthread_create(th + 2 ,NULL ,&waterCreation ,NULL ) != 0 ){
        perror("Thread could not be created\n");
    }

    for(iterator = 0; iterator < THREAD_NUM; iterator++){
        if(pthread_join(th[iterator], NULL) != 0){
            perror("Thread could not be started\n");
        }
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
