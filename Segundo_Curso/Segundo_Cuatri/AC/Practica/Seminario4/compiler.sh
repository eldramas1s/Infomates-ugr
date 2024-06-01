#!/bin/bash

if [[ $# -lt 2 ]]
then
	echo  "compiler archivo ejecutable [-CompilerOpcion] [-f]"
	exit 1
else
	case $# in
		2)
			gcc -O2 ./codigos/$1.c -o ./ejecutables/$2
			;;
		3)
			gcc $3 ./codigos/$1.c -o ./ejecutables/$2
			;;
		4)	
			gcc $3 ./codigos/$1.c -o ./ejecutables/$2$3
			gcc $3 -S ./codigos/$1.c -o ./ensamblador/$1$3.s
			;;
		*)
			echo "Lo siento no ha llamado bien al programa"
			exit 1
			;;
	esac
fi
