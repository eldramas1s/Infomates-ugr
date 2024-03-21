#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char * argv[]){
	int r_val,proc_vivos=5;
	for( int i=0; i<5; ++i){
		if((r_val=fork())<0){
			printf("\nNo se ha podido crear el hijo %d", i);
			perror("\nError en fork()");
			exit(EXIT_FAILURE);
		}
		if(r_val==0){
			printf("\nSoy el hijo %d\n",getpid());
			//exit(EXIT_SUCCESS);
		}
	}
	int status,childpid;
	while (procs_vivos > 0){ // Espera a que todos los hijos finalicen. El orden de finalización no importa.

		if ((r_val = wait(NULL)) <= 0){
			printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
			perror("waitpid");
			exit(EXIT_FAILURE);
		}

		printf("Acaba de finilizar mi hijo con PID %d\n", _tval);
		printf("Solo me quedan %d hijos vivos\n", --procs_vivos);
	}
	
	return EXIT_SUCCESS;
}
