#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int n, thread_count;

void* nada(void* a){

	return NULL;
}

int main(int argc, char const *argv[]) {

	long i,j;
	clock_t start_t, end_t;
	double total_t,prom_par, prom;

	thread_count = atoi(argv[1]);

	double tiempos[thread_count];

	pthread_t* threads;

	threads = (pthread_t*) malloc( sizeof(pthread_t) * thread_count );

	for( i = 0; i < thread_count; ++i){
		prom_par=0.0;
		for(j=0; j<10; ++j){
			start_t = clock();
			pthread_create(&threads[i], NULL, nada, (void*) i);
			pthread_join(threads[i], NULL);
			end_t = clock();
			total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
			prom_par+=total_t;
		}
		tiempos[i]=prom_par/10.0;
	}
	for( i=0; i< thread_count; ++i)
		printf("%f\n", tiempos[i]);
	
	prom=0;
	
	for( i=0; i< thread_count; ++i)
		prom+=tiempos[i];
	
	printf("\nPromedio final: %f\n", prom/thread_count);

	return 0;
}
