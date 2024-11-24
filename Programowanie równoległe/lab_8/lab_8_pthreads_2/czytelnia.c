#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"



pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // pilnuje zeby watki miedzy soba modyfikowaly prawidlowo dane w czytelnii + te globalne
pthread_mutex_t lock_czytelnicy = PTHREAD_MUTEX_INITIALIZER; //mutexy do obslugi wait i signal
pthread_mutex_t lock_pisarze = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_czytelnicy = PTHREAD_COND_INITIALIZER; //obsluga wait i signal
pthread_cond_t cond_pisarze = PTHREAD_COND_INITIALIZER;
int l_c_czekajacych = 0;
int l_p_czekajacych = 0;
int my_read_lock_lock(czytelnia_t* czytelnia_p){
	pthread_mutex_lock (&lock);
  	if(czytelnia_p->l_p > 0 || l_p_czekajacych > 0){
  		l_c_czekajacych++;
  		pthread_mutex_unlock(&lock);
  		pthread_mutex_lock(&lock_czytelnicy);
  		pthread_cond_wait(&cond_czytelnicy, &lock_czytelnicy);
  		pthread_mutex_unlock(&lock_czytelnicy);
  		pthread_mutex_lock(&lock);
  		l_c_czekajacych--;
  	}
  	czytelnia_p->l_c++;
  	pthread_cond_signal (&cond_czytelnicy);
	pthread_mutex_unlock (&lock);
}

int my_read_lock_unlock(czytelnia_t* czytelnia_p){
   	pthread_mutex_lock (&lock);
   	czytelnia_p->l_c--;
	if(czytelnia_p->l_c ==0){
		pthread_cond_signal(&cond_pisarze);
	}
   	pthread_mutex_unlock (&lock);
}

int my_write_lock_lock(czytelnia_t* czytelnia_p){
  	pthread_mutex_lock (&lock);
  	if(czytelnia_p->l_c + czytelnia_p->l_p > 0) {
  		l_p_czekajacych++;
  		pthread_mutex_unlock (&lock);
  		pthread_mutex_lock(&lock_pisarze);
  		pthread_cond_wait(&cond_pisarze, &lock_pisarze);
  		pthread_mutex_unlock(&lock_pisarze);
  		pthread_mutex_lock(&lock);
  		l_p_czekajacych--;
  	}
  	czytelnia_p->l_p++;
  	pthread_mutex_unlock (&lock);
}

int my_write_lock_unlock(czytelnia_t* czytelnia_p){
    	pthread_mutex_lock (&lock);
    	czytelnia_p->l_p--;
    	if(l_c_czekajacych > 0){
    		pthread_cond_signal(&cond_czytelnicy);
    	}
    	else {
    		pthread_cond_signal(&cond_pisarze);
    	}
    	pthread_mutex_unlock (&lock);
}

void inicjuj(czytelnia_t* czytelnia_p){
	czytelnia_p->l_p = 0;
	czytelnia_p->l_c = 0;
	
}

void czytam(czytelnia_t* czytelnia_p){
#ifdef MY_DEBUG

// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy

// sprawdzenie warunku poprawności i ewentualny exit
	pthread_mutex_lock (&lock);
	printf("liczba czytelnikow = %d, liczba pisarzy = %d\n", czytelnia_p->l_c, czytelnia_p->l_p); 
	if(czytelnia_p->l_p>1 || (czytelnia_p->l_p==1 && czytelnia_p->l_c>0) || czytelnia_p->l_p<0 || czytelnia_p->l_c<0 ) { 
	printf("Nie powinienem czytac\n"); 
	pthread_mutex_unlock (&lock);
	exit(0); 
	}
	pthread_mutex_unlock (&lock);
#endif
    usleep(rand()%300000);
}

void pisze(czytelnia_t* czytelnia_p){
#ifdef MY_DEBUG
// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy

// sprawdzenie warunku poprawności i ewentualny exit
	pthread_mutex_lock (&lock);
	printf("liczba czytelnikow = %d, liczba pisarzy = %d\n", czytelnia_p->l_c, czytelnia_p->l_p); 
	if( czytelnia_p->l_p>1 || (czytelnia_p->l_p==1 && czytelnia_p->l_c>0) || czytelnia_p->l_p<0 || czytelnia_p->l_c<0 ) { 
	printf("Nie powinienem pisac\n"); 
	pthread_mutex_unlock (&lock);
	exit(0); 
	}
	pthread_mutex_unlock (&lock);
	
#endif
    usleep(rand()%300000);
}


