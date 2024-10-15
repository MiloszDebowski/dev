#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

int zmienna_wspolna=0;

#define WYMIAR 1000
#define ROZMIAR WYMIAR*WYMIAR
double a[ROZMIAR],b[ROZMIAR],c[ROZMIAR];


double czasozajmowacz(){
  int i, j, k;
  int n=WYMIAR;
  for(i=0;i<ROZMIAR;i++) a[i]=1.0*i;
  for(i=0;i<ROZMIAR;i++) b[i]=1.0*(ROZMIAR-i);
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      c[i+n*j]=0.0;
      for(k=0;k<n;k++){
	c[i+n*j] += a[i+n*k]*b[k+n*j];
      }
    }
  }
  return(c[ROZMIAR-1]);
}

void * zadanie_watku (void * arg_wsk)
{
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	printf("\twatek potomny: uniemozliwione zabicie\n");

	czasozajmowacz();

	printf("\twatek potomny: umozliwienie zabicia\n");
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

	pthread_testcancel();

	zmienna_wspolna++;
	printf("\twatek potomny: zmiana wartosci zmiennej wspolnej\n");

	return(NULL);
}

int main()
{
	pthread_t tid;
	pthread_attr_t attr;
	void *wynik;
	int i;

	//Wątek przyłączalny
	
	printf("watek glowny: tworzenie watku potomnego nr 1\n");

	/*Tu wstaw kod tworzenia wątku z domyślnymi własnościami*/
	 pthread_create(&tid, NULL, zadanie_watku, NULL);//dopisane


	sleep(2); // czas na uruchomienie watku

	printf("\twatek glowny: wyslanie sygnalu zabicia watku\n");
	pthread_cancel(tid);

	//Co nalezy zrobić przed sprawdzeniem czy wątki się skonczyły?
	pthread_join(tid, &wynik);//dopisane
	if (wynik == PTHREAD_CANCELED)
		printf("\twatek glowny: watek potomny zostal zabity\n");
	else
		printf("\twatek glowny: watek potomny NIE zostal zabity - blad\n");

	//Odłączanie wątku

	zmienna_wspolna = 0;

	printf("watek glowny: tworzenie watku potomnego nr 2\n");

	/*Tu wstaw kod tworzenia wątku z domyślnymi własnościami*/
 	pthread_create(&tid, NULL, zadanie_watku, NULL);//dopisane
	sleep(2); // czas na uruchomienie watku

	printf("\twatek glowny: odlaczenie watku potomnego\n");
	//Instrukcja odłączenia?
	pthread_detach(tid);//dopisane
	printf("\twatek glowny: wyslanie sygnalu zabicia watku odlaczonego\n");
	pthread_cancel(tid);

	//Czy watek został zabity? Jak to sprawdzić?
	printf("\twatek glowny: czy watek potomny zostal zabity \n");//całe dopisane
 	printf("\twatek glowny: sprawdzanie wartosci zmiennej wspolnej\n");
 	for(i=0;i<10;i++)
	{
 		sleep(1);
 		if(zmienna_wspolna!=0) break;
 	}
 	if (zmienna_wspolna==0) printf("\twatek glowny: odlaczony watek potomny PRAWDOPODOBNIE zostal zabity\n");
 	else printf("\twatek glowny: odlaczony watek potomny PRAWDOPODOBNIE NIE zostal zabity\n");
	//Wątek odłączony
	 
	 
	//Inicjacja atrybutów?
	pthread_attr_init(&attr);//dopisane
	//Ustawianie typu watku na odłaczony
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);//dopisane
	printf("watek glowny: tworzenie odlaczonego watku potomnego nr 3\n");
	pthread_create(&tid, &attr, zadanie_watku, NULL);

	//Niszczenie atrybutów
	pthread_attr_destroy(&attr);//dopisane

	printf("\twatek glowny: koniec pracy, watek odlaczony pracuje dalej\n");
	pthread_exit(NULL); // co stanie sie gdy uzyjemy exit(0)?
}


