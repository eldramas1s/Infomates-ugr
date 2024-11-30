// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: filosofos-plantilla.cpp
// Implementación del problema de los filósofos (sin camarero).
// Plantilla para completar.
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------


#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   num_filosofos = 5 ,              // número de filósofos 
   num_filo_ten  = 2*num_filosofos, // número de filósofos y tenedores 
   num_procesos  = num_filo_ten ,   // número de procesos total (por ahora solo hay filo y ten)
   id_camarero = num_procesos;

int tag_toma= 1;
int tag_suelta= 2;
int tag_sienta=3;
int tag_levanta=4;

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

void funcion_filosofos( int id )
{
  int id_ten_izq = (id+1)              % num_filo_ten, //id. tenedor izq.
      id_ten_der = (id+num_filo_ten-1) % num_filo_ten; //id. tenedor der.
  int valor=0;

  while ( true )
  {
    cout << "Filósofo " << id << " pide sentarse a la mesa. " << endl;
    MPI_Ssend(&valor, 1, MPI_INT,id_camarero, tag_sienta, MPI_COMM_WORLD);

    cout <<"Filósofo " <<id << " solicita ten. izq." <<id_ten_izq <<endl;
    // ... solicitar tenedor izquierdo (completar)
    MPI_Ssend(&valor, 1, MPI_INT, id_ten_izq,tag_toma,MPI_COMM_WORLD);

    cout <<"Filósofo " <<id <<" solicita ten. der." <<id_ten_der <<endl;
    // ... solicitar tenedor derecho (completar)
    MPI_Ssend(&valor, 1, MPI_INT, id_ten_der, tag_toma,MPI_COMM_WORLD);

    cout <<"Filósofo " <<id <<" comienza a comer" <<endl ;
    sleep_for( milliseconds( aleatorio<10,1000>() ) );

    cout <<"Filósofo " <<id <<" suelta ten. izq. " <<id_ten_izq <<endl;
    // ... soltar el tenedor izquierdo (completar)
    MPI_Ssend(&valor, 1, MPI_INT, id_ten_izq, tag_suelta, MPI_COMM_WORLD);

    cout<< "Filósofo " <<id <<" suelta ten. der. " <<id_ten_der <<endl;
    // ... soltar el tenedor derecho (completar)
    MPI_Ssend(&valor, 1, MPI_INT, id_ten_der, tag_suelta, MPI_COMM_WORLD);

    cout << "Filósofo " << id << " pide abandonar la mesa" << endl;
    MPI_Ssend(&valor, 1, MPI_INT, id_camarero, tag_levanta,MPI_COMM_WORLD);

    cout << "Filosofo " << id << " comienza a pensar" << endl;
    sleep_for( milliseconds( aleatorio<10,1000>() ) );
 }
}
// ---------------------------------------------------------------------

void funcion_tenedores( int id )
{
  int valor, id_filosofo ;  // valor recibido, identificador del filósofo
  MPI_Status estado ;       // metadatos de las dos recepciones

  while ( true )
  {
      MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, tag_toma, MPI_COMM_WORLD, &estado);
      id_filosofo=estado.MPI_SOURCE;
     // ...... recibir petición de cualquier filósofo (completar)
     // ...... guardar en 'id_filosofo' el id. del emisor (completar)
     cout <<"\t\t\tTen. " <<id <<" ha sido cogido por filo. " <<id_filosofo <<endl;

     MPI_Recv(&valor,1,MPI_INT, id_filosofo, tag_suelta, MPI_COMM_WORLD, &estado);
     // ...... recibir liberación de filósofo 'id_filosofo' (completar)
     cout <<"\t\t\tTen. "<< id<< " ha sido liberado por filo. " <<id_filosofo <<endl ;
  }
}

// ---------------------------------------------------------------------

void funcion_camarero(){
    int cuenta=0;
    int valor;
    MPI_Status estado;
    while (true){
        if(cuenta<num_filosofos-1){
            MPI_Recv(&valor,1,MPI_INT,MPI_ANY_SOURCE, tag_sienta,MPI_COMM_WORLD, &estado);
            cout << "Filosofo " << estado.MPI_SOURCE << " sentado en la mesa" << endl;
            cuenta++;
        }

        MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, tag_levanta, MPI_COMM_WORLD, &estado);

        cout << "Filosofo "<< estado.MPI_SOURCE << " abandona la mesa" << endl;
        
        cuenta--;
    }
}


// ---------------------------------------------------------------------


int main( int argc, char** argv )
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );


   if ( num_procesos+1 == num_procesos_actual )
   {
      // ejecutar la función correspondiente a 'id_propio'
      if ( id_propio % 2 == 0 && id_propio != num_procesos )          // si es par
         funcion_filosofos( id_propio ); //   es un filósofo
      if ( id_propio % 2 == 1 && id_propio != num_procesos )                               // si es impar
         funcion_tenedores( id_propio ); //   es un tenedor
      if (id_propio==num_procesos){
          funcion_camarero();
      }

        
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   MPI_Finalize( );
   return 0;
}

// ---------------------------------------------------------------------
