#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int EsPrimo(long primo)
{
    int esprimo = 0;

    for (int i = 2; i <= sqrt((double)primo) && esprimo == 0; ++i)
    {
        if (primo % i == 0)
            esprimo = 1;
    }

    return esprimo;
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("\nLlamada al programa: <./hijo> <primo> ");
        exit(-1);
    }

    long primo = strtol(argv[1], NULL, 10);

    if (EsPrimo(primo) == 0)
    {
        printf("\nEl numero %ld es primo.", primo);
        return (EXIT_SUCCESS);
    }

    else
    {
        printf("\n%ld no es primo.", primo);
        while (EsPrimo(primo) == 1)
        {
            primo++;
        }
        printf("\nEl numero primo mas cercano es %ld.", primo);
        return (EXIT_SUCCESS);
    }
}
