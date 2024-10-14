#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include"pomiar_czasu/pomiar_czasu.h"

int zmienna_globalna=0;

int main(){
  
  int pid, wynik, i;

  inicjuj_czas();
  
  for(i=0;i<10000;i++){
    
    pid = fork(); 			
    
    if(pid==0){ 			
      
      zmienna_globalna++;

      // char arg1[] = "/bin/ls";
      // char arg2[] = ".";
      // char* arg[] = {arg1,arg2,NULL};
      // char* arg[] = {"/bin/ls",".",NULL};
      // wynik=execv("/bin/ls",arg); 
      // wynik=execv("./program",NULL); 
      // if(wynik==-1)
      //      printf("Proces potomny nie wykonal programu\n");

      exit(0);
      
    } else {					
      
      wait(NULL);
      
    }
    
  }

  drukuj_czas();
  
}

  
