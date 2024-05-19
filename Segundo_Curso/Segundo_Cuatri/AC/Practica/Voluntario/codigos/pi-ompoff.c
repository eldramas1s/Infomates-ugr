/**
 * 
PI secuencial con integración numérica. 
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>

/**
 * @file  pi.c 
 * @brief PI secuencial con integración numérica, área de rectángulos
 * @author Mancia Anguita
 *  
 * **Compilación**
 * @code
 *  gcc -O2 pi.c -o pi
 * @endcode
 * 
 *  **Ejecución**
 * ~~~~~~~~~~~~~~~~~~~~~
 * ./pi   1000000    (1000000 intervalos de integración)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/
int main(int argc, char **argv)
{
  register double width;
  double sum;
  register int intervals, i; 
  double pi_t1, pi_t2, pi_tt,tr_t1,tr_t2,tr_tt; //para tiempo
    
  //Los procesos calculan PI en paralelo
  if (argc<2) {
    printf("Falta número de intevalos");
    exit(-1);
  }

  intervals=atoi(argv[1]);  

  if (intervals<1) {
    intervals=1E6; 
    printf("Intervalos=%d",intervals);
  }

  width = 1.0 / intervals;
  sum = 0;

  //Transmision de datos a memoria (mapeado)//
  tr_t1 = omp_get_wtime();

  #pragma omp target enter data map(to: width,intervals,sum)

  tr_t2 = omp_get_wtime();
  //Fin Transmision de datos a memoria (mapeado)//

  tr_tt = tr_t2 - tr_t1;  //Tiempo mapeado

  //CALCULO DE PI//
  pi_t1 = omp_get_wtime();

  #pragma omp target teams distribute parallel for reduction(+:sum)
    for (i=0; i<intervals; ++i){
      register double x = (i+0.5)*width;
      sum+=(double)(4/(1+x*x));
    }

  #pragma omp target exit data map(delete:intervals,width)map(from:sum)
  sum *= width;
  pi_t2 = omp_get_wtime();
  //FIN CALCULO PI//

  pi_tt= pi_t2-pi_t1;     //Tiempo calculos
  printf("Iteraciones:\t%d\t. PI:\t%26.24f\t. Tiempos:\n\tTransmision:%8.6f\n\tCalculos:\t%8.6f\n", intervals,sum,tr_tt,pi_tt);

  return(0);
}