/*
 * se creeaza 8 threaduri care genereaza in total exact 2.000 numere intre 1000 si 2000
 * adauga numerele generate intr-un array, asigurandu-se ca dupa inserare sirul este sortat
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
int vec[5000] = {0};
int n = 0;

pthread_mutex_t exclusion;
void printVector() {
    int i;
    for(i = 1; i <= 2000; i++) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

/*
 * 5 10 15 20 25 35 40
 * 16
 */

void *computeThread(void *arg) {
    printf("Started thread \n");
    int i;
    for( i = 1; i <= 250; i++) {

        pthread_mutex_lock(&exclusion);
        //Add a number

        int r = rand() % 1000 + 1 + 1000;

        int pos = 1, j;
        while(pos <= n && vec[pos] < r)
            pos++;

        n = n + 1;

        for(j = n; j > pos; j--) {
            vec[j] = vec[j-1];
        }

        vec[pos] = r;

        pthread_mutex_unlock(&exclusion);
    }

    return 0;
}

int main(int argc, char* argv[]) {

    pthread_t threads[8];
    srand(time(NULL));

    //Initialise the mutex
    if(pthread_mutex_init(&exclusion, NULL) != 0) {
        perror("Error creating mutex");
        exit(1);
    }

    //Create the 8 threads
    int i;
    for(i = 0; i < 8; i++) {
        pthread_create(&threads[i], NULL, computeThread, NULL );
    }

    //Wait for the 8 treads to finish
    for(i = 0; i < 8; i++) {
        pthread_join(threads[i], NULL);
    }

    //Destroy the mutex
    pthread_mutex_destroy(&exclusion);

    printf("n: %d\n", n);
    printVector();

}