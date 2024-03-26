#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

//!Se asume que el archivo es de caracteres y que el segundo es regular
int Copiamem(char*copiador, char*receptor){
    int fd_cp,fd_rp;
    struct stat st_cp;

    //Trabajamos con el archivo a copiar haciendo la proyeccion.
    if((fd_cp=open(copiador, O_RDONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH))==-1){
        printf("\nNo se pudo abrir el archivo %s a copiar",copiador);
        return -1;
    }

    if(fstat(fd_cp,&st_cp)==-1){
        printf("\nError al hacer stat de %s",copiador);
        return -1;
    }

    //Comprobamos que es un archivo de caracteres

    if(!S_ISREG(st_cp.st_mode)){
        printf("\nEl archivo a copiar no es un archivo regular");
        return -1;
    }

    int tam_cp;

    tam_cp=st_cp.st_size;
    if(tam_cp==0){
        printf("\nEl archivo a copiar esta vacio");
        return -1;
    }
    char* cp;
    char* rp;

    //Hacemos el mapeo del fichero
    //*Solo permito la lectura de los datos(creo que la escritura de los mismos no es necesaria)
    cp=(char*)mmap(NULL,tam_cp,PROT_READ,MAP_SHARED,fd_cp,0);

    if(cp==MAP_FAILED){
        printf("\nError al crear el mapeo de la copia de %s ", copiador);
        return -1;
    }
    //Ya podemos cerrar el archivo a 
    
    if(close(fd_cp)==-1){
        printf("\nNo se pudo cerrar el archivo %s",copiador);
        return -1;
    }

    //Trabajamos sobre el archivo receptor creando de nuevo la zona de memoria.

    //*abrimos el archivo
    if((fd_rp=open(receptor, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH))==-1){
        printf("\nNo se pudo abrir el archivo %s a copiar",receptor);
        return -1;
    }

    //*Lo truncamos al tamaño correcto

    if(ftruncate(fd_rp,tam_cp)==-1){
        printf("\nNo se ha podido truncar el archivo %s", receptor);
        return -1;
    }

    rp=(char*)mmap(NULL,tam_cp,PROT_WRITE,MAP_SHARED,fd_rp,0);

    if(rp==MAP_FAILED){
        printf("\nError al crear el mapeo del receptor %s", receptor);
        return -1;
    }
    //Ya podemos cerrar el archivo receptor

    if(close(fd_rp)==-1){
        printf("\nNo se pudo cerrar el archivo %s",receptor);
        return -1;
    }

    if(memcpy(rp,cp,tam_cp)!=rp){
        printf("\nNo se ha podido realizar la copia de memoria");
        return -1;
    }
    
    //Todo se ha hecho a la perfeccion
    return 0;
}

int main(int argc, char*argv[]){

    if(argc!=3){
        printf("\nLlamada al programa: ./ejer5 <copiador> <receptor>\n");
        exit(-1);
    }

    if(Copiamem(argv[1],argv[2])==-1){
        printf("\nNo se ha podido realizar la copia de memoria");
        exit(-1);
    }

    return 0;
}