#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define READ_END 0
#define WRITE_END 1

void waitAndCheckReturnCode(int pid) {
    /*
     * Function waits for the process with given PID to end and
     */
    int status;

    if ( waitpid(pid, &status, 0) != -1 ) {
        if ( WIFEXITED(status) ) {
            int returned = WEXITSTATUS(status);
            printf("Exited normally with status %d\n", returned);
        }
        else if ( WIFSIGNALED(status) ) {
            int signum = WTERMSIG(status);
            printf("Exited due to receiving signal %d\n", signum);
        }
        else if ( WIFSTOPPED(status) ) {
            int signum = WSTOPSIG(status);
            printf("Stopped due to receiving signal %d\n", signum);
        }
        else {
            printf("Something strange just happened.\n");
        }
    }
    else {
        perror("waitpid() failed");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    int actualArgc = argc -1;
    int p1[2], p2[2];
    char res[40960];



    if(!actualArgc || actualArgc % 2 != 0) {
        perror("Invalid number of arguments");
        return 0;
    }

    int i;
    for(i = 1; i < argc; i += 2) {

        //Create two pipes for current iteration through arguments
        int p1[2], p2[2];

        if(pipe(p1) < 0 || pipe(p2) < 0 ) {
            perror("Error creating pipe");
            exit(1);
        }

        //Parent creates new son
        int pid = fork();

        if( pid == -1 ) {
            perror("Error when creating new process");
        }

        // =============== 1ST CHILD ====================
        if( pid == 0) {
            //Code for 1st SUN
            printf("PID1: %d \n", getpid());

            //Redirect output to p1[1]
            dup2(p1[WRITE_END], STDOUT_FILENO);

            close(p1[READ_END]);
            close(p2[WRITE_END]);
            close(p2[READ_END]);

            //Exec the given command (throw output to stdout)
            execlp("ls", "ls", NULL);

        }
        // =============== END 1ST CHILD ====================

        // Close pipes
        close(p1[READ_END]);
        close(p2[READ_END]);
        close(p1[WRITE_END]);
        close(p2[WRITE_END]);

        waitAndCheckReturnCode(pid);

        // Parent create a new son for the second command
        int pid2 = fork();
        if( pid2 == -1 ) {
            perror("Error when creating new process");
        }

        // =============== 2ND CHILD ====================
        if(pid2 == 0) {
            //Code for 2nd sun
            printf("PID2: %d \n", getpid());

            //Redirect input from p1[READ_END]
            dup2(p1[READ_END], STDIN_FILENO);
            close(p1[WRITE_END]);

            //Redirect output to p2[WRITE_END]
            dup2(p2[WRITE_END], STDOUT_FILENO);
            close(p2[READ_END]);

            //Exec the given command (input taken from stdin, aka pipe)
            execlp("sort", "sort", NULL);
            //execlp("head", "head", "-n", "3", NULL);
            exit(3);
        }
        // =============== 2ND CHILD ====================

        // Close pipes
        close(p1[READ_END]);
        close(p1[WRITE_END]);
        close(p2[WRITE_END]);

        //Wait for 2nd child to finish
        waitAndCheckReturnCode(pid2);

        //Print the result
        printf("Ready to print result\n");
        int nbytes = read(p2[READ_END], res, sizeof(res));
        printf("\nPair: %d  \n %s \n---\n", (i+1)/2, res);

        //Close remaining pipes
        close(p2[READ_END]);

        //Ready for next iteraton

    }

    getchar();
    return 0;
}
