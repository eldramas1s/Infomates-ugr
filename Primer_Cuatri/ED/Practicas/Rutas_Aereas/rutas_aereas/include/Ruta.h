//
// Created by el_dramas on 23/11/23.
//

#ifndef PRACTICAFINAL_RUTA_H
#define PRACTICAFINAL_RUTA_H

#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "Punto.h"

/**
 * @brief Instancia de la clase Ruta
 * @param ruta Lista de puntos que sigue la ruta
 * @param id String identificador único de cada ruta
 */
class Ruta {
private:
    
    /*  
        Utilizamos un vector ya que vamos a implementar
        métodos de acceso a los elementos de la ruta.
        Si lo implementamos como lista, el tiempo de
        acceso es lineal, mientras que con un vector es constante.
    */
    std::vector<Punto> ruta;
    std::string id;
    
public:
    
    /**
     * @brief Constructor. Crea una ruta vacía.
     */
    Ruta();
    
    /**
     * @brief Constructor de copia. Crea una ruta a partir de otra.
     * 
     * @param other Ruta a copiar.
     * 
     * @post El objeto implícito queda como una copia de other.
     */
    Ruta(const Ruta& other);
    
    /**
     * @brief Constructor. Crea una ruta a partir de los puntos
     * almacenados en un fichero fich_ruta. El formato de un
     * fichero ruta es el siguiente:
     * 
     *              <N> <P_1> <P_2> ... <P_N>
     * 
     * Donde N es el número de puntos de la ruta.
     * 
     * @param fich_ruta fichero que contiene los
     * datos de la ruta.
     * 
     * @throw std::ios_base::failure si no se pudo abrir el fichero.
     * 
     * @post La ruta contendrá los puntos que aparecían en
     * el fichero y se eliminarán todos los puntos que hubiera
     * almacenados antes.
     */
    Ruta(const char fich_ruta[]);
    
    ////////////////////////////////////////////////////////////
    // MÉTODOS DE CONSULTA DE LA CLASE RUTA.
    ////////////////////////////////////////////////////////////
    
    /**
     * @brief Devuelve una referencia al punto que ocupa la
     * posición pos de la ruta.
     * 
     * @param pos posición del punto al que queremos acceder.
     * @return referencia al punto de la posición pos.
     */
    Punto& operator[](int pos);
    
    /**
     * @brief Devuelve una referencia constante al punto que ocupa la
     * posición pos de la ruta.
     * 
     * @param pos posición del punto al que queremos acceder.
     * @return referencia constante al punto de la posición pos.
     */
    const Punto& operator[](int pos) const;
    
    /**
     * @brief Devuelve una referencia al punto que ocupa la
     * posición pos de la ruta.
     * 
     * @param pos posición del punto al que queremos acceder.
     * @return referencia al punto de la posición pos.
     */
    Punto& at(int pos);
    
    /**
     * @brief Devuelve una referencia constante al punto que ocupa la
     * posición pos de la ruta.
     * 
     * @param pos posición del punto al que queremos acceder.
     * @return referencia constante al punto de la posición pos.
     */
    const Punto& at(int pos) const;
    
    /**
     * @brief Comprueba si la ruta está vacía.
     *
     * @return true si está vacía, false en caso contrario.
    */
    bool empty() const;

    /**
     * @brief Devuelve el tamaño de la ruta.
     *
     * @return Tamaño de la ruta.
    */
    unsigned int size() const;
    
    /**
     * @brief Devuelve el identificador de la ruta.
     */
    const std::string& GetIDRuta() const;
    
    ////////////////////////////////////////////////////////////
    // CLASE ITERATOR DE RUTA.
    ////////////////////////////////////////////////////////////
    
    /**
     * @brief Clase iterator. Permite iterar sobre objetos de la
     * clase Ruta.
     */
    class iterator {
        
    private:
        
        friend class Ruta;
        std::vector<Punto>::iterator it;
        
    public:
        
        /**
         * @brief Constructor por defecto. Crea un iterador
         * que no apunta a nada.
         */
        iterator();
        
        /**
         * @brief Constructor de copia. Crea un iterador
         * a partir de otro iterador.
         * 
         * @param iter el iterador a copiar.
         * 
         * @post El objeto implícito queda como una copia de iter.
         */
        iterator(const iterator& iter);
        
        /**
         * @brief Operador de asignación.
         * 
         * @param iter el iterador el cuál vamos a asignar.
         * 
         * @post El objeto implícito queda como una copia de iter.
         * 
         * @return referencia al objeto implícito.
         */
        iterator& operator=(const iterator& iter);
        
        /**
         * @brief Operador ==.
         *
         * @param other el iterador con el que comparamos.
         *
         * @return true si son iguales, false en caso contrario.
        */
        bool operator==(const iterator& other) const;

        /**
         * @brief Operador !=.
         *
         * @param other el iterador con el que comparamos.
         *
         * @return true si son iguales, false en caso contrario.
        */
        bool operator!=(const iterator& other) const;

        /**
         * @brief Operador *.
         *
         * @return referencia al valor apuntado por el objeto implícito.
        */
        Punto& operator*();

        /**
         * @brief Operador ++;
         *
         * @post el objeto implícito indicará el siguiente
         * elemento almacenado.
         *
         * @return referencia al objeto implícito.
        */
        iterator& operator++();

        /**
         * @brief Operador --;
         *
         * @post el objeto implícito indicará el
         * elemento anterior almacenado.
         *
         * @return referencia al objeto implícito.
        */
        iterator& operator--();
    };

    /**
     * @brief Devuelve un iterador al primer valor almacenado.
     *
     * @return iterador al primer punto de la ruta.
    */
    iterator begin();

    /**
     * @brief Devuelve un iterador al siguiente del último elemento almacenado.
     *
     * @return iterador al punto siguiente al último de la ruta.
    */
    iterator end();
    
    ////////////////////////////////////////////////////////////
    // CLASE CONST_ITERATOR DE RUTA.
    ////////////////////////////////////////////////////////////
    
    /**
     * @brief Clase const_iterator. Permite iterar sobre objetos de la
     * clase Ruta sin modificarlos.
     */
    class const_iterator {
        
    private:
        
        friend class Ruta;
        std::vector<Punto>::const_iterator it;
        
    public:
        
        /**
         * @brief Constructor por defecto. Crea un const_iterator
         * que no apunta a nada.
         */
        const_iterator();
        
        /**
         * @brief Constructor de copia. Crea un const_iterator
         * a partir de otro const_iterator.
         * 
         * @param iter el const_iterator a copiar.
         * 
         * @post El objeto implícito queda como una copia de iter.
         */
        const_iterator(const const_iterator& iter);
        
        /**
         * @brief Operador de asignación.
         * 
         * @param iter el const_iterator el cuál vamos a asignar.
         * 
         * @post El objeto implícito queda como una copia de iter.
         * 
         * @return referencia al objeto implícito.
         */
        const_iterator& operator=(const const_iterator& iter);
        
        /**
         * @brief Operador ==.
         *
         * @param other el const_iterator con el que comparamos.
         *
         * @return true si son iguales, false en caso contrario.
        */
        bool operator==(const const_iterator& other) const;

        /**
         * @brief Operador !=.
         *
         * @param other el const_iterator con el que comparamos.
         *
         * @return true si son iguales, false en caso contrario.
        */
        bool operator!=(const const_iterator& other) const;

        /**
         * @brief Operador *.
         *
         * @return referencia constante al valor apuntado por
         * el objeto implícito.
        */
        const Punto& operator*() const;

        /**
         * @brief Operador ++;
         *
         * @post el objeto implícito apuntará al siguiente
         * elemento almacenado.
         *
         * @return referencia al objeto implícito.
        */
        const_iterator& operator++();

        /**
         * @brief Operador --;
         *
         * @post el objeto implícito apuntará al
         * elemento anterior almacenado.
         *
         * @return referencia al objeto implícito.
        */
        const_iterator& operator--();
    };

    /**
     * @brief Devuelve un const_iterator al primer valor almacenado.
     *
     * @return const_iterator al primer punto de la ruta.
    */
    const_iterator cbegin() const;

    /**
     * @brief Devuelve un const_iterator al siguiente del último elemento almacenado.
     *
     * @return const_iterator al punto siguiente al último de la ruta.
    */
    const_iterator cend() const;
    
    ////////////////////////////////////////////////////////////
    // OPERACIONES DE LA CLASE RUTA.
    ////////////////////////////////////////////////////////////
    
    /**
     * @brief Modifica el identificador de la ruta.
     */
    void SetIDRuta(const std::string& str);
    
    /**
     * @brief Elimina todos los puntos la ruta.
     *
     * @post Al eliminarse todos los puntos de la
     * ruta, esta queda vacía.
    */
    void clear();
    
    /**
     * @brief Elimina un punto de la ruta.
     * @param pos const_iterator que apunta al punto de la
     * ruta que se quiere eliminar.
     *
     * @return iterator que apunta a la posición anterior
     * a donde estaba el elemento que se borra.
    */
    Ruta::iterator erase(const_iterator pos);
    
    /**
     * @brief Añade un nuevo punto al final de la ruta.
     * 
     * @param punto punto nuevo que se añadirá.
    */
    void push_back(const Punto& punto);
    
    /**
     * @brief Inserta un nuevo punto en la ruta.
     * 
     * @param pos const_iterator que apunta a la
     * posición donde se insertará el nuevo punto.
     * 
     * @return iterator que apunta al lugar en el
     * que se ha insertado el punto.
     */
    iterator insert(const const_iterator& pos, const Punto& punto);
    
    /**
     * @brief Carga en la ruta los puntos almacenados en
     * un fichero fich_ruta. El formato de un fichero ruta
     * es el siguiente:
     * 
     *              <ID> <N> <P_1> <P_2> ... <P_N>
     * 
     * Donde ID es el identificador de la ruta y N es el número
     * de puntos de la ruta.
     * 
     * @param fich_ruta fichero que contiene los
     * datos de la ruta.
     * 
     * @throw std::ios_base::failure si no se pudo abrir el fichero.
     * 
     * @post La ruta contendrá los puntos que aparecían en
     * el fichero y se eliminarán todos los puntos que hubiera
     * almacenados antes.
     */
    void load(const char fich_ruta[]);
    
    /**
     * @brief Guarda en un fichero el contenido de una ruta.
     * El formato del fichero será el siguiente:
     * 
     *              <ID> <N> <P_1> <P_2> ... <P_N>
     * 
     * Donde ID es el identificador de la ruta y N es el número
     * de puntos de la ruta.
     * 
     * @param fich_ruta fichero que contendrá los
     * datos de la ruta.
     * 
     * @throw std::ios_base::failure si no se pudo abrir el fichero.
     */
    void save(const char fich_ruta[]) const;
    
};

/**
 * @brief Operador << de la clase Ruta.
 * 
 * @param os flujo de salida al que se envia la ruta.
 * @param ruta ruta a enviar al flujo.
 * 
 * @return referencia al flujo.
 */
std::ostream& operator<<(std::ostream& os, const Ruta& ruta);

/**
 * @brief Operador >> de la clase Punto. El formato
 * para enviar un punto al flujo es el siguiente:
 * 
 * (latitud,longitud)
 * 
 * @param is flujo de entrada al que se envía la ruta.
 * @param ruta ruta a enviar al flujo.
 * 
 * @return referencia al flujo. 
 */
std::istream& operator>>(std::istream& is, Ruta& ruta); // TERMINAR


#endif //PRACTICAFINAL_RUTA_H
