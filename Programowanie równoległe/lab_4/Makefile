LOADER = gcc
OPT = -g -DDEBUG

CCOMP = gcc

pub_sym_1: pub_sym_1.o
	$(LOADER) $(OPT) pub_sym_1.o -o pub_sym_1

pub_sym_1.o: pub_sym_1.c
	$(CCOMP) -c $(OPT) pub_sym_1.c

clean:
	rm -f *.o pub_sym_1