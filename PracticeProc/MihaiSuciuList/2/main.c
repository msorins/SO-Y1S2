/*
 * 2. Dandu-se un fisier text, sa se creeze cate un proces fiu pentru fiecare litera din alfabet ('a', 'b', ... 'z').
 *  Procesul corespunzator literei 'a' va cauta in acel fisier text toate cuvintele care incep cu litera 'a' si le va scrie intr-un fisier a.txt.
 *  De asemenea, acest proces ii va comunica procesului parinte numarul de cuvinte care incep cu litera 'a' din fisierul text.
 *  Procesul corespunzator literei 'b' va efectua aceeasi operatiune, doar ca el cauta toate cuvintele care incep cu 'b' si le va scrie in b.txt.
 *  La fel decurg lucrurile pentru toate celelalte procese fiu. In final, procesul parinte va afisa o statistica care sa cuprinda numarul de cuvinte care
 *  incep cu litera 'a', numarul de cuvinte care incep cu 'b', s.a.m.d.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define READ 0
#define WRITE 1
#define CHILD 0

int find(char letter) {
    FILE *file = fopen("words.txt", "r");


    char crtLine[1001];
    int i, nrOfWords = 0;


    while(fgets(crtLine, sizeof(crtLine), file)) {
        //printf("%s\n", crtLine);
        for(i = 0;  i < strlen(crtLine); i++) {
            if((i == 0 && crtLine[i] == letter) || (crtLine[i-1]==' ' && crtLine[i] == letter))
                nrOfWords++;
        }
    }



    return nrOfWords;


}
int main() {

    int i;

    for(i = 'a'; i<='z'; i++) {

        //CREATE PIPES
        int p2c[2], c2p[2];

        if(pipe(p2c) < 0 || pipe(c2p) <0) {
            perror("Error creating pipe");
            exit(1);
        }

        //CREATE PROCESS
        int pid = fork();

        if(pid < 0) {
            perror("Error creating child");
            exit(2);
        }

        //CHILD
        if(pid == CHILD) {
            close(p2c[WRITE]);
            close(c2p[READ]);

            char assignedLetter;
            read(p2c[READ], &assignedLetter, sizeof(char));
            close(p2c[READ]);

            int nrOfWordsFound = find(assignedLetter);

            FILE *outFile = fopen(assignedLetter, "w");

            fprintf(outFile, "Process %d has assigned letter %c. Nr of words found: %d\n", getpid(), assignedLetter, nrOfWordsFound);

            //Send this result back to the parent
            write(c2p[WRITE],&nrOfWordsFound, sizeof(int));
            close(c2p[WRITE]);

            exit(0);
        }

        //PARENT
        if(pid != CHILD) {
            close(p2c[READ]);
            close(c2p[WRITE]);

            char letter = (char)i;
            write(p2c[WRITE], &letter, sizeof(char));
            close(p2c[WRITE]);

            wait(0);
            int nrOfWordsResult;
            read(c2p[READ], &nrOfWordsResult, sizeof(int));
            close(c2p[READ]);

            printf("Son %c => Nr of words found: %d\n", (char)i, nrOfWordsResult);
        }

    }
    return 0;
}