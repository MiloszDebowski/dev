# kompilator c
CCOMP = mpicc
#CCOMP = mpicc
# konsolidator
LOADER = mpicc
#LOADER = mpicc
# program uruchomieniowy MPI
MPI_run = mpiexec -oversubscribe

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm
LIB = -lm

all: sztafeta run 

run: sztafeta
	$(MPI_run) -np 6 ./sztafeta

# zaleznosci i komendy
sztafeta : sztafeta.o
	$(LOADER) $(OPT) sztafeta.o -o sztafeta $(LIB)

# jak uzyskac plik moj_program.o ?
sztafeta.o: sztafeta.c 
	$(CCOMP) -c $(OPT) sztafeta.c

clean:
	rm -f *.o sztafeta
