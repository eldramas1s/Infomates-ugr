//
// Created by el_dramas on 16/10/23.
//
#include <iostream>

#include "image.h"

using namespace std;

void ShowEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "<program-name> <inputfile.pgm> <outputfile.pgm> <infAbscisa> <supAbscisa> <infOrdenada> <supOrdenada>" << endl;
}

int main (int argc, char *argv[]){
    if (argc != 7){
        ShowEnglishHelp(cerr);
        return 1;
    }

    //LECTURA DE DATOS
    string inputfile = argv[1];
    string outputfile = argv[2];

    byte in1 = atoi(argv[3]);
    byte in2 = atoi(argv[4]);
    byte out1 = atoi(argv[5]);
    byte out2 = atoi(argv[6]);

    Image im;

    if(im.Load(inputfile.c_str())){
        cout << "Se ha cargado la imagen " << inputfile << endl;
    }
    else{
        cerr << "No se ha podido cargar la imagen " << inputfile << endl;
        return 1;
    }

    im.AdjustContrast(in1,in2,out1,out2);

    if(im.Save(outputfile.c_str())){

        cout << "Se ha guardado la imagen en " << outputfile << endl;
    }
    else{
        cerr << "No se ha podido guardar la imagen en " << outputfile << endl;
        return 1;
    }

    return 0;

}