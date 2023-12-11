/* Implementa un programa que realice la siguiente funcionalidad. El programa acepta como argumento el nombre de un archivo (pathname), lo abre y lo lee en bloques de tamaño 80 bytes, y crea un nuevo archivo de salida, salida.txt, en el que debe aparecer la siguiente informacion:
	Bloque 1
	//Aquí van los primeros 80 Bytes del archivo pasado como argumento
	Bloque i
	/Aquí van los iésimos 80 Bytes del archivo pasado como argumento
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
	
	int fd_in,fd_out;
	
	if(argc != 2 && argc != 1){
		printf("\n Numero de parametros erroneo");
		exit ( EXIT_FAILURE);
	}
	
	if (argc == 2){
		char * pathname=argv[1];
		if((fd_in=open(	pathname, O_RDONLY))<0){
			printf("\nNo se ha abierto %s \n", argv[1]);
			perror("\n Error en open.");
			exit(EXIT_FAILURE);
		} 
	}
	
	else{
		fd_in=STDIN_FILENO;
	}
	
	//Abrimos salida
	char* path_salida="./salida.txt";
	if((fd_out=open(path_salida, O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR))<0){
		printf("\nError al abrir la salida %s",path_salida);
		perror("\n Error en open.");
		exit(EXIT_FAILURE);
	}
	
		
	int n_leidos,n_bloque=0;
	const int TAM_BLOCK=80;
	char buff[TAM_BLOCK];
	
	while((n_leidos=read(fd_in, buff, 80))>0){
		
		char cab[50];
		//Escribimos cabecera
		sprintf(cab, "\nBloque %d :\n", ++n_bloque);
		
		//Escribimos la cabecera
		write(fd_out, cab, strlen(cab));
		
		//Escribimos los 80 bytes
		
		write(fd_out, buff, n_leidos*sizeof(char));
	
	}
	
	close(fd_in);
	close(fd_out);
	
	return EXIT_SUCCESS;

}
