#include <iostream>
#include <cstring>
#include <random>

const int MAX=126;
const int MIN=33;
const int RANGO=94;
const int KMIN=1;
const int KMAX=94;
using namespace std;

/*-------------------------------*/
//Funcion de obtencion de k
template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}
/*-------------------------------*/
//Funciones de cifrado y descifrado.
void To_cesar(char * cad, int k){
    int cadl=strlen(cad);
    for(int i=0; i<cadl; i++)
    {
        if(cad[i]>=MIN && cad[i]<=MAX) //Compruebo que es un caracter dentro del rango
            cad[i]=((cad[i]-MIN+k)%RANGO)+MIN; //Voy a un rango donde se empieza en 0
                                              //para poder hacer el modulo y luego 
                                              //sumo el mimino para quedarme en el 
                                              //rango que buscamos.
    }
}

void From_cesar(char* cad, int k) {
    int cadl = strlen(cad);
    for (int i = 0; i < cadl; ++i) {
        if (cad[i] >= MIN && cad[i] <= MAX) {      //Compruebo que es un caracter dentro del rango
            cad[i] = ((cad[i] - MIN - k + RANGO) % RANGO) + MIN; //Voy a un rango donde se empieza en 0
                                                                 //evitando valores negativos sumando RANGO
                                                                 //hago el modulo para quedarme luego en el 
                                                                 //rango que buscamos
        }
    }
}

/*-------------------------------*/
//Función de corrección de la cadena alfanumérica
bool Cadena_correcta(char * cad){
    int cadl = strlen(cad);
    bool correcta=true;
    int i=0;
    while (correcta && i<cadl){
        correcta=(cad[i]>=MIN && cad[i]<=MAX);
        i++;
    }
    return correcta;
}

/*-------------------------------*/
int main(int argc, char**argv){
    char cad[256];
    do{
        cout << "Introduzca una cadena: " ;
        cin.getline(cad,256);
    }while(!Cadena_correcta(cad)||strlen(cad)<=0);



    int k=(int)aleatorio<KMIN,KMAX>();

    cout << "Constante de traslación: " << k << endl;
    cout << "Cadena introducida: " << cad << endl;
    To_cesar(cad,k);
    cout << "Cadena cifrada: " << cad << endl;
    From_cesar(cad,k);
    cout << "Cadena descifrada: " << cad << endl;
    return 0;
}
