//primeste x parametrii din linia de comanda
//creaza un fiu, fiul citeste un numar n de la tastatura, apoi trimite acel nr parintelui
//parinte ii trimite inapoi prin pipe al  n-lea parametru 

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define READ 0
#define WRITE 1
#define CHILD 0

int main(int argc, char *argv[])
{
  int p2c[2],  c2p[2];
  
  if(pipe(p2c) < 0 || pipe(c2p) < 0) {
    perror("Error creating pipe");
    exit(1);
  }

  //Create the child
  int pid = fork();
  if(pid < 0 ) {
    perror("Error creating child");
    exit(2);
  }

  if(pid == CHILD) {
    //Close unused pipes
    close(c2p[READ]);
    close(p2c[WRITE]);

    int c;
    printf("Give a number: ");
    scanf("%d",&c);

    //Write that number to parent
    write(c2p[WRITE], &c, sizeof(int));
    close(c2p[WRITE]);

    //Receive the anser
    char param[100];
    read(p2c[READ], &param, sizeof(char) * 100);
    close(p2c[READ]);

    //Print result
    printf("%d parameter is: %s\n", c, param);

    exit(0);
  }

  //Close unused pipes
  close(c2p[WRITE]);
  close(p2c[READ]);

  //Read the number from child
  int n;
  read(c2p[READ], &n, sizeof(int));
  close(c2p[READ]);
  
  if(n > argc){
     perror("Number too large");
     exit(5);
  }

  char nthParam[100];
  strcpy(nthParam, argv[n]);
  
  //Write the nTh parameter to child
  write(p2c[WRITE], &nthParam, sizeof(char) * 100);
  close(p2c[WRITE]);
}
