#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define READ_END 0
#define WRITE_END 1

void splitArgv(char *arg, char *cmd, char*  argMat[]) {
    int crtLine = 0, i = 0, crtLength = 0;
    argMat[crtLine] = malloc(sizeof(char) * 100);

    for(i = 0; i < strlen(arg); i++) {
        if(isalpha(arg[i]) || arg[i] == '-' || arg[i] == '/' || isdigit(arg[i])) {
            argMat[crtLine][crtLength] = arg[i];
            if(!crtLine)
                cmd[crtLength] = arg[i];

            crtLength++;
        }
        else if (arg[i] == ' ') {
            argMat[crtLine][++crtLength]='\0';
            if(!crtLine)
                cmd[crtLength]='\0';

            crtLine++;
            argMat[crtLine] = malloc(sizeof(char) * 100);
            crtLength=0;
        }

    }

    argMat[++crtLine] = NULL;
}

void waitAndCheckReturnCode(int pid) {
    /*
     * Function waits for the process with given PID to end and
     */
    int status;

    if ( waitpid(pid, &status, 0) != -1 ) {
        if ( WIFEXITED(status) ) {
            int returned = WEXITSTATUS(status);
            if(status != 0 ) {
                printf("%d", returned);
                perror("Something wrong with your command");
                exit(8);
            }
        }
        else if ( WIFSIGNALED(status) ) {
            int signum = WTERMSIG(status);
            perror("Something wrong happned");
            exit(9);
        }
        else if ( WIFSTOPPED(status) ) {
            int signum = WSTOPSIG(status);
            perror("Something wrong happned");
            exit(10);
        }
        else {
            perror("Something really wrong happned");
            exit(11);
        }
    }
    else {
        perror("waitpid() failed");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    int actualArgc = argc -1;
    char res[40960];


    //Check the argments
    if(!actualArgc || actualArgc % 2 != 0) {
        perror("Invalid number of arguments");
        exit(1);
    }

    int i;
    for(i = 1; i < argc; i += 2) {
        //Initialise the pipes
        int p1[2], p2[2];
        if(pipe(p1) < 0 || pipe(p2) < 0 ) {
            perror("Error creating pipe");
            exit(2);
        }

        //Parent creates new son
        int pid = fork();

        if( pid == -1 ) {
            perror("Error when creating new process");
            exit(3);
        }

        // ================= 1ST SON =================
        if( pid == 0) {
            //Code for sun

            //Redirect output to p1[1]
            dup2(p1[WRITE_END], STDOUT_FILENO);

            //Close pipes
            close(p1[READ_END]);
            close(p2[WRITE_END]);
            close(p2[READ_END]);

            //Split the arguments
            char *cmd = malloc(sizeof(char) * 100);
            char *argMat[1000];
            splitArgv(argv[i], cmd, argMat);

            //Exec the given command (throw output to stdout)
            execv(cmd, argMat);

            //Should not get here
            exit(13);
        }
        // ================= END 1ST SON =================


        //Wait for 1st son to exit
        waitAndCheckReturnCode(pid);


        //Create the 2nd son
        int pid2 = fork();
        if( pid2 == -1 ) {
            perror("Error when creating new process");
            exit(4);
        }


        // ================= 2ND SON =================
        if(pid2 == 0) {
            //Code for 2nd sun

            //Redirect input from p1[0]
            dup2(p1[READ_END], STDIN_FILENO);
            close(p1[WRITE_END]);

            //Redirect output to p2[1]
            dup2(p2[WRITE_END], STDOUT_FILENO);
            close(p2[READ_END]);

            //Split the arguments
            char *cmd = malloc(sizeof(char) * 100);
            char **argMat = malloc(sizeof(char*) * 100);

            splitArgv(argv[i + 1], cmd, argMat);

            //Exec the given command (input taken from stdin, aka pipe)
            execv(cmd, argMat);

            //Should not get here
            exit(14);
        }
        // ================= END 2ND SON =================

        //Close pipes before waiting 2nd son to exit
        close(p1[READ_END]);
        close(p1[WRITE_END]);
        close(p2[WRITE_END]);

        //Wait for 2nd son to exit
        waitAndCheckReturnCode(pid2);

        //Print the result
        int nbytes = read(p2[READ_END], res, sizeof(res));
        printf("\nResult from pair: %d \n%s \n---\n", (i+1)/2, res);

        //Close all pipes
        close(p2[READ_END]);

        //Ready for next iteration

    }

    getchar();
    return 0;
}
