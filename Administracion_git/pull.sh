#!/bin/bash
ruta_pull="/home/el_dramas/Desktop/Infomates"
ruta="/home/el_dramas/Desktop/Infomates/Administracion_git"
echo `date +%Y-%j-%T-$$` > $ruta/pull_error.txt
echo `date +%Y-%j-%T-$$` > $ruta/pull_ok.txt
if [ $# != 0 ]; then
	echo "Numero de parametros erroneo" >> $ruta/pullerror.txt 
	exit
else
	origen=`pwd`
	printf "PULL:\n" >> $ruta/pull_error.txt
	printf "PULL:\n" >> $ruta/pull_ok.txt
	cd $ruta_pull
	git pull 1>> $ruta/pull_error.txt 2>> $ruta/pull_ok.txt #Lo tiene así definida la orden
	cd $origen
fi
	
