# prosty Makefile dla prostych programow

# nazwa pliku z kodem wykonywalnym
NAZWA = czyt_pis

# kompilator C
CC = gcc
# konsolidator (linker, loader) C
LD = gcc
# archiwizator (program do tworzenia bibliotek)
AR = ar -ru

# opcje kompilacji
#CFL = -pthread
CFL = -pthread -DMY_DEBUG

LDFL = -pthread
# katalogi z bibliotekami i dolaczane biblioteki
LIB = -L. -lm
# katalogi z plikami naglowkowymi i wklejane pliki naglowkowe 
INC = -I.

czyt_pis: czyt_pis.o czytelnia.o
	$(LD) $(LDFL) -o $(NAZWA) czyt_pis.o czytelnia.o $(LIB)

czyt_pis.o: czyt_pis.c czytelnia.h
	$(CC) $(CFL) -c czyt_pis.c $(INC)

czytelnia.o: czytelnia.c czytelnia.h
	$(CC) $(CFL) -c czytelnia.c $(INC)

clean:
	rm *.o 
