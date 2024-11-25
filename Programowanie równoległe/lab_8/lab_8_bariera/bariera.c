#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Zmienne statyczne
static int ilosc_watkow = 0;
static int ilosc_watkow_w_funkcji = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

// Inicjalizacja bariery
void bariera_init(int n) {
    ilosc_watkow = n;
}

// Funkcja bariery
void bariera() {
    pthread_mutex_lock(&lock);

    ilosc_watkow_w_funkcji++;

    if (ilosc_watkow_w_funkcji == ilosc_watkow) {
        ilosc_watkow_w_funkcji = 0;
        pthread_cond_broadcast(&condition);
    } else {
        pthread_cond_wait(&condition, &lock);
    }

    pthread_mutex_unlock(&lock);
}
