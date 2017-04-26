#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define READ_END 0
#define WRITE_END 1


int main(int argc, char *argv[]) {
    int actualArgc = argc -1;
    int p1[2], p2[2];
    char res[40960];

    if(pipe(p1) < 0 || pipe(p2) < 0 ) {
        perror("Error creating pipe");
        exit(1);
    }

    if(!actualArgc || actualArgc % 2 != 0) {
        perror("Invalid number of arguments");
    }

    int i;
    for(i = 1; i < argc; i += 2) {
        //Parent creates new son
        int pid = fork();

        if( pid == 0) {
            //Code for sun
            printf("child1: %d \n", getpid());

            //Redirect output to p1[1]
            dup2(p1[WRITE_END], STDOUT_FILENO);
            close(p1[WRITE_END]);

            //Exec the given command (throw output to stdout?)
            execlp("ls", "ls", NULL);
            printf("done1\n");
        } else {
            // Parent create a new son for the second command
            int pid2 = fork();

            if(pid2 == 0) {
                //Code for 2nd sun
                printf("child2: %d \n", getpid());

                //Redirect input from p1[0]
                dup2(p1[READ_END], STDIN_FILENO);
                close(p1[READ_END]);

                //Redirect output to p2[1]
                dup2(p2[WRITE_END], STDOUT_FILENO);
                close(p2[WRITE_END]);
                
                //Exec the given command (input taken from stdin, aka pipe)
                int code = execlp("grep", "grep", "a", NULL);
                printf("done2\n");
                printf("CODE: %d \n", code);
            }
        }
    }

    //Parent waits for sons to finish
    for(i = 1; i < argc; i += 2) {
        wait(0);
        wait(0);
       
        printf("GETS HERE\n");
        //Here get the output from pipe
        int nbytes = read(p2[READ_END], res, sizeof(res));
        printf("%s\n", res);
        printf("%d\n", nbytes);
    }


    getchar();
    return 0;
}
