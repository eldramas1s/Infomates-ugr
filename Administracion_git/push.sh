#! /bin/bash

ruta="/home/el_dramas/Desktop/Infomates/Administracion_git"
ruta_add="/home/el_dramas/Desktop/Infomates/"
fecha=`date +%Y-%j-%T-$$`
cd $ruta_add
echo $fecha > $ruta/push_error.txt
echo $fecha > $ruta/push_ok.txt

if [ $# -ne 0 ]; then
	echo "Numero de parametros erroneo" > $ruta/push_error.txt
	exit
else
	printf "ADD:\n" > $ruta/push_error.txt
	printf "ADD:\n" > $ruta/push_ok.txt
	git add $ruta_add/* 1>> $ruta/push_error.txt 2>> $ruta/push_ok.txt
	git add $ruta_add/* 1>> $ruta/push_error.txt 2>> $ruta/push_ok.txt
	git add $ruta_add/* 1>> $ruta/push_error.txt 2>> $ruta/push_ok.txt

	printf "PUSH:\n" >> $ruta/push_ok.txt
	printf "PUSH:\n" >> $ruta/push_error.txt
	git push 1>> $ruta/push_error.txt 2>> $ruta/push_ok.txt 

fi

