#include <stdio.h>
#include <stdlib.h>

int lista[]={1,2,10, 1,2,0b10, 1,2,0x10};
int longlista= sizeof(lista)/sizeof(int);
int resultado= 0;

int suma(int* array, int len)
{
	asm("mov $0, %eax	\n"
	"	mov $0, %rdx		\n"
	"	bucle:			\n"
	"		add (%rdi,%rdx,4),%eax  \n"
	"		inc %edx		\n"
	"		cmp %edx,%esi		\n"
	"		jne	bucle 		"
	);
}	

int main(){
	resultado=suma(lista,longlista);
	printf("resultado = %d = 0x%x hex\n",resultado,resultado);
	exit(0);
}

