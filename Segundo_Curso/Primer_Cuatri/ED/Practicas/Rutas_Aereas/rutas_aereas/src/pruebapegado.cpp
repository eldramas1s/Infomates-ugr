
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Imagen.h"

int main(int argc, char * argv[]) {
    if (argc != 8) {
        cout << "Los parametros son :" << endl;
        cout << "1.-La imagen de fondo" << endl;
        cout << "2.-La imagen a pegar" << endl;
        cout << "3.-La máscara de la imagen a pegar" << endl;
        cout << "4.-El nombre de la imagen de salida" << endl;
        cout << "5.-La fila donde pegar" << endl;
        cout << "6.-La columna donde pegar" << endl;
        cout << "7.- 0: Pegado Opaco 1: Pegado Blending" << endl;
        return 0;
    }
    Imagen I, Ip;
    I.LeerImagen(argv[1]);
    Ip.LeerImagen(argv[2], argv[3]);
    int i, j;
    i = atoi(argv[5]);
    j = atoi(argv[6]);

    Tipo_Pegado tp = OPACO;
    int au = atoi(argv[7]);
    if (au != 0)
        tp = BLENDING;


    I.PutImagen(i, j, Ip, tp);
    I.EscribirImagen(argv[4]);

    return 0;
}