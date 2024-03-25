#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int lista[]={0x00000001,0x00000001,0x00000001,0x00000001,0x00000001,0x00000001};
int longlista=sizeof(lista)/sizeof(int);


int CounterOnes(int valor)
{	
	int result=0;
	int counter=0;
	asm("mov $0, %%ecx	\n"
	" 	bucle:		\n"
	"	mov %[v], %%ecx	\n"
	"	and $1, %%ecx	\n"
	"	add %%ecx,%[r]	\n"
	"	cmp $0,%[v]	\n"
	"	sarl $1,%[v]	\n"
	"	jne bucle	\n"
	"	add %%ecx, %[r]	\n"
	"	inc %[c]	"
	: [r] "+r"	(result),
	  [v] "+r"	(valor),
	  [c] "+r"	(counter)
	:
	:"%ecx"
	);
	
	return result;
}

int CounterBits ( int * array, int len)
{
	int result=0;
	int counter=0;
	while(counter < len)
	{
		asm("	mov $0, %%edx			\n"
		"	mov $0, %%ecx			\n"
		" 	mov [a], %%edx		\n"		
		"	mov %[c], %%ecx			\n"
		"	mov *%%edx(,%%ecx,4), %%edi	\n"
		"	call CounterOnes		\n"
		"	add %%eax,%[r]			\n"
		"	inc %%ecx			\n"
		"	mov %%ecx, %[c]			"
		: [c] 	"+r"	(counter),
		  [r]	"+r"	(result),
		  [a]	"r"	(array)
		:
		: "%edi","%eax","%edx","%ecx"
		);
		
	}

	return result;

}
void crono(int (*func)(), char* msg){
	int resultado=0;
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
int main(){

	crono(CounterBits, "Counterbits con for");
	return 0;
	
}
