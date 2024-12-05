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
   num_prod          = 3 ,
   id_buffer             = 3 ,
   num_cons         = 2 ,
   num_procesos_esperado         = 6, 
   num_items             = 30,
   tam_vector            = 10,
   etiq_P                = 1,
   etiq_C                = 2,
   etiq_B                = 0;


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
int producir(int orden, int num_vals)
{
   static int contador = orden*num_vals ;
   sleep_for( milliseconds( aleatorio<10,100>()) );
   contador++ ;
   cout << "Productor " << orden << " ha producido valor " << contador << endl << flush;
   return contador ;
}
// ---------------------------------------------------------------------

void funcion_productor(int orden)
{
   for ( unsigned int i= 0 ; i < num_items/num_prod ; i++ )
   {
      // producir valor
      int valor_prod = producir(orden, num_items/num_prod);
      // enviar valor
      cout << "Productor " << orden << " va a enviar valor " << valor_prod << endl << flush;
      MPI_Ssend( &valor_prod, 1, MPI_INT, id_buffer, etiq_P, MPI_COMM_WORLD );
   }
}
// ---------------------------------------------------------------------

void consumir( int valor_cons, int orden )
{
   // espera bloqueada
   sleep_for( milliseconds( aleatorio<110,200>()) );
   cout << "\t\t\tConsumidor " << orden <<  " ha consumido valor " << valor_cons << endl << flush ;
}
// ---------------------------------------------------------------------

void funcion_consumidor(int orden)
{
   int         peticion,
               valor_rec;
   MPI_Status  estado ;

   for( unsigned int i=0 ; i < num_items/num_cons; i++ )
   {
       /* cout << "Soy el consumidor [" << orden << "] voy a pedir dato i " << i <<  endl; */
      MPI_Ssend( &peticion,  1, MPI_INT, id_buffer, etiq_C, MPI_COMM_WORLD);
       /* cout << "Soy el consumidor [" << orden << "] voy a recibir dato i " << i << endl; */

      MPI_Recv ( &valor_rec, 1, MPI_INT, id_buffer, etiq_B, MPI_COMM_WORLD,&estado );
      cout << "\t\t\tConsumidor " << orden << " ha recibido valor " << valor_rec << endl << flush ;
      consumir( valor_rec, orden );
   }
   /* cout << "Soy Consumidor "<< orden << "y he terminado" << endl; */
}
// ---------------------------------------------------------------------

void funcion_buffer()
{
   int        buffer[tam_vector],      // buffer con celdas ocupadas y vacías
              valor,                   // valor recibido o enviado
              primera_libre       = 0, // índice de primera celda libre
              primera_ocupada     = 0, // índice de primera celda ocupada
              num_celdas_ocupadas = 0, // número de celdas ocupadas
              tag_aceptable ;    // identificador de emisor aceptable
   MPI_Status estado ;                 // metadatos del mensaje recibido

   for( unsigned int i=0 ; i < num_items*2 ; i++ )
   {
       int id_C_accept;

       if(buffer[primera_ocupada]%2==0)
           id_C_accept=num_prod+1;
       else
           id_C_accept=num_prod+2;

      // 1. determinar si puede enviar solo prod., solo cons, o todos

      if ( num_celdas_ocupadas == 0 )               // si buffer vacío
         tag_aceptable = etiq_P ;       // $~~~$ solo prod.
      else if ( num_celdas_ocupadas == tam_vector ) // si buffer lleno
         tag_aceptable = etiq_C ;      // $~~~$ solo cons.
      else                                          // si no vacío ni lleno
         tag_aceptable = MPI_ANY_TAG ;     // $~~~$ cualquiera
    /* cout << "Soy el buffer y la etiqueta que acepto es " << tag_aceptable << endl; */
      // 2. recibir un mensaje del emisor o emisores aceptables


      switch (tag_aceptable)
      {
          case etiq_P:
            MPI_Recv(&valor,1,MPI_INT,MPI_ANY_SOURCE,etiq_P,MPI_COMM_WORLD,&estado);
          break;
          case etiq_C:
            MPI_Recv(&valor, 1, MPI_INT, id_C_accept, etiq_C,MPI_COMM_WORLD,&estado);
          break;
          case MPI_ANY_TAG:
            //Priorizo consumidores
            int flag=0;

            while (flag == 0){
               MPI_Iprobe(id_C_accept,etiq_C,MPI_COMM_WORLD,&flag,&estado);
               if(flag!=0){
                  MPI_Recv(&valor,1,MPI_INT,id_C_accept,etiq_C,MPI_COMM_WORLD,&estado);
               }
               else{
                  MPI_Iprobe(MPI_ANY_SOURCE,etiq_P,MPI_COMM_WORLD,&flag, &estado);
                  if(flag!=0){
                     MPI_Recv(&valor,1,MPI_INT,MPI_ANY_SOURCE,etiq_P,MPI_COMM_WORLD,&estado);
                  }
               }
            }
            
            break;
      }
      // 3. procesar el mensaje recibido

      
      if( estado.MPI_SOURCE >=0  && estado.MPI_SOURCE < num_prod ){ 
         buffer[primera_libre] = valor ;
            primera_libre = (primera_libre+1) % tam_vector ;
            num_celdas_ocupadas++ ;
            cout << "\t   Buffer ha recibido valor " << valor << endl ;
      
        
      }
      if( estado.MPI_SOURCE > id_buffer && estado.MPI_SOURCE < num_procesos_esperado ){
         valor = buffer[primera_ocupada] ;
         primera_ocupada = (primera_ocupada+1) % tam_vector ;
         num_celdas_ocupadas-- ;
         cout << "\t   Buffer va a enviar valor " << valor << " a " << estado.MPI_SOURCE<< endl ;
         MPI_Ssend( &valor, 1, MPI_INT, estado.MPI_SOURCE, etiq_B, MPI_COMM_WORLD);
      
      }
   }

   /* cout << "Soy buffer y he terminado" << endl; */
}

// ---------------------------------------------------------------------
// Sacar num_vals
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
      if ( id_propio>=0 && id_propio < num_prod  )
         funcion_productor((num_procesos_esperado-num_cons+id_propio-1)%num_prod);
      else if ( id_propio == id_buffer ){
         /* cout<< "VOy a ser buffer["<<id_propio<< "]" << endl; */
          funcion_buffer();

        }
      else
         funcion_consumidor((num_procesos_esperado-num_prod+id_propio-1)%num_cons);
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
