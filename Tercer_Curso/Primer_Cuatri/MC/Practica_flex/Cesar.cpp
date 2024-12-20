#include <iostream>
#include <string>
#include <random>

const int MAX=128;
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
string To_cesar(string cad,int k){
    for(int i=0; i<cad.length();i++){
        cad[i]=(cad[i]+k)%MAX+MIN;
    }
    return cad;
}

string From_cesar(string cad, int k){
    for(int i=0; i<cad.length();i++){
        cad[i]=(cad[i]-k)%MAX+MIN;
    }
    return cad;
}

/*-------------------------------*/
//Función de corrección de la cadena alfanumérica
bool Cadena_correcta(string cad){
    bool correcta=true;
    int i=0;
    while (correcta && i<cad.length()){
        cout << cad[i] << endl;
        correcta=(MIN>=cad[i] && cad[i]<=MAX);
        cout << correcta << endl;
        i++;
    }
    return correcta;
}

/*-------------------------------*/
int main(int argc, char**argv){
    string cad;
    do{
        cin>>cad;
        cout << "La cadena no es correcta" << endl;
    }while(!Cadena_correcta(cad)||cad.length()<=0);


    int k=(int)aleatorio<KMIN,KMAX>();

    cout << "Constante de traslación: " << k << endl;
    cout << "Cadena introducida: " << cad << endl;
    cout << "Cadena cifrada: " << To_cesar(cad,k) << endl;
    cout << "Cadena descifrada: " << From_cesar(cad,k) << endl;
    return 0;
}
