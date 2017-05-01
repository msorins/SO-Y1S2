//
// Created by Sorin Sebastian Mircea on 30/04/2017.
// Parent reads two number, passes them to child which computes the sum and sends it back to parent
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1
#define CHILD 0

int main() {

    int pid;
    int p2c[2], c2p[2];
    int nr1, nr2;

    if(pipe(p2c) < 0 || pipe(c2p) < 0) {
        perror("Error creating pipe");
        exit(1);
    }


    //Create a new process
    pid = fork();

    if(pid == CHILD) {
        //in the child
        close(p2c[WRITE]);
        close(c2p[READ]);

        int nrR1, nrR2;
        if(read(p2c[READ], &nrR1, sizeof(int)) < 0 || read(p2c[READ], &nrR2, sizeof(int)) < 0) {
            perror("Error reading numbers in child");
            exit(2);
        }
        close(p2c[READ]);

        //Compute the sum right here
        int sum = nrR1 + nrR2;

        if(write(c2p[WRITE], &sum, sizeof(int)) < 0) {
            perror("Error writing in child");
            exit(3);
        }
        close(c2p[WRITE]);
    }

    if(pid != CHILD) {
        //in the parrent

        //Read two num
        scanf("%d %d", &nr1, &nr2);

        //Put them to pipe
        close(p2c[READ]);
        close(c2p[WRITE]);

        if(write(p2c[WRITE], &nr1, sizeof(int)) < 0) {
            perror("couldn't write");
            exit(2);
        }

        if(write(p2c[WRITE], &nr2, sizeof(int)) < 0) {
            perror("couldn't write");
            exit(3);
        }

        close(p2c[WRITE]);

        //Wait for the child to finish
        wait(0);

        //READ RESULT FROM CHILD

        int res;
        if( read(c2p[READ], &res, sizeof(int)) < 0) {
            perror("couldn't read parent");
            exit(4);
        }

        printf("Sum is: %d\n", res);
    }





    return 0;

}