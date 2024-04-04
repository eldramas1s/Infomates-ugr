/**
 * 
 Código para suma secuencial de 2 vectores SumaVectores.c
 * 
 */

#include <stdlib.h>	// biblioteca con funciones atoi()
#include <stdio.h>	// biblioteca donde se encuentra la función printf()
#include <omp.h> //biblioteca openMP

//Tratamos siempre como vector global
#define PC
#define NUM_THREADS 4
#define MAX 2^25-1	//=2^25
   
double v1[MAX], v2[MAX], v3[MAX]; 

/**
 * @file  SumaVectores.c  
 * @brief _Suma secuencial de dos vectores: v3 = v1 + v2_
 * 
 * @param int n=atoi(argv[1])  número de componentes a sumar
 * @return 0 upon exit success (print tiempo de cálculo de la suma de vectores, longitud vectores y resultados (primer y último componente del resultado para longitudes mayores que 9))
 *
 * **Compilación**
 * @code
	gcc  -O2  SumaVectores.c -o SumaVectores -lrt
    (-lrt: real time library, es posible que no sea necesario usar -lrt)
 * @endcode
* **Generar ensamblador**
 * @code
 * gcc  -O2 -S SumaVectores.c -lrt
 * @endcode
 *  **Ejecución**
 * ~~~~~~~~~~~~~~~~~~~~~{.c}
 * SumaVectores 8    (para 8 componentes a sumar)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/
int main(int argc, char** argv){ 
  
  int i; 
  double cgt1,cgt2; double ncgt; //para tiempo de ejecución
  
  //Leer argumento de entrada (nº de componentes del vector)
  if (argc<2){	
    printf("Faltan nº componentes del vector\n");
    exit(-1);
  }
  
  unsigned int n = atoi(argv[1]);
  long unsigned int tam = n*sizeof(unsigned int);
  
  //N=15;
  printf("Tamaño Vectores:%lu (%lu B)\n",tam, sizeof(unsigned int)); 
  printf("N: %u\n", n);
  //TODO: Corregir y preguntar poke hace el cambio siempre
  if (n>MAX) n=MAX;
  printf("N: %u\n", n);
  //Inicializar vectores 

  #ifdef PC 
  omp_set_num_threads(NUM_THREADS);
  #endif
  
  int max_num_threads = omp_get_max_threads();
  int num_threads_i = 0;
  #pragma omp parallel 
  {
    printf("N: %u\n", n);
    #pragma omp for
    for(i=0; i<n; i++)
      v1[i] = n*0.1+i*0.1; v2[i] = n*0.1-i*0.1; //Se puede usar drand48() para generar los valores de forma aleatoria (drand48_r() para una versión paralela) 
  }
  num_threads_i = omp_get_num_threads();
  cgt1 = omp_get_wtime();

  //Calcular suma de vectores 

  int num_threads_p = 0;
  #pragma omp parallel 
  {
    #pragma omp for
    for(i=0; i<n; i++){
      v3[i] = v1[i] + v2[i];
    } 
      
    num_threads_p = omp_get_num_threads();
  }

 
 
  cgt2 = omp_get_wtime();

  ncgt=cgt2-cgt1;

  printf ( "Threads:\n\t Inicializacion: %d \n\t Calculo: %d\n",num_threads_i,num_threads_p);

  //Imprimir resultado de la suma y el tiempo de ejecución
  if (n<15) {
    printf("Tiempo:%f\t / Tamaño Vectores:%u\n",ncgt,n); 
    //Imprimir vector y suma
    for(i=0; i<n; i++) 
      printf("/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",
           i,i,i,v1[i],v2[i],v3[i]); 
  }
  else
    //printf("Tiempo:%f\t / Tamaño Vectores:%lu\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",
    //       ncgt,tam,v1[0],v2[0],v3[0],N-1,N-1,N-1,v1[N-1],v2[N-1],v3[N-1]); 
      printf("Tiempo:%f\t NumThreads:%u\n",ncgt,num_threads_p);
  return 0; 
}
