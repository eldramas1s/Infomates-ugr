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

// Para saber si se trata de la primera credencial, usuario, o la contraseña
int cont_cred=0;

// Para las credenciales
char * credencial;
const char * user="U:";
const char * passwd="P:";

// Función para recortar U: y P: antes de cifrar
void recortar(char * cad, int ini);

// Funciones de cifrado y descifrado
void cifrar (char * cad, int k);
void descifrar (char * cad, int k);

int aleatorio(int min, int max);
bool isValidIP(const char * ip);

// Valor de k, variable para el cifrado:
//const int k=2;        // valor prefijado
const int k=aleatorio(KMIN, KMAX); //opción de k aleatorio

%}

IP_SEGMENT	([0-9]{1,2})|(1[0-9]{1,2})|(2[0-4][0-9])|(25[0-5])

%%

	/*----- Seccion de Reglas ----------------*/ // Hay que rellenar correctamente

IN:                  {in=true; fichero2 << YYText() << endl;}
OUT:                 {in=false; fichero2 << YYText() << endl;}

{IP_SEGMENT}\.{IP_SEGMENT}\.{IP_SEGMENT}\.{IP_SEGMENT} {if(in==false) {
								if(cont_ip==0) fichero2 << ip_src << endl;
								else fichero2 << YYText() << endl;
								cont_ip++;
							 }else{
							 	if(cont_ip==0) fichero2 << YYText() << endl;
								else fichero2 << ip_dst << endl;
								cont_ip++;
							 }}

([!-~])*       		      {credencial= (char * )YYText();  
				       if(in == false){
						 if(cont_cred==0) recortar(credencial, strlen(user));
						 else recortar(credencial, strlen(passwd));	
						 cont_cred++;        
						 cifrar(credencial , k);
						 fichero2 << credencial << endl; 
					}else{	        		
						 descifrar(credencial , k);
						 char aux[strlen(user)+strlen(credencial)]={'\0'};
						 
						 if(cont_cred==0) strcat(aux, user);
						 else strcat(aux, passwd);
						 
						 strcat(aux, credencial);
						 credencial=aux;
						 fichero2 << credencial << endl; 
						 cont_cred++; 
				        }
				      } 

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
		cout << "./nat fichero1 fichero1_nat" << endl;
		exit(1);
		
	} 
	
	
	
yyFlexLexer flujo (&fichero1,0);
flujo.yylex();
	
	return 0;

}

int aleatorio(int min, int max)    
{
   static default_random_engine generador((random_device())());
    static uniform_int_distribution<int> distribucion_uniforme(min,max);
    return (int)distribucion_uniforme(generador);
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

void recortar(char * cad, int ini){
   int cadl = strlen(cad);
   char aux[cadl-ini-1];
   int i=0;
   
   while(i+ini < cadl ){
   	aux[i]=cad[i+ini];
   	i++;
   }
   aux[i]='\0';
   strcpy(cad, aux);
}


