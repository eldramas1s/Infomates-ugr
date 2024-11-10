#include <iostream>
#include <mutex>
#include <iomanip>
#include <thread>
#include <chrono>
#include <cassert>

#include "scd.h"

using namespace std;
using namespace scd;

int ejercicio;
int n_hebras_a[8]={5,3,6,1,10,6,1,5};
int n_hebras_b[8]={0,2,2,1,0,0,1,0};

mutex mtx;

void trabajar(){
    this_thread::sleep_for(chrono::milliseconds(aleatorio<0,1000>()));
}
/*********************************************************************************/
/* Monitores*/
/*********************************************************************************/

//EJERCICIO____1 (se puede hacer porque admite semántica SU)

const int n1 = 5, n2=5;

class Monitor : public HoareMonitor
{
    private:  
                        //CORE DUMPED
        int n_libres_1;
        int n_libres_2;

        CondVar tipo_0_lib, //Cola de la peticion a tipo_0 liberante
                tipo_0_sol, //Cola de la petición a tipo_0 solicitante
                tipo_1_lib, //Cola de la petición a tipo_1 liberante
                tipo_1_sol, //Cola de la petición a tipo_1 solicitante
                tipo_2_lib, //Cola de la petición a tipo_2 liberante
                tipo_2_sol; //Cola de la peticion a tipo_2 solicitante
    public:
        Monitor();
        void liberar_recurso(int tipo);
        void pedir_recurso(int tipo);

};

Monitor::Monitor(){
    n_libres_1=n1;
    n_libres_2=n2;

    tipo_0_lib = newCondVar();
    tipo_0_sol = newCondVar();
    tipo_1_lib = newCondVar();
    tipo_1_sol = newCondVar();
    tipo_2_lib = newCondVar();
    tipo_2_sol = newCondVar();
}

void Monitor::liberar_recurso(int tipo){
    assert(tipo != 1 || tipo != 2 || tipo != 0);
    switch(tipo){
        case 0:
            if(n_libres_1 == n1 || n_libres_2 == n2){
                tipo_0_lib.wait();
            }
            n_libres_1++;
            n_libres_2++;
        case 1:
            if(n_libres_1 == n1)
                tipo_1_lib.wait();
            n_libres_1 ++;
        break;

        case 2:
            if(n_libres_2 == n2)
                tipo_2_lib.wait();
            n_libres_2 ++;
        break;
    }

    if(!tipo_0_sol.empty())
        tipo_0_sol.signal();
    else{
        if(tipo==1 && !tipo_1_sol.empty())
            tipo_1_sol.signal();
        else{
             if(!tipo_2_sol.empty())
                tipo_2_sol.signal();

        }    
    }

    mtx.lock();
    cout << " Recurso " << tipo << " liberado" << endl;
    mtx.unlock();
}

void Monitor::pedir_recurso(int tipo){
    assert (tipo !=0 || tipo != 1 || tipo != 2);

    switch(tipo){
        case 0:
            if(n_libres_1 == 0 || n_libres_2 == 0){
                tipo_0_sol.wait();
            }
            n_libres_1 --;
            n_libres_2 --;
        break;
        case 1:
            if(n_libres_1==0)
                tipo_1_sol.wait();
            n_libres_1--;
        break;
        case 2:
            if(n_libres_2 == 0)
                tipo_2_sol.wait();
            n_libres_2--;
        break;
    }

    mtx.lock();
    cout << "Recurso " << tipo << " consumido"<< endl;
    mtx.unlock();
    
    //! Deberíamos diferenciar entre estado liberador y estado solicitante
    if(!tipo_0_lib.empty())
        tipo_0_lib.signal();
    else{
        if(tipo==1 && !tipo_1_lib.empty()){
            tipo_1_lib.signal();
        }
        else{
            if(!tipo_2_lib.empty())
                tipo_2_lib.signal();
        }
    }
}

//Funciones auxiliares

int selectorTipo(){
    return aleatorio<0,2>();
}

void process_1(MRef<Monitor>monitor){
            int tipo = selectorTipo();
            monitor->pedir_recurso(tipo);
            trabajar();
            monitor->liberar_recurso(tipo);
}

/*********************************************************************************/
/* funcines de las hebras */
/*********************************************************************************/
void hebra_a_procedure(){
    
    MRef <Monitor> monitor = Create<Monitor>();

    switch(ejercicio){
        case 1:
            process_1(monitor);
            
        break;
        case 2:
            ;
        break;
        case 3:
            ;
        break;
        case 4:
            ;
        break;   
        case 5:
            ;
        break;
        case 6:
            ;
        break;
        case 7:
            ;
        break;
        case 8:
            ;
        break;
    }
}

void hebra_b_procedure(){
    switch(ejercicio){
        case 1:
            mtx.lock();
            cout << "No se requiere mi trabajo, soy hebra B" << endl;
            mtx.unlock();
        break;
        case 2:

        break;
        case 3:

        break;
        case 4:

        break;   
        case 5:
            mtx.lock();
            cout << "No se requiere mi trabajo, soy hebra B" << endl;
            mtx.unlock();
        break;
        case 6:
            mtx.lock();
            cout << "No se requiere mi trabajo, soy hebra B" << endl;
            mtx.unlock();
        break;
        case 7:

        break;
        case 8:
            mtx.lock();
            cout << "No se requiere mi trabajo, soy hebra B" << endl;
            mtx.unlock();
        break;
    }
}









/*********************************************************************************/
/* función principal */
/*********************************************************************************/
int main(){
    cin >> ejercicio;
    while(ejercicio < 1 && ejercicio >8){
        cin >> ejercicio;
    }

    thread hebras_a[n_hebras_a[ejercicio-1]];
    thread hebras_b[n_hebras_b[ejercicio-1]];

    for (int i=0; i<n_hebras_a[ejercicio] && n_hebras_a[ejercicio]!=0;i++){
        hebras_a[i] = thread(hebra_a_procedure);
    }

    for (int i=0; i<n_hebras_b[ejercicio] && n_hebras_b[ejercicio]!=0; i++){
        hebras_b[i] = thread(hebra_b_procedure);
    }

    for(int i=0; i<n_hebras_a[ejercicio] && n_hebras_a[ejercicio]!=0; i++){
        hebras_a[i].join();
    }
    
    for(int i=0; i<n_hebras_b[ejercicio] && n_hebras_b[ejercicio]!=0; i++){
        hebras_b[i].join();
    }
}
