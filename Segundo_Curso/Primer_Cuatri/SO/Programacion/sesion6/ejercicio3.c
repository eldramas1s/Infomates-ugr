#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char*argv[]){
    
    if(argc!=1){
        printf("\nLlamada al programa: ./ejer3 ");
        exit(-1);
    }
    char fichero[]="./tmp.txt";
    int fd;

    if((fd=open(fichero, O_RDWR))==-1){
        perror("\nNo se pudo abrier el fichero");
        exit(-1);
    }
    struct flock cerrojo;
    cerrojo.l_type=F_WRLCK;
    cerrojo.l_whence=SEEK_SET;
    cerrojo.l_start=0;
    cerrojo.l_len=0;
    //Vamos a bloquear todo el archivo.

    if(fork()==0){
        //Creamos hijo1
        if(fcntl(fd,F_SETLK,&cerrojo)!=0){
            perror("\nError al crear el cerrojo de escritura");
            exit(-1);
        }

        printf("\nSe ha creado el primer cerrojo");
        sleep(10);
        exit(EXIT_SUCCESS);
        //Se ha creado el cerrojo
    }

    sleep(1);//Dejamos que actue el cerrojo

    if(fork()==0){
        //Creamos hijo2

        if(fcntl(fd,F_SETLK,&cerrojo)!=0){
            perror("\nEl segundo cerrojo no se puede realizar, el kernel ha solucionado el interbloqueo\n");
            exit(-1);
        }
        printf("\nSe ha creado el segundo cerrojo\n");
        exit(EXIT_SUCCESS);
    }

    wait(NULL);
    wait(NULL);

    return (0);

}