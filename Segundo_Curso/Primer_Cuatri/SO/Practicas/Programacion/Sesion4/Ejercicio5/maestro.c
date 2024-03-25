#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char * argv[]){
    if (argc !=3){
        errno=1;
        printf ("\n Necesito dos valores para consolidar un intervalo\n");
        perror("Error en la llamada al programa");
        exit (EXIT_FAILURE);
    }

    int init, final;

    init=atoi(argv[1]);
    final=atoi(argv[2]);

    int mitad= (init + final)/2;

    int fd1[2],fd2[2];

    pid_t PID_1,PID_2;

    char in[10];
    char fin[10];

    //esclavo1
    pipe(fd1);
    sprintf(in,"%d", init);
    sprintf(fin,"%d", mitad);
    if((PID_1=fork())<0){
        perror("\nError en fork esclavo1");
        exit(EXIT_FAILURE);
    }

    if(PID_1==0){
        close(fd1[0]);
        dup2(fd1[1],STDOUT_FILENO);

        execlp("./esclavo","./esclavo",in,fin,NULL);
    }

    else{
        close(fd1[1]);
        dup2(fd1[0],STDIN_FILENO);
        int leidos=0;
        int primo;
        while((leidos=read(fd1[0],&primo,sizeof(int)))>0){
            //if(write(STDOUT_FILENO,&primo,sizeof(int))<0){
            //    perror("\nError en write");
            //    exit(EXIT_FAILURE);
            //}
            printf("\n%i",primo);
        }

        close(fd1[0]);
    }

    //esclavo2

    pipe(fd2);
    
    if((PID_2=fork())<0){
        perror("\nError en fork esclavo2");
        exit(EXIT_FAILURE);
    }
    mitad++;
    sprintf(in,"%d", mitad);
    sprintf(fin,"%d", final);
    if(PID_2==0){
        close(fd2[0]);
        dup2(fd2[1],STDOUT_FILENO);
        
        execlp("./esclavo","./esclavo",in,fin,NULL);
    }

    else{
        close(fd2[1]);
        dup2(fd2[0],STDIN_FILENO);
        int leidos=0;
        int primo;
        while((leidos=read(fd2[0],&primo,sizeof(int)))>0){
            while((leidos=read(fd1[0],&primo,sizeof(int)))>0){
                //if(write(STDOUT_FILENO,&primo,sizeof(int))<0){
                //    perror("\nError en write");
                //    exit(EXIT_FAILURE);
                //}
                printf("\n%i",primo);
            }
        }
        close(fd2[0]);
    }

    return EXIT_SUCCESS;
}