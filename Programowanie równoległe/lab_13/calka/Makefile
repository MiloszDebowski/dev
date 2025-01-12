# Makefile for compiling calka_omp.c with OpenMP support in two steps

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -O3 -fopenmp

# Target executable
TARGET = calka_omp

# Object file
OBJ = calka_omp.o

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): calka_omp.c
	$(CC) $(CFLAGS) -c calka_omp.c -o $(OBJ)

# Clean up
clean:
	rm -f $(TARGET) $(OBJ)
