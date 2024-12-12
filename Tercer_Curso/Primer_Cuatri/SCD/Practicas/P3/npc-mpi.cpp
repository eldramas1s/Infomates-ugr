// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: prodcons2.cpp
// Implementación del problema del productor-consumidor con
// un proceso intermedio que gestiona un buffer finito y recibe peticiones
// en orden arbitrario
// (versión con un único productor y un único consumidor)
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <atomic>
#include <mpi.h>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   num_plys          = 3 ,
   id_npc             = 3 ,
   num_procesos_esperado         = 4, 
   num_rondas            = 10,
   etiq_npc                = 1,
   etiq_fin                = 2,
   etiq_recibido           = 3;

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}
// ---------------------------------------------------------------------
// ptoducir produce los numeros en secuencia (1,2,3,....)
// y lleva espera aleatorio
int genera_corazon()
{
   sleep_for( milliseconds( aleatorio<10,100>()) );
   int posicion=int (aleatorio<0,2>()); 
   cout << "NPC  genera posicion " << posicion << endl << flush;
   return posicion;
}
// ---------------------------------------------------------------------

void funcion_npc()
{
   static int puntos[num_plys]={0};
   static int corazon;
   static int fin=-1;
   static int recibido[num_plys]={0};
   int flag=0;
   MPI_Status estado;
   int recv;
   for ( unsigned int i= 0 ; i < num_rondas ; i++ )
   {
      corazon = 5;
      cout << "Ronda " << i << endl << flush; 
      // producir valor
      while(corazon>0){
        cout << "Corazon : " << corazon << endl << flush;
        int id_corazon = genera_corazon();
        cout << " ID : " << id_corazon << endl << flush;
        MPI_Iprobe(id_corazon,etiq_recibido,MPI_COMM_WORLD,&flag,&estado);
        if(flag!=0){
            MPI_Recv(&recv,1,MPI_INT, id_corazon,etiq_recibido, MPI_COMM_WORLD,&estado);
            recibido[id_corazon]=recv;
        }
        // enviar valor
        if(!recibido[id_corazon]){
            cout << "NPC va a enviar corazon a " << id_corazon << endl << flush;
            MPI_Ssend( &corazon, 1, MPI_INT, id_corazon, etiq_npc, MPI_COMM_WORLD );
            puntos[id_corazon]+=corazon;
        }
        corazon -= id_corazon;
      }
      cout << "Puntos: [ " << flush;
      for (int i=0;i<num_plys; i++){
          cout << puntos[i] << " " << flush;
      }
      cout << "]" << endl << flush;
      for(int i=0; i<num_plys;i++){
          recibido[i]=0;
      }
   }

   for (int i=0; i<num_plys; i++){
       MPI_Send(&fin, 1, MPI_INT, i, etiq_fin,MPI_COMM_WORLD);//Realmente no es necesario un fin sabiendo la etiqueta que se manda
   }
}
// ---------------------------------------------------------------------

void funcion_jugador(int id_propio)
{
   int         peticion,
               valor_rec;
   MPI_Status  estado ;
   int flag_fin=0;
   int flag_pet=0;
   int recv=0;

   MPI_Iprobe(id_npc,etiq_fin,MPI_COMM_WORLD,&flag_fin,&estado);
   while(flag_fin==0)
   {
       /* cout << "Hola" << flush; */
       MPI_Iprobe(id_npc,etiq_npc,MPI_COMM_WORLD,&flag_pet,&estado);
       if(flag_pet!=0){
           MPI_Recv(&valor_rec,1,MPI_INT,id_npc,etiq_npc,MPI_COMM_WORLD,&estado);
           cout << "Jugador "<<id_propio << " consigue 1 punto"<< endl<<flush;
           MPI_Send(&recv,1,MPI_INT, id_npc,etiq_recibido,MPI_COMM_WORLD);
       }
       MPI_Iprobe(id_npc,etiq_fin,MPI_COMM_WORLD,&flag_fin,&estado);
   }
   /* cout << "Soy Consumidor "<< orden << "y he terminado" << endl; */
}


// ---------------------------------------------------------------------
int main( int argc, char *argv[] )
{

    //¿Como controlo el orden?

   int id_propio, num_procesos_actual;
   // inicializar MPI, leer identif. de proceso y número de procesos
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

   if ( num_procesos_esperado == num_procesos_actual )
   {
      // ejecutar la operación apropiada a 'id_propio'
      // Cómo controlo el orden dentro de cada rol?
      if ( id_propio>=0 && id_propio < num_plys  )
         funcion_jugador(id_propio);
      else {
         /* cout<< "VOy a ser buffer["<<id_propio<< "]" << endl; */
          funcion_npc();

      }
      
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos_esperado << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   // al terminar el proceso, finalizar MPI
   MPI_Finalize( );
   return 0;
}
