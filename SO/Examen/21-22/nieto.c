#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define SALIDA "salida.txt"

int main (int argc, char*argv[]){
    if(argc!=2){
        perror("\nError de llamada al programa");
        exit(-1);
    }
    int num=strtol(argv[1],NULL,10);
    int fd;

    if((fd=open(SALIDA,O_RDWR|O_CREAT|O_TRUNC,S_IRWXU))<0){
        perror("\nNo se ha podido abrir el archivo de solo escritura");
        exit(-1);
    }

    
    if(dup2(STDOUT_FILENO,fd)<0){
        perror("\nNo se ha duplicado la salida estandar");
        exit(-1);
    }
    if(write(fd,&num,sizeof(int))<0){
        perror("\nerror al escribir");
        exit(-1);
    }

    printf("%d ",num);

    //mode_t new_perm=642;

    /*if(fchmod(fd,new_perm)<0){
        perror("\nNo se pueden cambiar los permisos de un archivo");
        exit(-1);
    }*/

    if(close(fd)<0){
        perror("\nNo se ha cerrado el descriptor de archivo");
        exit(-1);
    }

    return 0;
}