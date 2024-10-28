LOADER = gcc
OPT = -g -DDEBUG

CCOMP = gcc

target: pub_sym_1 pub_sym_2

pub_sym_1: pub_sym_1.o
	$(LOADER) $(OPT) pub_sym_1.o -o pub_sym_1

pub_sym_1.o: pub_sym_1.c
	$(CCOMP) -c $(OPT) pub_sym_1.c

pub_sym_2: pub_sym_2.o
	$(LOADER) $(OPT) pub_sym_2.o -o pub_sym_2

pub_sym_2.o: pub_sym_2.c
	$(CCOMP) -c $(OPT) pub_sym_2.c

clean:
	rm -f *.o pub_sym_1 pub_sym_2