%option noyywrap
	// flex++ nat.l
	// g++ lex.yy.cc -o nat -ll
	// ./nat fichero1 fichero1_nat


	/*----- Seccion de Declaraciones ----------------*/
%{
#include <iostream>
#include <fstream>

using namespace std;

ifstream fichero1;
ofstream fichero2;

// Para determinar el tipo de traducción a realizar usamos la variable "in"
//       · in== false -> el fichero sale de la zona priv. a la pub.
//       · in== true -> el fichero va de la zona pub. a la priv.
bool in = false;


// IPs usadas para la traducción (según la topología que estamos usando)
const char * ip_dst="192.168.1.1";
const char * ip_src="12.1.1.1";

// Para saber si se trata de la primera IP, es decir, origen o el destino
int cont_ip=0;

// Para las credenciales
char * user;
char * passwd;

void cifrar ();
void descifrar ();
%}

%%

	/*----- Seccion de Reglas ----------------*/ // Hay que rellenar correctamente

IN:                  {in=true; fichero2 << YYText() << endl;}
OUT:                 {in=false; fichero2 << YYText() << endl;}

[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}   {fichero2 << ip_src << endl;} // comprobar que sea menor que 255, pensar mejor

U:([0-9]|[a-z]|[A-Z])*       {fichero2 << YYText() << endl;} // primera aproximación
P:([0-9]|[a-z]|[A-Z])*       {fichero2 << YYText() << endl;}



%%

	/*----- Seccion de Procedimientos --------*/
	
int main (int argc, char *argv[])
{
	if (argc == 3)
	{
		fichero1.open (argv[1]);
		if (!fichero1.is_open())
		{
			cout << "error de lecura fichero de entrada" << endl;
			exit (1);
		}
		fichero2.open (argv[2]);
		if (!fichero2.is_open())
		{
			cout << "error de lecura fichero de salida" << endl;
			exit (1);
		}
	}
	else{
		cout << "Se necesitan un fichero de lectura y otro de escritura:" << endl;
		cout << "./nat fichero1 fichero2" << endl;
		exit(1);
		
	} 
	
	
	
yyFlexLexer flujo (&fichero1,0);
flujo.yylex();
	
	return 0;

}

void cifrar ()
{
	
}
void descifrar ()
{
	
}
