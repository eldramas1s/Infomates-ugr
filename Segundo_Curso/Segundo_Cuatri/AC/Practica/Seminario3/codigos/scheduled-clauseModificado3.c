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
 
    int schedule;
    omp_sched_t kind;

    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("Dentro de parallel - antes modificacion: \n");
            printf("\t Dyn-var(0->true): %d \n", omp_get_dynamic());
            printf("Num threads: %d\n",omp_get_max_threads()),
            omp_get_schedule(&kind,&schedule);
            printf("Kind(1->Static 2->Dynamic 3->Guided): %d\n",kind);
            printf("Chunk: %d\n",schedule);
        }
        
        #pragma omp for firstprivate(suma) \
                    lastprivate(suma) schedule(dynamic,chunk)
        for (i=0; i<n; i++)
        {
            if(i==0){
                omp_set_dynamic(5);
                omp_set_schedule(3,5);
                printf("Dentro de parallel - despues modificacion: \n");
                printf("\t Dyn-var(0->true): %d \n", omp_get_dynamic());
                printf("Num threads: %d\n",omp_get_max_threads()),
                omp_get_schedule(&kind,&schedule);
                printf("Kind(1->Static 2->Dynamic 3->Guided): %d\n",kind);
                printf("Chunk: %d\n",schedule);

            }
            suma = suma + a[i];
            printf(" thread %d suma a[%d]=%d suma=%d \n",
                omp_get_thread_num(),i,a[i],suma);
        }
    }
    

    printf("Fuera de 'parallel for' suma=%d\n",suma); 
    printf("\t Dyn-var(0->true): %d \n", omp_get_dynamic());
    printf("Num threads: %d\n",omp_get_max_threads()),
    omp_get_schedule(&kind,&schedule);
    printf("Kind(1->Static 2->Dynamic 3->Guided): %d\n",kind);
    printf("Chunk: %d\n",schedule);
    return 0;
}

