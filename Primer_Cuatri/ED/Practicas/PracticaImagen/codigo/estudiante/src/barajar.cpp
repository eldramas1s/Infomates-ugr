/*
 * Dada una imagen, el programa genera una nueva como resultado
 * de barajar las filas de la original.
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
    outputStream << "<program_name> <inputfile.pgm> <outputfile.pgm>" << endl;
}

int main(int argc, char * argv[])
{
    if(argc != 3)
    {
        showEnglishHelp(cerr);
        return 1;
    }

    char* archivo_entrada = argv[1];
    char* archivo_salida = argv[2];

    Image original;

    cout << "Nombre de la imagen original: " << argv[1] << endl;
    cout << "Nombre de la imagen destino: " << argv[2] << endl;


    // Leer la imagen del fichero de entrada

    if (!original.Load(archivo_entrada)) {

        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << archivo_entrada << ":" << endl;
    cout << "   Imagen   = " << original.get_rows()  << " filas x " << original.get_cols() << " columnas " << endl;

    original.ShuffleRows();

    bool imagen_salvada = original.Save(archivo_salida);

    if(!imagen_salvada) {

        cout << "No ha sido posible guardar la imagen. Se ha producido un error" << endl;
        return 1;
    }

    cout << "La imagen barajada se ha guardado correctamente en " << archivo_salida << endl;

    return 0;

}