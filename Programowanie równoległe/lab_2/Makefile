# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
#OPT = -g -DDEBUG -O0
# wersja zoptymalizowana do mierzenia czasu
 OPT = -O3
all: fork clone program
# pliki naglowkowe
INC = -Ipomiar_czasu

# biblioteki
LIB = -Lpomiar_czasu -lpomiar_czasu -lm

# zaleznosci i komendy
fork: fork.o 
	$(LOADER) $(OPT) fork.o -o fork $(LIB)

# jak uzyskac plik fork.o ?
fork.o: fork.c pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) fork.c $(INC) 

# zaleznosci i komendy
clone: clone.o 
	$(LOADER) $(OPT) clone.o -o clone $(LIB)

# jak uzyskac plik clone.o ?
clone.o: clone.c pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) clone.c $(INC) 

#program
program: program.o
	$(LOADER) $(OPT) program.o -o program $(LIB)

program.o: program.c pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) program.c $(INC)

clean:
	rm -f *.o fork clone program
#fork to procesy
#clone to wątki



