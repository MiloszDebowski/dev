CCOMP = /usr/bin/mpicc
LOADER = $(CCOMP)
MPIRUN = /usr/bin/mpiexec --use-hwthread-cpus -display-map --bind-to core --map-by socket 
OPT = -O3
LIB =  -lm
all: mat_vec_row_MPI run

mat_vec_row_MPI: mat_vec_row_MPI.o
	$(LOADER) $(OPT) mat_vec_row_MPI.o -o mat_vec_row_MPI $(LIB)

mat_vec_row_MPI.o: mat_vec_row_MPI.c
	$(CCOMP) -c $(OPT) mat_vec_row_MPI.c $(INC)

run:
	$(MPIRUN) -np 12  ./mat_vec_row_MPI

clean:
	rm -f *.o ./mat_vec_row_MPI
