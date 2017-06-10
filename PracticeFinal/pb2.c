#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define READ 0
#define WRITE 1
#define CHILD 0

int main(int argc, char *argv[]) {
  int i, j;

  for(i = 1; i < argc; i++) {
    int p2c[2], c2p[2];

    if(pipe(p2c) < 0 || pipe(c2p) < 0 ) { 
      perror("Error creating pipe");
      exit(1);
    }

    //Get number from parameter;    
    char aux[100];
    strcpy(aux, argv[i]);
    int nr = 0;
    
    for(j = 0; j < strlen(aux); j++) {
      nr = nr * 10 + aux[j] -'0';
    }
    
    //Create the child
    int pid = fork();
    if(pid == CHILD) {
	//Closed unused buffers
	if(close(p2c[WRITE]) < 0 || close(c2p[READ]) < 0) { perror("Error closing pipe"); exit(11); }

        //Read data from parent
        int seconds = 0;
        if(read(p2c[READ], &seconds, sizeof(int)) < 0 ) { perror("Error reading"); exit(12); }
        if(close(p2c[READ]) < 0 ) { perror("Error closing"); exit(13); }
       
        printf("Thread %d starting to sleep for %d seconds \n", getpid(), seconds);
        sleep(seconds);
        printf("Thread %d finished sleeping\n", getpid());

        //Send data to parent
	int ok = 1;
        if(write(c2p[WRITE], &ok, sizeof(int)) < 0 ) { perror("Error writing"); exit(14); }
        if(close(c2p[WRITE]) < 0 ) { perror("Error closing pipe"); exit(15); }

        //Exit thread succesfully
        exit(0);
    }

    //Parent
    if(close(c2p[WRITE]) < 0 || close(p2c[READ]) < 0) {
      perror("error closing pipe");
      exit(1);
    }

    //send data to child
    if(write(p2c[WRITE], &nr, sizeof(int)) < 0) { perror("Error writing!"); exit(7); }
    if(close(p2c[WRITE]) < 0) { perror("Error closing pipe"); exit(10); }

    //read data from child
    int res;
    if(read(c2p[READ], &res, sizeof(int)) < 0) { perror("Error reading"); exit(8); }
    if(close(c2p[READ]) < 0 ) { perror("Error closing pipe"); exit(9); }
     
    //Done    
    if(res == 1)
    	printf("%d child finished\n", i);
    else
        printf("There has been a problem \n");
  }

  return 0;
    
}
