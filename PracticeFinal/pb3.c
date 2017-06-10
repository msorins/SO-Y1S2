#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t threadExclusion, dataExclusion;

#define MAXN 100
int n, v[MAXN+5];

void *computeThread(void *arg) {
  int nr = *(int *) arg;
  printf("Thread started. Nr: %d \n", nr);
  while(n < 100) {
    printf("while\n");
    sleep(nr);
    
    pthread_mutex_lock(&threadExclusion);
    pthread_mutex_unlock(&threadExclusion);

    int nr = rand() % MAXN + 1;
    printf("Thread inserting number: %d\n", nr);    
  }
	
  free(arg);
}

int main(int argc, char *argv[]) {
	pthread_t threads[105];
       
        srand(time(NULL));
		
	if(pthread_mutex_init(&threadExclusion, NULL) != 0 || pthread_mutex_init(&dataExclusion, NULL) != 0) {
          perror("Error creating mutex");
          exit(1);
        }
        
        n = 1;

        int i;
        pthread_mutex_lock(&threadExclusion);
	for(i = 1; i < argc; i++) {
           int nr = atoi(argv[i]);
           
           int *toSend = malloc(sizeof(int));
           *toSend = nr;
           pthread_create(&threads[i], NULL, computeThread, toSend);
        }
        pthread_mutex_unlock(&threadExclusion);
 	
	for(i = 1; i < argc; i++) {
          pthread_join(threads[i], NULL);
        } 
        
        if(pthread_mutex_destroy(&threadExclusion) != 0 || pthread_mutex_destroy(&dataExclusion) != 0) {
          perror("Error destroing mutex");
          exit(1);
        }

        printf("Daa\n");
        return 0;
}
