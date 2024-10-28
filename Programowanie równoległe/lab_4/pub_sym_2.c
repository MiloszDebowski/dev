#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<pthread.h>
#include<unistd.h>

#define ILE_MUSZE_WYPIC 3

void * watek_klient (void * arg);
pthread_mutex_t mutex_kufli; // Mutex do kontrolowania dostępu do kufli
pthread_mutex_t mutex_kranow; // Mutex do kontrolowania dostępu do kranów

int liczba_kufli = 0; // Liczba dostępnych kufli
int liczba_kranow = 0; // Liczba dostępnych kranów

int main(void) {
    pthread_t *tab_klient;
    int *tab_klient_id;

    int l_kl, l_kf, l_kr, i;

    pthread_mutex_init(&mutex_kufli, NULL);
    pthread_mutex_init(&mutex_kranow, NULL);

    printf("\nLiczba klientow: "); scanf("%d", &l_kl);
    printf("\nLiczba kufli: "); scanf("%d", &l_kf);
    liczba_kufli = l_kf;

    printf("\nLiczba kranow: "); scanf("%d", &l_kr);
    liczba_kranow = l_kr;

    tab_klient = (pthread_t *) malloc(l_kl * sizeof(pthread_t));
    tab_klient_id = (int *) malloc(l_kl * sizeof(int));
    for (i = 0; i < l_kl; i++) tab_klient_id[i] = i;

    printf("\nOtwieramy pub!\n");
    printf("\nLiczba wolnych kufli: %d\n", l_kf);
    printf("Liczba dostępnych kranów: %d\n", l_kr);

    for (i = 0; i < l_kl; i++) {
        pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]);
    }
    for (i = 0; i < l_kl; i++) {
        pthread_join(tab_klient[i], NULL);
    }

    printf("\nZamykamy pub!\n");

    if (liczba_kufli == l_kf) {
        printf("Liczba kufli się zgadza\n");
    } else {
        printf("Liczba kufli się nie zgadza\n");
    }
    printf("Liczba kufli: %d\n", liczba_kufli);

    pthread_mutex_destroy(&mutex_kufli);
    pthread_mutex_destroy(&mutex_kranow);
    free(tab_klient);
    free(tab_klient_id);
}

void * watek_klient(void * arg_wsk) {
    int moj_id = *((int *)arg_wsk);
    int i;
    long int wykonana_praca = 0;

    printf("\nKlient %d, wchodzę do pubu\n", moj_id);

    for (i = 0; i < ILE_MUSZE_WYPIC; i++) {
        while (1) {
            if (pthread_mutex_trylock(&mutex_kufli) == 0) {
                if (liczba_kufli > 0) {
                    liczba_kufli--;
                    printf("\nKlient %d, wybieram kufel. Liczba kufli: %d\n", moj_id, liczba_kufli);
                    pthread_mutex_unlock(&mutex_kufli);
                    break;
                }
                pthread_mutex_unlock(&mutex_kufli);
            }
            wykonana_praca++;
            usleep(100000);
        }

        while (1) {
            if (pthread_mutex_trylock(&mutex_kranow) == 0) {
                if (liczba_kranow > 0) {
                    liczba_kranow--;
                    printf("\nKlient %d, nalewam z kranu. Liczba dostępnych kranów: %d\n", moj_id, liczba_kranow);
                    pthread_mutex_unlock(&mutex_kranow);
                    usleep(30000);
                    pthread_mutex_lock(&mutex_kranow);
                    liczba_kranow++;
                    printf("\nKlient %d, zwalniam kran. Liczba dostępnych kranów: %d\n", moj_id, liczba_kranow);
                    pthread_mutex_unlock(&mutex_kranow);
                    break;
                }
                pthread_mutex_unlock(&mutex_kranow);
            }
            wykonana_praca++;
            usleep(100000);
        }

        printf("\nKlient %d, pije\n", moj_id);
        nanosleep((struct timespec[]){{0, 50000000L}}, NULL);

        pthread_mutex_lock(&mutex_kufli);
        liczba_kufli++;
        printf("\nKlient %d, odkladam kufel. Liczba kufli: %d\n", moj_id, liczba_kufli);
        pthread_mutex_unlock(&mutex_kufli);
    }

    printf("\nKlient %d, wychodzę z pubu, wykonana praca: %ld\n", moj_id, wykonana_praca);
    return NULL;
}