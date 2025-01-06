#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SCALAR double
//#define SCALAR float

#ifndef M_PI // standardy C99 i C11 nie wymagają definiowania stałej M_PI
#define M_PI (3.14159265358979323846)
#endif

int main( void ){ // program obliczania przybliżenia PI za pomocą wzoru Leibniza
                  // PI = 4 * ( 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + itd. )
  
  int max_liczba_wyrazow=0;

  printf("Podaj maksymalną liczbę wyrazów do obliczenia przybliżenia PI\n");
  scanf("%d", &max_liczba_wyrazow);
  //  double t = MPI_Wtime();

 // wzór: PI/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 itd. itp.  
  SCALAR suma_plus=0.0;
  SCALAR suma_minus=0.0;
  int i=0;
  for(i=0; i<max_liczba_wyrazow; i++){  
    int j = 1 + 4*i; 
    suma_plus += 1.0/j;
    suma_minus += 1.0/(j+2.0);
    //printf("PI obliczone: %20.15lf, aktualna poprawka: %20.15lf\n",
    //  	 4*(suma_plus-suma_minus), 4.0/j-4.0/(j+2.0));
  }
  double pi_approx = 4*(suma_plus-suma_minus);

  //  t = MPI_Wtime() - t;
  printf("PI obliczone: \t\t\t%20.15lf\n", pi_approx);
  printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
  //  printf("Czas obliczeń: %lf\n", t);
  
}


