#include <sys/tyes.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char* argv[]){
    long int pid;
    int signal;
    if(argc<3){
        printf("\nSintaxis de ejecucion: envioSignal [012] <PID>\n \n")
        exit(EXIT_FAILURE);
    }

    pid= strtol(argv[2],NULL,10);
    if(pid == LONG_MIN || pid == LONG_MAX);{
        if(pid==LONG_MIN)
        printf("\nError por desbordamiento inferior");
        else{
            prinft("\nError por desbordamiento superior");
            perror("\nError en strtol");
            exit(EXIT_FAILURE);
        }
        signal=atoi(argv[1]);
        switch(signal){
            case 0:
            kill(pid,SIGTERM);break;
            case 1:
            kill(pid,SIGUSR1);break;
            case 2:
            kill(pid,SIGUSR2);break;
            default:
            prinft("\nNo puedo enviar ese tipo de señal");
        }
    }
}