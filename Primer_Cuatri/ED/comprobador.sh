#!/bin/bash

if [ $# -ne 0 ]; then
	$HOME/Desktop/ED/comprobador.sh
	echo "Se ha realizado la llamada por defecto"
	exit
else
	printf "PULL:\n\tOK:\n"
	cat $HOME/Desktop/ED/pullok.txt
	printf "\tERROR:\n"
	cat $HOME/Desktop/ED/pullerror.txt
	printf "PUSH:\n\tOK:\n"
	cat $HOME/Desktop/ED/push_ok.txt
	printf  "\tERROR:\n"
	cat $HOME/Desktop/ED/push_error.txt
fi
