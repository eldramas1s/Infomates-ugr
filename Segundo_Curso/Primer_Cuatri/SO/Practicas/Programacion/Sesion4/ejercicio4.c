#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]){
    int fd[2];
    pid_t PID;

    pipe(fd);

    if((PID=fork())<0){
        perror("Fork");
        exit(EXIT_FAILURE);
    }

    if(PID==0){
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls",NULL);
    }

    else{
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        execlp("sort","sort",NULL);
    }

    return EXIT_SUCCESS;
}