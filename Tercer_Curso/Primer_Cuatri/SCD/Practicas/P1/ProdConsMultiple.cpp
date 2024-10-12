#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include "scd.h"


using namespace std;
using namespace scd;

//Variable compartida de vector de elementos

const int NUM_COMP = 10;
int valores[NUM_COMP]={0};

const int desde = 0, hasta = 1000, nprod=5,ncons=4;

atomic<int> pos_lectura(0), pos_escritura(0),producidos(0);
//Declaramos los semaforos de escritura y lectura
Semaphore can_read(NUM_COMP);
Semaphore can_write(NUM_COMP);//Tantos valores como veces consecutivas se pueda escribir

//Cerrojos de control de escritura en pantalla, cada uno representa una función.
mutex escribir_pantalla;

int vprod[nprod]={0};
//Produce un valor aleatorio entre "desde" y "hasta".
//return entero producido
//pos -> escribe en pantalla el valor producido
//    -> aumenta en uno la cantidad de valores producidos
int ProducirValor(int pos){
    this_thread::sleep_for(chrono::milliseconds(aleatorio<desde,hasta>()));
    int num = vprod[pos];
    vprod[pos]=producidos;
    producidos++;
    escribir_pantalla.lock();
    cout << "P["<<pos<<"] =" << num << " producido" << endl;
    escribir_pantalla.unlock();
    return num; 
}

//Consume el valor escrito en la posicion de un vector
//pos -> posicion donde consumir
//pre -> pos debe ser positiva o 0
void ConsumirValor(int pos,int p){
    this_thread::sleep_for(chrono::milliseconds(aleatorio<desde,hasta>())); //
    cout << "\t\t\t\tC["<<pos<<"] = " << valores[p] << " consumido"<<endl;
}

//Lee del vector usando al funcion ConsumirValor
//Pos es el consumidor que consume el valor
void leer(int pos){
    
    while(true){
    /* while (producidos<100){ */

        sem_wait(can_read); //Espera hasta que pueda leer
                            //Poniendolo aqui provoco que un semaforo no escriba la poscion erronea 
        int p;
        //Escribe la situacion
        escribir_pantalla.lock();
        p=pos_lectura;
        cout << "\t\t\t\tC["<<pos<< "] posicion " << p << endl;
        pos_lectura++;
        escribir_pantalla.unlock();

        if(pos_lectura >= NUM_COMP){
            pos_lectura=0;
        }

        ConsumirValor(pos,p);
        sem_signal(can_write);//Habilita una posicion mas de escritura
    }
}

//Escribe en el vector usando la funcion ProducirValor
//Pos es el productor que produce el valor
void escribir(int pos){
    while(true){
    /* while (producidos < 100){ */
        int producto = ProducirValor(pos);
        int p;
        //Espera hasta que pueda esccribir
        sem_wait(can_write);
        escribir_pantalla.lock();
        p=pos_escritura;
        pos_escritura++;
        escribir_pantalla.unlock();

        if(pos_escritura >= NUM_COMP){
            pos_escritura=0;
        }

        valores[p]=producto;

        //Informe de la situacion
        sem_signal(can_read);//Habilita la lectura
        
        escribir_pantalla.lock();
        cout << "P["<<pos<<"] =" << producto << " escrito" << endl;
        escribir_pantalla.unlock();
    }    
}

int main(){
    thread productor[nprod],consumidor[ncons];
    
    for (int i=0; i<nprod; i++){
        productor[i]= thread (escribir, i);
    }
    
    for (int i=0; i<ncons; i++){
        consumidor[i]= thread (leer,i);
    }

    for (int i=0; i<nprod; i++){
        productor[i].join();
    }

    for (int i=0; i<ncons; i++){
        consumidor[i].join();
    }
}
