#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Zmienne statyczne
static int ilosc_watkow = 0;                // Liczba wątków
static int ilosc_watkow_w_funkcji = 0;      // Liczba wątków na barierze
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

// Inicjalizacja bariery
void bariera_init(int n) {
    ilosc_watkow = n;
}

// Funkcja bariery
void bariera() {
    pthread_mutex_lock(&lock); // Sekcja krytyczna

    ilosc_watkow_w_funkcji++;

    if (ilosc_watkow_w_funkcji == ilosc_watkow) {
        // Ostatni wątek resetuje licznik i budzi pozostałe
        ilosc_watkow_w_funkcji = 0;
        pthread_cond_broadcast(&condition);
    } else {
        // Wątki oczekują na zmienną warunkową
        pthread_cond_wait(&condition, &lock);
    }

    pthread_mutex_unlock(&lock); // Wyjście z sekcji krytycznej
}
