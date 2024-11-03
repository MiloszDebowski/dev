# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
#OPT = -O3 -fopenmp

# pliki naglowkowe
INC = -I./include

# biblioteki
#LIB = -L../pomiar_czasu -lpomiar_czasu -lm -lpthread
LIB = -L./lib -lpomiar_czasu -lm -lpthread

# zaleznosci i komendy
pthreads_suma: pthreads_suma.o 
	$(LOADER) $(OPT) pthreads_suma.o -o pthreads_suma $(LIB)

# jak uzyskac plik pthreads_suma.o 
pthreads_suma.o: pthreads_suma.c include/pomiar_czasu.h
	$(CCOMP) -c $(OPT) pthreads_suma.c $(INC) 

clean:
	rm -f *.o pthreads_suma
