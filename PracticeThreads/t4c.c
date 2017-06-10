#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

pthread_mutex_t exclusion;
int sum = 0;
void *computeThread(void *arg) {
	int nr = *(int *) arg;
	
	printf("Receiving: %d\n", nr);

	pthread_mutex_lock(&exclusion);
	sum += nr;
	pthread_mutex_unlock(&exclusion);
	
	free(arg);
}

int main(int argc, char *argv[]) {
	
	pthread_t threads[100];

	//Initialsie mutex
	if(pthread_mutex_init(&exclusion, NULL) != 0) {
		perror("Error creating mutex");
		exit(1);
        }

	//For each argument create a new thread
	int i;
	for(i = 1; i < argc; i++) {
		
		int j, nr = 0;
		char auxp[100];
		strcpy(auxp, argv[i]);

		for(j = 0; j < strlen(auxp); j++)
			nr = nr * 10 + auxp[j] - '0';
		
		int *toSend = malloc(sizeof(int));

		*toSend = nr;
		
		printf("Sending: %d\n", nr);
		pthread_create(&threads[i], NULL, computeThread, toSend);
	}

	//Wait for threads to finish
	for(i = 1; i < argc; i++) {
		pthread_join(threads[i], NULL);
	}

	//Destroy the mutex
	pthread_mutex_destroy(&exclusion);

	//Result
	printf("Result: %d\n", sum); 
}
