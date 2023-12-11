#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<limits.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char * argv[])
{
	//Comprobacion de llamada al programa
	if (argc != 3){
	
		printf(stderr, "Use argumentos correctos.:", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	//Comrobacion de llamada al programa
	if(strlen(argv[2]) != 4){
		printf("No es un numero en base octal");
		exit (EXIT_FAILURE);
	}
	
	//Comprobacion y toma de permisos
	char * invalid;
	mode_t new_perm=strtol(argv[2], &invalid, 8);
	
	if ( new_perm = '\0'){
		printf("Se han tomado mal los permisos");
		exit(EXIT_FAILURE);
	}
	
	//Abrimos el directorio
	DIR *directory;
	if ((directory=opendir(argv[1])) == NULL){
		printf("Se ha abierto mal el directorio");
		perror("\nError al abrir el archivo");
		exit (EXIT_FAILURE);	
	}
	
	errno = 0;
	const mode_t MASK_PERM = S_IRWXU | S_IRWXG | S_IRWXO | S_ISGID | S_ISUID | S_ISVTX;	//Obtencion de los permisos
	struct dirent *entrada;	//Puntero al directorio
	struct stat atributos; 	//Aqui estaran los atricutos de cada archivo
	
	while((entrada=readdir(directory))!=NULL){
		//Obtener permisos antiguos usamos lstat
		
		if(lstat(entrada->d_name, &atributos) <0){
			printf("\nError %d al intentar acceder a los atributos de %s.\n", errno, entrada->d_name);
			perror("\nError en lsata");
			exit(EXIT_FAILURE);
		}
		
		if (!SI_ISDIR(atributos.st_mode)){
			mode_t old_perm = atributos.st_mode & MASK_PERM;
			if(chmod(entrada->d_name, new_perm) <0){
				printf("No se han podido cambiar los permisos");
			}
			else{
				printf("No ha habido error");
			}
		}
		
		errno = 0;
	}
	
	if (errno != 0){
		printf( "Error en readdir");
		perror ("\n Error terminal en readdir");
		exit(EXIT_FAILURE);
	}
	
	closedir(directory);
	
	return EXIT_SUCCESS;
}

