#!/bin/bash
if [ $# != 0 ]; then 
	exit
else
	ls -la ~ >> /home/el_dramas/Desktop/SO/Administracion/Demonios/listahome-`date +%Y-%j-%T-$$`.txt
fi
