#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>

double funkcja ( double x );

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w);

static int l_w_global=0;

static double calka_global=0.0;
static double *tab_calka_global;
static double a_global;
static double b_global; 	
static double dx_global;
static int N_global;

void* calka_fragment_petli_w(void* arg_wsk);
pthread_mutex_t mutex; 
double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w){

  int N = ceil((b-a)/dx);
  double dx_adjust = (b-a)/N;
  
  a_global = a;
  b_global = b;
  dx_global = dx_adjust;
  N_global = N;
  l_w_global = l_w;

  printf("Obliczona liczba trapezów: N = %d, dx_adjust = %lf\n", N, dx_adjust);


  
  pthread_mutex_init(&mutex, NULL);
  int index [l_w];
  for (int i=0; i < l_w; i++){
  	index [i] = i;
  }

  tab_calka_global = (double *) malloc(l_w*sizeof(double));
  
  pthread_t watki [l_w];
  for (int i=0; i<l_w ; i++){
  	pthread_create(&watki[i], NULL, calka_fragment_petli_w, (void*)(&index[i]));
  }	

  for (int i=0; i<l_w ; i++){
  	pthread_join(watki[i], NULL);
  }
  
    for (int i=0; i < l_w; i++){
  	calka_global += tab_calka_global[i];
    }
  
  return(calka_global);
}

void* calka_fragment_petli_w(void* arg_wsk){

  int my_id =*((int*)arg_wsk);

  double a = a_global, b = b_global, dx = dx_global;
  int N = N_global, l_w = l_w_global;   


  // dekompozycja cykliczna
  int my_start = my_id; //zaczynamy od nr watku 
  int my_end = N; //ilosc danych / liczba watkow
  int my_stride = l_w;
  
  int j = ceil((float)(N/l_w));
  
  if (j*l_w > N) {
  	printf("Error!");
  }
  // dekompozycja blokowa
  // int my_start = j * my_id;
  // int my_end = j * (my_id + 1);
  
  // if(my_id == l_w - 1){ 
  // 	my_end = N;
  // }
  
  // int my_stride = 0;

  int i;
  double calka = 0.0;

  for(i=my_start; i<my_end; i+=my_stride+1){

    double x1 = a + i*dx;
    calka += 0.5*dx*(funkcja(x1)+funkcja(x1+dx));
  }
  // pthread_mutex_lock(&mutex);
  // calka_global += calka;
  // pthread_mutex_unlock(&mutex);   
  tab_calka_global [my_id] = calka;   
  
}

