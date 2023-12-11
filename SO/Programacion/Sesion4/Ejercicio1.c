#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define ARCHIVO_FIFO "ComunicacionFifo"

int main(void){
    int fd;
    char buffer[80];
    int leidos;

    //Crear cauce con nombre (fifo) si no existe

    umask(0);
    mknod(ARCHIVO_FIFO, S_IFIFO|0666,0);
    
    //Tambien vale: mkfifo(ARCHIVO_FIFO,0666);

    //Abrir cauce para la lectura-escritura

    if( (fd=open(ARCHIVO_FIFO,O_RDWR))<0){
        perror("\nOpen");
        exit(EXIT_SUCCESS);
    } 

    //Aceptar datos a consumir hasta que se envíe la cadena fin

    while(1){
        leidos=read(fd,buffer,80);
        if(strcmp(buffer,"fin")==0){
            close(fd);
            return (EXIT_SUCCESS);
        }
        printf("\nMensaje recibido: %s\n", buffer);
    }
    return(EXIT_SUCCESS);
}