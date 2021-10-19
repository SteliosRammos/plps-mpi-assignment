#include <stdio.h>
#include "../test_mpi.h"
#include "time.h"

int N;
int R;
int r = 0;

int main(int argc, char *argv[]) {
	
	clock_t begin = clock();
	
	int *A = allocate_mem(N);
	fill_ascending(A, N);
	int cntr = 0;
	
	do {
		if(cntr % 100 == 0) {
			printf("element %d (r=%d)", cntr, r);
			fflush(stdout);
		}
		if (test_imbalanced(*A)) r++;
		A++;
		cntr++;
	} while (r < R);
	
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Sequential Elapsed time: %f seconds\n", time_spent);
}