#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include "scd.h"


using namespace std;
using namespace scd;

//Variable compartida de vector de elementos

const int NUM_COMP = 10;
int valores[NUM_COMP]={0};

const int desde = 0, hasta = 1000;
int producidos=0, pos_escritura=0, pos_lectura=0, dato=0;

//Declaramos los semaforos de escritura y lectura
Semaphore can_read(0);
Semaphore can_write(NUM_COMP);//Tantos valores como veces consecutivas se pueda escribir

//Cerrojos de control de escritura en pantalla, cada uno representa una función.
mutex escribir_pantalla, main_lock;

//Produce un valor aleatorio entre "desde" y "hasta".
//return entero producido
//pos -> escribe en pantalla el valor producido
//    -> aumenta en uno la cantidad de valores producidos
int ProducirValor(){
    this_thread::sleep_for(chrono::milliseconds(aleatorio<desde,hasta>()));
    producidos++;
    int num = dato;
    dato++;
    escribir_pantalla.lock();
    cout << "Produzco el valor " << num << endl;
    escribir_pantalla.unlock();
    return num; 
}

//Consume el valor escrito en la posicion de un vector
//pos -> posicion donde consumir
//pre -> pos debe ser positiva o 0
void ConsumirValor(int pos){
    this_thread::sleep_for(chrono::milliseconds(aleatorio<desde,hasta>())); //
    cout << "\t\t\t\tValor " << valores[pos] << " consumido"<<endl;
}

//Lee del vector usando al funcion ConsumirValor
void leer(){
    
//    while(true){
    while (producidos<100){

        //Escribe la situacion
        escribir_pantalla.lock();
        cout << "\t\t\t\tLeo en posicion " << pos_lectura << endl;
        escribir_pantalla.unlock();

        sem_wait(can_read); //Espera hasta que pueda leer
        if(pos_lectura >= NUM_COMP){
            pos_lectura=0;
        }

        ConsumirValor(pos_lectura);
        pos_lectura++;
        sem_signal(can_write);//Habilita una posicion mas de escritura
    }
}

//Escribe en el vector usando la funcion ProducirValor
void escribir(){
//    while(true){
    while (producidos < 100){
        int producto = ProducirValor();
        
        //Espera hasta que pueda esccribir
        sem_wait(can_write);
        if(pos_escritura < NUM_COMP){
            valores[pos_escritura]=producto;
        }
        else{
//            cout << "Vuelta dada" << endl;
            pos_escritura = 0;
            valores[pos_escritura]=producto;
        }

        //Informe de la situacion

        escribir_pantalla.lock();
        cout << "Valor " << producto << " escrito" << endl;
        escribir_pantalla.unlock();

//        cout << "hola" << endl;
        pos_escritura++;
        sem_signal(can_read);//Habilita la lectura
    }    //?DUDA: Puedo porner sem_signal antes de dar el informe de la situacion???
}

int main(){
    thread productor, consumidor;
    
    productor = thread(escribir);
    consumidor = thread(leer);
    productor.join();
    consumidor.join();
}
