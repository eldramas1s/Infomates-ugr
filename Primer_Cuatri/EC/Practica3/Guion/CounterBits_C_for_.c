#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int lista[]={0x00000001,0x00000001,0x00000001,0x00000001,0x00000001,0x00000001};
int longlista=sizeof(lista)/sizeof(int);


int CounterOnes(int valor)
{	
	int result=0;
	for (int i=0;i<sizeof(int); ++i)
	{
		result+=valor & 0x1;
		valor>>=1;
	} 
	
	return result;
}

int CounterBits ( int * array, int len)
{
	int result=0;
	for(int i=0; i<len; ++i)
	{
		result+=CounterOnes(array[i]);
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
