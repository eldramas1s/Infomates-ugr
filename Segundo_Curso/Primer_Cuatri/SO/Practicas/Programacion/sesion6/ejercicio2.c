#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define CAUCE "|"

int main(int argc, char * argv[]){
    if(argc!=4){
        printf("\nEl programa se ejecuta: ./ejer2  <orden1> \"cauce\" <orden2>");
        exit(EXIT_FAILURE);
    }

    char orden1[100];
    strcpy(orden1,argv[1]);
    char orden2[100];
    strcpy(orden2,argv[3]);

    if(strcmp(argv[2],CAUCE)!=0){
        printf("\nEl programa se ejecuta: ./ejer2  <orden1> \"cauce\" <orden2>");
        exit(EXIT_FAILURE);
    }
    pid_t rval;
    int fd[2];
    pipe(fd);
    if((rval=fork())<0){
        perror("\nFallo en fork");
        exit(EXIT_FAILURE);
    }

    if(rval==0){
        close(fd[0]);
        close(STDOUT_FILENO);
        if(fcntl(fd[1],F_DUPFD,1)<0){
            perror("\nError en fcntl");
            exit(EXIT_FAILURE);
        }

        if(execlp(orden1,orden1,NULL)<0){
            perror("\nError en exec hijo");
            exit(-1);
        }
    }

    if(rval>0){
        close(fd[1]);
        close(STDIN_FILENO);
        if(fcntl(fd[0],F_DUPFD,0)<0){
            perror("\nError en fcntl");
            exit(EXIT_FAILURE);
        }

        if(execlp(orden2,orden2,NULL)<0){
            perror("\nError en exec hijo");
            exit(-1);
        }
    }

    return (EXIT_SUCCESS);
}
