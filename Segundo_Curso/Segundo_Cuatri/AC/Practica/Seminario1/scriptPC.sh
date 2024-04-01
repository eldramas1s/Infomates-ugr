#!/bin/bash
if [ $# != 1 ]; then
	echo "Numero de parametros erroneo"
	exit 1
fi

#Ejecutamos el ejecutable

echo "Secuencial: "
./ejecutables/exeSumaVectores $1

echo "Parallel for: "
./ejecutables/exeSumaVectoresParallel $1

echo "Parallel sections: "
./ejecutables/exeSumaVectoresSections $1


