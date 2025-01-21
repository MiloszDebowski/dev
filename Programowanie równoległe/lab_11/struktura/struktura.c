#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include "mpi.h"

struct My_struct {
	char name[10];
	int age;
	int points;
};

int main( int argc, char** argv ){ 
  
  int rank, ranksent, size, source, dest, tag; 
  MPI_Status status;
  MPI_Init( &argc, &argv ); 
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );  
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  int size_struct; 
  int packet_size; 
  int position = 0;
  MPI_Pack_size(10, MPI_CHAR, MPI_COMM_WORLD, &size_struct);
  packet_size = size_struct;
  MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &size_struct);
  packet_size += size_struct;
  MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &size_struct);
  packet_size += size_struct;
  void* bufor = (void* ) malloc(packet_size);
  if(size>1){
    if(rank == 0){
      tag = 0; dest = 1;
      struct My_struct value = {"Paweł", 37, 0};
      MPI_Pack(&value.name[0], 6, MPI_CHAR, bufor, packet_size, &position, MPI_COMM_WORLD);
      MPI_Pack(&value.age, 1, MPI_INT, bufor, packet_size, &position, MPI_COMM_WORLD);
      MPI_Pack(&value.points, 1, MPI_INT, bufor, packet_size, &position, MPI_COMM_WORLD);
      MPI_Send (&rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
      MPI_Send (bufor, position, MPI_PACKED, dest, tag+1, MPI_COMM_WORLD);
    }
    else{
      int prev = rank - 1;
      int next = rank + 1;
      MPI_Recv (&ranksent, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
      MPI_Recv (bufor, 32, MPI_PACKED, prev, 1, MPI_COMM_WORLD, &status);
      struct My_struct value;
      MPI_Unpack (bufor, 32, &position, &value.name, 6, MPI_CHAR, MPI_COMM_WORLD);
      MPI_Unpack (bufor, 32, &position, &value.age, 1, MPI_INT, MPI_COMM_WORLD);
      MPI_Unpack (bufor, 32, &position, &value.points, 1, MPI_INT, MPI_COMM_WORLD);
      printf("proces %d, odebrał imie: %s, wiek: %d, ilosc punktow: %d od procesu %d \n",  rank, value.name, value.age, value.points, ranksent);
      if(rank < size - 1) {
        position = 0;
        value.points++;
        MPI_Pack(&value.name[0], 6, MPI_CHAR, bufor, packet_size, &position, MPI_COMM_WORLD);
        MPI_Pack(&value.age, 1, MPI_INT, bufor, packet_size, &position, MPI_COMM_WORLD);
        MPI_Pack(&value.points, 1, MPI_INT, bufor, packet_size, &position, MPI_COMM_WORLD);
        MPI_Send(&rank, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        MPI_Send(bufor, position, MPI_PACKED, next, 1, MPI_COMM_WORLD);		
      }
    }
  }
  else{
	printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }
  MPI_Finalize(); 
  return(0);
}

