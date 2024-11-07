#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include <atomic>
#include <mutex>
#include "scd.h"


using namespace std;
using namespace scd;

// ELEMENTOS CONSTANTES

const int n_fumadores = 3;

mutex mtx;


/***********************************************************************/
//Procedimientos ajenos al monitor
void Fumar(int pos){
    mtx.lock();
    cout << "Fumador "<< pos << " fumando..."<< endl;
    mtx.unlock();
    this_thread::sleep_for(chrono::milliseconds(aleatorio<0,2000>()));
    mtx.lock();
    cout << "Fumador " << pos << " necesita materiales" << endl;
    /* cout << "Hola" << endl; */
    mtx.unlock();
    /* cout << "Hola2"<< endl; */
}

int producirIngrediente(){

    int material = aleatorio<0,2>();
    this_thread::sleep_for(chrono::milliseconds(aleatorio<0,1000>()));
    return material;
}

/*******************************************************************/
/* Monitor */
class Estanco : public HoareMonitor
{
    private:
        int mostrador;

        CondVar mat_0, mat_1, mat_2, estanquero; 

    public:
        Estanco();
        void obtenerIngrediente(int i);
        void ponerIngrediente(int ingrediente);
};

Estanco::Estanco(){
    mostrador=-1;
    estanquero = newCondVar();
    mat_0 = newCondVar();
    mat_1 = newCondVar();
    mat_2 = newCondVar();
}

void Estanco::obtenerIngrediente(int i){

    if(mostrador != i){
        switch (i){
            case 0:
                mat_0.wait();
            break;
            case 1:
                mat_1.wait();
            break;
            case 2: 
                mat_2.wait();
            break;
            default:
                mat_0.wait();mat_1.wait();mat_2.wait();
        }   
    }

    mtx.lock();
    cout << " Fumador "<< i << " toma su ingrediente" << endl;
    mtx.unlock();
    mostrador=-1;
    
    estanquero.signal();
}

void Estanco::ponerIngrediente(int ingrediente){
    if(mostrador!=-1)
        estanquero.wait();
    mostrador=ingrediente;
    /* this_thread::sleep_for(chrono::milliseconds(aleatorio<0,1000>())); */
    switch (ingrediente){
        case 0:
            mat_0.signal();
        break;
        case 1:
            mat_1.signal();
        break;
        case 2:
            mat_2.signal();
        break;
        default:
            estanquero.wait();
    }
    
    mtx.lock();
    cout << "\t\t\tIngrediente puesto ("<< ingrediente<<")" << endl;
    mtx.unlock();
}

/* Funciones de las hebras */
void hebraEstanquera(MRef<Estanco> monitor){
    while (true){
       int ingrediente = producirIngrediente(); 
       monitor->ponerIngrediente(ingrediente);
       /*No hace falta que espere la recogida pues en teoría ya lo hace*/
    }
}

void hebraFumador(MRef<Estanco> monitor, int i){
    while (true){
        monitor->obtenerIngrediente(i);
        Fumar(i);
    }
}


/* Función principal */ 

int main(){
    
    
    MRef<Estanco> monitor = Create<Estanco>() ;

    thread estanquero (hebraEstanquera,monitor);
    thread fumadores[n_fumadores];

    for (int i=0; i< n_fumadores; i++){
        fumadores[i]=thread(hebraFumador,monitor,i);
    }

    /* Esperamos a las hebras */

    estanquero.join();

    for(int i=0; i<n_fumadores;i++){
        fumadores[i].join();
    }

}
