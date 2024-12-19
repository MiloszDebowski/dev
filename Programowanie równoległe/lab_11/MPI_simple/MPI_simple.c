#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include<unistd.h>
#include "mpi.h"

int main( int argc, char** argv ){ 
  
  int rank, ranksent, size, source, dest, tag, i; 
  MPI_Status status;
  
  MPI_Init( &argc, &argv ); 
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );
 
  if(size>1){
    
    if( rank != 0 ){ dest=0; tag=0; 
       char hostname[100];
       gethostname(hostname, 100);
      MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
      MPI_Send( &hostname, 100, MPI_CHAR, dest, tag+1, MPI_COMM_WORLD);
    } else {
      char receive_hostname[100];
      for( i=1; i<size; i++ ) { 
	MPI_Recv( &ranksent, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status );
	MPI_Recv( &receive_hostname, 100, MPI_CHAR, i, 1, MPI_COMM_WORLD, &status );
	printf("Dane od procesu o randze (status.MPI_SOURCE ->) %d: %d (i=%d) otrzymany hostname: %s\n", status.MPI_SOURCE, ranksent, i, receive_hostname );
      }
      
    }

  }
  else{
	printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  
  MPI_Finalize(); 
  
  return(0);

}

