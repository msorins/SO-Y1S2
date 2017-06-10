#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

/*
 * A program that receives as command line arg serveral integer numbers
 * For each number the program creates a thread and checks if the nr contains one of the digits 5 or 7
 * It incrementes a global variable for 5 & another global variable for 7
 *
 */
pthread_mutex_t exclusionMutex5;
pthread_mutex_t exclusionMutex7;
int nrOf5 = 0, nrOf7 = 0;

void* computeThread(void *arg) {
    int nr = *(int *)arg;
    int initialNr = nr;
    int increment5 = 0, increment7 = 0;

    while(nr) {
        if(nr % 10 == 5)
            increment5++;
        if(nr % 10 == 7)
            increment7++;
        nr /= 10;
    }

    if(increment5) {
        pthread_mutex_lock(&exclusionMutex5);
        nrOf5 += increment5;
        pthread_mutex_unlock(&exclusionMutex5);
    }

    if(increment7) {
        pthread_mutex_lock(&exclusionMutex7);
        nrOf7 += increment7;
        pthread_mutex_unlock(&exclusionMutex7);
    }

    printf("Thread. Initial: %d . Five: %d, Seven: %d\n", initialNr, increment5, increment7);
    return 0;
}

int main(int argc, char *argv[]) {
    pthread_t threads[101];

    //Create Mutex
    if (pthread_mutex_init(&exclusionMutex5, NULL) != 0 || pthread_mutex_init(&exclusionMutex7, NULL) != 0) {
        perror("Error creating mutex");
        exit(1);
    }

    int i, j;
    for(i = 1;  i < argc; i++)
    {
        //Create an int variable to send it to thread
        char aux[100];
        int nr = 0;

        for(j = 0; j < strlen(argv[i]); j++) {
            nr = nr * 10 + (argv[i][j] - '0');
        }


        int *nrToSend = malloc(sizeof(int));
        *nrToSend = nr;

        //Create the thread
        pthread_create(&threads[i], NULL, computeThread, nrToSend);
    }

    for(i = 1; i < argc; i++) {
        pthread_join(threads[i], NULL);
    }

    //Destroy Mutex
    pthread_mutex_destroy(&exclusionMutex5);
    pthread_mutex_destroy(&exclusionMutex7);

    //Print result
    printf("Number of digits 5: %d \n Number of digits 7: %d", nrOf5, nrOf7);
}