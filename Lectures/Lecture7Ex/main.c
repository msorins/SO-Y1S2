#include <stdio.h>
#include <unistd.h>
int main() {

    execl("/usr/bin/sort", "usr/bin/sort", "-r", "a.c", NULL);
    return 0;
}