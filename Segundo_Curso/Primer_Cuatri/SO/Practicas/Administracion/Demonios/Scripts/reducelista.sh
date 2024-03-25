#!/bin/bash
if [ $# != 0 ]; then
	exit
else	
	ruta=/home/el_dramas/Desktop/SO/Administracion/Demonios/Results
	head -n 10 $ruta/BorraCores.txt > $ruta/tmp.txt
	cp $ruta/tmp.txt $ruta/BorraCores.txt
	rm $ruta/tmp.txt
	echo `date +%Y-%j-%T-$$` >> /$ruta/BorraCores.txt	
fi
