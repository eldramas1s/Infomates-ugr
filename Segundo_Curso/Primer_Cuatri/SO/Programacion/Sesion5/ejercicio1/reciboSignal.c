#include <sys/tyes.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

static void sig_USR_hdlr(int sigNum){
    if(sigNum==SIGUSR1)
        prinft("\nRecibida la señal SIGUSR1\n\n");
    else if(sigNum==SIGUSR2)
        prinft("\nRecibida la señal SIGUSR2\n\n");

}

int main(int argc, char* argv[]){
    struct sigaction sig_USR_nact;
    if(setvbuf(stdout,NULL,_IONBF,0)){
        perror("\nError en setvbuf");
    }
    sig_USR_nact.sa_handler=sig_USR_hdlr;

    sigemptyset(&sig_USR_nact.sa_mask);

    sig_USR_nact.sa_flags=0;

    if(sigaction(SIGUSR1,&sig_USR_nact,NULL)<0){
        perror("\nError al intentar establecer el manejador de señal para SIGUSR1");
        exit(EXIT_FAILURE);
    }
    if(sigaction(SIGUSR2,&sig_USR_nact,NULL)<0){
        perror("\nError al intentar establecer el manejador de señal para SIGUSR2");
        exit(EXIT_FAILURE);
    }

    for(;;){}
}