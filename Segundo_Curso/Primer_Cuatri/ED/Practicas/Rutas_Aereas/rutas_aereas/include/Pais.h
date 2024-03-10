//
// Created by el_dramas on 23/11/23.
//

#ifndef PRACTICAFINAL_PAIS_H
#define PRACTICAFINAL_PAIS_H

#include "Punto.h"
/**
 * @brief Instancia de la clase Pais. Almacena el punto en el plano de la bandera,
 * su nombre y la ruta de la bandera dentro del parchivo.
 */
class Pais {
private:
    Punto p;
    std::string pais;
    std::string bandera;
public:

    /**
     * @brief Constructor por defecto de pais
     * @post El punto se inicializa con su constructor por defecto, el pais a cadena vacía
     * y bandera a cadena vacía.
     */
    Pais();

    /**
     * @brief Constructor con argumentos
     * @param point Punto de localizacion del pais
     * @param name Nombre del pais
     * @param path Direccion de la imagen de la bandera
     *
     * @post El objeto queda inicializado con los datos recibidos como argumentos
     */
    Pais(const Punto& point, const std::string& name, const std::string & path);
    /**
     * @brief Metodo consultor del punto asociado al pais.
     * @return Referencia constante del punto del país.
     * @post El objeto implícito no se modifica.
     */
    const Punto& GetPunto()const;

    /**
     * @brief Metodo consultor del nombre asociado al pais.
     * @return Referencia constante al nombre del pais
     * @post El objeto implícito no se modifica.
     */
    const std::string& GetPais()const;

    /**
     * @brief Metodo consultor de la ruta de la bandera asociado al pais.
     * @return Referencia constante a la ruta de la bandera del país.
     * @post El objeto implícito no se modifica.
     */
    const std::string & GetBandera()const;

    /**
     * @brief Permite modificar el punto de un país
     * @param other Nuevo punto
     *
     * @post El punto del objeto implícito queda modificado
     */
    void SetPoint(const Punto& other);

    /**
     * @brief Permite modificar la bandera de un país
     * @param other Nuevo punto
     *
     * @post La direccion de la bandera queda modificada;
     */
    void SetBandera(const std::string & other);

    /**
     * @brief Permite modificar el punto de un país
     * @param other Nuevo punto
     *
     * @post El punto del objeto implícito queda modificado
     */
    void SetPais(const std::string & other);

    /**
     * @brief Sobrecarga del operador menor
     * @param other Objeto con el que comparar
     * @return true si el objeto implicito es menor que el objeto pasado como argumento
     */
    bool operator<(const Pais & other)const;

    /**
     * @brief Sobrecarga del operador de igualdad
     * @param other Objeto con el que comparar
     * @return true si other es igual al objeto implicito
     */
    bool operator==(const Pais & other)const;

    /**
     * @brief Sobrecarga del operador de igualdad(dos paises son iguales <=> sus puntos coinciden)
     * @param p Punto a comparar
     * @return true si los puntos coinciden
     */
    bool operator==(const Punto & point)const;

    /**
     * @brief Sobrecarga del operador de distinción
     * @param other Pais con el que comparar
     * @return true si los paises no son iguales
     */
    bool operator!=(const Pais & other)const;

    /**
     * @brief Sobrecarga del operador > (un pais es mayor que otro <=> lo es lexicoggraficamente)
     * @param other Pais con el que comparar
     * @return true si !(*this<other) && !(*this==other)
     */
    bool operator>(const Pais & other)const;

    /**
     * @brief Sobrecarga del operador <=
     * @param other Pais con el que comparar
     * @return true si *this<other || *this==other
     */
    bool operator<=(const Pais & other)const;

    /**
     * @brief Sobrecarga del operador <=
     * @param other Pais con el que comparar
     * @return true si !(*this<other)
     */
    bool operator>=(const Pais & other)const;
    /**
     * @brief Calcula la distancia entre dos paises
     * @param other Pais con el que calcular la distancia
     * @return Distancia
     *
     * @post No se modifica ningun objeto
     */
    double Distancia(const Pais& other)const;
};

/**
 * @brief Sobrecarga del operador de entrada
 * @param is referencia a un objeto de flujo de entrada
 * @param pais Pais a cargar por el flujo de entrada
 * @return referencia al flujo de entrada ya usado
 */
std::istream & operator >>(std::istream& is, Pais & pais);

/**
 * @brief Sobrecarga del operador de salida
 * @param os referencia a un objeto de flujo de salida
 * @param pais Pais a imprimir por el flujo de salida
 * @return referencia al flujo de salida ya usado
 */
std::ostream & operator <<(std::ostream &os, const Pais & pais);


#endif //PRACTICAFINAL_PAIS_H
