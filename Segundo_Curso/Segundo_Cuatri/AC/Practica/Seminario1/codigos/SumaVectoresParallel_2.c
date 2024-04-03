/**
 * 
 Código para suma secuencial de 2 vectores SumaVectores.c
 * 
 */

#include <stdlib.h>	// biblioteca con funciones atoi()
#include <stdio.h>	// biblioteca donde se encuentra la funcion printf()
#include <omp.h> //biblioteca openMP 

#define MAX 33554432	//=2^25
   
double v1[MAX], v2[MAX], v3[MAX]; 
//TODO:Asignar en el scritpt:
    //export OMP_PROC_BIND=spread (podria estar en close)(asegurar que se ejcuta con cores fisicos)
/**
 * @file  SumaVectores.c  
 * @brief _Suma secuencial de dos vectores: v3 = v1 + v2_
 * 
 * @param int n=atoi(argv[1])  numero de componentes a sumar
 * @return 0 upon exit success (print tiempo de calculo de la suma de vectores, longitud vectores y resultados (primer y último componente del resultado para longitudes mayores que 9))
 *
 * **Compilacion**
 * @code
	gcc  -O2  SumaVectores.c -o SumaVectores -lrt
    (-lrt: real time library, es posible que no sea necesario usar -lrt)
 * @endcode
* **Generar ensamblador**
 * @code
 * gcc  -O2 -S SumaVectores.c -lrt
 * @endcode
 *  **Ejecucion**
 * ~~~~~~~~~~~~~~~~~~~~~{.c}
 * SumaVectores 8    (para 8 componentes a sumar)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/
int main(int argc, char** argv){ 
  
  int i; 

  double cgt1,cgt2,ncgt; //para tiempo de ejecucion
  
  //Leer argumento de entrada (numero de componentes del vector)
  if (argc<2){	
    printf("Faltan numero componentes del vector\n");
    exit(-1);
  }
  
  unsigned int N = atoi(argv[1]);

  if(N>MAX) N=MAX;

  //Inicializar vectores 
  #pragma omp parallel for
  
    for(i=0; i<N; i++){ 
        v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1; //Se puede usar drand48() para generar los valores de forma aleatoria (drand48_r() para una version paralela)
    } 
  
  
  int max_num_threads = omp_get_max_threads();
  
  cgt1 = omp_get_wtime();
  //Calcular suma de vectores 
  #pragma omp parallel for 
    for(i=0; i<N; i++) 
        v3[i] = v1[i] + v2[i]; 

  cgt2 = omp_get_wtime();

  ncgt = cgt2-cgt1;
  //Imprimir resultado de la suma y el tiempo de ejecucion
  if (N<15) {
  printf("Tiempo:%11.9f\t/ Max_num_threads: %11.d / Tamanio Vectores:%lu\n",ncgt,max_num_threads,N*sizeof(double)); 
  for(i=0; i<N; i++) 
    printf("/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",
           i,i,i,v1[i],v2[i],v3[i]); 
  }
  else{
    printf("Tiempo:%11.9f\t Max_num_threads: %11.d\t/ Tamanio Vectores:%lu\n",ncgt,max_num_threads,N*sizeof(double)); 
    printf("V1[0]=%f, V2[0]=%f, V3[0]=%f \n V1[N-1]=%f,V2[N-1]=%f,V3[0]=%F\n",v1[0],v2[0],v3[0],v1[N-1],v2[N-1],v3[N-1]);
  }
  return 0; 
}
