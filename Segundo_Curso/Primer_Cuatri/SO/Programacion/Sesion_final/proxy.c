#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

#define FIFO_PROXY "./fifo_proxy"
#define BLOQUEO "./archivo_bloqueo"
#define BUFFER 1024

int main(int argc, char * argv[]){
    if(argc!=1){
        perror("\nLlamada a proxy: ./proxy");
        exit(EXIT_FAILURE);
    }

    //creamos fifo del proxy con el nombre solicitado
    char fifo_proxy[50];
    sprintf(fifo_proxy,"%s.%d",FIFO_PROXY,getpid());

    if(mkfifo(fifo_proxy,S_IFIFO)==-1){
        perror("\nNo se ha creado el archivo fifo del proxy-cliente");
        exit(EXIT_FAILURE);
    } 
    
    //?Abrimos el fifo(supongo)
    int fd_fifo_proxy;
    if((fd_fifo_proxy=open(fifo_proxy,O_RDONLY,S_IRWXU))<0){
        printf("\nError al abrir el fifo proxy");
        exit(EXIT_FAILURE);
    }

    //Hacemos que la entrada estandar sea el fifo;
    if(close(STDIN_FILENO)<0){
        perror("\nNo se va a poder realizar la entrada de fifo");
        exit(-1);
    }

    if(fcntl(fd_fifo_proxy,F_DUPFD,1)<0){
        perror("\n No se ha podido duplicar la entrada estandar para redirigirla al fifo proxy");
        exit(-1);
    }

    //Creamos el archivo temporal del fifo;
    FILE* fd_temp;

    if((fd_temp=tmpfile())==NULL){
        perror("\nNo se ha creado correctamente el archivo temporal");
        exit(-1);
    }

    //Leemos y escribimos en el archivo de bloqueo.
    int leidos;
    char buff[BUFFER];
    while((leidos=read(STDIN_FILENO,buff,BUFFER))>0){
        if(fwrite(buff,sizeof(char),leidos,fd_temp)<0){
            perror("\nNo se ha podido escribir en el archivo temporal");
            exit(-1);
        }
    }

    //Tratamos el archivo bloqueo

    int fd_bloqueo;

    struct flock lock;
    lock.l_type=F_WRLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start=0;
    lock.l_len=0;

    if((fd_bloqueo=open(BLOQUEO,O_RDWR,S_IRWXU))<0){
        printf("\nNo se ha podido abrir el archivo de bloqueo");
        exit(-1);
    }

    int tries=0;
    while(fcntl(fd_bloqueo,F_SETLK,&lock)<0){
        printf("\nIntentando bloquear el archivo %s",BLOQUEO);
        tries++;
        if(tries>1000){
            perror("\nNo se ha podido imponer el bloqueo");
            exit(-1);
        }
    }

    //Ya se ha impuesto el bloqueo, es decir, el archivo es mio.
    
    if(fseek(fd_temp,0,SEEK_SET)<0){
        perror("\nError al leer modificar el puntero de lestura/escritura");
        exit(-1);
    }

    while((leidos=fread(buff,sizeof(char),BUFFER,fd_temp))>0){
        if(write(STDOUT_FILENO,buff,leidos)<0){
            perror("\nNo se ha podido escribir por pantalla");
            exit(-1);
        }
    }

    //Desbloqueamos el archivo;

    lock.l_type=F_UNLCK;

    if(fcntl(fd_bloqueo,F_SETLKW,lock)<0){
        perror("\nNo se ha podido desbloquear el archivo.");
        exit(-1);
    }

    //Cerramos los archivos

    if(fclose(fd_temp)<0){
        perror("\nError al cerrar el archivo temporal");
        exit(-1);
    }
    if(close(fd_fifo_proxy)<0){
        perror("\nNo se ha podido cerrar el fifo");
        exit(EXIT_FAILURE);
    }

    if(unlink(fifo_proxy)<0){
        perror("\nNo se ha podido desanclar el fifo");
        exit(-1);
    }
}