#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREADS_COUNT 6

void* zadanie_watku(void* arg_wsk) {

    int moj_arg = *((int*)arg_wsk);
    
    printf("SYSTEM ID: %d & SELF ID = %ld\n", moj_arg, pthread_self());

    return NULL;
}

int main() {
    pthread_t threads[THREADS_COUNT];
    int index[THREADS_COUNT];

    for (int i = 0; i < THREADS_COUNT; i++) {
        index[i] = i;
        pthread_create(&threads[i], NULL, zadanie_watku, (void*)&index[i]);
    }

    for (int i = 0; i < THREADS_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_exit(NULL);
}




