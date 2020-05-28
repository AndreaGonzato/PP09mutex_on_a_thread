#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>


void * thread_function(void * index);

#define N 2
#define LIMIT 10000

int count;
int work[2];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void) {
	pthread_t treads[2];
	int s;

	int * par = calloc(2, sizeof(int));
	par[1] = 1;

	// create N threads
	for(int i=0 ; i<N ; i++){
		s = pthread_create(&treads[i], NULL, thread_function, (void *) ((long) i));
		if (s != 0) {
			perror("pthread_create()\n");
			exit(EXIT_FAILURE);
		}
	}


	// join N threads
	for(int i=0 ; i<N ; i++){
		s = pthread_join(treads[i], NULL);
		if (s != 0) {
			perror("pthread_join()\n");
			exit(EXIT_FAILURE);
		}
	}

	printf("thread 0 ha incrementato: %d volte\n", work[0]);
	printf("thread 1 ha incrementato: %d volte\n", work[1]);


	printf("[f] fine");


	exit(EXIT_SUCCESS);
}

void * thread_function(void * index){

	int i = (int) ((long) index);
	while(1){
		pthread_mutex_lock(&mutex);

		if(count >= LIMIT){
			// rilascio mutex
			pthread_mutex_unlock(&mutex);
			return 0;
		}

		count++;
		printf("thread index: %d ha incrementato count a: %d\n", i, count);
		work[i]++;

		// rilascio mutex
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
