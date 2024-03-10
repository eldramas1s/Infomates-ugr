//
// Created by el_dramas on 13/10/23.
//

#include <iostream>

#include "image.h"

using namespace std;

void ComparadorError(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "<program-name> <image1.pgm> <image2.pgm>" << endl;
}

int main(int argc,char * argv[]){
    if(argc!=3){
        ComparadorError(cerr);
        return 1;
    }

    string imagen1s,imagen2s;

    imagen1s=argv[1];
    imagen2s=argv[2];

    //Mostramos los datos
    cout << endl;
    cout << "Imagen1: " << imagen1s << endl;
    cout << "Imagen2: " << imagen2s << endl;
    cout << endl;

    Image i1,i2;
    if(i1.Load(imagen1s.c_str())) cout << "Se ha cargado la imagen 1" << endl;
    else{
        cerr << "No se ha podido cargar la imagen " << imagen1s << endl;
        return 1;
    }
    if(i2.Load(imagen2s.c_str())) cout << "Se ha cargado la imagen 2" << endl;
    else{
        cerr << "No se ha podido cargar la imagen " << imagen2s << endl;
        return 1;
    }
    if(i1==i2) cout << "Son la misma imagen." << endl;
    else cout << "Son imagenes distintas" << endl;
}