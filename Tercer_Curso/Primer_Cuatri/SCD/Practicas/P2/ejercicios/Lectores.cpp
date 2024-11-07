#include <iostream>
#include <cassert>
#include <mutex>
#include <random>
#include <thread>

#include "scd.h"

using namespace std;
using namespace scd;

const int n_lectores = 5;
const int n_escritores = 5;

mutex mtx;

void leerEscribir(bool lector){
    if(lector){
        mtx.lock();
        cout << "Estoy leyendo" << endl;
        mtx.unlock();
    }

    else{
        mtx.lock();
        cout << "Estoy escribiendo" << endl;
        mtx.unlock();
    }
    this_thread::sleep_for(chrono::milliseconds(aleatorio<0,2000>()));
}

void Esperar(){
    this_thread::sleep_for(chrono::milliseconds(aleatorio<0,1000>()));
}

/****************************************************************************/
/* Monitor */

class Lec_Esc : public HoareMonitor
{
    private:
        int n_leen,         //Lectores que hay leyendo
            n_escrit;       //Escritores esperando
        bool escrib;        //¿Se está escribiendo ahora?

        CondVar 
            lectores,       //Cola de lectores
            escritores;     //Cola de escritores
            

    public:
        Lec_Esc();
        void ini_lectura();
        void fin_lectura();
        void ini_escritura();
        void fin_escritura();
};


Lec_Esc::Lec_Esc(){
    n_leen=0;
    n_escrit=0;
    escrib=true;                //Para forzar que se empiece escribiendo.
    lectores = newCondVar();
    escritores = newCondVar();
}

void Lec_Esc::ini_lectura(){
    if(escrib || n_escrit > 0)
        lectores.wait();

    n_leen++;

    if(!lectores.empty())
        lectores.signal();
}

void Lec_Esc::fin_lectura(){
    n_leen--;

    if(!escritores.empty())
        escritores.signal();
}

void Lec_Esc::ini_escritura(){
    if(n_leen > 0)
        escritores.wait();
    
    n_escrit++;
    escrib = true;
}

void Lec_Esc::fin_escritura(){
    escrib=false;
    n_escrit--;

    if(!escritores.empty()){
        escritores.signal();
    }
    else{
        lectores.signal();
    }
}
/******************************************************************************/
/* hebras */
void hebraLectora(MRef<Lec_Esc> monitor){
    while(true){
        monitor->ini_lectura();
        leerEscribir(true);
        monitor->fin_lectura();
        Esperar();
    }
}

void hebraEscritora(MRef<Lec_Esc> monitor){
    while(true){
        monitor->ini_escritura();
        leerEscribir(false);
        monitor->fin_escritura();
        Esperar();
    }
}

int main(){
    MRef<Lec_Esc> monitor = Create<Lec_Esc>();
    thread readers[n_lectores], authors[n_escritores];

    for (int i=0; i<n_lectores; i++){
        readers[i]=thread(hebraLectora,monitor);
    }
    
    for (int i=0; i<n_escritores; i++){
        authors[i]=thread(hebraEscritora,monitor);
    }

    for (int i=0; i<n_lectores; i++){
        readers[i].join();
    }

    for (int i=0; i<n_escritores; i++){
        authors[i].join();
    }
}
