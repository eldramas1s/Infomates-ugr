
/*

*/

#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>

static void handler(int sigNum){
    if(sigNum==SIGCHLD){
        wait(NULL);
    }
}

/*
    Calcula el numero de bloques del archivo pasado como argumento
    path: ruta del archivo
    -1 si hay error, 0 si todo ha salido bien.
*/
int du(char*path){
    struct stat atributos;
    if(stat(path,&atributos)<0){
        perror("\nError al obtener los atributos");
        return -1;
    }
    int bl=atributos.st_blocks;
    printf("\n%d",bl);

    return 0;
    
}

int main(int argc, char* argv[]){

    if(argc<=1){
        printf("\nLlamada al programa: ./du <Ficharch1> <Ficharch2>");
        exit(-1);
    }

    if(signal(SIGCHLD,handler)==SIG_ERR){
        perror("\nError al establecer el manejador de señal\n");
        exit(-1);
    }

    //Comprobamos que todos los archivos son regulares

    int fd[2];

    pipe(fd);
    int blcks=0;
    for(int i=1; i<argc; ++i){
        
        pid_t r_val;
        if((r_val=fork())<0){
            perror("\nNo se ha podido crear un hijo.");
            exit(-1);
        }

        //Trabajamos con el hijo
        if(r_val==0){

            close(fd[0]);
            close(STDOUT_FILENO);
            if(fcntl(fd[1],F_DUPFD,1)<0){
                perror("\nNo se ha podido duplicar la salida estandar");
                exit(-1);
            }
            if(du(argv[i])<0){
                printf("\nNo se ha podido ejecutar du sobre el archivo %s", argv[i]);
                exit(-1);
            }

            /*
                if(execlp("/usr/bin/du","du","-k",argv[i],NULL)<0){
                    perror("\nNo se ha ejecutado la orden du");
                    exit(-1);
                }
            */
        }
    }

    close(fd[1]);
    close(STDIN_FILENO);
    if(fcntl(fd[0],F_DUPFD,0)<0){
        perror("\nNo se ha podido duplicar la entrada estandar");
        exit(-1);
    }

    for(int i=1; i<argc; ++i){
        if(read(STDIN_FILENO,&blcks,sizeof(int))<0){
            perror("\nNo se ha leido bien del cauce");
            exit(-1);
        }

        printf("\nEl archivo %s tiene %d bloques.\n",argv[i],blcks);
    }

    return 0;
}