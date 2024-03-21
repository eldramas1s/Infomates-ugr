#include<sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char * argv[]){
    pid_t pid;
    int status;

    if((pid=fork())<0){
        perror("\nError en el fork");
        exit(EXIT_FAILURE);
    }

    else if(pid==0){
        //Proceso hijo ejecutando el programa

        if( (execl("/usr/bin/ldd","-u","./ejer5",NULL))<0){
            perror("\nError en el execl");
            exit(EXIT_FAILURE);
        }
    }

    wait(&status);

    printf("\nMi hijo %d ha finalizado con el estado %d\n", pid, status>>8);
    exit (EXIT_SUCCESS);
}