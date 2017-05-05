//Creeaza un fiu, fiul citeste de la tastatura numele unui fisiere
//Trimite numele fisierului catre parinte
//Parintele calculeaza dimensiunea acelui fisier si o transmite printr-un alt pipe fiului
//Care afiseaza
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

#define READ 0
#define WRITE 1
#define CHILD 0

int main(int argc, char *argv[])
{
   int p2c[2], c2p[2];
   
   //Create the pipe
   if(pipe(p2c) < 0 || pipe(c2p) < 0) {
     perror("Error creating pipe");
     exit(1);
   }

   int pid = fork();

   if(pid < 0 ) {
     perror("Error creating child");
     exit(2);
   }

   if(pid == CHILD) {
     //Close unused pipes
     close(c2p[READ]);
     close(p2c[WRITE]);

     //Read file name
     char fisier[100];
     scanf("%s", fisier);

     //Send filename to parent
     write(c2p[WRITE], &fisier, sizeof(char) * 100);
     close(c2p[WRITE]);

     //Receive response from parrent
     int size;
     read(p2c[READ], &size, sizeof(int));
     close(p2c[READ]);
     
     //Write result
     printf("File size: %d\n", size);
     exit(0);
   }

   //PARENT
   //Close unused pipes
   close(c2p[WRITE]);
   close(p2c[READ]);

   //Read the file from child
   char fisierP[100];
   read(c2p[READ], &fisierP, sizeof(char) * 100);
   close(c2p[READ]);

   //Compute dimension of given file
   struct stat st;
   stat(fisierP, &st);
   int sizeP = st.st_size;

   //Write dimension to child
   write(p2c[WRITE], &sizeP, sizeof(int));
   close(p2c[WRITE]);

   return 0;
}
