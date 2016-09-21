#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define MAX 200

int n, thread_count;
sem_t* sem;

void* tokenize(void* rank){

	long my_rank = (long) rank;

	int count, next = (my_rank + 1) % thread_count;

	char *fg_rv, my_line[MAX], *my_string, *saveptr;

	sem_wait(&sem[my_rank]);
	fg_rv = fgets(my_line, MAX, stdin);
	sem_post(&sem[next]);

	while(fg_rv != NULL){

		printf("Thread %ld > my line = %s", my_rank, my_line);

		count = 0;
		//my_string = strtok(my_line, " \t\n");
		my_string = strtok_r(my_line, " \t\n", &saveptr);
		while( my_string != NULL ){
			++count;

			printf("Thread %ld > string %d = %s\n", my_rank, count, my_string);
			//my_string = strtok(NULL, " \t\n");
			my_string = strtok_r(NULL, " \t\n", &saveptr);
		}

		sem_wait(&sem[my_rank]);
		fg_rv = fgets(my_line, MAX, stdin);
		sem_post(&sem[next]);
	}

	return NULL;
}

int main(int argc, char const *argv[]) {

	long thread = 0;

	thread_count = atoi(argv[1]);

	pthread_t* threads;

	threads = (pthread_t*) malloc( sizeof(pthread_t) * thread_count );
	sem = (sem_t*) malloc( sizeof(sem_t) * thread_count );

	sem_post(&sem[0]);

	for( thread = 0; thread < thread_count; ++thread){
		pthread_create(&threads[thread], NULL, tokenize, (void*) thread);
	}
	for( thread = 0; thread < thread_count; ++thread){
		pthread_join(threads[thread], NULL);
	}

	free(threads);

	return 0;
}
