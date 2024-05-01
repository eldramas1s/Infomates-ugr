#!/bin/bash

if [[ $# -lt 2 ]]
then
	echo  "compiler archivo ejecutable [-f]"
	exit 1
else
	case $# in
		2)
			gcc -O2 ./codigos/$1 -o ./ejecutables/$2
			;;
		3)
			gcc -O2 -fopenmp ./codigos/$1 -o ./ejecutables/$2
			;;
		*)
			echo "Lo siento no ha llamado bien al programa"
			exit 1
	esac
fi
