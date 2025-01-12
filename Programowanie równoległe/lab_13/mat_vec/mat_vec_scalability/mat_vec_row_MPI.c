#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

//#define WYMIAR 6400 
//#define ROZMIAR 40960000 

//#define WYMIAR 7936
//#define ROZMIAR 62980096
//#define WYMIAR 19200
//#define ROZMIAR 368640000

//#define WYMIAR 40320 // divisible by 128
//#define WYMIAR 20160 // divisible by 64
#define WYMIAR 10080 // divisible by 1,2,3,4,5,6,7,8,9,10,12,14,16,18,20,24,28,30,32,36,40,60
// weak scalability:    3040	4298	5265	6080	6795	7446	8043	8592
// weak scalability:    10080	14254	17457	20160	22535	24690	26663	28504

//#define WYMIAR 4800 // max possible for MPI_Alltoall on Estera
#define ROZMIAR (WYMIAR*WYMIAR)

void mat_vec(double* a, double* x, double* y, int n, int nt);

int
main ( int argc, char** argv )
{
  static double x[WYMIAR],y[WYMIAR],z[WYMIAR]; // z is sized for column decomposition
  double *a;
  double t1;
  int n,nt,i,j;
  const int ione=1;
  const double done=1.0;
  const double dzero=0.0;
  
  int rank, size, source, dest, tag=0; 
  int n_wier, n_wier_last;
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  n=WYMIAR;
  
  // x is locally initialized to zero
  for(i=0;i<WYMIAR;i++) x[i]=0.0;

  if(rank==0){  
    
    a = (double *) malloc((ROZMIAR+1)*sizeof(double));
    
    for(i=0;i<ROZMIAR;i++) a[i]=1.0*i;
    for(i=0;i<WYMIAR;i++) x[i]=1.0*(WYMIAR-i);
    
    
    mat_vec(a,x,y,n,nt);
    
  }
  
  if(size>0){
    
    /************** || block row decomposition || *******************/
    
    // z is initialized for all ranks
    for(i=0;i<WYMIAR;i++) z[i]=0.0;

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD );
    // podzial wierszowy
    n_wier = ceil(WYMIAR / size);
    n_wier_last = WYMIAR - n_wier*(size-1);
    
    // for n_wier!=n_wier_last arrays should be oversized to avoid problems
    if(n_wier!=n_wier_last){
      
      printf("This version does not work with WYMIAR not a multiple of size!\n");
      MPI_Finalize(); 
      exit(0);
      
    }

    // local matrices a_local form parts of a big matrix a
    double *a_local = (double *) malloc(WYMIAR*n_wier*sizeof(double)); 
    for(i=0;i<WYMIAR*n_wier;i++) a_local[i]=0.0;
    

    MPI_Scatter( a, n_wier*WYMIAR, MPI_DOUBLE, a_local, n_wier*WYMIAR, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Bcast(x, WYMIAR, MPI_DOUBLE, 0, MPI_COMM_WORLD );


    if(rank==0) {
      printf("Starting MPI matrix-vector product with block row decomposition!\n");
      t1 = MPI_Wtime();
    }
    
    // local parts of x start at rank*n_wier
    MPI_Allgather(&x[rank*n_wier], n_wier, MPI_DOUBLE, x, n_wier, MPI_DOUBLE, MPI_COMM_WORLD );
    
    
    for(i=0;i<n_wier;i++){
            
      double t=0.0;
      int ni = n*i;
      
      for(j=0;j<n;j++){
	t+=a_local[ni+j]*x[j];
	//if(i==1){
	//  printf("rank %d: row %d, column %d, a %lf, x %lf, current y %lf\n", 
	//         rank, i, j, a_local[ni+j], x[j], t);
	//}
      }
      //printf("rank %d: row %d, final y %lf\n", rank, i, t);
      z[i]=t;
    }
    
    // just to measure time
    MPI_Barrier(MPI_COMM_WORLD);        
    if(rank==0) {
      t1 = MPI_Wtime() - t1;
      printf("Werja rownolegla MPI z dekompozycją wierszową blokową\n");
      printf("\tczas wykonania: %lf, Gflop/s: %lf, GB/s> %lf\n",  
	     t1, 2.0e-9*ROZMIAR/t1, (1.0+1.0/n)*8.0e-9*ROZMIAR/t1);
      
    }
    
    MPI_Gather( z, n_wier, MPI_DOUBLE, z, n_wier, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    
    if(rank==0){
      
      for(i=0;i<WYMIAR;i++){
	if(fabs(y[i]-z[i])>1.e-9*z[i]) {
	  printf("Blad! i=%d, y[i]=%lf, z[i]=%lf\n",i, y[i], z[i]);
	}
      }
      
    }  

    // the end if size > 1
  }


  MPI_Finalize(); 
  
  return(0);
  
  
}


void mat_vec(double* a, double* x, double* y, int nn, int nt)
{
  

   register int k=0;
   register int n=nn;
   register int i;
   register int j;
  for(i=0;i<n;i+=2){
    register double ty1 = 0;
    register double ty2 = 0;
   for(j=0;j<n;j+=2){
      register double t0=x[j];
      register double t1=x[j+1];
      k= i*n+j;
      ty1  +=a[k]*t0    +a[k+1]*t1 ;
      ty2  +=a[k+n]*t0  +a[k+1+n]*t1;
    }
      y[i]  = ty1;
      y[i+1]+=ty2;
  }
}
