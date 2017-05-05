#include "library.h"

#include <stdio.h>
#include <unistd.h>

void hello(void) {
    int a=1, b=0, c = 0, d= 0;

    fork();
    b++;
    fork();
    c++;
    fork();
    d++;

    printf("a: %d, b: %d, c: %d, d: %d\n", a, b, c, d);
}