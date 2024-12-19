# kompilator c
CCOMP = /usr/bin/mpicc

# konsolidator
LOADER = /usr/bin/mpicc

# program uruchomieniowy MPI
MPI_run = /usr/bin/mpiexec -oversubscribe

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

all: MPI_simple run 


#zmiana liczby procesów
run: MPI_simple
	$(MPI_run) -np 6 ./MPI_simple

# zaleznosci i komendy
MPI_simple : MPI_simple.o
	$(LOADER) $(OPT) MPI_simple.o -o MPI_simple $(LIB)

# jak uzyskac plik moj_program.o ?
MPI_simple.o: MPI_simple.c 
	$(CCOMP) -c $(OPT) MPI_simple.c

clean:
	rm -f *.o MPI_simple 
