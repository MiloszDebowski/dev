#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

extern void bariera_init(int);
extern void bariera(void);

#define LICZBA_W 4
//#define LICZBA_W 44

pthread_t watki[LICZBA_W];

void *cokolwiek( void *arg);

int main( int argc, char *argv[] ){

  int i, indeksy[LICZBA_W]; for(i=0;i<LICZBA_W;i++) indeksy[i]=i; 

  // use of pthread_once (once_control, init_routine) ?
  // int pthread_once(pthread_once_t *once_control, void (*init_routine)(void));
  // but init_routine has no arguments...
  bariera_init(LICZBA_W);

  for(i=0; i<LICZBA_W; i++ ) {
    pthread_create( &watki[i], NULL, cokolwiek, (void *) &indeksy[i] );
  }

  for(i=0; i<LICZBA_W; i++ ) pthread_join( watki[i], NULL );

  pthread_exit( NULL);  
}


void *cokolwiek( void *arg){

  int i, moj_id;

  moj_id = *( (int *) arg ); 

  printf("przed bariera 1 - watek %d\n",moj_id);

  bariera();

    printf("przed bariera 2 - watek %d\n",moj_id);

  bariera();

  printf("przed bariera 3 - watek %d\n",moj_id);

  bariera();

  printf("przed bariera 4 - watek %d\n",moj_id);

  bariera();

  printf("po ostatniej barierze - watek %d\n",moj_id);  

  pthread_exit( (void *)0);
}
