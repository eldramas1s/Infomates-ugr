#include <iostream>
#include <thread>
#include <mpi.h>

using namespace std;

void funcion_inicio(int id_propio,int procesos){
    static int x = 2;
    int i=1;
    MPI_Status estado;
    MPI_Request request;

    MPI_Send(&x,1,MPI_INT,procesos-1,MPI_ANY_TAG,MPI_COMM_WORLD);
    cout << "Numero " << x << " enviado."<<endl;
    
    while(x!=procesos-1){
        i+=2;
        x=i;
        MPI_Send(&x,1,MPI_INT,id_propio+1,0,MPI_COMM_WORLD);
        MPI_Irecv(&x,1,MPI_INT,procesos-1,MPI_ANY_TAG,MPI_COMM_WORLD, &request);
    }
}


void funcion_filtro(int id_propio,int procesos){
    int valor,x;
    MPI_Status estado;
    MPI_Request request;
    //Recibe el dato del anterior
    MPI_Recv(&valor,1,MPI_INT,id_propio-1,0,MPI_COMM_WORLD, &estado);
    MPI_Send(&valor, 1, MPI_INT, procesos+1, 0, MPI_COMM_WORLD);

    while(x!=procesos-1){
        MPI_Recv(&valor,1,MPI_INT,id_propio-1,0,MPI_COMM_WORLD,&estado);
        if(id_propio<(procesos-2))
            if(x%valor!=0){
                MPI_Send(&x,1,MPI_INT, id_propio+1,0,MPI_COMM_WORLD);
            }
        MPI_Irecv(&x,1, MPI_INT,procesos-1,MPI_ANY_TAG,MPI_COMM_WORLD,&request);
    }
}

void funcion_impresor(int procesos){

    int valor;
    MPI_Request request;
    MPI_Irecv(&valor, 1, MPI_INT,0,0,MPI_COMM_WORLD, &request);
    cout << "Lista de primos: "<< valor << " ";
    MPI_Send(&valor, 1, MPI_INT,0,0,MPI_COMM_WORLD);
    while(valor!=procesos-1){
        MPI_Irecv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &request);
        cout << valor << " ";
        MPI_Send(&valor, 1, MPI_INT, request->MPI_SOURCE, 0, MPI_COMM_WORLD);
    }
}



int main(int argc, char **argv){
    
    int size,id_propio;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id_propio);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int tam = size;

    switch (id_propio){
        case 0:
            funcion_inicio(id_propio,size);
        break;
        case tam-1:
            funcion_impresor(size);
        break;
        default:
            funcion_filtro(id_propio, size);
    }

    MPI_Finalize();

}
