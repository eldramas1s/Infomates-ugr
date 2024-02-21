/*
 * Este programa devuelve la porción de una imagen aumentada X2.
 */

#include <iostream>
#include <string>
#include "image.h"

using namespace std;

/*
 * @brief Muestra al usuario cómo debe ejecutar el programa.
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "<program_name> <inputfile.pgm> <outputfile.pgm> <row> <column>"
                 << " <size>" << endl;
}

int main(int argc, char * argv[]) {

    // Comprobamos que el número de argumentos es correcto.
    if(argc != 6)
    {
        showEnglishHelp(cerr);
        return 1;
    }

    char* fichero_entrada = argv[1];
    char* fichero_salida = argv[2];

    Image original;

    original.Load(fichero_entrada);
    int fila = stoi(argv[3]);
    int col = stoi(argv[4]);
    int lado = stoi(argv[5]);

    // Mostramos los datos en pantalla.

    cout << "Nombre de la imagen original: " << fichero_entrada << endl;
    cout << "Nombre de la imagen destino: " << fichero_salida << endl;
    cout << "Esquina superior izquierda de la porcion a aumentar: "
    << "( " << fila << ", " << col << ")" << endl;

    cout << "Dimensión de la porción a aumentar: " << lado << " filas x "
         << lado << " columnas" << endl;

    Image sub_imagen_zoom(original.Crop(fila,col,lado,lado));
    sub_imagen_zoom = sub_imagen_zoom.Zoom2X();

    bool imagen_salvada = sub_imagen_zoom.Save(fichero_salida);

    // Comprobamos que la imagen se haya guardado correctamente.

    if(!imagen_salvada) {

        cout << "No ha sido posible guardar la imagen. Se ha producido un error" << endl;
        return 1;
    }

    cout << "La sub imagen aumentada se ha guardado correctamente en " << argv[2] << endl;

    return 0;
}
