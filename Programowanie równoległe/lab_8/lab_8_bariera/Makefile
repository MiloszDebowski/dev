
CC = gcc

LD = gcc

OPT = -O3

INC = 

LIB = -pthread

main: main.o bariera.o
	$(LD) $(OPT) -o main main.o bariera.o $(LIB)

main.o: main.c
	$(CC) -c $(OPT) main.c $(INC)

bariera.o: bariera.c
	$(CC) -c $(OPT) bariera.c $(INC)

clean:
	rm -f *.o main
