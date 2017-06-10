#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

pthread_mutex_t exclusion;

int x, y, z;
int nr_divizor[3];


void *compute(void* arg) {
  int nr = *(int *) arg;
  
  if( pthread_mutex_lock(&exclusion) != NULL ) {
    perror("Error locking thread");
    exit(6);
  }

  //Safe zone
  if(x % nr == 0) nr_divizor[0]++;
  if(y % nr == 0) nr_divizor[1]++;
  if(z % nr == 0) nr_divizor[2]++;
 
  if( pthread_mutex_unlock(&exclusion) != NULL ) {
    perror("Error unlocking thread");
    exit(7);
  }

  free(arg);

}

int main(int argc, char* argv[]) {
  scanf("%d%d%d", &x, &y, &z);
  pthread_t threads[101];
  int i, j; 

  //Initialsie the mutex
  if(pthread_mutex_init(&exclusion, NULL) != 0) {
    perror("error creating mutex");
    exit(2);
  }
 
  //For each parameter, create a thread
  for(i = 1; i < argc; i++) {
    int *toSend = malloc(sizeof(int));
    int nr = 0;
    char aux[1001];
    strcpy(aux, argv[i]);

    //Transform the number to be printed
    for(j = 0; j < strlen(aux); j++) {
      nr = nr  * 10 + aux[j] - '0';      
    }
    
    *toSend = nr;
    //Create the thread
    if( pthread_create(&threads[i], NULL, compute, toSend) != 0) {
    	perror("error creating thread");	
	exit(1);
    }
  }

  //Close the thread
  for(i = 1; i < argc; i++) {
    if( pthread_join(threads[i], NULL) != 0 ) {
        perror("Error exiting thread");
        exit(3);
    }
  }

  //Close the mutex
  if( pthread_mutex_destroy(&exclusion) != 0) {
      perror("Error destroying mutex");
      exit(4);
  } 
  
  if(nr_divizor[0] >= nr_divizor[1] && nr_divizor[0] >= nr_divizor[2])
    printf("%d\n", x);
  else
    if(nr_divizor[1] >= nr_divizor[0] && nr_divizor[1] >= nr_divizor[2])
      printf("%d\n", y);
    else
      printf("%d\n", z);
  
  return 0;
}
