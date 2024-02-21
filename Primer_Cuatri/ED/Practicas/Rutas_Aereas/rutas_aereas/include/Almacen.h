//
// Created by el_dramas on 23/11/23.
//

#ifndef PRACTICAFINAL_ALMACEN_H
#define PRACTICAFINAL_ALMACEN_H

#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "Ruta.h"


/**
 * @brief Una instancia del T.D.A Almacen representa un conjunto
 * de rutas, diferenciadas por su identificador. De esta forma
 * a cada ruta del almacén le corresponde un único identificador.
 */
class Almacen {
private:
    
    std::map<std::string,Ruta> store;
    
    /**
     * @brief Cadena mágica para identificar ficheros que
     * almacenan los datos de un almacén.
     */
    static const std::string MAGIC_STRING;
    
public:
    
    /**
     * @brief Constructor por defecto. Crea un almacén vacío.
     */
    Almacen();
    
    /**
     * @brief Constructor de copia. Crea un almacén a partir de otro.
     * 
     * @param orig Almacén a copiar.
     */
    Almacen(const Almacen& orig);
    
    /**
     * @brief Constructor. Recibe un fichero que contiene la información
     * del almacén.
     * El formato del fichero será el siguiente:
     * 
     * - En la primera línea aparece la cadena mágica, que
     * identifica al fichero como uno que contiene los
     * datos de un almacén.
     * 
     * - En las líneas siguientes, aparecen las rutas almacenadas
     * en el almacén.
     * 
     * @param fich_almacen fichero que contiene los
     * datos del almacén.
     * 
     * @throw std::ios_base::failure si no se pudo abrir el fichero.
     *
     * @throw throw std::invalid_argument si no se encuentra
     * la palabra mágica en el fichero.
     * 
     * @post El almacén contendrá las rutas que aparecían en
     * el fichero y se eliminarán todas las rutas que hubiera
     * almacenadas antes.
     */
    Almacen(const char fich_almacen[]);
    
    ////////////////////////////////////////////////////////////
    // MÉTODOS DE CONSULTA DE LA CLASE ALMACÉN.
    ////////////////////////////////////////////////////////////
    
    /**
     * @brief Devuelve una referencia a la ruta indicada
     * por un identificador.
     * 
     * @param id identificador de la ruta a la que queremos acceder.
     * @return referencia a la ruta indicada.
     */
    Ruta& operator[](const std::string& id);
    
    /**
     * @brief Devuelve una referencia a la ruta indicada
     * por un identificador.
     * 
     * @param id identificador de la ruta a la que queremos acceder.
     * @return referencia a la ruta indicada.
     */
    Ruta& at(const std::string& id);
    
    /**
     * @brief Devuelve una referencia constante a la ruta indicada
     * por un identificador.
     * 
     * @param id identificador de la ruta a la que queremos acceder.
     * @return referencia constante a la ruta indicada.
     */
    const Ruta& at(const std::string& id) const;
    
    /**
     * @brief Comprueba si el almacén está vacío.
     *
     * @return true si está vacío, false en caso contrario.
    */
    bool empty() const;

    /**
     * @brief Devuelve el tamaño del almacén.
     *
     * @return Tamaño del almacén.
    */
    unsigned int size() const;
    
    ////////////////////////////////////////////////////////////
    // CLASE ITERATOR DE ALMACÉN.
    ////////////////////////////////////////////////////////////
    
    /**
     * @brief Clase iterator. Permite iterar sobre objetos de la
     * clase Almacen.
     */
    class iterator {
        
    private:
        
        friend class Almacen;
        std::map<std::string,Ruta>::iterator it;
        
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
        Ruta& operator*();

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
     * @return iterador a la primera ruta del almacén.
    */
    iterator begin();

    /**
     * @brief Devuelve un iterador al siguiente del último elemento almacenado.
     *
     * @return iterador a la ruta siguiente a la última del almacén.
    */
    iterator end();
    
    ////////////////////////////////////////////////////////////
    // CLASE CONST_ITERATOR DE ALMACÉN.
    ////////////////////////////////////////////////////////////
    
    /**
     * @brief Clase const_iterator. Permite iterar sobre objetos de la
     * clase Almacen sin modificarlos.
     */
    class const_iterator {
        
    private:
        
        friend class Almacen;
        std::map<std::string,Ruta>::const_iterator it;
        
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
        const Ruta& operator*() const;

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
     * @return const_iterator a la primera ruta del almacén.
    */
    const_iterator cbegin() const;

    /**
     * @brief Devuelve un const_iterator al siguiente del último elemento almacenado.
     *
     * @return const_iterator a la ruta siguiente a la última del almacén.
    */
    const_iterator cend() const;
    
    ////////////////////////////////////////////////////////////
    // OPERACIONES DE LA CLASE ALMACÉN.
    ////////////////////////////////////////////////////////////
    
    /**
     * @brief Elimina todas las rutas del almacén.
     *
     * @post El almacén queda vacío.
    */
    void clear();
    
    /**
     * @brief Elimina una ruta del almacén.
     * @param pos const_iterator que apunta a la ruta
     * que se quiere eliminar del almacén.
     *
     * @return iterator que apunta a la posición anterior
     * a donde estaba el elemento que se borra.
    */
    iterator erase(const_iterator pos);
    
    /**
     * @brief Añade una nueva ruta al final del almacén.
     * 
     * @param ruta ruta nueva que se añadirá.
     * 
     * @return booleano que indica si la inserción
     * ha tenido éxito.
    */
    bool push_back(const Ruta& ruta);
    
    /**
     * @brief Inserta una nueva ruta al final del almacén.
     * 
     * @param pos const_iterator que apunta a la
     * posición donde se insertará la nueva ruta.
     * 
     * @return pair<Almacen::iterator, bool>, en el que el
     * primer elemento es un iterador que apunta al lugar
     * en el que se ha insertado la ruta y el segundo es
     * un bool que indica si la inserción tuvo éxito.
     */
    std::pair<iterator, bool> insert(const const_iterator& pos, const Ruta& ruta);
    
    /**
     * @brief Carga en el almacén los datos guardados en
     * un fichero.
     * El formato del fichero será el siguiente:
     * 
     * - En la primera línea aparece la cadena mágica, que
     * identifica al fichero como uno que contiene los
     * datos de un almacén.
     * 
     * - En las líneas siguientes, aparecen las rutas almacenadas
     * en el almacén.
     * 
     * @param fich_almacen fichero que contiene los
     * datos del almacén.
     * 
     * @throw std::ios_base::failure si no se pudo abrir el fichero.
     *
     * @throw throw std::invalid_argument si no se encuentra
     * la palabra mágica en el fichero.
     * 
     * @post El almacén contendrá las rutas que aparecían en
     * el fichero y se eliminarán todas las rutas que hubiera
     * almacenadas antes.
     */
    void load(const char fich_almacen[]);
    
    /**
     * @brief Guarda en un fichero el contenido de un Almacén.
     * El formato del fichero será el siguiente:
     * 
     * - En la primera línea aparece la cadena mágica, que
     * identifica al fichero como uno que contiene los
     * datos de un almacén.
     * 
     * - En las líneas siguientes, aparecen las rutas almacenadas
     * en el almacén.
     * 
     * @param fich_almacen fichero que contendrá los datos del almacén.
     * 
     * @throw std::ios_base::failure si no se pudo abrir el fichero.
     */
    void save(const char fich_almacen[]) const;
    
};

/**
 * @brief Operador << de la clase Almacén.
 * 
 * @param os flujo de salida al que se envia el almacén.
 * @param almacen almacen a enviar al flujo.
 * 
 * @return referencia al flujo.
 */
std::ostream& operator<<(std::ostream& os, const Almacen& almacen);

/**
 * @brief Operador >> de la clase Almacén.
 * 
 * @param is flujo de entrada al que se envía la ruta.
 * @param almacen almacen a enviar al flujo.
 * 
 * @return referencia al flujo. 
 */
std::istream& operator>>(std::istream& is, Almacen& almacen); // TERMINAR

#endif //PRACTICAFINAL_ALMACEN_H
