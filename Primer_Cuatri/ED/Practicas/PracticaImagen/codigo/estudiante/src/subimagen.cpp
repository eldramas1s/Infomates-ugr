//
// Created by el_dramas on 7/10/23.
//
//This program is meant to be used to extract a piece of an image//

#include <iostream>
#include <string>
#include "image.cpp"

using namespace std;

void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "<subimagen> <inputfile.pgm> <outputfile.pgm> <initial-row> <initial-column> <height> <width>" << endl;
}

int main(int argc, char * argv[]){
    //Comprobación de que el número de parámetros es correcto.
    if (argc != 7){
        showEnglishHelp(cerr);
        return 1;
    }

    //ENTRADA DE DATOS
    string inputfile = "unknown.pgm";
    string outputfile = "output.pgm";
    int fil, col, heig,wid;

    //verificar que acaba en pgm
    inputfile = argv[1];
    outputfile = argv[2];

    fil= stoi(argv[3]);
    col=stoi(argv[4]);
    heig=stoi(argv[5]);
    wid=stoi(argv[6]);

    //Mostramos los datos
    cout << endl;
    cout << "Imagen de partida: " << inputfile << endl;
    cout << "Imagen de destino: " << outputfile << endl;
    cout << endl;
    cout << "Datos de recorte:"<<endl;
    cout << "\tEsquina superior izquierda: (" << fil << "," << col << ")" << endl;
    cout << "\tEsquina inferior derecha: (" << fil+heig << "," << col+wid << ")" << endl;

    //PROCESAMIENTO Y SALIDA
    Image im;
    if(im.Load(inputfile.c_str())){
        cout << "Se ha leido la imagen: " << inputfile << endl;
    }
    else{
        cerr << "No se ha podido cargar la imagen " << inputfile << endl;
        return 1;
    }

    Image result=im.Crop(fil,col,heig,wid);

    if(result.Save(outputfile.c_str())){
        cout << "Se ha guardado la imagen en:" << outputfile << endl;
    }
    else{
        cerr << "No se ha podido guardar la imagen en " << outputfile << endl;
        return 1;
    }

    return 0;

}