# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
#OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
OPT = -O3 -Wno-unused-result

# pliki naglowkowe
INC = -I./include -I.

# biblioteki
LIB = -L./lib -L. -L../pomiar_czasu -lpomiar_czasu -lm -lpthread

# zaleznosci i komendy


all: clean obliczanie_calki

obliczanie_calki: obliczanie_calki.o dekompozycja_petli.o dekompozycja_obszaru.o
	$(LOADER) $(OPT) obliczanie_calki.o dekompozycja_petli.o dekompozycja_obszaru.o -o obliczanie_calki $(LIB)

obliczanie_calki.o: obliczanie_calki.c 
	$(CCOMP) -c $(OPT) obliczanie_calki.c $(INC) 

dekompozycja_petli.o: dekompozycja_petli.c 
	$(CCOMP) -c $(OPT) dekompozycja_petli.c $(INC) 

dekompozycja_obszaru.o: dekompozycja_obszaru.c
	$(CCOMP) -c $(OPT) dekompozycja_obszaru.c $(INC) 
clean:
	rm -f *.o obliczanie_calki
