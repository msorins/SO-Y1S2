//Primeste ca parametru un nume de fisier si o dimensiune N
//Creeaza si transmite unui fiu numarl n
//Fiul citeste de la tastatura un sir de catactere. Trimite primele n caractere
//Parintelui. Acesta afiseaza rezultatul
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define READ 0
#define WRITE 1
#define CHILD 0

int main(int argc, char* argv[])
{
  //Create the pipes
  int p2c[2], c2p[2];
  if(pipe(p2c) < 0 || pipe(c2p) < 0) {
    perror("Error creating pipe");
    exit(1);
  }


  if(argc != 3) {
    perror("Invalid number of arguments");
    exit(2);
  }

  //Get parameters
  char file[100], aux[100];
  strcpy(file, argv[1]);
  strcpy(aux, argv[2]);

  int n = (int)aux[0] - '0';
  

  //Create the child
  int pid = fork();
  if( pid < 0 ) {
    perror("Error creating child");
    exit(3);
  }

  if( pid == CHILD ) {
   //Close unused pipes
   close(p2c[WRITE]);
   close(c2p[READ]);

   //Get N from parent
   int n;
   read(p2c[READ], &n, sizeof(int));
   close(p2c[READ]);

   //Read a string
   char str[100];
   fgets(str, 100, stdin);

   //Only the first n elements matter
   str[n]='\0';

   //Send the result back to parrent
   write(c2p[WRITE], &str, sizeof(char) * 100);
   close(c2p[WRITE]);

  //Exit child
   exit(0);
  }

  //PARENT

  //Close unused pipes
  close(p2c[READ]);
  close(c2p[WRITE]);

  //Send n to child
  write(p2c[WRITE], &n, sizeof(int));
  close(p2c[WRITE]);

  //Receive answer from child
  char rasp[100];
  read(c2p[READ], &rasp, sizeof(char)*100);
  
  //Write answer to file
  FILE *f = fopen(file, "w");
  fprintf(f,"Answer is: %s\n", rasp);

  return 0;
}
