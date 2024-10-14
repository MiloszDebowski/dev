#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include "pomiar_czasu/pomiar_czasu.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{

   int zmienna_lokalna = *(int *)argument;
    for(int i = 0; i < 1e+8; i++){
        zmienna_globalna++;
        zmienna_lokalna++;
    }

    printf("Wewnatrz funkcji:\n");
    printf("Zmienna globalna: %d\n",zmienna_globalna);
    printf("Zmienna lokalna: %d\n",zmienna_lokalna);
  /* int wynik; */
  /* wynik=execv("./program",NULL); */
  /* if(wynik==-1) */
  /*   printf("Proces potomny nie wykonal programu\n"); */

  return 0;
}

int main()
{

  void *stos,*stos1;
  pid_t pid,pid1;
  int i; 
  int zmienna_lokalna = 0;
  //inicjuj_czas();
  stos = malloc( ROZMIAR_STOSU );
  stos1 = malloc( ROZMIAR_STOSU );
  if (stos == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }

//   for(i=0;i<10000;i++){

//     pid = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU, 
// 		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );

//     waitpid(pid, NULL, __WCLONE);

//   }
pid = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU,CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &zmienna_lokalna );
pid1 = clone( &funkcja_watku, (void *) stos1+ROZMIAR_STOSU, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &zmienna_lokalna );
waitpid(pid, NULL, __WCLONE);
waitpid(pid1, NULL, __WCLONE);

  //drukuj_czas();
  printf("Zmienna globalna: %d\n",zmienna_globalna);
  printf("Zmienna lokalna: %d\n",zmienna_lokalna);
  free( stos );
  free(stos1);
}
