#!/bin/bash

ruta="/home/el_dramas/Desktop/Infomates/Administracion_git"
if [ $# -ne 0 ]; then
	$ruta/comprobador.sh
	echo "Se ha realizado la llamada por defecto"
	exit
else
	printf "PULL:\n\tOK:\n"
	cat $ruta/pullok.txt
	printf "\tERROR:\n"
	cat $ruta/pullerror.txt
	printf "PUSH:\n\tOK:\n"
	cat $ruta/push_ok.txt
	printf  "\tERROR:\n"
	cat $ruta/push_error.txt
fi
