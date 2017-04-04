#include <stdio.h>
#include <stdlib.h>

int main() {
    /*
     *  Alocare DINAMICA
     *    void* malloc(size_t);
     */
     int *p = (int*) malloc( sizeof(int) );

    /*
     * Dezalocare
     *   free(pointer)
     */

    free(p);

    printf("Working");

    /*
     * Variabile constante
     * c++ varianta
     * const int v
     * v = 11;
     */

    /*
     * Pointer constant
     */
    int *const pointerConstant;


    /*
     * Declarare sir pointer
     */

    int dim = 100;
    int *s = (int*) malloc( sizeof(int) * dim);
    free(s);

    /*
     * Declarare matrice
     */

    int n = 10;
    int m = 20;
    int **mat = (int **) malloc(sizeof(int *) * n);
    for(int i = 1; i < n; i++) {
        mat[i] = malloc(sizeof(int *) * m); // or m + i
    }

    /*
     *  Dezalocare matrice
     */

    for(int i= 1; i < n; i++) {
        free(mat[i]);
    }
    free(mat);

    /*
     *  TOOL valgrind pentru testarea LEAK-urilor de memorie
     *  gcc nume.c -o nume or gcc nume.c -g -o nume
     *  valgrind ./ nume
     */


}