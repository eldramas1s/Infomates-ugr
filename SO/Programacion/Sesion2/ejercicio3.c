#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>		// Needed por managing directories

void busqueda_directorios(const char * path_dir, long * count_files, long* tot_size, const mode_t PERM){

	DIR * directorio;
	if ((directorio=opendir(path_dir))==NULL){
		printf("\nNo se ha podido abrir el directorio %s", path_dir);
		perror("\nError en opendir.");
		exit(EXIT_FAILURE);
	}
	
	errno=0;
	
	struct dirent* entrada;
	struct stat atributos;
	
	while((entrada=readdir(directorio))!=NULL){
		
		if((strcmp(path_dir, ".")==0)||(strcmp(path_dir,"..")==0)) continue;
		
		char path_entrada[500];
		sprintf(path_entrada, "%s/%s",path_dir,entrada->d_name);
		if(lstat(path_entrada, &atributos)<0){
			printf("\Error %d al intentar tomar los atributos de %s", errno, path_entrada);
			perror("\nError en lstat.");
			exit(EXIT_FAILURE);
			
		}
		
		if (S_ISDIR(atributos.st_mode))
			busqueda_directorios(path_entrada,count_files,tot_size,PERM);
			
		else if((atributos.st_mode & PERM)==PERM){
			printf("\t%-20s:\t %9lu\n", path_entrada, entrada->d_ino);
			(*count_files)++;
			(*tot_size)+=atributos.st_size;
		}
		errno=0;
	}
	
	if(errno != 0){
		printf("Error al usar readdir\n");
		perror("\nError en readdir.");
		exit(EXIT_FAILURE);
	}
	
	if (closedir(directorio) < 0){ // Ha habido error en closedir
		printf("Error %d en closedir(%s)\n", errno, path_dir);
		perror("\nError en readdir.");
		exit(EXIT_FAILURE);
	}		
}	

int main(int argc,char * argv[]){
	
	if(argc>2){
		printf("\nNumero de parametros erroneo");
		exit(EXIT_FAILURE);
	}
	
	char path_ini[100]=".";
	
	if(argc==2) strcpy(path_ini,argv[1]);
	
	const mode_t PERMS= S_IXGRP|S_IXOTH;
		
	long tot_size=0;
	long count_files=0;
	
	printf("Los inodos son:\n");
	busqueda_directorios(path_ini, count_files, tot_files, PERMS);
	printf("\nExisten %ld archivos regulares con permiso x para grupo y otros.\n", count_files);
	printf("El tamaño total ocupado por dichos archivos es %ld bytes.\n", tot_size);
	
	return EXIT_SUCCESS;
	
}
			
