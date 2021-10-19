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
	
	// The array fill should be done only by one process (say rank 0)
	// That process should then broadcast to all the others
	int *A;
	
	int bucketSize = (int)(N / world_size);
	int batchSize = (int)((R / world_size)+1); // num of iterations before syncing local r's
	
	if (world_rank == 0) {
		A = allocate_mem(N);
		fill_random(A, N);
		
		for (int procNum = 1; procNum < world_size; procNum ++) {
			MPI_Send(A, N, MPI_INT, procNum, 0, MPI_COMM_WORLD);
		}
	} else {
		A = allocate_mem(N);
		MPI_Recv(A, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	
	int cntr = 0;
	A += bucketSize * world_rank;
	
	// Give slightly more work to the last process
	if (world_rank == world_size - 1) bucketSize += N - (world_size * bucketSize);
	
	// Start timer
	start=MPI_Wtime();
	
	do {
		// Only do Allreduce after a certain amount of iterations
		// The number of iterations is set to be the minimum number of iterations required 
		// to reach an r of 100 (depends on num of processes)
		if(cntr % batchSize == 0) {
//			 Do a sum of all local r's to see if the threshold is met
//			 r_global is used for the check, but it may not have been updated yet when the
//			 condition check occurs.
			MPI_Allreduce(&r_local, &r_global, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
//			printf("element %d (r_local=%d, r_global=%d, process=%d)\n", cntr, r_local, r_global, world_rank);
		}
		
		if (test(*A)) r_local++;
		A++;
		cntr++;
		
	} while (cntr < bucketSize && r_global < R); // note: r_global is used so that all terminate simultaneously
	
	// Stop timer
	finish=MPI_Wtime();
	MPI_Finalize();
	printf("Finished in %f seconds (r=%d)\n", finish-start, r_global);
	return 0;
}