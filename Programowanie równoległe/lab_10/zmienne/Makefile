# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG  -fopenmp
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
INC =

# biblioteki
LIB = -lm

# zaleznosci i komendy
openmp_watki_zmienne: openmp_watki_zmienne.o 
	$(LOADER) $(OPT) openmp_watki_zmienne.o -o openmp_watki_zmienne $(LIB)

# jak uzyskac plik openmp_watki_zmienne.o ?
openmp_watki_zmienne.o: openmp_watki_zmienne.c
	$(CCOMP) -c $(OPT) openmp_watki_zmienne.c $(INC) 

clean:
	rm -f *.o
