#include <sys/tyes.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <strlib.h>
#include <string.h>

#define __USE_XOPEN_EXTENDED
#include <ftw.h>

const mode_t PERM=S_IXGRP|S_IXOTH;

long tot_size=0
long count_files = 0; 

int check_file(const char *path, const struct stat * atributos, int typeflag, struct FTW *ftwbuf){
	if ( (typeflag != FTW_D) && ( (atributos->st_mode & PERM) ==PERM)){
		printf("\t%-20s:\t %9lu\n", path, atributos->st_ino);
		coutn_files++;
		tot_size+=atributos->st_size;
	}
	return 0;
}

int main(itn argc, char * argv[]){
	
	if argc >2){
		printf("Uso de parametros erroneo");
		exit(EXIT_FAILURE);
	}
	
	
	char path_ini[100]=".";
	
	if (argc == 2)
		strcpy(path_ini, argv[1]);
	
	printf( "Los inodos son:\n";
	
	if (nftw(path_ini,check_file,10,FTW_PHYS) != 0){
		perror("Error en nftw");
		exit (EXIT_FAILURE);
	}
	
	
	printf("\nExisten %ld archivos regulares con permiso x para grupo y otros.\n", count_files);
	printf("El tamaño total ocupado por dichos archivos es %ld bytes.\n", tot_size);
	
	return EXIT_SUCCESS;
}
	
