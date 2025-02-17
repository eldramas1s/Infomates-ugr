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
            int dynVar = omp_get_dynamic();
            int nthreadsVar = omp_get_max_threads();
            int threadLimitVar = omp_get_thread_limit();
            int modifier;
            omp_sched_t kind;
            omp_get_schedule(&kind, &modifier);

            printf("Ajuste dinamico(0->true):%d\n",dynVar);
            printf("Numero de hebras: %d\n",nthreadsVar);
            printf("Limite de hebras: %d\n",threadLimitVar);
            printf("Kind(1->Static 2->Dynamic 3->Guided): %d\n",kind);
            printf("Chunk:%d\n",modifier);

        }
        //suma = suma + a[i];
        /*printf(" thread %d suma a[%d]=%d suma=%d \n",
               omp_get_thread_num(),i,a[i],suma);*/
    }

    printf("Fuera de 'parallel for' suma=%d\n",suma); 
    int dynVar = omp_get_dynamic();
    int nthreadsVar = omp_get_max_threads();
    int threadLimitVar = omp_get_thread_limit();
    int modifier;
    omp_sched_t kind;
    omp_get_schedule(&kind, &modifier);

    printf("Ajuste dinamico(0->true):%d\n",dynVar);
    printf("Numero de hebras: %d\n",nthreadsVar);
    printf("Limite de hebras: %d\n",threadLimitVar);
    printf("Kind(1->Static 2->Dynamic 3->Guided): %d\n",kind);
    printf("Chunk: %d\n",modifier);
}
