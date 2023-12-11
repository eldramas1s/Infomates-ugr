/*
Define una macro en lenguaje C que tenga la misma funcionalidad que la macro S_ISREG(mode) usando para ello los flags definidos en <sys/sta.h> para el campo st_mode de la strct stat, y comprueba que funciona en un programa simple. Consulta en un libro de C o en internet como se especifica un amacre con argumento en C
	#define S_ISREG2(mode) ...
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#define S_ISREG2(mode)	(mode)==S_IFREG //NO POSIX
#define S_ISREG3(mode)	(mode)==(S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH) //NO POSIX

//Aparentemente deben ser iguales

//bool is_regular1(char * pathname){
//	
//	struct stat atributos;
//	if (lstat(pathname,&atributos)<0){
//		perror("Error al intentar acceder a los atributos");
//		exit (EXIT_FAILURE);
//	}
//	bool valor=S_ISREG2(atributos.st_mode);
//	return valor;
//}

bool is_regular2(char * pathname){
	
	struct stat atributos;
	if (lstat(pathname,&atributos)<0){
		perror("Error al intentar acceder a los atributos");
		exit (EXIT_FAILURE);
	}
	
	bool valor=S_ISREG3(atributos.st_mode);
	return valor;
}

int main(int argc, char * argv[]){
	
	char buf1[]="Es regular";
	char buf2[]= "No es regular";
	
	if (argc != 2){printf("\nNumero de parametros erroneo");exit(EXIT_FAILURE);}
	
	//if(is_regular1(argv[1])) printf("\n %s", buf1);
	//else printf("\n %s", buf2);
	
	if(!is_regular2(argv[1])) printf("\n %s", buf1);
	else printf("\n %s", buf2);
	
	return 0;
}	
	
	
	
	
