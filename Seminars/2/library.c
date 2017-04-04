#include "library.h"

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void hello(void) {
    printf("Hello, World!\n");
}

void main() {
    /*
     * I/0
     * scanf / printf
     * read / write
     * man 2 open
     */

    /*
     * int read(int fd, void* buff, size_t n);
     * fd = file descriptor / handler
     * returneaza cati octeti a putut citi
     *
     * int open(cont char* name, int flag, [int mod])
     *
     */

    //Declara un buffer
    char *str = (char*) malloc(1024 * sizeof(char));

    //Deschide un fisier (handler)
    int fd = open("test-1", O_RDONLY);
    if( fd < 0 ) {
        perror("Erroare de deschidere");
        exit(1);
    }

    //Citeste din handler-ul respectiv
    int rb = (int) read(fd, str, 1024);
    if(rb < 0) {
        perror("Eroare la citire");
        exit(2);
    }

    //Printeaza acell buffer
    str[rb] = 0;
    printf("%s\n", str);

    //Scrie in fisier (handler)
    /*
     * int write(int fd, void* buff, size_t n);
     */

    //Inchide un fisier (handler)
    /*
     * int close(int fd);
     *
     */


    //Functii
    /*
     * strcpy
     * strncpy
     * int memcpy(void *dest, void* src, size_t n);
     * int memcpy(dest, src, ch, n) => copiezi din src in dest maxim n caractere sau pan aintalnesti caracterul ch
     */

    //Memcpy vs strcpy
    /*
     * memcpy(d, s);
     * strcpy(d, s);
     * => memcpy nu pune si 0 la final
     */

    //Memset
    /*
     * memset(void *dest, int val, size_t n);
     */

    //Fopen (omologul lui open)
    /*
     * FILE *fopen(constchar *path, const char* mode);
     * If null => error
     * modes can be "r"  -> read only
     *              "r+" -> read & write
     *              "w"  -> write only | truncate
     *              "w+" -> read & write | truncate
     *              "a"  -> append
     *              "a+" -> append & read
     */

    //LSEEK and FSEEK
    /*
     * fseek(FILE *, int offset, int where) // al treilea param econstanta
     * SEEK_SET
     * SEEK_CUR
     * SEEK_E D
     */

    //FREAD
    /*
     * INT FREAD(VOID *BUFF, INT BSIZE, INT NB, FILE*)
     * bsize = block size
     * nb = number of blocks
     */

    //FWRITE
    /*
     * INT FWRITE(VOID *BUFF, INT BSZIE, INT NB, FILE*);
     */

    //FCLOSE
    /*
     * INT FCLOSE(FILE *);
     */

    //FGETC / GETC

    //FGETS / GETS

    //FPUTS / PUTS

    //FPUTC / PUTC
}