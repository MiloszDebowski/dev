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

all: oblicz_PI

run: oblicz_PI
	$(MPI_run) -np 6 ./oblicz_PI

# zaleznosci i komendy
oblicz_PI : oblicz_PI.o
	$(LOADER) $(OPT) oblicz_PI.o -o oblicz_PI $(LIB)

# jak uzyskac plik moj_program.o ?
oblicz_PI.o: oblicz_PI.c
	$(CCOMP) -c $(OPT) oblicz_PI.c

clean:
	rm -f *.o oblicz_PI
