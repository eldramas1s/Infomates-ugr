#!/bin/bash
if [ $# != 0 ]; then
	exit
else
	tree /home/el_dramas/Desktop > /home/el_dramas/Desktop/SO/Administracion/Demonios/Results/salvado.txt
	find /home/el_dramas/Desktop/ -atime -1 | cpio -pmduv /tmp/salvadoDesktop >> /home/el_dramas/Desktop/SO/Administracion/Demonios/Results/salvado.txt
	echo `date +%Y-%j-%T-$$` >> /home/el_dramas/Desktop/SO/Administracion/Demonios/Results/salvado.txt
fi
	
