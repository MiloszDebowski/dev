#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"



pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/*** Implementacja procedur interfejsu ***/


int my_read_lock_lock(czytelnia_t* czytelnia_p){
	pthread_mutex_lock (&lock);
  	czytelnia_p->l_c++;
	pthread_mutex_unlock (&lock);
}

int my_read_lock_unlock(czytelnia_t* czytelnia_p){
   	pthread_mutex_lock (&lock);
   	czytelnia_p->l_c--;
   	pthread_mutex_unlock (&lock);
}

int my_write_lock_lock(czytelnia_t* czytelnia_p){
  	pthread_mutex_lock (&lock);
  	czytelnia_p->l_p++;
  	pthread_mutex_unlock (&lock);
}

int my_write_lock_unlock(czytelnia_t* czytelnia_p){
    	pthread_mutex_lock (&lock);
    	czytelnia_p->l_p--;
    	pthread_mutex_unlock (&lock);
}

void inicjuj(czytelnia_t* czytelnia_p){
	czytelnia_p->l_p = 0;
	czytelnia_p->l_c = 0;
	
}

void czytam(czytelnia_t* czytelnia_p){
#ifdef MY_DEBUG
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


