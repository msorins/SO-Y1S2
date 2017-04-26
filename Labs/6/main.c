#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    int p2c[2], c2p[2];
    if(pipe(p2c) < 0) {
       perror("Error creating pipe");
       exit(1);
    }

    if(pipe(c2p) < 0) {
        perror("Error creating pipe");
        exit(1);
    }

    /*
     * p[0] - citire
     * p[1] - scriere
     */

    int f;
    f = fork();
    if(f < 0) {
        perror("Error creating child");
        exit(2);
    }

    //Daca a ajuns aici executia, avem 2 procese
    if(f == 0) {
        close(p2c[1]);
        close(c2p[0]);

        //child
        int a, b, c;
        if(read(p2c[0], &a, sizeof(int)) < 0) {
            perror("Error reading a");
            exit(3);
        }

        if(read(p2c[0], &b, sizeof(int)) < 0) {
            perror("Error reading b");
            exit(3);
        }

        if(read(p2c[0], &c, sizeof(int)) < 0) {
            perror("Error reading c");
            exit(3);
        }

        close(p2c[0]);

        int sum = a + b + c;
        if(write(c2p[1], &sum, sizeof(int)) < 0) {
            perror("nu o putut scrie");
            exit(4);
        }

        close(c2p[1]);


        //Totul ok
        exit(0);
    }

    //Parent
    //wait(0);
    int a, b, c, sum=-1;

    printf("Dati a\n");
    scanf("%d", &a);

    printf("Dati b\n");
    scanf("%d", &b);

    printf("Dati c\n");
    scanf("%d", &c);

    close(p2c[0]);
    close(c2p[1]);

    if(write(p2c[1], &a, sizeof(int)) < 0) {
        perror("nu o putut scrie a");
        exit(4);
    }

    if(write(p2c[1], &b, sizeof(int)) < 0) {
        perror("nu o putut scrie b");
        exit(4);
    }

    if(write(p2c[1], &c, sizeof(int)) < 0) {
        perror("nu o putut scrie c");
        exit(4);
    }

    close(p2c[1]);
    wait(0);

    if(read(c2p[0], &sum, sizeof(int)) < 0) {
        perror("Error reading a + b + c");
        exit(3);
    }


    close(c2p[0]);

    printf("Suma este: %d", sum);

    printf("%s", execl("/bin/ls", "/bin/ls", 0));
    printf("gata cu astaa");

    return 0;
}