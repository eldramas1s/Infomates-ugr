#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)
{
    int i, n=20, tid,x=1;
    int a[n], suma=0, sumalocal;
    
    if (argc < 2)
    {
        fprintf(stderr,"[ERROR] Falta el número de iteraciones y numero de hebras\n");
        if (argc <3){
            fprintf(stderr, "[ERROR] Falta el numero de hebras.\n");
            exit(-1);
        }
        exit(-1);
    }

    n = atoi(argv[1]);

    if(argc >= 3){
        x = atoi(argv[2]);
    }

    if (n>20)
        n=20; 

   for (i=0; i<n; i++)
      a[i]=i; 
 
    #pragma omp parallel num_threads(x) default(none) \
                private(sumalocal,tid) shared(a,suma,n)
    {
        sumalocal=0;
        tid=omp_get_thread_num();

        #pragma omp for private(i) schedule(static) nowait
        for (i=0; i<n; i++)
        {
            sumalocal += a[i];
            printf(" thread %d suma de a[%d]=%d sumalocal=%d \n",
                   tid, i, a[i], sumalocal);
        } 

        #pragma omp atomic 
        suma += sumalocal;

        #pragma omp barrier

        #pragma omp master
        printf("thread master=%d imprime suma=%d\n", tid, suma);
    }  
}

