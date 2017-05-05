/*
 * 14. Sa se calculeze suma unui sir de numere folosind metoda divide et impera:
 * un proces imparte sirul in doua subsiruri pe care le da altor doua procese (fii) sa le calculeze suma,
 * dupa care aduna cele doua rezultate obtinute. Procesele fii aplica in continuare aceeasi tehnica.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1
#define CHILD 0

void compute(int p2c[2], int c2p[2]) {

    int crtSum = 0, crtSumFirst = 0, crtSumSecond = 0;
    int v[10001];
    int n, st, dr;

    //Read from parent
    read(p2c[READ], &n, sizeof(int));
    read(p2c[READ], &st, sizeof(int));
    read(p2c[READ], &dr, sizeof(int));
    read(p2c[READ], &v, sizeof(int) * ( n + 1));
    
    if(st < dr) {
        int mij = (st + dr) / 2;

        //CREATE TWO CHILD
        int c2First[2], First2c[2], c2Second[2], Second2c[2];

        //Create the pipes
        if(pipe(c2First) < 0 || pipe(First2c) < 0 || pipe(c2Second) < 0 || pipe(Second2c) < 0) {
            perror("Error creating pipes");
            exit(3);
        }

        //Create first children
        int pid = fork();
        if(pid < 0) {
            perror("Error creating child");
            exit(1);
        }

        if(pid == CHILD) {
            //FIRST CHILDREN
            compute(c2First, First2c);
            exit(0);
        }

        if(pid != CHILD) {
            //FATHER
            close(c2First[READ]);
            close(First2c[WRITE]);

            //write to 1st children
            write(c2First[WRITE], &n, sizeof(int));
            write(c2First[WRITE], &st, sizeof(int));
            write(c2First[WRITE], &mij, sizeof(int));
            write(c2First[WRITE], &v, sizeof(int) * (n+1));
            close(c2First[WRITE]);

            //wait for the execution of that program
            wait(0);

            //get result from the above function
            read(First2c[READ], &crtSumFirst, sizeof(int));


            //CREATE SECOND CHILDREN
            int pid2 = fork();
            if(pid2 < 0) {
                perror("Error creating 2nd child");
                exit(2);
            }

            if(pid2 == CHILD) {
                //FIRST CHILDREN
                compute(c2Second, Second2c);
                exit(0);
            }

            if(pid2 != CHILD) {
                close(c2Second[READ]);
                close(Second2c[WRITE]);

                //write to 2nd children
                int mijN = mij + 1;
                write(c2Second[WRITE], &n, sizeof(int));
                write(c2Second[WRITE], &mijN, sizeof(int));
                write(c2Second[WRITE], &dr, sizeof(int));
                write(c2Second[WRITE], &v, sizeof(int) * (n+1));
                close(c2Second[WRITE]);

                //wait for the execution of that program
                wait(0);

                //get result from the above function
                read(Second2c[READ], &crtSumSecond, sizeof(int));
                close(Second2c[READ]);

                crtSum = crtSumFirst + crtSumSecond;

            }


        }

    }
    else if( st == dr) {
        crtSum = v[st];
    }


    printf("PID: %d. ST: %d  . DR: %d. CRTSUM: %d\n", getpid(), st, dr, crtSum);

    //From child write to parent
    write(c2p[WRITE], &crtSum, sizeof(int));
}

int main() {
    int p2c[2], c2p[2];
    int pid;

    int v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int st = 1, dr = 10, n = 10;

    //Create the pipe
    if(pipe(p2c) < 0 || pipe(c2p) < 0) {
        perror("Error creating pipe");
        exit(1);
    }

    //Write to the process who whill continue the computing
    write(p2c[WRITE], &n, sizeof(int));
    write(p2c[WRITE], &st, sizeof(int));
    write(p2c[WRITE], &dr, sizeof(int));
    write(p2c[WRITE], &v, sizeof(int) * (n+1));
    close(p2c[WRITE]);

    //Call the recursive computation algorithm
    compute(p2c, c2p);

    //Get the result
    int sum;
    read(c2p[READ], &sum, sizeof(int));
    printf("Total sum is: %d\n", sum);

    return 0;
}