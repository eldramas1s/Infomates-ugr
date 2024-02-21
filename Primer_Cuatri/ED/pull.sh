#!/bin/bash
ruta=/home/el_dramas/Desktop/ED
echo `date +%Y-%j-%T-$$` > $ruta/pullerror.txt
echo `date +%Y-%j-%T-$$` > $ruta/pullok.txt
if [ $# != 0 ]; then
	echo "Numero de parametros erroneo" >> $ruta/pullerror.txt 
	exit
else
	printf "PULL:\n" >> $ruta/pullok.txt
	printf "PULL:\n" >> $ruta/pullerror.txt
	git pull $ruta 1>> $ruta/pullok.txt 2>> $ruta/pullerror.txt #Lo tiene así definida la orden
fi
	
