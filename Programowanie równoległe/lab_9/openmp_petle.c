#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

void tablica(double a[WYMIAR][WYMIAR]) {
    for (int i = 0; i < WYMIAR; i++) {
        for (int j = 0; j < WYMIAR; j++) {
            a[i][j] = 1.02 * i + 1.01 * j;
        }
    }
}

double suma_sekwencyjnie(double a[WYMIAR][WYMIAR]) {
    double suma = 0.0;
    for (int i = 0; i < WYMIAR; i++) {
        for (int j = 0; j < WYMIAR; j++) {
            suma += a[i][j];
        }
    }
    return suma;
}

double suma_rownolegle_wiersze(double a[WYMIAR][WYMIAR]) {
    double suma = 0.0;
    #pragma omp parallel for default(none) schedule(static, 2) reduction(+:suma) shared(a)
    for (int i = 0; i < WYMIAR; i++) {
        for (int j = 0; j < WYMIAR; j++) {
            suma += a[i][j];
            printf("(%1d,%1d) -> W_%1d ", i, j, omp_get_thread_num());
        }
        printf("\n");
    }
    return suma;
}

double suma_rownolegle_kolumny_wew(double a[WYMIAR][WYMIAR]) {
    double suma = 0.0;
    for (int i = 0; i < WYMIAR; i++) {
        #pragma omp parallel for default(none) schedule(dynamic) reduction(+:suma) shared(a, i)
        for (int j = 0; j < WYMIAR; j++) {
            suma += a[i][j];
            printf("(%1d,%1d) -> W_%1d ", i, j, omp_get_thread_num());
        }
        printf("\n");
    }
    return suma;
}

double suma_rownolegle_kolumny_zew(double a[WYMIAR][WYMIAR]) {
    double suma = 0.0;
    #pragma omp parallel default(none) shared(a, suma)
    {
        double suma_tmp = 0.0;
        #pragma omp for schedule(static)
        for (int j = 0; j < WYMIAR; j++) {
            for (int i = 0; i < WYMIAR; i++) {
                suma_tmp += a[i][j];
                printf("(%1d,%1d) -> W_%1d ", i, j, omp_get_thread_num());
            }
            printf("\n");
        }
        #pragma omp critical
        suma += suma_tmp;
    }
    return suma;
}

int main() {
    omp_set_num_threads(3);
    double a[WYMIAR][WYMIAR];

    
    tablica(a);

    // Sekwencyjne obliczanie sumy
    double suma = suma_sekwencyjnie(a);
    printf("Suma wyrazów tablicy (sekwencyjnie): %lf\n", suma);

    // Dekompozycja wierszowa schedule static, rozmiar porcji=2
    double suma_rownolegle_wiersze_wynik = suma_rownolegle_wiersze(a);
    printf("Suma (wierszowa): %lf\n", suma_rownolegle_wiersze_wynik);

    // Dekompozycja kolumnowa - zrównoleglenie pętli wewnętrznej schedule dynamic, rozmiar porcji domyślny
    double suma_rownolegle_kolumny_wew_wynik = suma_rownolegle_kolumny_wew(a);
    printf("Suma (kolumnowa - wewnętrzna): %lf\n", suma_rownolegle_kolumny_wew_wynik);

    // Dekompozycja kolumnowa - zrównoleglenie pętli zewnętrznej
    double suma_rownolegle_kolumny_zew_wynik = suma_rownolegle_kolumny_zew(a);
    printf("Suma (kolumnowa - zewnętrzna): %lf\n", suma_rownolegle_kolumny_zew_wynik);

    return 0;
}
