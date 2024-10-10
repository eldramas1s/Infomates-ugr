#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include "scd.h"

using namespace std;
using namespace scd;

//Variable compartida de vector de elementos

const int NUM_COMP = 100, NUM_HEBRAS_C=10,NUM_HEBRAS_P=10;
int valores[NUM_COMP]={0};

const int desde = 0, hasta = 1000;
atomic<int> producidos(0);
int pos_read[NUM_HEBRAS_C]={0};
int pos_write[NUM_HEBRAS_P]={0};

//Declaramos los semaforos de escritura y lectura
Semaphore can_read(0);
Semaphore can_write(NUM_COMP/NUM_HEBRAS_P);//Tantos valores como veces consecutivas se pueda escribir

//¿¿¿Al no usar un vector de semaforos estoy atrasando el tempo de ejecucion??????


//Cerrojos de control de escritura en pantalla, cada uno representa una función.
mutex leer_pantalla, escribir_pantalla, main_lock;

//Produce un valor aleatorio entre "desde" y "hasta".
//return entero producido
//pos -> escribe en pantalla el valor producido
//    -> aumenta en uno la cantidad de valores producidos
int ProducirValor(){
    producidos++;
    int num = aleatorio<desde,hasta>();
    escribir_pantalla.lock();
    cout << "Produzco el valor " << num << endl;
    escribir_pantalla.unlock();
    return num; 
}

//Consume el valor escrito en la posicion de un vector
//pos -> posicion donde consumir
//pre -> pos debe ser positiva o 0
void ConsumirValor(int pos){
    leer_pantalla.lock();
    cout << "Valor " << valores[pos] << " consumido"<<endl;
    leer_pantalla.unlock();
}

//Lee del vector usando al funcion ConsumirValor
void leer(int inicio, int fin, int i){
    
//    while(true){
    while (producidos<100){

        //Escribe la situacion

        sem_wait(can_read); //Espera hasta que pueda leer
        if(pos_read[i] >= fin){
            pos_read[i]=inicio;
        }
    
        escribir_pantalla.lock();
        cout << "Leo en posicion " << pos_read[i] << endl;
        escribir_pantalla.unlock();
        ConsumirValor(pos_read[i]);
        
        //Calculamos la posicion relativa de la hebra que escribe
        

        pos_read[i]++;
        sem_signal(can_write);//Habilita una posicion mas de escritura
    }
}

//Escribe en el vector usando la funcion ProducirValor
void escribir(int inicio, int fin, int i){
//    while(true){
    while (producidos < 100){
        int producto = ProducirValor();
        
        //Espera hasta que pueda esccribir
        sem_wait(can_write);
        if(pos_write[i] < NUM_COMP){
            valores[pos_write[i]]=producto;
        }
        else{
//            cout << "Vuelta dada" << endl;
            pos_write[i] = 0;
            valores[pos_write[i]]=producto;
        }

        //Informe de la situacion
        escribir_pantalla.lock();
        cout << "Valor " << producto << " escrito" << endl;
        escribir_pantalla.unlock();

//        cout << "hola" << endl;
        pos_write[i]++;
        sem_signal(can_read);//Habilita la lectura
    }    //?DUDA: Puedo porner sem_signal antes de dar el informe de la situacion???
}

int main(){
    thread productores[NUM_HEBRAS_P], consumidores[NUM_HEBRAS_C];
    
    int division_p = NUM_COMP/NUM_HEBRAS_P;
    int division_c = NUM_COMP/NUM_HEBRAS_C;
    
    for (int i=0; i<NUM_HEBRAS_P-1;i+=1){
        productores[i] = thread(escribir,i*division_p,i*division_p+division_p-1,i);
    }
    productores[NUM_HEBRAS_P-1] = thread(escribir,NUM_COMP-NUM_HEBRAS_P,NUM_COMP,NUM_HEBRAS_P-1);

    for (int j=0; j<NUM_HEBRAS_C-1; j+=1){
        consumidores[j] = thread(leer,j*division_c,j*division_c+division_c-1,j);
    } 
    consumidores[NUM_HEBRAS_C-1] = thread(leer,NUM_COMP-NUM_HEBRAS_C,NUM_COMP,NUM_HEBRAS_C-1);

    for (int i=0; i<NUM_HEBRAS_C ; i++){
        productores[i].join();
    }

    for(int j=0;j<NUM_HEBRAS_C;++j){
        consumidores[j].join();
    }
}
