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
int n_hebras_b[8]={0,2,2,7,0,0,1,0};

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

//EJERCICIO___2 -> Practica 2 lectores
//EJERCICIO___3

class Puente : public HoareMonitor
{
    private:
        int umbral;
        int coches_N, coches_S,N_pueden,S_pueden;
        CondVar cola_n, cola_s;

    public:
        Puente(int umb);
        void EntrarCocheNorte();
        void SalirCocheNorte();
        void EntrarCocheSur();
        void SalirCocheSur();
};

Puente::Puente(int umb){
    coches_N=0;
    coches_S=0;
    umbral = umb;
    N_pueden=umbral;
    S_pueden=umbral;

    cola_n = newCondVar();
    cola_s = newCondVar();
}

void Puente::EntrarCocheNorte(){
    if(coches_S>0 || N_pueden==0){
        cola_n.wait();
    }

    mtx.lock();
    cout << "Norte entrando" << endl;
    mtx.unlock();

    coches_N++;

    if(!cola_s.empty()) N_pueden--;

    if(!cola_n.empty() && N_pueden>0){
        cola_n.signal();
    }
}

void Puente::EntrarCocheSur(){
    if(coches_N>0 || S_pueden == 0)
        cola_s.wait();

    coches_S++;
    mtx.lock();
    cout << "Sur entrando" << endl;
    mtx.unlock();

    if(!cola_n.empty()) S_pueden--;

    if(!cola_s.empty()&&S_pueden>0)
        cola_s.signal();
}

void Puente::SalirCocheNorte(){
    coches_N--;
    mtx.lock();
    cout << "Norte saliendo " << endl;
    mtx.unlock();

    if(coches_N==0){
        cola_s.signal();
        N_pueden=umbral;
    }
}

void Puente::SalirCocheSur(){
    coches_S--;
    
    mtx.lock();
    cout << "Sur saliendo" << endl;
    mtx.unlock();

    if(coches_S==0){
        cola_n.signal();
        S_pueden=umbral;
    }
}


//Funciones auxiliares
void cocheNorte(MRef <Puente> puente){
    while(true){
        puente->EntrarCocheNorte();
        trabajar();
        puente->SalirCocheNorte();
        trabajar();
    }
}

void cocheSur(MRef <Puente> puente){
    while(true){
        puente->EntrarCocheSur();
        trabajar();
        puente->SalirCocheSur();
        trabajar();
    }
}

//EJERCICIO___4

class Olla : public HoareMonitor
{
    private:
        int misioneros, umbral;
        CondVar salvajes, cocinero;

    public:

        Olla(int umb);
        void Servirse_Misionero();
        void Dormir();
        void Rellenar_Olla();
};

Olla::Olla(int umb){
    umbral=umb;
    misioneros=0;
    
    salvajes=newCondVar();
    cocinero=newCondVar();
}

void Olla::Servirse_Misionero(){
    if(misioneros <= 0 ){
        salvajes.wait();
        cocinero.signal();
    }

    misioneros--;

    mtx.lock();
    cout << " Misionero servido " << endl;
    mtx.unlock();

    if(misioneros > 0 && !salvajes.empty()){
    /* if(misioneros > 0){ */ //Produce interbloqueo 
        salvajes.signal();
    }
    else{                   //Quitarlo produce interbloqueo
        cocinero.signal();  
    }
}

void Olla::Dormir(){
    if(misioneros>0) cocinero.wait();
    mtx.lock();
    cout << "Cocinero durmiendo" << endl;
    mtx.unlock();
}

void Olla::Rellenar_Olla(){
    misioneros=umbral;

    mtx.lock();
    cout << "Olla rellena" << endl;
    mtx.unlock();

    if(!salvajes.empty()){
        salvajes.signal();
    }
}


//Funciones auxiliares

void Salvaje(MRef<Olla> monitor){
    while(true){
        monitor->Servirse_Misionero();
        trabajar();
    }
}

void Cocinero(MRef<Olla> monitor){
    while(true){
        monitor->Dormir();
        monitor->Rellenar_Olla();
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

    //MONITORES A USAR
    MRef <Puente> monitor3 = Create<Puente>(10);
    MRef <Olla> monitor4 = Create<Olla>(3);
    switch(ejercicio){
        case 1:

        break;
        case 2:

        break;
        case 3:
            for(int i=0; i<n_hebras_a[ejercicio-1]; i++){
                hebras_a[i] = thread(cocheNorte, monitor3);
            }

            for(int i=0; i<n_hebras_b[ejercicio-1]; i++){
                hebras_b[i] = thread(cocheSur,monitor3);
            }
            

            for(int i=0; i<n_hebras_a[ejercicio-1]; i++){
                hebras_a[i].join();
            }

            for(int i=0; i<n_hebras_b[ejercicio-1]; i++){
                hebras_b[i].join();
            }

        break;
        case 4:
            for(int i=0; i<n_hebras_a[ejercicio-1]; i++){
                hebras_a[i] = thread(Cocinero, monitor4);
            }

            for(int i=0; i<n_hebras_b[ejercicio-1]; i++){
                hebras_b[i] = thread(Salvaje,monitor4);
            }
            

            for(int i=0; i<n_hebras_a[ejercicio-1]; i++){
                hebras_a[i].join();
            }

            for(int i=0; i<n_hebras_b[ejercicio-1]; i++){
                hebras_b[i].join();
            }
        break;

        default:
            cerr << "No existe ese ejercicio" << endl;
        break;
    }
   
}
