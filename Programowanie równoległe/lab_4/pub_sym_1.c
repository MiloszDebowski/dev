#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<pthread.h>
#include <unistd.h>

#define ILE_MUSZE_WYPIC 3

void * watek_klient (void * arg);
pthread_mutex_t mutex;
int liczba_kufli = 0;

int main( void ){

  pthread_t *tab_klient;
  int *tab_klient_id;

  int l_kl, l_kf, l_kr, i;

  pthread_mutex_init(&mutex, NULL);

  printf("\nLiczba klientow: "); scanf("%d", &l_kl);

  printf("\nLiczba kufli: "); scanf("%d", &l_kf);
  liczba_kufli = l_kf;

  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++) tab_klient_id[i]=i;

  printf("\nOtwieramy pub (simple)!\n");
  printf("\nLiczba wolnych kufli %d\n", l_kf); 

  for(i=0;i<l_kl;i++){
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]); 
  }
  for(i=0;i<l_kl;i++){
    pthread_join( tab_klient[i], NULL);
  }

  printf("\nZamykamy pub!\n");
  if(liczba_kufli==l_kf) printf("Liczba kufli się zgadza\n");
  else printf("Liczba kufli się nie zgadza\n");
  printf("Liczba kufli: %d\n", liczba_kufli);

  pthread_mutex_destroy(&mutex);
}


void * watek_klient (void * arg_wsk){
  
  int moj_id = * ((int *)arg_wsk);

  int i, j;
  int ile_musze_wypic = ILE_MUSZE_WYPIC;

  printf("\nKlient %d, wchodzę do pubu\n", moj_id); 
    
  for(i=0; i<ile_musze_wypic; i++){
    pthread_mutex_lock(&mutex);
    while (liczba_kufli <= 0) {
        printf("Klient %d, Brak wolnych kufli. Czekam\n", moj_id);
        pthread_mutex_unlock(&mutex);
        usleep(100000); //klient czeka przed ponownym sprawdzeniem czy jest kufel
        //usleep(1);
        pthread_mutex_lock(&mutex);
    }
    liczba_kufli--;//klient bierze kufel
    printf("\nKlient %d, wybieram kufel. Liczba pozostałych kufli: %d\n", moj_id, liczba_kufli);
    pthread_mutex_unlock(&mutex);

    
    j = 0;
    printf("\nKlient %d, nalewam z kranu %d\n", moj_id, j); 
    usleep(10000);//czas na nalanie piwa 
    
    //klient pije piwo
    printf("\nKlient %d, pije\n", moj_id); 
    nanosleep((struct timespec[]){{0, 50000000L}}, NULL);

    //klient odklada piwo
    pthread_mutex_lock(&mutex);
    liczba_kufli++;
    printf("\nKlient %d, odkladam kufel. Liczba dostępnych kufli: %d\n", moj_id, liczba_kufli);
    pthread_mutex_unlock(&mutex);
  }

  printf("\nKlient %d, wychodzę z pubu\n", moj_id); 
    
  return(NULL);
}
