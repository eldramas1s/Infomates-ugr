#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int resultado=0;
int lista[]={0xffffffff,0xffffffff,0xffffffff,0xffffffff};
int longlista=sizeof(lista)/sizeof(int);

int popcount1 (int* array, size_t len)
{
	int result=0;
	for (int i=0; i<len; ++i){
		int dato=array[i];
		asm( "mov $0, %%ecx	\n"
		"	bucle:		\n"
		"		mov %[d], %%r9d	\n"
		"		and $1 , %%r9d	\n"
		" 		add %%r9d, %%ecx	\n"
		"		shrl $1,%[d]	\n"
		"		cmp $0,%[d]	\n"
		"		jne bucle	\n"
		"	mov %%ecx, %%eax	\n"
		"	add %%ecx, %[r]	"
		:   [d]	"+r" 	(dato),
		    [r] "+r"	(result)
		:
		: "%ecx","%r9","%eax"
		);
	}
	return result;
}

void crono(int (*func)(), char* msg){
	struct timeval tv1,tv2; // gettimeofday() secs-usecs
	long tv_usecs; // y sus cuentas
	gettimeofday(&tv1,NULL);
	resultado = func(lista, longlista);
	gettimeofday(&tv2,NULL);
	tv_usecs=(tv2.tv_sec -tv1.tv_sec )*1E6+
		(tv2.tv_usec-tv1.tv_usec);
	printf( "%ld" "\n", tv_usecs);
	printf("resultado = %d\t", resultado);
	printf("%s:%9ld us\n", msg, tv_usecs);
}

int main()
{
	crono(popcount1 , "popcount1 (lenguaje C con casitodo asm()");
	exit(0);
}
	
