#!/bin/bash

# Verifica que se pasen exactamente 2 argumentos
if [ "$#" -ne 2 ]; then
    echo "Uso: $0 <usuario> <servidor>"
    echo "  <usuario>   → Nombre del usuario SSH"
    echo "  <servidor>  → 1 para 192.168.57.2, 2 para 192.168.57.3"
    exit 1
fi

USUARIO="$1"
DESTINO="$2"
CLAVE="./llaves/llave_prueba"

# Elegir IP según segundo argumento
if [ "$DESTINO" -eq 1 ]; then
    IP="192.168.57.2"
elif [ "$DESTINO" -eq 2 ]; then
    IP="192.168.57.3"
else
    echo "Error: el segundo argumento debe ser 1 o 2"
    exit 1
fi

# Ejecutar SSH
ssh -i "$CLAVE" "${USUARIO}@${IP}"
