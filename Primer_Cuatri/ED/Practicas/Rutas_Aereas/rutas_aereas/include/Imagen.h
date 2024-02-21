//
// Created by el_dramas on 23/11/23.
//

#ifndef PRACTICAFINAL_IMAGEN_H
#define PRACTICAFINAL_IMAGEN_H

#include <string>
#include <cmath>

/**
 * @brief Tipo enumerado de la forma de pegado
 */
enum Tipo_Pegado {OPACO, BLENDING};

using namespace std;

/**
 * @brief Estructura de un pixel
 * @param r,g,b pixel de rojo, verde y azul.
 * @param transp representacion de cantidad de transparencia
 */
struct Pixel{
    unsigned char r,g,b;
    unsigned char transp; //0 no 255 si
};

/**
 * @brief Instancia del T.D.A Imagen, representa una matriz de pixeles que dependiendo
 * del dato pixel formara una imagen o otra.
 */
class Imagen {
private:
    Pixel **data;
    int nf, nc;

    /**
     * @brief Metodo para reservar memeoria para una imagen
     * @pre La imagen debe estar sin crear.
     * @param fils Filas a reservar
     * @param cols COlumnas a reservar
     * @post La imagen pasa a tener fils filas y cols columnas.
     */
    void Allocate(int fils, int cols);

    /**
     * @brief Metodo de borrado de la imagen completa.
     */
    void Delete();

    /**
     * @brief Metodo para copiar la imagen I en la imagen actual.
     * @pre Ambos objetos deben tener el mismo tamaño
     * @param I Imagen a copiar.
     * @post El objeto implicito queda igual que la imagen I.
     */
    void Copiar(const Imagen &I);

public:

    /**
     * @brief Constructor de la clase Imagen, inicializa la Imagen a la instancia
     * básica.
     */
    Imagen();

    /**
     * @brief Constructor con parametros de la clase Imagen, inicializa sus pixeles
     * con el costructor por defecto.
     * @param f Filas de la imagen
     * @param c Columnas de la imagen
     * @post El objeto implicito queda inicializado.
     */
    Imagen(int f, int c);

    /**
     * @brief Constructor de copia de la clase Imagen
     * @param I Imagen a copiar.
     * @post EL objeto implicito queda inicializado con los valores de I
     */
    Imagen(const Imagen &I);

    /**
     * @brief Sobrecarga del operador de asignacion de la clase Imagen.
     * @param I Imagen a copiar.
     * @return Referencia al objeto implicito
     * @post El objeto implicito toma los valores de I.
     */
    Imagen &operator=(const Imagen &I);

    /**
     * @brief Destructor de la clase Imagen
     */
    ~Imagen();

    /**
     * @brief Sobrecarga del operador ().
     * @param i Fila de la matriz
     * @param j Columna de la matriz
     * @return Referencia a un pixel de la matriz
     * @post Ese pixel referenciado puede llegas a ser modificado
     */
    Pixel &operator()(int i, int j);

    /**
     * @brief Sobrecarga del operador ()
     * @param i Fila de la matriz
     * @param j Columna de la matriz
     * @return Referencia constante a un pixel de la matriz.
     */
    const Pixel &operator()(int i, int j) const;

    /**
     * @brief Metodo de carga de una imagen en un archivo(normalmente sera ppm)
     * @param nombre Nombre del archivo donde cargar la imagen.
     * @post El objeto implicito no se modifica.
     */
    void EscribirImagen(const char *nombre);

    /**
     * @brief Metodo de lectura de imagenes de un arhcivo(normalmente sera ppm)
     * @param nombre
     * @param nombremascara
     */
    void LeerImagen(const char *nombre, const string &nombremascara = "");
    /**
     * @brief Pone la transparencia de la imagen a 0, volviendola opaca
     * @post Todos los pixeles son opacos
     */
    void LimpiarTransp();

    /**
     * @brief Metodo de consulta de filas de la imagen.
     * @return Numero de filas de la imagen
     * @post No se modifica el objeto.
     */
    int num_filas() const { return nf; }

    /**
     * @brief Metodo de consulta de columnas de la imagen.
     * @return Numero de columnas de la imagen
     * @post No se modifica el objeto.
     */
    int num_cols() const { return nc; }

    /**
     * @brief Metodo de pegado de imagenes
     * @param posi Fila del pixel donde empezar a pegar
     * @param posj Columna del pixel donde empezar a pegar
     * @param I Imagen a pegar
     * @param tippegado Tipo enumerado que indica el pegado a realizar
     * @post La imagen resultante  que es el objeto implicito tiene pegado
     */
    void PutImagen(int posi, int posj, const Imagen &I, Tipo_Pegado tippegado = OPACO);

    /**
     * @brief Metodo que extrae una imagen
     * @param posi Fila del pixel donde se comienza a extraer
     * @param posj Columna del pixel donde se comienza a extraer.
     * @param dimi Largo de la imagen a extraer
     * @param dimj Ancho de la imagen a extraer
     * @return
     */
    Imagen ExtraeImagen(int posi, int posj, int dimi, int dimj);

};

/**
 * @brief Obtiene una nueva imagen que es la versión rotada de una imagen de entrada
 * @param Io: imagen de entrada
 * @param angulo: angulo a rotar la imagen de entrada. Debe estar en radianes.
 * @return Una nueva imagen que es la versión rotada de Io.
 */
Imagen Rota(const Imagen &Io, double angulo);
    
/**
* @brief Función que pinta una imagen "avión" sobre la imagen I.
* @param f1 Fila que representa una esquina de la imagen avion sobre la imagen I
* @param f2 Fila que representa la esquina opuesta de la imagen avion sobre la imagen I
* @param c1 Columna que representa la esquina de f1 de la imagen avion sobre la imagen I
* @param c2 Columna que representa la esquina de f2 de la imagen avion sobre la imagen I
* @param avion Imagen a pintar sobre la imagen dada
* @param mindisf Representa la minima distancia entre las filas
* @param mindisc Representa la minima distancia entre las columnas
*/
void Pintar(int f1, int f2, int c1, int c2, Imagen &I, const Imagen &avion, int mindisf, int mindisc);

#endif //PRACTICAFINAL_IMAGEN_H
