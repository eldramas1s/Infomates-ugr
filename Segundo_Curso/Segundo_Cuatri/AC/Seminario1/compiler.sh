#!/bin/bash

if [ $# != 1 ]; then
    echo 'Numero de parametros erroneo, se espera un nombre de programa'
    exit 1
fi
archivo="$HOME/Desktop/Infomates/Segundo_Curso/Segundo_Cuatri/AC/Seminario1/codigos/$1.c"
ejecutable="$HOME/Desktop/Infomates/Segundo_Curso/Segundo_Cuatri/AC/Seminario1/ejecutables/exe$1"
gcc -O2 -fopenmp -o $ejecutable $archivo
exit