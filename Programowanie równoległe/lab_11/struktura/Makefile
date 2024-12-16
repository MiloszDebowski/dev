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

all: struktura run 

run: struktura
	$(MPI_run) -np 6 ./struktura

# zaleznosci i komendy
struktura : struktura.o
	$(LOADER) $(OPT) struktura.o -o struktura $(LIB)

# jak uzyskac plik moj_program.o ?
struktura.o: struktura.c 
	$(CCOMP) -c $(OPT) struktura.c

clean:
	rm -f *.o struktura
