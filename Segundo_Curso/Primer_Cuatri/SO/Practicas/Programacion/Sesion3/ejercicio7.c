#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    //TOMA DE ARGUMENTOS

    //COmprobacion numero y correccion argumentos
    if(argc <2 || strcmp(argv[1],"bg")==0){
        printf("\n Introduzca un programa a ejercutar");
        exit(EXIT_FAILURE);
    }

    char bg='n';    //Flag de background
    //char program[100];
    //strcpy(argv[1],program);
    char *matriz[argc-1]; 
    for ( int i=0; i<argc-1; ++i){
        matriz[i]=argv[i+1];
    }

    if((argc>2)&&(strcmp(argv[argc-1],"bg")==0)){
        bg='y';
        matriz[argc-2]=NULL;
    }
    else{
        matriz[argc-1]=NULL;
    }

    //EJECUCION DEL PROGRAMA
    int r_val;
    if((r_val=fork())<0){
        printf("\nNo se ha podido crear el hijo");
        perror("\nError en fork");
        exit (EXIT_FAILURE);
    }

    if(r_val==0){
        //Estoy en el hijo

        if((execvp(matriz[0],matriz))<0){
            printf("\nNo se ha podido ejecutar el programa %s", matriz[0]);
            perror("\nError en execvp");
            exit (EXIT_FAILURE);
        }

    }
   if(wait(NULL)<0){
        printf("\nNo ha acabado el hijo, ha habido una interrupcion o un fallo");
        perror("\nError en wait");
        exit (EXIT_FAILURE);
   }
    if(bg=='y'){
        printf("\nEl programa pasado como argumento se ha ejecutado en background");
    }

    else
        printf("\nEl programa pasado como argumento se ha ejecutado en foreground.");
    
    return EXIT_SUCCESS;
}