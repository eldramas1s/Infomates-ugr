//
// Created by el_dramas on 14/10/23.
//

#include <iostream>
#include <cstring>

#include "imageIO.h"
#include "image.h"

using namespace std;

void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "<program-name> <inputfile.pgm> <outputfile.pgm> <factor>" << endl;
}

int main(int argc, char * argv[]){
    if(argc != 4){
        showEnglishHelp(cerr);
        return 1;
    }

    string inputfile = "input.pgm";
    string outputfile = "output.pgm";
    int factor=1;

    inputfile=argv[1];
    outputfile=argv[2];
    factor=stoi(argv[3]);

    Image icono,imagen;

    if(imagen.Load(inputfile.c_str()))
        cout << "Se ha cargado la imagen " << inputfile << endl;
    else{
        cerr << "No se ha podido cargar la imagen " << inputfile << endl;
        return 1;
    }

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << inputfile << ":" << endl;
    cout << "   Imagen   = " << imagen.get_rows()  << " filas x "
    << imagen.get_cols() << " columnas " << endl;
    cout << "Factor de reducción: " << factor << endl;

    icono=imagen.Subsample(factor);

    if(icono.Save(outputfile.c_str()))
        cout << "Se ha guardado el icono " << outputfile << endl;
    else{
        cerr << "No se ha podido guardar el icono " << outputfile << endl;
        return 1;
    }

    return 0;
}