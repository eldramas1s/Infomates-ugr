#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define SEÑAL SIGUSR1

int main(int argc, char*argv[]){

    if(argc!=1){
        printf("\nLlamada al programa: ./suspend\n");
        exit(EXIT_FAILURE);
    }
    sigset_t new_mask;
    sigfillset(&new_mask);

    sigdelset(&new_mask,SEÑAL);

    sigsuspend(&new_mask);

    //*No lo imprime
    printf("\nSeñal recibida\n");

    return (EXIT_SUCCESS);
}