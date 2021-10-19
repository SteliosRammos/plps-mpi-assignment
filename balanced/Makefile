EXECS=test_sequential_random test_parallel_random test_sequential_ascending test_parallel_ascending
MPICC?=mpicc
SEQ_RAND_OBJS=sequential_random.o ../test_mpi.o
PAR_RAND_OBJS=parallel_random.o ../test_mpi.o
SEQ_ASC_OBJS=sequential_ascending.o ../test_mpi.o
PAR_ASC_OBJS=parallel_ascending.o ../test_mpi.o
CFLAGS=-Wall -std=gnu99 -lm -ldl

all: ${EXECS}

test_sequential_random: ${SEQ_RAND_OBJS}
	${MPICC} ${CFLAGS} ${SEQ_RAND_OBJS} -o test_sequential_random

test_parallel_random: ${PAR_RAND_OBJS}
	${MPICC} ${CFLAGS} ${PAR_RAND_OBJS} -o test_parallel_random

test_sequential_ascending: ${SEQ_ASC_OBJS}
	${MPICC} ${CFLAGS} ${SEQ_ASC_OBJS} -o test_sequential_ascending

test_parallel_ascending: ${PAR_ASC_OBJS}
	${MPICC} ${CFLAGS} ${PAR_ASC_OBJS} -o test_parallel_ascending

test_mpi.o: ../test_mpi.c
	${MPICC} ${CFLAGS} -O3 -c -o ../test_mpi.o ../test_mpi.c

sequential_random.o: sequential_random.c
	${MPICC} ${CFLAGS} -O3 -c -o sequential_random.o sequential_random.c

parallel_random.o: parallel_random.c
	${MPICC} ${CFLAGS} -O3 -c -o parallel_random.o parallel_random.c

sequential_ascending.o: sequential_ascending.c
	${MPICC} ${CFLAGS} -O3 -c -o sequential_ascending.o sequential_ascending.c
	
parallel_ascending.o: parallel_ascending.c
	${MPICC} ${CFLAGS} -O3 -c -o parallel_ascending.o parallel_ascending.c
	
clean:
	rm -f *.o ${EXECS} *~ *core