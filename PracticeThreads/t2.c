#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

pthread_mutex_t exclusion;
int a,e,i,o,u;

void *computeThread(void *arg) {
    char *str = (char *)arg;
    printf("Thread computing word: %s\n", str);

    pthread_mutex_lock(&exclusion);

    if(str[0] == 'a')
        a++;
    if(str[0] == 'e')
        e++;
    if(str[0] == 'i')
        i++;
    if(str[0] == 'o')
        o++;
    if(str[0] == 'u')
        u++;

    pthread_mutex_unlock(&exclusion);


    return 0;
}

int main(int argc, char *argv[]) {
    pthread_t threads[100];

    //Initialise mutex
    if(pthread_mutex_init(&exclusion, _NULL) != 0) {
        perror("Error creating mutex");
        exit(1);
    }

    //Loop through all words in argv
    int i;
    for(i = 1; i < argc; i++) {

        //Create a new address variable for sending it to thread
        char *word = malloc(sizeof(char) * 100);
        strcpy(word, argv[i]);

        //Start the threads
        pthread_create(&threads[i], NULL, computeThread, word);
    }

    //Wait for threads to finish
    for(i = 1; i < argc; i++) {
        pthread_join(threads[i], NULL);
    }

    //Close Mutex
    pthread_mutex_destroy(&exclusion);

    //Print result
    printf("a: %d, e: %d, i: %d, o: %d, u: %d\n", a, e, i, o, u);

    return 0;
}