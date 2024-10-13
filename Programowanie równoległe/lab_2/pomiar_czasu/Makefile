# kompilator c
CCOMP = gcc

# konsolidator (linker)
LiNKER = gcc

# archiwizator bibliotek
AR = ar -rs

#
# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm

# zaleznosci i komendy
pomiar_czasu: pomiar_czasu.o pomiar_czasu.h
	$(AR) libpomiar_czasu.a pomiar_czasu.o


pomiar_czasu.o: pomiar_czasu.c pomiar_czasu.h
	$(CCOMP) -c $(OPT) pomiar_czasu.c

clean:
	rm -f *.o
