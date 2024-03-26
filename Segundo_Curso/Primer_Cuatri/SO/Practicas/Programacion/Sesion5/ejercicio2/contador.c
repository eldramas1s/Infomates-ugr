#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

#define SEÑALES 9
int contadores[SEÑALES];

static void sig_USR_hdlr(int sigNum){
    if(sigNum<=0 || sigNum >= 9){
        printf("\nLa señal %d no la puedo manejar\n",sigNum);
    }
    ++contadores[sigNum];
    printf("\nLa señal %d se ha recivido %d veces\n",sigNum,contadores[sigNum]);
    printf("\nEsperando señales...\n");
}

int main(int argc, char*argv[]){
    struct sigaction sig_nact;
    if(setvbuf(stdout,NULL,_IONBF,0)){
        perror("\nError en setvbuf");
    }

    sig_nact.sa_handler=sig_USR_hdlr;

    sigemptyset(&sig_nact.sa_mask);

    sig_nact.sa_flags=0;

    for (int i=0; i<SEÑALES; ++i){
        contadores[i]=0;
    }
    for(int signal=1; signal<9; ++signal ){
        if(sigaction(signal,&sig_nact,NULL)<0){
        printf("\nError al intentar establecer el manejador de señal para %d\n",signal);
        exit(EXIT_FAILURE);
    }
    }
    for(;;){}
}