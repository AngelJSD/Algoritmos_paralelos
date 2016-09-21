#include <time.h>
#include <semaphore.h>
#include <stdbool.h>
#include "LInkedList.h"

#define work_per_thread 10000

pthread_t* Threads;
sem_t* Semaphores;

int *Inserts,*Deletes,*Finds;

bool flag = true;

int thread_count = 0;

void* tareas(void* rank){

	int	j;

	long my_rank = (long) rank;

	while( flag ){
		sem_wait(&Semaphores[my_rank]);
		if( my_rank % 2 == 0 && my_rank % 3 == 0){
			for( j = 0; j < work_per_thread; ++j){
				Insert(Inserts[j], &head_p);
			}
		}
		if( my_rank % 2 == 1 ){
			for( j = 0; j < work_per_thread; ++j){
				Delete(Deletes[j], &head_p);
			}
		}
		else{
			for( j = 0; j < work_per_thread; ++j){
				Member(Deletes[j], head_p);
			}
		}
	}

	return NULL;
}


int main(int argc, char const *argv[]) {

	srand(time(NULL));

	int i,j;

	long thread;

	thread_count = atoi(argv[1]);

	Threads = (pthread_t*) malloc(sizeof(pthread_t) * thread_count);
	Semaphores = (sem_t*) malloc(sizeof(sem_t) * thread_count);

	Inserts = (int*) malloc(sizeof(int) * 50);
	Deletes = (int*) malloc(sizeof(int) * 50);
	Finds = (int*) malloc(sizeof(int) * 50);

	for(i = 0; i < thread_count; ++i){
		pthread_create(&Threads[i], NULL, tareas, (void*) i);
	}

	i = 0;
	hilo = 0;
	while( i < 100 ){
		hilo = (hilo + 1) % thread_count;
		sem_post(&Semaphores[hilo]);
		for( j = 0; j < work_per_thread; ++j){
			Inserts[j] = rand() % 100000;
			Deletes[j] = rand() % 100000;
			Finds[j] = rand() % 100000;
		}
		++i;
	}

	flag = false;

	for(i = 0; i < thread_count; ++i){
		pthread_join(Threads[i], NULL);
	}

	return 0;
}


