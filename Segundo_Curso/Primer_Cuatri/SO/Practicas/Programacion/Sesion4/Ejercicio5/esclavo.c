#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>


int EsPrimo(long primo){
    int esprimo=0;

    for(int i=2; i<=sqrt((double)primo)&&esprimo==0; ++i){
        if(primo%i==0)  esprimo=1;
    }

    return esprimo;
}

int main (int argc, char * argv[]){

    if(argc != 3){
        printf ("\n Necesito dos valores para consolidar un intervalo\n");
        perror("Error en la llamada al programa");
        exit (EXIT_FAILURE);
    }

    long init, final;

    init=strtol(argv[1],NULL,10);
    final=strtol(argv[2],NULL,10);

    //Calculamos los numeros primos;

    for(int i=init; i<=final ; ++i){
        if(EsPrimo(i)==0){
            write(STDOUT_FILENO,&i,sizeof(int));
            //if(write(STDOUT_FILENO,&i,sizeof(int))<0){
            //    perror("Error en write");
            //    exit(EXIT_FAILURE);
            //}
        }
    }

    return EXIT_SUCCESS;

}