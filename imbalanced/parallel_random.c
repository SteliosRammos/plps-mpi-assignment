#include <stdio.h>
#include "mpi.h"
#include "../test_mpi.h"

int N;
int R;
int r_local = 0;
int r_global = 0; 
double start, finish;

int main(int argc, char *argv[]) {
	// Initialize the MPI environment
	MPI_Init(NULL, NULL);
	
	// Get the number of processes
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	
	// Get the rank of the process
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
	// Start timer
	start=MPI_Wtime();

	// Stop timer
	finish=MPI_Wtime();
	MPI_Finalize();
	printf("Parallel Elapsed time: %f seconds\n", finish-start); 
	return 0;
}