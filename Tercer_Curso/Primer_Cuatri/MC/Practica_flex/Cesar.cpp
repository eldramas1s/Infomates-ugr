#include <iostream>
#include <string>
#include <random>

const int MAX=126;
const int MIN=33;
const int KMAX=93;
const int KMIN=0;
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
void To_cesar(string & cad,int k){
    int cif;
    for(int i=0; i<cad.length();i++){
        cout << cad[i] << endl;
        cif=cad[i]+k;
        if(cif< MIN)
            cad[i]=toascii(cif%MAX+MIN);
        else 
            cad[i]=toascii(cif%MAX);
    }
}

void From_cesar(string & cad, int k){
    for(int i=0; i<cad.length();i++){
        if(cad[i]-k<MIN)
            cad[i]=toascii((cad[i]-k)%MAX+MAX);
        else 
            cad[i]=toascii((cad[i]-k)%MAX+MIN);
    }
}

/*-------------------------------*/
//Función de corrección de la cadena alfanumérica
bool Cadena_correcta(string cad){
    bool correcta=true;
    int i=0;
    while (correcta && i<cad.length()){
        correcta=(cad[i]>=MIN && cad[i]<=MAX);
        i++;
    }
    return correcta;
}

/*-------------------------------*/
int main(int argc, char**argv){
    string cad;
    do{
        cout << "Introduzca una cadena: " ;
        cin>>cad;
    }while(!Cadena_correcta(cad)||cad.length()<=0);



    int k=(int)aleatorio<KMIN,KMAX>();

    cout << "Constante de traslación: " << k << endl;
    cout << "Cadena introducida: " << cad << endl;
    To_cesar(cad,k);
    cout << "Cadena cifrada: " << cad << endl;
    From_cesar(cad,k);
    cout << "Cadena descifrada: " << cad << endl;
    return 0;
}
