#! /bin/bash
home=/home/el_dramas
ruta=$home/Desktop/SO/Administracion/Demonios/Scripts
if [ $# -ne 0 ]; then 
	echo "Numero de parms erroneo" >> $home/log.txt
	exit
else
	free | head -2 >> $home/log.txt
fi
