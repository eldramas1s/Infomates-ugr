#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include "scd.h"

using namespace std;
using namespace scd;
using namespace std::chrono;

const int num_mats=3;
int mats[num_mats]={0};

Semaphore estanquero(6);
Semaphore fumador[num_mats]={0,0,0};

mutex locker,flocker;

int ProducirMaterial(){
    int material = aleatorio<0,2>();
    this_thread::sleep_for(chrono::milliseconds(aleatorio<0,1000>()));
    return material;
}

void Fumar(int pos){
    locker.lock();
    cout << "Fumador "<< pos << " fumando..."<< endl;
    locker.unlock();
    this_thread::sleep_for(chrono::milliseconds(aleatorio<0,2000>()));
    locker.lock();
    cout << "Fumador " << pos << " necesita materiales" << endl;
    /* cout << "Hola" << endl; */
    locker.unlock();
    /* cout << "Hola2"<< endl; */
}

void Estanquero(){
    while (true){
        sem_wait(estanquero);
        int num = ProducirMaterial();
        locker.lock();
        switch(num){
            case 0:
                cout << "\t\t\t\tProduzco papel"<<endl;
            break;
            case 1:
                cout << "\t\t\t\tProduzco tabaco"<<endl;
            break;
            case 2:
                cout << "\t\t\t\tProduzco mechero"<<endl;

        }
        locker.unlock();
        mats[num]++;
        sem_signal(fumador[num]);
    }
}

void Fumador(int pos){

    while(true){
        sem_wait(fumador[pos]);
        mats[pos]--; 
        flocker.lock();//Por qué no es  necesario este cerrojo?
        /* cout << "Hola1"<< endl; */
        Fumar(pos);
        /* cout << "Hola2" << endl; */
        flocker.unlock();
        switch(pos){
            case 0:
                cout << "Consumo papel"<<endl;
            break;
            case 1:
                cout << "Consumo tabaco"<<endl;
            break;
            case 2:
                cout << "Consumo mechero"<<endl;

        }
        sem_signal(estanquero);
    
    }
}
int main(){
    
    thread fumadores[num_mats];
    thread estanquero(Estanquero);

    for(int i=0; i<num_mats; i++){
        fumadores[i] = thread(Fumador,i);
    }

    for(int i=0; i< num_mats; i++){
        fumadores[i].join();
    }

    estanquero.join();
}
