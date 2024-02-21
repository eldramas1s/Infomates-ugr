#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>

/**
 * @brief El T.D.A Dictionary representa una colección de palabras
 * del mismo idioma, ordenadas alfabéticamente y sin repetirse.
*/
class Dictionary
{
private:

    std::set<std::string> words;

public:

    /**
     * @brief Constructor por defecto.
     * Crea un Dictionary vacío.
    */
    Dictionary();

    /**
     * @brief Constructor de copia.
     * Crea un Dictionary con el mismo contenido que el que
     * se le pasa como argumento.
     *
     * @param other Dictionary que se quiere copiar.
    */
    Dictionary(const Dictionary& other);
    
    /**
     * @brief Constructor. Crea un Dictionary a partir de un fichero.
     * Un fichero Dictionary_file contiene las palabras que contendrá
     * el diccionario, habiendo una palabra por cada línea.
     * 
     * @param d_file fichero Dictionary_file a partir del cual se crea el diccionario.
     * 
     * @throw std::ios_base::failure si no se pudo abrir el fichero.
     * 
     * @post El diccionario contendrá las palabras que aparecían en
     * el fichero.
    */
    Dictionary(const char d_file[]);

    /**
     * @brief Indica si una palabra está en el diccionario o no.
     * Este método comprueba si una determinada palabra se encuentra
     * o no en el diccionario.
     *
     * @param palabra la palabra que se quiere buscar.
     *
     * @return true si la palabra se encuentra en el diccionario, false
     * en caso de que no se encuentre.
    */
    bool exists(const std::string& palabra) const;

    /**
     * @brief Inserta una palabra en el diccionario.
     *
     * @param palabra la palabra que se quiere insertar en el diccionario.
     *
     * @return true si la palabra se ha insertado con éxito, false
     * en caso de que no se haya insertado.
    */
    bool insert(const std::string& palabra);

    /**
     * @brief Elimina una palabra del diccionario.
     * @param palabra la palabra que se quiere borrar del diccionario.
     *
     * @return true si la palabra se ha borrado del diccionario, false
     * en caso contrario.
    */
    bool erase(const std::string& palabra);

    /**
     * @brief Vacía completamente el diccionario.
     *
     * @post El diccionario queda vacío.
    */
    void clear();

    /**
     * @brief Comprueba si el diccionario está vacío.
     *
     * @return true si está vacío, false en caso contrario.
    */
    bool empty() const;

    /**
     * @brief Devuelve el tamaño del diccionario.
     *
     * @return Tamaño del diccionario.
    */
    unsigned int size() const;

    /**
     * @brief Devuelve las palabras en el diccionario con una longitud dada.
     *
     * @param length Longitud de las palabras buscadas.
     *
     * @return Vector de palabras con la longitud deseada.
    */
    std::vector<std::string> wordsOfLength(int length);
    
    /**
     * @brief Indica el número de apariciones de una letra.
     * 
     * @param c la letra a buscar.
     * 
     * @return el número de veces que aparece la letra en el diccionario.
    */
    int getOcurrences(const char c) const;
    
    /**
     * @brief Carga en el diccionario las palabras almacenadas
     * en un fichero Dictionary_file.
     * Un fichero Dictionary_file contiene las palabras que contendrá
     * el diccionario, habiendo una palabra por cada línea.
     * 
     * @param d_file Dictionary_file que contiene la nueva
     * colección de palabras del diccionario.
     * 
     * @throw std::ios_base::failure si no se pudo abrir el fichero.
     * 
     * @post El diccionario contendrá las palabras que aparecían en
     * el fichero y se eliminarán todas las palabras que hubiera almacenadas
     * antes.
    */
    void load(const char d_file[]);
    
    /**
     * @brief Añade las palabras de un diccionario al diccionario
     * actual.
     * 
     * @param dic el diccionario que vamos a añadir.
     * 
     * @post el diccionario contendrá las palabras que tenía antes
     * más las que tenga el diccionario que se ha añadido.
    */
    void aniade(const Dictionary& dic);

    ///////////////////////////////////////////////////////////////////////
    // CLASE ITERATOR.
    ///////////////////////////////////////////////////////////////////////

    /**
     * @brief Clase iterator de Dictionary. Permite iterar sobre
     * objetos de la clase Dictionary.
    */
    class iterator {

    private:
        
        friend class Dictionary;
        std::set<std::string>::iterator el_iterador;

    public:

        /**
         * @brief Constructor por defecto.
        */
        iterator();

        /**
         * @brief Constructor de copia. Crea un
         * iterador a partir de uno dado.
         *
         * @param other el iterador que se quiere copiar.
        */
        iterator(const iterator& other);

        /**
         * @brief Operador de asignación.
         *
         * @param other el iterador que vamos a asignar.
         *
         * @post el objeto implícito se convierte en una
         * copia de other.
         *
         * @return referencia al objeto implícito.
        */
        iterator& operator=(const iterator& other);

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
         * @return el valor indicado por el objeto implícito.
        */
        std::string& operator*();

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
     * @return iterador a la primera palabra del diccionario.
    */
    iterator begin();

    /**
     * @brief Devuelve un iterador al siguiente del último elemento almacenado.
     *
     * @return iterador a la palabra siguiente a la última del diccionario.
    */
    iterator end();

    ///////////////////////////////////////////////////////////////////////
    // CLASE CONST_ITERATOR.
    ///////////////////////////////////////////////////////////////////////

    /**
     * @brief Clase const_iterator de Dictionary. Permite iterar sobre
     * objetos de la clase Dictionary sin modificar el objeto.
    */
    class const_iterator {

    private:

        friend class Dictionary;
        std::set<std::string>::const_iterator el_iterador;

    public:

        /**
         * @brief Constructor por defecto.
        */
        const_iterator();

        /**
         * @brief Constructor de copia. Crea un
         * iterador a partir de uno dado.
         *
         * @param other el iterador que se quiere copiar.
        */
        const_iterator(const const_iterator& other);

        /**
         * @brief Operador de asignación.
         *
         * @param other el iterador que vamos a asignar.
         *
         * @post el objeto implícito se convierte en una
         * copia de other.
         *
         * @return referencia al objeto implícito.
        */
        const_iterator& operator=(const const_iterator& other);

        /**
         * @brief Operador ==.
         *
         * @param other el iterador con el que comparamos.
         *
         * @return true si son iguales, false en caso contrario.
        */
        bool operator==(const const_iterator& other) const;

        /**
         * @brief Operador !=.
         *
         * @param other el iterador con el que comparamos.
         *
         * @return true si son iguales, false en caso contrario.
        */
        bool operator!=(const const_iterator& other) const;

        /**
         * @brief Operador *.
         *
         * @return el valor indicado por el objeto implícito.
        */
        const std::string& operator*() const;

        /**
         * @brief Operador ++;
         *
         * @post el objeto implícito indicará el siguiente
         * elemento almacenado.
         *
         * @return referencia al objeto implícito.
        */
        const_iterator& operator++();

        /**
         * @brief Operador --;
         *
         * @post el objeto implícito indicará el
         * elemento anterior almacenado.
         *
         * @return referencia al objeto implícito.
        */
        const_iterator& operator--();

    };

    /**
     * @brief Devuelve un iterador constante al primer valor almacenado.
     *
     * @return iterador constante a la primera palabra del diccionario.
    */
    const_iterator cbegin() const;

    /**
     * @brief Devuelve un iterador constante al siguiente del 
     * último elemento almacenado.
     *
     * @return iterador constante a la palabra siguiente a la última del diccionario.
    */
    const_iterator cend() const;
    
};

/**
 * @brief Operador << de la clase Dictionary.
 * 
 * @param os flujo de salida
 * @param d diccionario a enviar al fuljo de salida.
 * 
 * @return flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const Dictionary& d);

#endif /* DICTIONARY_H*/
