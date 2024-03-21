#include <sys/types.c>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char * argv[]){
    int fd[2], numBytes;
    pid_t PID;
    char mensaje[]="\nEl primer mensaje transmitido por un cauce!!\n";
    char buffer [80];

    pipe(fd);

    if((PID=fork())<0){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(PID==0){
        close(fd[0]);
        write(fd[1],mensaje, strlen(mensaje)+1);
        exit(EXIT_SUCCESS);
    }

    else{
        close(fd[1]);
        numBytes=read(fd[0],buffer,sizeof(buffer));
        printf("\nEl numero de bytes recibidos es: %d",numBytes);
        printf("\nLa cadena enviada a través del cauce es: %s",buffer)
    }

    return EXIT_SUCCESS;
}