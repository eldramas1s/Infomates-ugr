#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        printf("\nLlamada al programa: ./ejer4 <fichero_vacio>");
        exit(-1);
    }

    int fd;
    struct flock cerrojo;
    cerrojo.l_type=F_WRLCK;
    cerrojo.l_len=0;
    cerrojo.l_start=0;
    cerrojo.l_whence=SEEK_SET;

    //*Apertura del fichero
    if((fd=open(argv[1],O_RDWR))==-1){
        perror("\nNo se pudo abrir el archivo");
        exit(-1);
    }

    //*Comprobacion del que el fichero está vacío
    if(lseek(fd,0,SEEK_END)!=0){
        printf("\nEl archivo %s no está vacio\n",argv[1]);
        exit(-1);
    }
    //*Si está vacío, el puntero de lectura y escritura estará en la primera posicion del archivo, ya que SEEK_SET=SEEK_END

    //Implantamos el cerrojo

    if(fcntl(fd,F_SETLK,&cerrojo)==-1){
        perror("\nError el implantar el cerrojo\n");
        exit(-1);
    }

    printf("\nSe ha implantado el cerrojo sobre el archivo\n");
    //*Si hemos llegado aquí es porque se ha implantado el cerrojo

    //En lugar de usar un bucle infinito, para poder cerrar exhaustivamente el fichero, se dara un período de tiempo en el que se 
    //podrá comprobar que no se puede crear otro programa que haga esto, en caso de hacerlo, el kernel soluciona un interbloqueo.

    sleep(15);

    //!Desbloqueamos el cerrojo

    if(fcntl(fd,F_UNLCK,&cerrojo)==-1){
        perror("\nError al desbloquear el archivo");
        exit(-1);
    }

    printf("\nSe ha desbloqueado el cerrojo");

    if(close(fd)!=0){
        perror("\nNo se ha podido cerrar el archivo");
        exit(-1);
    }

    return 0;
}