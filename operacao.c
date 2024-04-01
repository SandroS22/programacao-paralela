#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

//#define IMPRIME

#define MAX_NUMBERS 500000000
//#define MAX_NUMBERS 5000000
#define MAX_VALUE 1000;
#define NUM_THREADS 5
#define ELEMENTS_PER_THREADS MAX_NUMBERS/NUM_THREADS

float numbers[MAX_NUMBERS];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;
pthread_t t[NUM_THREADS];


void *aloca_numero(void * start){
	for(long i = (long) start; i < ELEMENTS_PER_THREADS; i++){
		float number =  ((float)rand()/(float)RAND_MAX) * MAX_VALUE;
		pthread_mutex_lock(&mtx2);
		numbers[i] = number;
		pthread_mutex_unlock(&mtx2);
	}
	pthread_exit(NULL);
}

void init_numbers(){
	for(int i = 0; i < NUM_THREADS; i++){
		long start = ELEMENTS_PER_THREADS * i;
		int id = pthread_create(&t[i], NULL, aloca_numero, (void *) start);
	}
	for (int j = 0; j < NUM_THREADS;  j++){
		pthread_join(t[j], NULL);
	}
}


void *calculate(void * start){
	long s = (long) start + ELEMENTS_PER_THREADS;
	for (long i = (long)start; i < s; i++){
		numbers[i] =  numbers[i]*0.2 + numbers[i]/0.3;
	}
	pthread_exit(NULL);
}

int show_numbers(){
	for (long i = 0; i < MAX_NUMBERS; i++)
		printf("number[%ld] = %f\n",i,numbers[i]);
	return 0;
}

int main (int argc, char **argv){
	
	struct timeval t1, t2; 
	srand(time(NULL));
	gettimeofday(&t1, NULL);

	init_numbers();
	
	#ifdef IMPRIME
		show_numbers();
	#endif
	for (int j = 0; j < NUM_THREADS;  j++){
			long start = j*ELEMENTS_PER_THREADS;
		int id = pthread_create(&t[j], NULL, calculate, (void *) start);
	}
	for (int j = 0; j < NUM_THREADS;  j++){
		pthread_join(t[j], NULL);
	}
	gettimeofday(&t2, NULL);
	double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec)/1000000.0);

	#ifdef IMPRIME
		printf("Apos a operacao matematica\n"); 
		show_numbers();
	#endif

	printf("Total time: %f\n",t_total);
	return 0;
}

