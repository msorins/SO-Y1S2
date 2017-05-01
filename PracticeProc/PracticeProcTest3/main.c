#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1
#define CHILD 0

int main() {
    int p2a[2], a2b[2], b2a[2], a2p[2];

    //Create pipes
    if(pipe(p2a) < 0 || pipe(a2b) < 0 || pipe(b2a) < 0 || pipe(a2p) < 0) {
        perror("Error creating pipes");
        exit(1);
    }

    int pidA = fork();
    if(pidA == CHILD) {

        int pidB = fork();
        if(pidB == CHILD) {
            //Close unused pipes
            close(p2a[READ]); close(p2a[WRITE]);
            close(a2b[WRITE]);
            close(b2a[READ]);
            close(a2p[READ]); close(a2p[WRITE]);


            //Read from child a
            int nrB;
            read(a2b[READ], &nrB, sizeof(int));
            close(a2b[READ]);

            //Multiply the number with 2
            nrB *=2;

            printf("childB nr: %d\n", nrB);

            //Write to child a
            write(b2a[WRITE], &nrB, sizeof(int));
            close(b2a[WRITE]);
        }

        if(pidB != CHILD) {
            //Close unused pipes
            close(p2a[WRITE]);
            close(a2b[READ]);
            close(b2a[WRITE]);
            close(a2p[READ]);

            //Read from parent
            int nrA;
            read(p2a[READ], &nrA, sizeof(int));
            close(p2a[READ]);

            //Multiply the number with 2
            nrA *= 2;

            printf("childA nr: %d\n", nrA);

            //Write to child b
            write(a2b[WRITE], &nrA, sizeof(int));
            close(a2b[WRITE]);

            //Wait for child b to finish
            wait(0);

            //Get result from child b
            int resFinal;
            read(b2a[READ], &resFinal, sizeof(int));
            close(b2a[READ]);

            //Send result to parent
            write(a2p[WRITE], &resFinal, sizeof(int));
            close(a2p[WRITE]);
        }
    }

    if(pidA != CHILD) {

        int a;
        scanf("%d", &a);

        //Close unused pipes
        close(p2a[READ]);
        close(a2b[READ]); close(a2b[WRITE]);
        close(b2a[READ]); close(b2a[WRITE]);
        close(a2p[WRITE]);

        //Write to first child
        write(p2a[WRITE], &a, sizeof(int));
        close(p2a[WRITE]);

        //Wait for first childA to finish
        wait(0);

        //Read from first child
        int res;
        read(a2p[READ], &res, sizeof(int));
        printf("Result: %d\n", res);

        //Close remaining pipes
        close(a2p[READ]);
    }

    return 0;
}