# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# zaleznosci i komendy
zad2: zad2.o 
	$(LOADER) $(OPT) zad2.o -o zad2 -lpthread $(LIB)

# jak uzyskac plik pthreads_kill_detach.o ?
zad2.o: zad2.c
	$(CCOMP) -c $(OPT) zad2.c 

clean:
	rm -f *.o zad2