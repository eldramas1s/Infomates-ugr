/*
Nombre: Lucas Hidalgo Herrera
DNI: 26512990Q
*/

#include <iostream>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <atomic>
#include <mpi.h>

using namespace std;
using namespace std::chrono;

const int
   num_clientes             = 10 ,
   id_encargado             = 10 ,
   num_procesos_esperado    = 11, 
   num_cajas                = 3,
   tag_pago                 = 1,
   tag_libre                = 2;

const char cajas[num_cajas]={'A','B','C'};

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

void funcion_cliente(int id){

    int valor,caja;
    MPI_Status estado;

    while(true){
        //cout << "Cliente "<< id << " comprando" << endl;
       std::this_thread::sleep_for( milliseconds( aleatorio<10,300>()) );

        cout << "Cliente " << id << ": solicito que se me asigne caja" << endl;

        MPI_Ssend(&valor, 1 ,MPI_INT, id_encargado,tag_pago,MPI_COMM_WORLD);

        //Si paso de aqui es porque el encargado me ha dado paso a pagar

        MPI_Recv(&caja,1,MPI_INT, id_encargado,tag_pago,MPI_COMM_WORLD,&estado);

        cout << "Cliente " << id << ": comienzo pago en caja " << cajas[caja] << endl;
        
        std::this_thread::sleep_for( milliseconds( aleatorio<1000,3000>()) );

        cout << "Cliente " << id << ": termino pago en caja " << cajas[caja] << endl; 
    
        //Cliente avisa de que ha terminado en la caja
        MPI_Ssend(&caja,1,MPI_INT,id_encargado,tag_libre,MPI_COMM_WORLD);
    }
}

void funcion_encargado(){
    static bool libre[num_cajas]={true}; //Guardo el numero de cajas libres
    int num_libres=num_cajas;
    int tag_aceptable,valor;
    MPI_Status estado;
    int pos;
    bool found = false;
    int i=0;
    while(true){

        found=false;

        //Imponemos qué mensaje vamos a leer segun el numero de cajas libres
        if(num_libres>0)
            tag_aceptable=MPI_ANY_TAG;
        if(num_libres==0)
            tag_aceptable=tag_libre;

        MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE,tag_aceptable,MPI_COMM_WORLD,&estado);

        switch (estado.MPI_TAG){
            case tag_pago:
                //Calculamos la posicion libre
                
                for (int i=0; i<num_libres; i++){
                    if(libre[i]&&!found) {
                        found=true;
                        pos=i;
                    }
                }
                libre[pos]=false;
                num_libres--;

                cout << "Encargado: asignada caja " << cajas[pos] << endl; //1 << endl;

                MPI_Ssend(&pos,1,MPI_INT,estado.MPI_SOURCE,tag_pago,MPI_COMM_WORLD);
            break;
            case tag_libre:
                libre[valor]=true;
                num_libres++; 

                cout << "Encargado: liberada caja " << cajas[valor] << endl;//char(cod_ASCII+valor) << " por el cliente " << estado.MPI_SOURCE << endl;
            break;

        }
    }
}

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
      if ( id_propio>=0 && id_propio < num_clientes  )
         funcion_cliente(id_propio);
      else {
          funcion_encargado();
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
