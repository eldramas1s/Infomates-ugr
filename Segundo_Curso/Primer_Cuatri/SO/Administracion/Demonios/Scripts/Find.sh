#!/bin/bash
if [ $# != 0 ]; then
	exit
else
	ruta=/home/el_dramas/Desktop/SO/Administracion/Demonios/Results
	find /home/el_dramas/Desktop -atime -1 > $ruta/Find.txt 
	echo `date +%Y-%j-%T-$$` >> $ruta/Find.txt
fi
	
