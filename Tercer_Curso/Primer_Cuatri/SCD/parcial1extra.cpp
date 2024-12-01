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

Semaphore s[np]={0,0,0};
Semaphore sem_npc(0);

mutex mtx,em;

int generar_posicion(){
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
    cout << "]" << endl<< endl;
    mtx.unlock();
    
    return pos_max;
}

//Vacía el vector compartido, basicamente el mostrador.
void empty_shared_vector(){
    em.lock();
    for (int i=0; i<np;i++){
        shared_vector[i]=0;
    }
    em.unlock();
}

/* Funcion de los jugadores */
void funcion_jugadores(int i){
    int pos;

    for(int j=0; j<num_rondas; j++){
        pos=generar_posicion();

        sem_wait(s[i]);

        //Entramos en seccion critica
        
        em.lock();
        puntos[i]+=shared_vector[pos];
        switch (shared_vector[pos])
        {
            case 5:
                shared_vector[pos]-=2;
            break;
            case 3:
                shared_vector[pos]=0;
            break;
        }

        em.unlock();

        entradas = entradas+1;
        
        if(entradas = np){
            sem_signal(sem_npc);
            entradas=0;
        }
    }
}



/* Funcion del NPC */
void funcion_npc(){
    int pos;

    for(int i=0; i<num_rondas; i++){
       

        //Numero de ronda
        mtx.lock();
        cout << "_____________________________"<<endl<<endl;
        cout << "Ronda " << i+1 << endl;
        cout << "------------------------------" <<endl<<endl;
        mtx.unlock();

        pos = generar_posicion();
        
        //Esperamos que acabe la ronda anterior

        em.lock();
        shared_vector[pos]=corazon;
        em.unlock();

        mtx.lock();
        cout << "\t\tCorazon puesto" << endl;
        cout << "\t\t¡Que comience la caza!" << endl;
        mtx.unlock();


        for (int j=0; j<np;j++){
            sem_signal(s[j]);
        }
        
        sem_wait(sem_npc);

        imprime_puntuacion();

        empty_shared_vector();
    }
}




int main(){
    
    //Inicialización de los semáforos
    
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
   
    cout << "=============================================" << endl << endl;
    cout << "FIN DE LA PARTIDA" << endl;

    int ganador=imprime_puntuacion();

    cout << "El ganador es P[ "<< ganador << " ] con " << puntos[ganador] << " puntos" << endl;
}
