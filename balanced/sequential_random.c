#include <stdio.h>
#include "../test_mpi.h"
#include "time.h"

int N;
int R;
int r = 0;

int main(int argc, char *argv[]) {
	
		
	int *A = allocate_mem(N);
	fill_random(A, N);
	int cntr = 0;

	clock_t begin = clock();

	do {
//		if(cntr % 100 == 0) {
//			printf("element %d (r=%d)", cntr, r);
//			fflush(stdout);
//		}
		if (test(*A)) r++;
		A++;
		cntr++;
	} while (r < R);
	
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Finished in %f seconds (r=%d)\n", time_spent, r);
}