/**
 * 
 Código para multimplicación secuencial matriz cuadrada triangular superior por vector: v2 = m * v1 pmtv-secuencial.c
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

/**
 * @file  pmv-secuencial.c  
 * @brief multimplicación secuencial matriz cuadrada triangular superior por vector: v2 = m * v1
 * 
 * @param int n=atoi(argv[1])  número de componentes de los vectores y número de filas y columnas de la matriz
 * @return 0 upon exit success (print tiempo de cálculo de la multiplicación, longitud vectores y resultados (primer y último componente del resultado para longitudes mayores que 9))
 *  
 * **Compilación**
 * @code
	gcc  -O2  pmtv-secuencial.c -o pmtv-secuencial -lrt
    (-lrt: real time library, es posible que no sea necesario usar -lrt)
 * @endcode
* **Generar ensamblador**
 * @code
 * gcc  -O2 -S pmv-secuencial.c -lrt
 * @endcode
 *  **Ejecución**
 * ~~~~~~~~~~~~~~~~~~~~~{.c}
 * pmtv-secuencial 8    (para 8 componentes en los vectores)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
**/
int main(int argc, char** argv){
    unsigned int N;
    double cgt1,cgt2,ncgt;
    int i,j;
    double suma = 0;
    int chunk=1;
    omp_sched_t kind;

    if (argc < 4){
        printf("Falta tamaño, kind o chunk. \n \t Kind -> (1-static 2-dynamic 3-guided)");
        exit(EXIT_FAILURE);
    }

    //Toma de datos
    N = atoi(argv[1]);
    if(atoi(argv[2])>=1 && atoi(argv[2])<=3){
        kind = atoi(argv[2]);
    }
    else{
        //Por defecto estatico.
        kind = 1;
    }
    chunk = atoi(argv[3]);
    
    omp_set_schedule(kind,chunk);

    double *v1, *v2, **m;
    v1 = (double*)malloc(N*sizeof(double));
    v2 = (double*)malloc(N*sizeof(double));
    m = (double**)malloc(N*sizeof(double*));
    if ((v1 == NULL) || (v2 == NULL) || (m == NULL)) {
        printf("No hay suficiente espacio para v1, v2 y m \n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < N; i++) {
        m[i] = (double*)malloc(N*sizeof(double));
        if (m[i] == NULL) {
            printf("No hay suficiente espacio para m \n");
            exit(EXIT_FAILURE);
        }
    }


    // Inicializar vector y matriz
    // No haremos uso de drand pues hace que la ejecucion sea mas lenta(salvo especificacion).
    for (i = 0; i < N; i++){
        v1[i] = 0.1*i;
        v2[i] = 0;
        for (j = 0; j < i; j++)
            m[i][j] = 0;
        for (j = i; j < N; j++)
            m[i][j] = i*N+j;
    }

    // Calcular v2 = m * v1
    cgt1=omp_get_wtime();
    #pragma omp parallel shared(m,v1,v2)
    {
        #pragma omp for private(j) schedule(runtime)
        for(i = 0; i < N; i++){
            if(i == 0){
                omp_get_schedule(&kind,&chunk);
                printf ("(%d,%d)", kind,chunk);
            }
            for (j = 0; j < N; j++){
                v2[i]+=m[i][j] * v1[j];
            }            
        }
    }
    cgt2=omp_get_wtime();
    ncgt=cgt2-cgt1;

    // for(i = 0; i < N; i++){
    //     for (j = i; j < N; j++)
    //         v2[i] += m[i][j] * v1[j];
    // }
    // Imprimir resultados
    if (N < 10){
        printf("Tiempo: %11.9f\t Tamaño: %u\n", ncgt, N);
        printf("Matriz:\n\t");
        for (i = 0; i < N; i++){
            for (j = 0; j < N; j++)
                printf("%8.6f \t ", m[i][j]);
            printf("\n\t");
        }
        printf("\nVector:\n\t");
        for (i = 0; i < N; i++)
            printf("%8.6f ", v1[i]);
        printf("\n\nVector resultado:\n\t");
        for (i = 0; i < N; i++)
            printf("%8.6f ", v2[i]);
        printf("\n");
    } else {
        printf("Tiempo: %11.9f \t Tamaño: %u \t v2[0]: %8.6f \t v2[N-1]: %8.6f \n",ncgt, N, v2[0], v2[N-1]);
    }
    return(0);
}