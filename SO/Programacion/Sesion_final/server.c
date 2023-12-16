/*
    Servidor del spool de impresión, es el programa que controla todos los demas elementos.
    Lenguaje: C
    Autor: Lucas Hidalgo Herrera
    Fecha de creación: dic 12, 2023
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define FIFO "./fifo_conocido"
#define SOLICITUD "Nuevo cliente"
#define PROXY "./proxy"
#define BLOQUEO "./archivo_bloqueo"

//establecemos un manejador de señales.
static void manejador(int sigNum){
    if(sigNum==SIGCHLD){
        waitpid(-1,NULL,WNOHANG);
    }
    
}

int main(int argc,char*argv[]){

    //Comprobacion de llamada al servidor
    if (argc!=1){
        perror("\nLlamada al servidor: ./server");
        exit (-1);
    }

    //Creacion del cauce cliente-server

    if(mkfifo(FIFO,0666)==-1){
        printf("\nError al crear el archivo fifo %s", FIFO);
        exit(-1);
    }

    if(signal(SIGCHLD,manejador)==SIG_ERR){
        perror("\nError al imponer el manejador");
        exit(EXIT_FAILURE);
    }

    //Abrimos el fifo de entrada
    int fifo_in,fifo_out;
    if((fifo_in=open(FIFO,O_RDONLY,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH))==-1){
        printf("\nError al abrir el archivo fifo %s",FIFO);
        exit(-1);
    }
    
    //Abrimos el archivo de bloqueo
    if((creat(BLOQUEO,S_IRWXU))==-1){
        perror("\nNo se ha podido crear el archivo de bloqueo.");
    }
    //Imponemos que el puntero esté al principio
    if(lseek(fifo_in,SEEK_SET,0)==-1){
        perror("\nNo se ha establecido el puntero de lectura al inicio");
        exit(-1);
    }

    //Abrimos el fifo de salida.
    if((fifo_out=open(FIFO,O_CREAT|O_WRONLY))<0){
        perror("\nError al abrir el fifo de salida");
        exit(EXIT_FAILURE);
    }
    //Lectura de un nuevo cliente
    pid_t r_val;
    char buffer_reception[14];
    while(read(fifo_in,buffer_reception,sizeof(SOLICITUD))!=0 ){
        //!Solo permitimos que en dicho archivo se escriba la cadena SOLICITUD

        if(strcmp(buffer_reception,SOLICITUD)!=0){
            printf("\nSe ha encontrado una cadena erronea de solicitud de cliente %s", buffer_reception);
            exit(-1);
        }

        printf("\nSe ha leido la solicitud de un nuevo cliente.");

        //Como se ha leido la solicitud correcta, llama al proxy.

        if((r_val=fork())==-1){
            perror("\nError al crear un proceso proxy");
            exit(EXIT_FAILURE);
        }
        if(r_val==0){
            if(execlp(PROXY,PROXY,NULL)==-1){
                perror("\nNo se ha podido ejecutar el proxy");
                exit(EXIT_FAILURE);
            }
        }
        if(r_val>0){
            if(write(fifo_out,&r_val,sizeof(r_val))!=sizeof(r_val)){
                perror("\nNo se ha podido escribir el pid en el fifo de salida.");
                exit(EXIT_FAILURE);
            }
        }

    } 

    if(close(fifo_in)<0){
        perror("\nNo se ha cerrado el fifo de entrada");
        exit(-1);
    }

    if(close(fifo_out)<0){
        perror("\nNo se ha cerrado el fifo de entrada");
        exit(-1);
    }
    
    if (inlink(FIFO)<0){
        perror("\nNo se ha podido desanclar el fifo de entrada");
    }
    
    return 0;
}