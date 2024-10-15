#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREADS_MAX 4

void* zadanie_watku(void* arg_wsk) {
    int moj_arg = *((int*)arg_wsk);
    pthread_t x = pthread_self();
    printf("SYSTEM ID: %d & SELF ID = %ld\n", moj_arg, x);
    return NULL;
}

int main() {
    pthread_t threads[THREADS_MAX];
    int index[THREADS_MAX];
    int p = THREADS_MAX;

    for (int i = 0; i < p; i++) {
        index[i] = i;
    }

    for (int i = 0; i < p; i++) {
        pthread_create(&threads[i], NULL, zadanie_watku, (void*)&index[i]);
    }
    for (int i = 0; i < p; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_exit(NULL);
}




