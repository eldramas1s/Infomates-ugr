if [ $# != 2 ]; then
    echo "Ejecucion del programa: ./compiler.sh <ruta relativa archivo c> <nombre ejecutable>"
    exit

else
    archivo=./$1
    gcc -Wall -Wpedantic -Wextra $archivo -o $2
fi