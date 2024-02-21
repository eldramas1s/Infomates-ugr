#!/bin/bash
if [ $# != 0 ]; then
	exit
	echo "Numero de parametros erroneo" >> /home/el_dramas/Desktop/SO/Administracion/Demonios/Results/listabusqueda.txt
else
	echo `date +%Y-%j-%T-$$` ":" `pwd` >> /home/el_dramas/Desktop/SO/Administracion/Demonios/Results/listabusqueda.txt
fi 
