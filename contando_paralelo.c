#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

#define NUM_THREADS 5
#define NUM  10000000000
#define ELEMENTS_PER_THREADS NUM/NUM_THREADS


void *contar(void * start){
	long count = 0;
	for (long i = 0; i < (long) ELEMENTS_PER_THREADS; ++i) {
		start++;
	}
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	pthread_t t[NUM_THREADS];
	struct timeval t1, t2;
	long elementsPerThreads = NUM / NUM_THREADS;
	gettimeofday(&t1, NULL);
	for(long i = 0; i < NUM_THREADS; i++){
		long start = i * ELEMENTS_PER_THREADS;
		long id = pthread_create(&t[i], NULL, contar, (void*)start);
	}
	for(int i = 0; i < NUM_THREADS; i++){
		pthread_join(t[i], NULL);
	}

	gettimeofday(&t2, NULL);
	double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
	printf("Total time: %f\n", t_total);
	return 0;
}



