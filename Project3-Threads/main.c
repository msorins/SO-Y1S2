#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

#define MAXSIR 1005


pthread_mutex_t countAppearencesMutex;
int appearences;

//Struct for transferring information to thread
typedef struct dataTransferThread{
    char file[MAXSIR];
    char word[MAXSIR];
};


//Thread computing function
void* computeFileThread(void *arg) {
    struct dataTransferThread *obj = (struct dataTransferThread*)arg;

    //Open the file
    FILE *file = fopen(obj->file, "r");
    char crtChar, crtCuv[MAXSIR], crtLength = 0;
    int nrAppearances = 0;

    //Check to see if file really opened
    if(!file) {
        perror("Could not open the file");
        exit(5);
    }

    //Count the words
    while((crtChar = getc(file)) != EOF) {
        //If current character is a space or new line. Check to see if the word formed is a match & resete the current word
        if(crtChar == ' ' || crtChar =='\n') {
            crtCuv[crtLength] = '\0';

            if(strcmp(crtCuv, obj->word) == 0)
                nrAppearances++;

            crtLength=0;
            continue;
        }

        //If current character is a letter add it to the word
        if(isalpha(crtChar) || (crtChar == '-')) {
            crtCuv[crtLength++] = crtChar;
            continue;
        }
    }

    //One more check at the final
    if(strcmp(crtCuv, obj->word) == 0)
        nrAppearances++;

    //Print current result
    printf("Words: %s  ->   Appearences: %d\n", obj->word, nrAppearances);

    //Add current result to a global one (synchronised operation)
    pthread_mutex_lock(&countAppearencesMutex);
    appearences += nrAppearances;
    pthread_mutex_unlock(&countAppearencesMutex);


    return 0;
}

int main(int argc, char *argv[]) {
    //Initialisaton
    int actualArgc = argc -1;
    int i;
    char file[100];
    pthread_t threads[100];

    //Arguments validation
    if(actualArgc < 2) {
        perror("Must be minimum 2 arguments");
        exit(1);
    }

    //Save the first argument as the file
    strcpy(file, argv[1]);

    //Initialise MUTEX
    if (pthread_mutex_init(&countAppearencesMutex, NULL) != 0)
    {
        perror("Mutex init failed");
        exit(2);
    }

    //Create the threads
    for(i = 2; i < argc; i++) {
        //Create the transfer object (to free it at the end of thread)
        struct dataTransferThread* obj = malloc(sizeof(struct dataTransferThread));
        strcpy(obj->file, file);
        strcpy(obj->word, argv[i]);

        //Start that thread
        pthread_create(&threads[i], NULL, computeFileThread, obj);
    }

    //Save the threads
    for(i = 2; i < argc; i++) {
        pthread_join(threads[i], NULL);
    }

    //Just print the result
    printf("Number of total appearences: %d \n", appearences);

    //Destroy MUTEX
    pthread_mutex_destroy(&countAppearencesMutex);

    return 0;
}