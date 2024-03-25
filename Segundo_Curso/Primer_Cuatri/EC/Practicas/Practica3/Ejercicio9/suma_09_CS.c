#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SIZE (1<<16)
int lista[SIZE];
int resultado=0;

int suma1(int *array, int len){
	int i, res=0;
	for (i=0; i<len; ++i)
		res += array[i];
	return res;
}

int suma2 (int* array, int len){
	int i, res=0;
	for(i=0; i<len; ++i)
		asm ( "add (%[a],%[i],4), %[r] "
		:   [r] "+r" 	(res)
		:   [i] "r"	((long)i),
		   [a] "r"	(array)		// referenciamos arraya  un registro cualquiera
		//:"cc"				//clobber
		);
}

int suma3(int* array, int len)
{
	asm("mov $0, %%eax	\n"
	"	mov $0, %%rdx		\n"
	"	bucle:			\n"
	"		add (%%rdi,%%rdx,4),%%eax  \n"
	"		inc %%edx		\n"
	"		cmp %%edx,%%esi		\n"
	"		jne	bucle 		"
	:					//output
	:					//input
	: "cc",					//clobber
	  "eax","rdx"				//usamos %%reg			
	);
}

void crono(int (*func)(), char* msg){
	struct timeval tv1,tv2; // gettimeofday() secs-usecs
	long tv_usecs; // y sus cuentas
	gettimeofday(&tv1,NULL);
	resultado = func(lista, SIZE);
	gettimeofday(&tv2,NULL);	
	tv_usecs=(tv2.tv_sec -tv1.tv_sec )*1E6+
			(tv2.tv_usec-tv1.tv_usec);
	printf("resultado = %d\t", resultado);
	printf("%s:%9ld us\n", msg, tv_usecs);
}	

int main(){
	int i; // inicializar array
	for (i=0; i<SIZE; i++) // se queda en cache
		lista[i]=i;
	crono(suma1, "suma1 (en lenguaje C )");
	crono(suma2, "suma2 (1 instrucción asm)");
	crono(suma3, "suma3 (bloque asm entero)");
	printf("N*(N+1)/2 = %d\n", (SIZE-1)*(SIZE/2)); /*OF*/
	exit(0);
}

