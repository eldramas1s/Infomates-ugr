%option noyywrap
	// flex++ nat.l
	// g++ lex.yy.cc -o nat -ll
	// ./nat fichero1 fichero1_nat


	/*----- Seccion de Declaraciones ----------------*/
%{
#include <iostream>
#include <fstream>
#include <random>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAX=128;      //Codigo ASCII máximo aceptable
const int MIN=33;       //Codigo ASCII minimo aceptable
const int KMIN=1;       //Minimo valor de desplazamiento
const int KMAX=94;      //Maximo valor de desplazamiento
const int Ip_min=0;     //Minimo valor de segmento de IP
const int IP_max=255;   //Máximo valor de segmento de IP

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

void cifrar (char * cad, int k);
void descifrar (char * cad, int k);
template <int min, int max> int aleatorio();
bool isValidIP(const char * ip);
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

template <int min, int max>aleatorio()
{
    static default_random_engine generador((random_device())());
    static uniform_int_distribution<int> distribucion_uniforme(min,max);
    return distribucion_uniforme(generador);
}

void cifrar (char* cad, int k)
{
   static int rango = MAX-MIN-1;
   int cadl = strlen(cad);
   for(int i=0;i<cadl; i++)
   {
        if(cad[i]>=MIN && cad[i]<=MAX)
            cad[i]=((cad[i]-MIN+k)%rango)+MIN;
   }
}

void descifrar (char * cad, int k)
{
    static int rango = MAX-MIN-1;
    int cadl=strlen(cad);

    for (int i=0; i<cadl; i++)
    {
        if(cad[i]>=MIN && cad[i]<=MAX)
            cad[i]=((cad[i]-MIN-k+rango)%rango)+MIN;
    }
}

bool isValidIP(const char * ip)
{
    int ipl = strlen(ip);
    if(ipl == 0 || ipl>15) return false;

    int num_segments = 0;
    char segment[4];
    int segIndex = 0;

    for( int i=0; i<=ipl; i++ )
    {
        if(ip[i] == '.' || ip[i]=='\0')
        {
            if(segIndex==0) return false;
            
            segment[segIndex] = '\0';
            int num = atoi(segment);
            if(num<0 || num>255) return false;

            ++num_segments;
            segIndex=0;

            if(num_segments>4) return false;
        } 
        else if(ip[i]>='0'&&ip[i]<='9')
        {
            if(segIndex>=3)return false;
            segment[segIndex++] = ip[i];
        }
        else
        {
            return false;
        }
    }
    return num_segments == 4;
}
