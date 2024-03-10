// gcc bombaPrimos.c -o bombaPrimos

//LA ENCRIPTACION DEL NUMERO PRIMO_MODULO2 para la contraseña  division 97/sizeof(passcode) para passcode

#include <stdio.h>	// para printf(), fgets(), scanf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE 9
#define TLIM 60

int vector[]={1,2,3,5,7,11,13,17,19,23,29,31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
char password[]="abduscan";	// contrasenia
int  passcode = 2015;			// pin
int longvector=sizeof(vector)/sizeof(int);	//Longitud del vector

//Funcion de explosion
void boom(void){
	printf(	"\n"
		"***************\n"
		"*** BOOM!!! ***\n"
		"***************\n"
		"\n");
	exit(EXIT_FAILURE);
}

//Funcion de desactivacion
void defused(void){
	printf(	"\n"
		"Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·\n"
		"Â·Â·Â· bomba desactivada Â·Â·Â·\n"
		"Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·\n"
		"\n");
	exit(EXIT_SUCCESS);
}

int Codiff_pc(int n){
	if(((vector[longvector-1])/sizeof(n))%2==0) n+= (vector[longvector-1])/sizeof(passcode);
	else n-= (vector[longvector-1])/sizeof(n);

	return n;
}

//Funcion main
int main(){

//*Lo suyo seria saltarse este for y el que encripta el pin
	for(int i=0; i<26 && i<strlen(password); ++i){
		if(i%2==0){password[i]+=vector[i];}
		else	{password[i]-=vector[i];}
	}

	char pw[SIZE];
	int  pc;
	int n;

	struct timeval tv1,tv2;	//*gettimeofday() secs-usecs
	gettimeofday(&tv1,NULL);

	//lectura de la contrasenia
	do	printf("\nIntroduce la contrasenia: ");
	while (	fgets(pw, SIZE, stdin) == NULL );

	if    (	strncmp(pw,password,sizeof(password)))
	    boom();

	gettimeofday(&tv2,NULL);

	//Control del tiempo
	if    ( tv2.tv_sec - tv1.tv_sec > TLIM )
	    boom();

	//Codificacion del pin
	passcode=Codiff_pc(passcode);

	//Lectura del pin
	do  {	printf("\nIntroduce el pin: ");
	 if ((n=scanf("%i",&pc))==0)			//Cuidado con empezar por 0 que toma base octal.
		scanf("%*s")    ==1;         }
	while (	n!=1 );

	//Explosion por equivocacion
	if    (	pc!=passcode )
	    boom();

	gettimeofday(&tv1,NULL);
	
	//Control del tiempo
	if    ( tv1.tv_sec - tv2.tv_sec > TLIM )
	    boom();

	//Desactivada
	defused();
}
