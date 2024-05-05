#!/bin/bash
ruta_pull="/home/el_dramas/Desktop/Infomates"
ruta="/home/el_dramas/Desktop/Infomates/Administracion_git"
echo `date +%Y-%j-%T-$$` > $ruta/pullerror.txt
echo `date +%Y-%j-%T-$$` > $ruta/pullok.txt
if [ $# != 0 ]; then
	echo "Numero de parametros erroneo" >> $ruta/pullerror.txt 
	exit
else
	origen=`pwd`
	printf "PULL:\n" >> $ruta/pullok.txt
	printf "PULL:\n" >> $ruta/pullerror.txt
	cd $ruta_pull
	git pull 1>> $ruta/pullok.txt 2>> $ruta/pullerror.txt #Lo tiene así definida la orden
	cd $origen
fi
	
