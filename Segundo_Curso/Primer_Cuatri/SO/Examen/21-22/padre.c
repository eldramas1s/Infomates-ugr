#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#define TERMINADOR "fin"

static void manejador(int sigNum)
{
    if (sigNum == SIGCHLD)
    {
        wait(NULL);
    }
}

int main(int argc, char *argv[])
{
    int seguir = 1;
    char cad[100];
    int num;

    // Establecemos el manejador de señales
    if (signal(SIGCHLD, manejador) == SIG_ERR)
    {
        perror("\nNo se ha podido establecer el manejador de señales");
        exit(-1);
    }

    while (seguir)
    {
        scanf("%s", cad);

        if (strcmp(cad, TERMINADOR) == 0)
            seguir = 0;

        else
        {
            num = strtol(cad, NULL, 10);
            char arg[10];
            sprintf(arg, "%d",num);
            // Creamos hijo 1;
            pid_t r_val;
            if ((r_val = fork()) < 0)
            {
                perror("\nError al crear el proceso hijo");
                exit(-1);
            }
            if (r_val == 0)
            {
                // Le mandamos el trabajo al hijo 1
                if (execlp("./hijo", "./hijo", arg, NULL) < 0)
                {
                    perror("\nNo se ha podido ejecutar al hijo1.");
                    exit(-1);
                }
            }

            // Creamos hijo2;

            if ((r_val = fork()) < 0)
            {
                perror("\nError al crear el proceso hijo2");
                exit(-1);
            }
            
            if(r_val==0){
                if(execlp("./nieto","./nieto",arg,NULL)<0){
                    perror("\nError al ejecutar hijo2");
                    exit(-1);
                }
            }
        }
    }

    return 0;
}