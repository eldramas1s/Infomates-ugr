#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv)
{
    int i, n=200, chunk, a[n], suma=0;
    
    if(argc < 3)
    {
        fprintf(stderr,"\nFalta iteraciones o chunk\n");
        exit(-1);
    }

    n = atoi(argv[1]);
    if (n>200)
        n=200;

    chunk = atoi(argv[2]); 

    for (i=0; i<n; i++)
        a[i] = i; 
 
    #pragma omp parallel for firstprivate(suma) \
                lastprivate(suma) schedule(dynamic,chunk)
    for (i=0; i<n; i++)
    {
        if(i==0){
            printf("Numero de hebras: %d\n",omp_get_num_threads());
            printf("Numero de procesos: %d\n",omp_get_num_procs());
            printf("Omp in Parallel(0->false):%d\n",omp_in_parallel());
        }
        suma = suma + a[i];
        printf(" thread %d suma a[%d]=%d suma=%d \n",
               omp_get_thread_num(),i,a[i],suma);
    }

    printf("Fuera de 'parallel for' suma=%d\n",suma); 
    printf("Numero de hebras: %d\n",omp_get_num_threads());
    printf("Numero de procesos: %d\n",omp_get_num_procs());
    printf("Omp in Parallel(0->false):%d\n",omp_in_parallel());
}
