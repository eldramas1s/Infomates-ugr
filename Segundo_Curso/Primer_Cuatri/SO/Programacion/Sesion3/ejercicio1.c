#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main( int argc, char *argv[]){
	if(argc >2){
		printf("\nError en la llamada al programa");
		exit(EXIT_FAILURE);
	}
	
	int number=1;
	
	if(argc==2){
		number=strtol(argv[1],NULL,10);
	}
	
	int r_val;
	
	if((r_val=fork())<0){
		printf("\n Se ha producido el error %d", errno);
		perror("\nError al crear un proceso hijo");
		exit (EXIT_FAILURE);
	}
	
	if(r_val==0){
		char cad[50]="\nEl numero introducido es par\n";
		if(number%2!=0)
			strcpy(cad,"\nEl numero introducido es impar\n");
		
		if(write(STDOUT_FILENO,cad,strlen(cad)*sizeof(char))<0){
			printf("\nNo se ha podido escribir %s por pantalla",cad);
			perror("\nError en write hijo");
			exit(EXIT_FAILURE);
		}
	}
	
	if(r_val >0){
	
		char cad[50]="\nEs multiplo de 4";
		if(number%4!=0)
			strcpy(cad,"\nNo es multiplo de 4\n");
		if(write(STDOUT_FILENO,cad,strlen(cad)*sizeof(char))<0){
			printf("\nNo se ha podido escribir %s por pantalla,cad");
			perror("\nError en write padre");
			exit(EXIT_FAILURE);
		}
		
		exit(EXIT_SUCCESS);
	}
	return EXIT_SUCCESS;	
}
