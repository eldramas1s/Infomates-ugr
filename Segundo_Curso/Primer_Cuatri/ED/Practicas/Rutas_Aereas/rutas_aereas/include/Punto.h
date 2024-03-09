//
// Created by el_dramas on 23/11/23.
//

#ifndef PRACTICAFINAL_PUNTO_H
#define PRACTICAFINAL_PUNTO_H

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

/**
 * @brief Instancia de la clase punto
 * @param x Latitud (abscisa)
 * @param y Longitud (ordenada)
 */
class Punto {

private:
    double x,y;
public:

    /**
     * @brief Constructor por defecto de la clase Punto
     * @post El objeto queda inicializado a (0,0)
     */
    Punto(double latitud = 0, double longitud = 0);

    /**
     * @brief Constructor de copia.
     * @param other Punto a copiar.
     * @post El objeto implícito queda inicializado.
     */
    Punto(const Punto& other);
    
    /**
     * @brief Constructor. Recibe un string a partir del cuál
     * crea el punto. El formato del string es:
     * 
     *                  (latitud, longitud)
     * 
     * @param str cadena a partir de la cuál se construye el punto.
     * 
     * @post El punto creado tendrá el contenido del string.
     */
    Punto(const std::string& str);

    /**
     * @brief Método para modificar la latitud.
     * @param l Latitud nueva.
     * @post El valor de la latitud queda modificado al valor de l.
     */
    void SetLat(double l);

    /**
     * @brief Método para modificar la longitud.
     * @param l longitud nueva.
     * @post El valor de la longitud queda modificado al valor de l.
     */
    void SetLong(double l);

    /**
     * @brief Devuelve la latitud del punto.
     * @return Latitud del punto.
     */
    double GetLat() const;

    /**
     * @brief Devuelve la longitud del punto.
     * @return Longitud del punto.
     */
    double GetLong() const;

    /**
     * @brief Devuelve la distancia euclídea del punto a otro punto.
     * La distancia eucídea entre dos puntos se calcula como:
     * 
     *            d(x,y)=sqrt((p_1.x - p_2.x)² + (p_1.y - p_2.y)²)
     * 
     * @param other Punto con el que calcular la distancia.
     * @return Distancia euclída entre los puntos.
     */
    double Distancia(const Punto& other) const;
    
    /**
     * @brief Operador == de la clase Punto. 2 puntos son iguales
     * si sus coordenadas lo son.
     * 
     * @param punto punto con el que comparamos.
     * 
     * @return true si son iguales, false en caso contrario.
     */
    bool operator==(const Punto& punto);
    
    /**
     * @brief Operador != de la clase Punto. 2 puntos son distintos
     * si alguna de sus coordenadas lo es.
     * 
     * @param punto punto con el que comparamos.
     * 
     * @return true si son distintos, false en caso contrario.
     */
    bool operator!=(const Punto& punto);
};

/**
 * @brief Operador << de la clase Punto.
 * 
 * @param os flujo de salida al que se envia el punto.
 * @param punto punto a enviar al flujo.
 * 
 * @return referencia al flujo.
 */
std::ostream& operator<<(std::ostream& os, const Punto& punto);

/**
 * @brief Operador >> de la clase Punto. El formato
 * para enviar un punto al flujo es el siguiente:
 * 
 * (latitud,longitud)
 * 
 * @param is flujo de entrada al que se envía el punto.
 * @param punto punto a enviar al flujo.
 * 
 * @return referencia al flujo. 
 */
std::istream& operator>>(std::istream& is, Punto& punto);

#endif //PRACTICAFINAL_PUNTO_H
