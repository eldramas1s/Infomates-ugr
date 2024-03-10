//
// Created by el_dramas on 23/11/23.
//

#ifndef PRACTICAFINAL_MUNDO_H
#define PRACTICAFINAL_MUNDO_H

#include <set>
#include <fstream>
#include <iostream>

#include "Pais.h"

/**
 * @brief Instancia de la clase Mundo
 * @param mundo set de paises
 */
class Mundo {
private:
    std::set<Pais> mundo;   //Los paises estan ordenados por orden lexicografico

    /**
     * @brief Cabecera de todo archivo  que contenga un Mundo.
     */
    static const std::string CABECERA;
public:
    /**
     * @brief Constructor sin parametros de la clase Mundo
     * @post El objeto queda inicializado segun el constructor por defecto de la clase set, usando
     * el constructor sin parametros de la clase Pais.
     */
    Mundo();

    /**
     * @brief Constructor de copia de la clase Mundo
     * @param other Obejto a copiar
     * @post El objeto implícito se inicializa con los valores de other.
     */
    Mundo(const Mundo & other);

    /**
     * @brief Constructor. Crea un mundo a partir de los paises almacenados en un fichero fich_Mundo.
     * EL formato de uno de estos ficherso es el siguiente:
     *
     *          #Latitud    Longitud    Pais    Bandera
     *
     * Donde el caracter # solo aparece en la primera linea.
     *
     * @param fich_Mundo fichero que contiene los
     * datos del mundo.
     *
     * @throw std::ios_base::failure si no se pudo abrir el fichero.
     *
     * @post EL objeto implícito contendrá todos los paises que aparezcan en ese fichero y sólo esos,
     * los que ya hubieran serán borrados.
     */
    Mundo(const char fich_Mundo[]);

    ////////////////////////////////////////////////////////////
    // MÉTODOS DE CONSULTA DE LA CLASE MUNDO.
    ////////////////////////////////////////////////////////////
    
    /**
     * @brief Comprueba si la ruta está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool empty() const;

    /**
     * @brief Vacía el objeto Mundo al completo
     * @post El objeto queda en estado base.
     */
    void clear();
    /**
     * @brief Devuelve el tamaño de este Mundo
     * @return Tamaño del objeto implícito
     */
    unsigned int size() const;
    
    ////////////////////////////////////////////////////////////
    // CLASE ITERATOR DE MUNDO.
    ////////////////////////////////////////////////////////////

    /**
     * @brief Clase iterator. Permite iterar sobre objetos de la
     * clase Mundo.
     */
    class iterator{
    private:
        friend class Mundo;
        std::set<Pais>::iterator it;
    public:
        /**
         * @brief Constructor por defecto. Crea un iterador
         * que no apunta a nada.
         */
        iterator();

        /**
         * @brief Constructor de copia. Crea un iterador a partir de otro iterador
         *
         * @param iter Iterador a copiar
         *
         * @post EL objeto implícito queda como copia de iter.
         */
        iterator(const iterator& iter);

        /**
         * @brief Operador de asignación
         *
         * @param other Iterador el cuál vamos a asignar
         *
         * @return referencia al objeto implícito
         *
         * @post El objeto implícito queda como copia de iter.
         */
        iterator& operator=(const iterator&other);

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
        bool operator!=(const iterator & other)const;

        /**
         * @brief Operador *.
         *
         * @return referencia al valor apuntado por el objeto implícito.
        */
        const Pais& operator*() const;

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
     * @return iterador al primer punto del Mundo.
    */
    iterator begin();

    /**
     * @brief Devuelve un iterador al siguiente del último elemento almacenado.
     *
     * @return iterador al Pais siguiente al último del Mundo.
    */
    iterator end();

    ////////////////////////////////////////////////////////////
    // CLASE CONST_ITERATOR DE RUTA.
    ////////////////////////////////////////////////////////////

    class const_iterator{
    private:
        friend class Mundo;
        std::set<Pais>::const_iterator cit;

    public:
        /**
         * @brief Constructor por defecto. Crea un const_iterator que no apunta a nada
         */
        const_iterator();

        /**
         * @brief Constructor de copia. Crea un const_iterator
         * a partir de otro const_iterator.
         *
         * @param other el const_iterator a copiar.
         *
         * @post El objeto implícito queda como una copia de other.
         */
        const_iterator(const const_iterator& other);

        /**
         * @brief Operador de asignación.
         *
         * @param other el const_iterator el cuál vamos a asignar.
         *
         * @post El objeto implícito queda como una copia de other.
         *
         * @return referencia al objeto implícito.
         */
        const_iterator& operator=(const const_iterator& other);

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
        const Pais& operator*() const;

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
     * @return const_iterator al primer Pais del Mundo
    */
    const_iterator cbegin() const;

    /**
     * @brief Devuelve un const_iterator al siguiente del último elemento almacenado.
     *
     * @return const_iterator al Pais siguiente al último del Mundo.
    */
    const_iterator cend() const;
    
    ////////////////////////////////////////////////////////////
    // OPERACIONES DE LA CLASE MUNDO.
    ////////////////////////////////////////////////////////////
    
    /**
     * @brief Borra un objeto de la clase Mundo
     * @param pos Posicion a borrar
     * @return Iterador al objeto siguiente al borrado.
     */
    iterator erase(const_iterator& pos);

    /**
     * @brief Borra un objeto de la clase Mundo
     * @param pais Pais a borrar
     * @return true si se ha borrado, false si no.
     */
    bool erase(const Pais& pais);

    /**
     * @brief Busca un País en el Mundo
     * @param pais País a buscar
     * @return Iterador al país encontrado, en caso contrario devuelve *this.end();
     */
    iterator find(const Pais& pais);
    
    /**
     * @brief Busca un país dado su punto.
     * @param punto punto a buscar
     * @return Iterador al país encontrado, en caso contrario devuelve *this.end();
     */
    iterator find(const Punto& punto);

    /**
     * @brief Busca un País en el Mundo
     * @param pais País a buscar
     * @return Iterador constante al país encontrado, en caso contrario devuelve *this.cend();
     */
    const_iterator cfind(const Pais& pais);

    /**
     * @brief Inserta un nuevo Pais en Mundo
     *
     * @param pais Pais a insertar
     *
     * @return Iterador a la posicion donde se ha insertado el elemento.
     *
     * @post El nuevo país ya pertenece al Mundo.
     */
    iterator insert(const Pais& pais);

    /**
     * @brief Carga en el Mundo los Paises almacenados en
     * un fichero fich_Mundo.
     * El formato de uno de estos ficherso es el siguiente:
     *
     *          #Latitud    Longitud    Pais    Bandera
     *
     * Donde el caracter # solo aparece en la primera linea.
     *
     * @param fich_Mundo fichero que contiene los
     * datos del Mundo.
     *
     * @throw std::ios_base::failure si no se pudo abrir el fichero.
     *
     * @post EL objeto implícito contendrá todos los paises que aparezcan en ese fichero y sólo esos,
     * los que ya hubieran serán borrados.
     */
    void load(const char fich_Mundo[]);

    /**
     * @brief Guarda en un fichero el contenido de un Mundo.
     * El formato del fichero será el siguiente:
     *
     *             #Latitud    Longitud    Pais    Bandera
     *
     * Donde el caracter # solo aparece en la primera linea.
     *
     * @param fich_Mundo fichero que contendrá los
     * datos del Mundo.
     *
     * @throw std::ios_base::failure si no se pudo abrir el fichero.
     */
    void save(const char fich_Mundo[]) const;
};

/**
 * @brief Operador << de la clase Mundo.Con el formato:
 *
 *          #Latitud    Longitud    Pais    Bandera
 *
 * Donde # solo aparece en la primera linea
 * @param os flujo de salida al que se envia la ruta.
 * @param mundo Mundo a enviar al flujo.
 *
 * @return referencia al flujo.
 */
std::ostream& operator<<(ostream& os, const Mundo& mundo);

/**
 * @brief Operador >> de la clase Mundo. El formato
 * para enviar un mundo al flujo es el siguiente:
 *
 *          #Latitud    Longitud    Pais    Bandera
 *
 * Donde # solo aparece en la primera linea
 * @param is flujo de entrada al que se envía la ruta.
 * @param ruta ruta a enviar al flujo.
 *
 * @return referencia al flujo.
 */
std::istream& operator>>(std::istream& is, Mundo& mundo);

#endif //PRACTICAFINAL_MUNDO_H
