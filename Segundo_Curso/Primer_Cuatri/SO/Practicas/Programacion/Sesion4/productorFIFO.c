#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define ARCHIVO_FIFO "ComunicacionFifo"

int main(int argc, char *argv[]){
    int fd; 

    if(argc!=2){
        printf("\nproductorFIFO: faltan argumentos(mensaje0)");
        printf("\nPruebe: productorFIFO <mensaje>, donde <mensaje> es una cadena de caracteres. \n");
        exit(EXIT_FAILURE);
    }
    if((fd=open(ARCHIVO_FIFO,O_WRONLY))<0){
        perror("\nError en open");
        exit(EXIT_FAILURE);
    }

    if((write(fd,argv[1],strlen(argv[1])+1))!=strlen(argv[1])+1){
        perror("\nError al escribir en el FIFO");
        exit(EXIT_FAILURE);
    }

    close(fd);

    return EXIT_SUCCESS;
}