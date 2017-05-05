//Primeste n argumente cuvinte
//Pentru fiecare cuvant creeaza un proces care afiseaza PID-ul propriu si cuvantul
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define READ 0
#define WRITE 1
#define CHILD 0

int main(int argc, char *argv[])
{
   int i;

   for(i = 1; i < argc; i++) {
     int p2c[2], c2p[2];
     
     //Create pipe
     if(pipe(p2c) < 0 || pipe(c2p) < 0) {
       perror("Error creating pipe");
       exit(1);
     }

     //Create child
     int pid = fork();

     if(pid == CHILD) {
       //Close unused pipes
       close(p2c[WRITE]);
       close(c2p[READ]); close(c2p[WRITE]);

       //Read from parrent
       char crtArg[100];
       int n;

       read(p2c[READ], &n, sizeof(int));
       read(p2c[READ], &crtArg, sizeof(char) * n);
       close(p2c[READ]);

       //Output result
       crtArg[n]='\0';
       printf("Current pid %d. Received argument %s\n", getpid(),crtArg);
       exit(0); 
     }

     //Parent
     //Close unused PIPES
     close(p2c[READ]);
     close(c2p[READ]); close(c2p[WRITE]);

     //Send current argument to child
     char crtArg[100];
     strcpy(crtArg, argv[i]);

     int n;
     n = strlen(crtArg);
     write(p2c[WRITE], &n, sizeof(int));
     write(p2c[WRITE], &crtArg, sizeof(char) * n );
     close(p2c[WRITE]);

     wait(0);
   }

   return 0;
}
