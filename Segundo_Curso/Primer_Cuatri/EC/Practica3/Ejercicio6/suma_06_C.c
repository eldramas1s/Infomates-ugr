#include <stdio.h>
#include <stdlib.h>

extern int suma(int* array, int len);

int lista[]={1,2,10, 1,2,0b10, 1,2,0x10};
int longlista= sizeof(lista)/sizeof(int);
int resultado= -1;

int main(){
	resultado=suma(lista,longlista);
	printf("resultado = %d = 0x%x hex\n",resultado,resultado);
	exit(0);
}

