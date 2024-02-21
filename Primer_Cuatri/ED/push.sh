#! /bin/bash

ruta=/home/el_dramas/Desktop/ED
fecha=`date +%Y-%j-%T-$$`
echo $fecha > $ruta/push_error.txt
echo $fecha > $ruta/push_ok.txt 

if [ $# -ne 0 ]; then 
	echo "Numero de parametros erroneo" > $ruta/push_error.txt
	exit
else 
	printf "ADD:\n" > $ruta/push_ok.txt 
	printf "ADD:\n" > $ruta/push_error.txt
	git add $ruta/Practicas 1>> $ruta/push_ok.txt 2>> $ruta/push_error.txt
	git add $ruta/retos 1>> $ruta/push_ok.txt 2>> $ruta/push_error.txt
	git add $ruta/Ejercicios 1>> $ruta/push_ok.txt 2>> $ruta/push_error.txt
		
	printf "PUSH:\n" >> $ruta/push_ok.txt 
	printf "PUSH:\n" >> $ruta/push_error.txt	
	git push $ruta 1>> $ruta/push_ok.txt 2>> $ruta/push_error.txt #Si no hay nada que subir pondra "Everything-up-to-date" en el archivo error (asi esta predefinido en la orden git push)
fi

