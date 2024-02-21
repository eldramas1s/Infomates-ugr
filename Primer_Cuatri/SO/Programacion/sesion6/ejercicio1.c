#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

const char SALIDA = '>';
const char ENTRADA = '<';
int main(int argc, char * argv[]){
    if(argc!=4){
        printf("\nEl programa se ejecuta: ./ejer1  <orden1> \"redireccion\" <fichero>");
        exit(EXIT_FAILURE);
    }

    char red;
    char orden[100];
    strcpy(orden,argv[1]);
    char fichero[100];
    strcpy(fichero,argv[3]);

    if(strcmp(argv[2],"<")!=0 && strcmp(argv[2],">")!=0){
        printf("\nEl programa se ejecuta: ./ejer1  <orden1> \"redireccion\" <fichero>");
        exit(EXIT_FAILURE);
    }

    red=(strcmp(argv[2],"<")==0)?'<':'>';

    int fd_e, fd_s;
    int flag_exec;
    if(red==SALIDA){
        if((fd_s=open(fichero,O_WRONLY))<0){
            perror("\nError en open 1");
            exit(EXIT_FAILURE);
        }
        fd_e=0; //Ponemos la entrada en la entrada estandar.
        if((flag_exec=fcntl(fd_s,F_GETFD))!=0){
            fcntl(fd_s,F_SETFD,0);//Limpiamos el close_on_exec para que mi proceso hijo herede los descriptores.
        }
        close(STDOUT_FILENO);
        if(fcntl(fd_s,F_DUPFD,1)<0){
            perror("\nError en la duplicacion de la salida");
            exit (EXIT_FAILURE);
        }
        execlp(orden,orden,NULL);

    }
    if(red==ENTRADA){
        if((fd_e=open(fichero,O_RDONLY))<0){
            perror("\nError en open 2");
            exit(EXIT_FAILURE);
        }

        fd_s=1;

        if((flag_exec=fcntl(fd_s,F_GETFD))!=0){
            fcntl(fd_e,F_SETFD,0); //Limpiamos el close_on_exec para que mi proceso hijo herede los descriptores
        }

        close(STDIN_FILENO);

        if(fcntl(fd_e,F_DUPFD,0)<0){
            perror("\nError en la duplicacion de la entrada");
            exit(EXIT_FAILURE);
        }

        execlp(orden,orden,NULL);
    }

    return (EXIT_SUCCESS);
}
