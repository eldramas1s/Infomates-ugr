#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char * argv[]){
    int fd[2];
    pid_t PID;

    pipe(fd);

    if ((PID=fork())<0){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(PID==0){
        close(fd[0]);
        close(STDOUT_FILENO);
        dup(fd[1]);
        execlp("ls","ls",NULL);
    }

    else{
        close(fd[1]);
        close(STDIN_FILENO);
        dup(fd[0]);
        execlp("sort","sort",NULL);
    }

    return EXIT_SUCCESS;
}