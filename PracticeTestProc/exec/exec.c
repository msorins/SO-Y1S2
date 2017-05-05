#include <unistd.h>

int main()
{
  char *const paramList[] = {"/bin/ls", "-l", "-a", NULL}; 
  execv("/bin/ls", paramList);
}
