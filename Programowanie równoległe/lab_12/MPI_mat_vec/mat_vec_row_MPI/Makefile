# kompilator c
CCOMP = /usr/bin/mpicc

# konsolidator
LOADER = /usr/bin/mpicc

MPIRUN = /usr/bin/mpiexec 

# opcje optymalizacji:
# wersja do debugowania
# OPT = -g -DDEBUG -p
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3 -fopenmp -p
OPT = -O2 -fopenmp
#OPT = -O0 

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lpomiar_czasu
LIB =  -lm
#LIB = -L/opt/intel//mkl/8.1/lib/em64t -lmkl_em64t
#LIB = -L/opt/intel//mkl/8.1/lib/32 -lmkl_ia32
#LIB = -L/opt/intel/mkl/10.1.0.015/lib/em64t/ -lmkl -liomp5 -lpthread

# zaleznosci i komendy
all: mat_vec_row_MPI run

#mat_vec_row_MPI: mat_vec_row_MPI.o mat_vec.o pomiar_czasu.o
#	$(LOADER) $(OPT) mat_vec_row_MPI.o mat_vec.o pomiar_czasu.o -o mat_vec_row_MPI $(LIB)
mat_vec_row_MPI: mat_vec_row_MPI.o
	$(LOADER) $(OPT) mat_vec_row_MPI.o -o mat_vec_row_MPI $(LIB)

#mat_vec_row_MPI.o: mat_vec_row_MPI.c pomiar_czasu.h
mat_vec_row_MPI.o: mat_vec_row_MPI.c
	$(CCOMP) -c $(OPT) mat_vec_row_MPI.c $(INC)

#mat_vec.o: mat_vec.c
#	$(CCOMP) -c $(OPT) mat_vec.c

#pomiar_czasu.o: pomiar_czasu.c pomiar_czasu.h
#	$(CCOMP) -c $(OPT) pomiar_czasu.c

run:
	$(MPIRUN) -np 4 --oversubscribe  ./mat_vec_row_MPI

clean:
	rm -f *.o ./mat_vec_row_MPI
