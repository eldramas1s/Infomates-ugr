#!/bin/bash
if [ $# != 1 ]; then
	echo "Numero de parametros erroneo"
	exit 1
fi

#Ejecutamos el ejecutable

./ejecutables/exeSumaVectores $1 >> ./results/SumaVectores.txt
./ejecutables/exeSumaVectoresParallel $1 >> ./results/SumaVectoresParallel.txt
./ejecutables/exeSumaVectoresSections $1 >> ./results/SumaVectoresSections.txt
