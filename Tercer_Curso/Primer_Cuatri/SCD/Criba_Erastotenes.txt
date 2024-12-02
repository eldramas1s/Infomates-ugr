#include <iostream>
#include <thread>
#include <mpi.h>

using namespace std;

int tag_siguiente=2,tag_print=3,tag_aceptado=4;

void funcion_inicio(int id_propio,int cantidad){
    static int x = 2;
    int i=1;
    MPI_Request request;

    MPI_Send(&x,1,MPI_INT,cantidad-1,tag_print,MPI_COMM_WORLD);
    while(x < cantidad-1){
        i+=2;
        x=i;
        MPI_Send(&x,1,MPI_INT,id_propio+1,tag_siguiente,MPI_COMM_WORLD);
    }
}


void funcion_filtro(int id_propio,int procesos){
    int valor=0,x=0;
    MPI_Status estado;
    MPI_Request request;
    
    MPI_Recv(&valor,1,MPI_INT,id_propio-1,tag_siguiente,MPI_COMM_WORLD, &estado);
    MPI_Send(&valor, 1, MPI_INT, procesos-1, tag_print, MPI_COMM_WORLD);
    while(x < procesos-1){
        MPI_Recv(&x,1,MPI_INT,id_propio-1,tag_siguiente,MPI_COMM_WORLD,&estado);
        if(id_propio<procesos-2){
            if(x%valor!=0){ 
                MPI_Send(&x,1,MPI_INT, id_propio+1,tag_siguiente,MPI_COMM_WORLD);
            }    
        }
    }
    /* if(id_propio <= procesos-2){ */

        /* MPI_Send(&x,1,MPI_INT,id_propio+1,tag_siguiente,MPI_COMM_WORLD); */
    /* } */
}

void funcion_impresor(int procesos){

    int valor=0;
    MPI_Status estado;
    
    cout << "Resultado: [ ";
    MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, tag_print, MPI_COMM_WORLD, &estado);
    cout << valor << " ";
    while(valor<procesos-1){
        MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, tag_print, MPI_COMM_WORLD, &estado);
        cout << valor << " ";
        
    }
    cout << "]" << endl;

}



int main(int argc, char **argv){
    
    int size,id_propio;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id_propio);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(id_propio==0) funcion_inicio(id_propio,size);
    if(id_propio==size-1) funcion_impresor(size);
    if(id_propio>0 && id_propio<=size-2) funcion_filtro(id_propio,size);

    MPI_Finalize();

}
