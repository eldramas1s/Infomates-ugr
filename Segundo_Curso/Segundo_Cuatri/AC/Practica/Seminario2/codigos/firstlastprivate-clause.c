/**
 * 
 Cláusulas firstprivate lastprivate
 *
 **/

#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
  #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif

/**
 * @file  firstlastprivate-clause.c 
 * @brief _Parte del código de suma paralalela_
 * @return 0 upon exit success (print la variable suma dentro y fuera del <tt>parallel</tt>)
 *  
 * **Objetivo**
 * 
 * El código usa:
 * 
 * - Directivas <tt>parallel, for</tt> 
 * - Cláusulas <tt>firstprivate, lastprivate</tt> 
 * - Funciones <tt>omp_get_thread_num()</tt> 
 *
 * **Compilación **
 * @code
 * gcc -O2 -fopenmp -o firstlastprivate-clause firstlastprivate-clause.c
 * @endcode
 * 
 *  **Ejecución **
 * ~~~~~~~~~~~~~~~~~~~~~
 * firstlastprivate-clause 
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
**/
int main()
{
   int i, n = 10;
   int a[n],suma=0;

   for (i=0; i<n; i++)
      a[i] = i;

#pragma omp parallel 
{
   #pragma omp for firstprivate(suma) lastprivate(suma)
   for (i=0; i<n; i++)
   {
       suma = suma + a[i];
       printf(" Hebra %d suma a[%d] suma=%d \n",
             omp_get_thread_num(),i,suma);
   } 

   #pragma omp single
   {
      suma+=a[1];
   } 
}
   
   printf("\nFuera de la construcción parallel suma=%d\n",suma); 
   return(0);
}
