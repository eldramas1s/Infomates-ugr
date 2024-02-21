//
// Created by el_dramas on 14/11/23.
//

#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

#ifndef PRACTICA_SET_MAP_GUIA_TLF_H
#define PRACTICA_SET_MAP_GUIA_TLF_H

using namespace std;

class Guia_tlf {
private:
    map<string,unsigned int> telefonos;

public:
    /**
     * @brief Constructor por defecto
     * @post Objeto inicializado
     */
    Guia_tlf();

    /**
     * @brief Constructor de copia
     * @param other Objeto a copiar
     * @post EL objeto implicito queda inicializado como copia dle objeto other
     */
    Guia_tlf(const Guia_tlf& other);

    /**
     * @brief   Operador de asignacion
     * @param other Objeto a asignar
     * @return Referencia al objeto implicito para permitir encadenar igualdades
     * @post El objeto implicito se vuelve una copia de other
     */
    Guia_tlf& operator=(const Guia_tlf& other);

    /**
     * @brief MEtodo que devuelve el tamaño del objeto implicito
     * @post No se modifica el objeto
     */
    size_t size() const;

    /**
     * @brief Metodo que comprueba si el objeto implicito esta vacio
     * @return Devuelve true si esta vacio y false si tiene elementos
     * @post No modifica el objeto implicito
     */
    bool empty() const;

    /**
     * @brief Limpia el objeto implicito
     * @post EL objeto queda en estado invalido
     */
    void clear();

    /**
     * @brief Metodo que borra un elemento del objeto
     * @param iter Iterador que apunta al elemento a borrar
     * @return Iterador al elemento siguiente al borrado
     * @post El objeto pasa a tener un elemento menos
     */
    iterator erase(iterator&iter);
    /**
     * @brief Metodo que borra un elemento del objeto
     * @param clave Clave del elemento a borrar
     * @return Iterador al elemento siguiente al borrado
     * @post El objeto pasa a tener un elemento menos
     */
    size_t erase(const string & clave);
    /**
     * @brief Metodo que inserta un nuevo elemento en la guía.
     * @param dato Elemento a insertar
     */
    void insert(const pair<string, unsigned int> & dato);

    /**
     * Metodo que busca un elemento en la guía.
     * @param clave Clave del elemento a buscar
     * @return Iterador constante a la posicion del elemento buscado
     * @post No se modifica el objeto
     */
    const_iterator find(const string & clave)const;

    ///////////////////////////////////////////////////////////////////////
    // CLASE ITERATOR.
    ///////////////////////////////////////////////////////////////////////

    class iterator {
    private:

        map<string, unsigned int>::iterator it;
        friend class Guia_tlf;

    public:
        /**
         * @brief Constructor por defecto de la clase iteradora
         * @post El iteador se crea apuntando a nullptr;
         */
        iterator();
        /**
         * @briefConstructor de copia de iteradores
         * @param other Iterador a copiar;
         * @post El iterador resultante queda como other
         */
        iterator(const iterator &other);

        /**
         * @brief Operador de asignacion de iteradores
         * @param other Objeto a asignar
         * @return Referencia al objeto implicito
         * @post EL iterador implicito queda con el valor de other
         */
        iterator &operator=(const iterator &other);


        /**
         * @brief Operador de comparacion de iteradores
         * @param other Iterador con el que comparar
         * @return True si son el mismo iterador, false si es otro
         */
        bool operator==(const iterator &other)const;

        /**
         * @brief Operador de desigualdad
         * @param other Iterador con el que comparar
         * @return True si sin distintos, false si son iguales
         */
        bool operator!=(const iterator &other)const;

        /**
         * @brief Operador de incremento
         * @return Iterador aumentado;
         * @post Permite encadenar incrementos
         */
        iterator & operator++();

        /**
         * @brief Operador de decremento
         * @return Referencia a un iterador aumentado
         */
        iterator &operator--();

        pair<const basic_string<char>, unsigned int> operator*();
    };

    /**
     * @brief Devuelve un iterador que apunta al principio de la guia
     * @return Iterador que apunta al principio de la guia
     */
    iterator begin()

    /**
     * @brief Devuelve un iterador que apunta al final de la guia
     * @return Iterador que apunta al final de la guia
     */
    iterator end();


    ///////////////////////////////////////////////////////////////////////
    // CLASE CONST_ITERATOR.
    ///////////////////////////////////////////////////////////////////////

    class const_iterator{
    private:
        map<string,unsigned int>::const_iterator cit;
        friend class Guia_tlf;

    public:
        /**
         * @brief Constructor por defecto de la clase iteradora
         * @post El iteador se crea apuntando a nullptr;
         */
        const_iterator();
         /**
        * @briefConstructor de copia de iteradores
        * @param other Iterador a copiar;
        * @post El iterador resultante queda como other
        */
        const_iterator(const_iterator &other);

        /**
          * @brief Operador de asignacion de iteradores
          * @param other Objeto a asignar
          * @return Referencia al objeto implicito
          * @post EL iterador implicito queda con el valor de other
          */
        const_iterator &operator=(const_iterator &other);

        /**
         * @brief Operador de comparacion de iteradores
         * @param other Iterador con el que comparar
         * @return True si son el mismo iterador, false si es otro
         */
        bool operator==(const_iterator &other) const;
        /**
         * @brief Operador de desigualdad
         * @param other Iterador con el que comparar
         * @return True si sin distintos, false si son iguales
         */
        bool operator!=(const_iterator &other) const;

        /**
         * @brief Operador de incremento
         * @return Iterador aumentado;
         * @post Permite encadenar incrementos
         */
        const_iterator &operator++();

        /**
         * @brief Operador de decremento
         * @return Referencia a un iterador aumentado
         */
        const_iterator &operator--();

    };

    /**
     * @brief Devuelve un iterador que apunta al principio de la guia
     * @return Iterador que apunta al principio de la guia
     */
    const_iterator cbegin() const;

    /**
     * @brief Devuelve un iterador que apunta al final de la guia
     * @return Iterador que apunta al final de la guia
     */
    const_iterator cend() const;

    void Insertar_EN(Guia_tlf & other) const;

    void changetlf(const string & clave,unsigned int tlf);

    Guia_tlf Interseccion(const Guia_tlf & other) const;
};


#endif //PRACTICA_SET_MAP_GUIA_TLF_H
