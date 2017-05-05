#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  char *xFifo = "./xfifo.txt";
  char *yFifo = "./yfifo.txt";
  
  //Create the FIFO
  mkfifo(xFifo, 0777);
  mkfifo(yFifo, 0777);
 
  //Open the FIFO
  int x = open(xFifo, O_RDONLY);
  int y = open(yFifo, O_WRONLY);

  //Initiate the loops
  int step=0;
  write(y, &step, sizeof(int));

  //Actual counting loop
  while(1)
  {
   read(x, &step, sizeof(int));

   printf("X: %d\n", step);
   step++;

   write(y, &step, sizeof(int));
  }

}
