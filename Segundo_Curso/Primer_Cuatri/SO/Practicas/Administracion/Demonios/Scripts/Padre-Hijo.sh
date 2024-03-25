#!/bin/bash
if [ $# != 0 ];then
	exit
else
	nombrearchivo=`date +%Y-%j-%T`
	ps -ef > ~/Desktop/SO/Administracion/Demonios/Results/$nombrearchivo
	echo Mi pid = $$ >> ~/Desktop/SO/Administracion/Demonios/Results/$nombrearchivo
fi
 
