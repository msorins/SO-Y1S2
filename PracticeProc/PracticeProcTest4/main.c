#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1
#define CHILD 0

#define MAXN 100
int main() {
    int p2c[2];
    int mat[MAXN][MAXN];
    mat[0][0]=1; mat[0][1] =2; mat[1][0]=3; mat[1][1]=4;

    if(pipe(p2c) < 0) {
        perror("Error creating pipe");
        exit(1);
    }

    int pid = fork();

    if(pid < 0) {
        perror("Error creating a child");
        exit(2);
    }

    if(pid == CHILD) {
        int mat2[MAXN][MAXN];
        read(p2c[READ], &mat2, sizeof(int) * MAXN * MAXN);

        printf("%d %d %d %d %d\n", mat2[0][0], mat2[0][1], mat2[1][0], mat2[1][1], mat2[34][34]);
        close(p2c[WRITE]);
    }

    if(pid != CHILD) {
        int x;
        close(p2c[READ]);

        mat[0][0]=5;
        mat[1][1]=99;
        mat[34][34]=34;
        write(p2c[WRITE], &mat, sizeof(int) * MAXN * MAXN);
        close(p2c[WRITE]);

        wait(0);
    }


}