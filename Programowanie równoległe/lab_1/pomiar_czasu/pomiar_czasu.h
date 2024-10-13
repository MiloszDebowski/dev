/******************************************************************************
Plik pomiar_czasu.h - interfejs procedur pomiaru czasu dla roznych systemow 
                      operacyjnych

Procedury wykorzystujace funkcje standardowe C:
  czas_C - zwraca czas CPU w sekundach od rozpoczecia dzialania lub -1 jesli
           funkcja clock() nie jest prawidlowo zaimplementowana w systemie 

Procedury UNIX-owe:
  inicjuj_czas   - inicjacja pomiaru czasu
  czas_zegara    - zwrocenie czasu zegarowego od momentu inicjacji
  czas_CPU       - zwrocenie czasu CPU od momentu inicjacji
  drukuj_czas    - pomiar i wydruk czasu CPU i zegarowego od momentu inicjacji

Sposob uzycia:
  zgodnie z interfejsem w niniejszym pliku

------------------------------  			
Historia:
      02.2002 - Krzysztof Banas, kbanas@pk.edu.pl
******************************************************************************/

#ifndef _pomiar_czasu_
#define _pomiar_czasu_


/*---------------------------------------------------------
  inicjuj_czas - inicjuje pomiar czasu 
---------------------------------------------------------*/
void inicjuj_czas();


/*---------------------------------------------------------
  czas_C - zwraca czas CPU w sekundach od rozpoczecia dzialania lub -1 jesli
           funkcja clock() nie jest prawidlowo zaimplementowana w systemie 
---------------------------------------------------------*/
double czas_C();

/*---------------------------------------------------------
  czas_zegara - procedura zwraca czas zegarowy w sekundach od momentu
                inicjacji (jako liczbe podwojnej precyzji) 
---------------------------------------------------------*/
double czas_zegara();

/*---------------------------------------------------------
  czas_CPU - procedura zwraca czas CPU w sekundach od momentu
             inicjacji (jako liczbe podwojnej precyzji) 
 ---------------------------------------------------------*/
double czas_CPU();

/*---------------------------------------------------------
  drukuj_czas - pomiar i wydruk czasu standardowego C, CPU i zegarowego 
               w sekundach od momentu inicjacji pomiaru czasu
 ---------------------------------------------------------*/
void drukuj_czas();


#endif
