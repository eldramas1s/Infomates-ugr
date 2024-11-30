#include <thread>
#include <atomic>
#include <mutex>
#include "scd.h"

using namespace std;
using namespace scd;

const int np = 3; //Número de jugadores
const int nc = 4; //Número de casillas disponibles
const int num_rondas = 10; //Numero de rondas
const int corazon=5;

int puntos[np]={0}; //Puntos de los jugadores

//Material comprometido
int shared_vector[nc]={0};

atomic <int> entradas(0);

Semaphore sem_players(0), sem_npc(1);

mutex mtx,em;

int genera_posicion(){
    return aleatorio<0,nc-1>();
}

//Se encarga de imprimir las puntuaciones y devolver el indice de la puntuacion mas alta hasta el momento.
int imprime_puntuacion(){
    int pos_max=-1;
    int max=0;

    mtx.lock();
    cout << "Puntos: [ ";
    for (int i=0; i<np; i++){
        cout << puntos[i] << " ";
        if(puntos[i]>max){
            max=puntos[i];
            pos_max=i;
        }
    }
    mtx.unlock();
    
    return pos_max;;
}

//Vacía el vector compartido, basicamente el mostrador.
void empty_shared_vector(){
    for (int i=0; i<np;i++){
        shared_vector[i]=0;
    }
}

/* Funcion de los jugadores */
void funcion_jugadores(int i){
    int pos_acceso;

    for( int j=0; j<num_rondas; j++ ){

        pos_acceso = genera_posicion();
        
        em.lock();
        if(shared_vector[pos_acceso]==0) puntos[i]+=2;
        else{
            puntos[i]+=shared_vector[pos_acceso];
            if(shared_vector[pos_acceso]==corazon) shared_vector[pos_acceso]-=2;
            if(shared_vector[pos_acceso]==3) shared_vector[pos_acceso]=0;
        }
        entradas=entradas+1;
        em.unlock();
    }

}



/* Funcion del NPC */
void funcion_npc(){
    int pos_insercion;

    for (int i=0; i<num_rondas; i++){
        
        //Genero posicion para el corazón
        pos_insercion=genera_posicion();

        //Garantizo exclusión mutua gracias a la inicializacion de los semaforos
        
        shared_vector[pos_insercion]=corazon;  

        mtx.lock();
        cout << "Corazon colocado" << endl;
        mtx.unlock();
        
        for(int i=0; i<np; i++){
            sem_signal(sem_players);
        }

        while(entradas != np-1){}

        sem_wait(sem_players);

        em.lock();
        empty_shared_vector();
        em.unlock();

        mtx.lock();
        imprime_puntuacion();
        mtx.unlock();


    } 

}




int main(){

    thread players[np];
    thread npc = thread(funcion_npc);

    for ( int i=0; i<np; i++ ){
        players[i]=thread(funcion_jugadores,i);
    }

    npc.join();
    
    for (int i=0; i<np; i++){
        players[i].join();
    }

    //Imprimimos las puntuaciones finales
    
    int ganador=imprime_puntuacion();

    cout << "El ganador es P[ "<< ganador << " ] con " << puntos[ganador] << " puntos" << endl;
}
