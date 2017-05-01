#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define READ 0
#define WRITE 0

#define CHILD 0
int main() {
    int pid;

    printf("Start parent\n");
    pid = fork();

    if(pid == CHILD) {
        printf("Start child1\n");


        int pid2 = fork();

        if(pid2 == CHILD) {
            printf("Start child2\n");
            printf("End child2\n");
        }

        if(pid2 != CHILD) {
            wait(0);
            printf("End child1\n");
        }

    }

    //PARENT
    if( pid != CHILD) {
        wait(0);
        printf("End parent\n");
    }



    return 0;

}