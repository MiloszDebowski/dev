#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

int main(int argc, char *argv[]) {
    int rank, size, max_liczba_wyrazow = 0;
    double local_sum_plus = 0.0, local_sum_minus = 0.0;
    double global_sum_plus = 0.0, global_sum_minus = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Podaj maksymalną liczbę wyrazów do obliczenia przybliżenia PI\n");
        scanf("%d", &max_liczba_wyrazow);
    }

    MPI_Bcast(&max_liczba_wyrazow, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int my_start = (max_liczba_wyrazow / size) * rank;
    int my_end;
    if (rank == size - 1) {
        my_end = max_liczba_wyrazow;
    } else {
        my_end = (max_liczba_wyrazow / size) * (rank + 1);
    }

    for (int i = my_start; i < my_end; i++) {
        int j = 1 + 4 * i;
        local_sum_plus += 1.0 / j;
        local_sum_minus += 1.0 / (j + 2.0);
    }

    MPI_Reduce(&local_sum_plus, &global_sum_plus, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_sum_minus, &global_sum_minus, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double pi_approx = 4 * (global_sum_plus - global_sum_minus);
        printf("PI obliczone: \t\t\t%20.15lf\n", pi_approx);
        printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
    }

    MPI_Finalize();
}
