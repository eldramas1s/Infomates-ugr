//
// Created by el_dramas on 14/11/23.
//

#ifndef PRACTICA_SET_MAP_DICTIONARY_MULTI_H
#define PRACTICA_SET_MAP_DICTIONARY_MULTI_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <list>
#include <fstream>

using namespace std;
class Dictionary_multi {
/**
* @brief El T.D.A Dictionary_multi representa una colecci�n de palabras
* del mismo idioma, ordenadas alfab�ticamente y con repetición.
*/
private:
    multiset<string> words;

    /**
     * @brief Funcion auxiliar que calcula la cantidad de veces que aparece el caracter c en la cadena pasada por referencia
     * @param cad Cadena sobre la cual calcular las ocurrencias
     * @param c Caracter a conocer sus apariciones
     * @return Cantidad de veces que aparece en la cadena cad
     *
     * @post No se modifica nada del objeto, se usa en el metodo GetOcurrences
     */
    int Ocurrences(const string& cad, char c)const;
public:
    class iterator;
    class const_iterator;
    /**
    * @brief Constructor por defecto.
    * Crea un Dictionary_multi vac�o.
    */
    Dictionary_multi();

    /**
    * @brief Constructor de copia.
    * Crea un Dictionary_multi con el mismo contenido que el que
    * se le pasa como argumento.
    *
    * @param other Dictionary que se quiere copiar.
     * @post El objeto implícito es una copia de other
    */
    Dictionary_multi(const Dictionary_multi& other);


    //~Dictionary_multi();

    /**
    * @brief Devuelve el numero de veces que está una palabra en el
     * Dictionary_multi
    *
    * @param clave la palabra que se quiere buscar.
    *
    * @return 0 si la palabra no se encuentra en el diccionario, n
    * en caso de que se encuentre n veces.
    */
    int count(const string & clave) const;

    /**
     * @brief Devuelve un par de iteradores donde el primero apunta a la
     * primera ocurrencia de la clave y el segundo a la ultima.
     *
     * @param clave Elemento a bucar en el multiset
     * @return Iterador a la primera ocurrencia e iterador a la ultima ocurrencia.
     */
     pair<multiset<string>::iterator,multiset<string>::iterator>buscar(const string & clave)const;

    /**
    * @brief Vac�a completamente el diccionario.
    *
    * @post El diccionario queda vac�o.
    */
    void clear();

    /**
    * @brief Comprueba si el diccionario est� vac�o.
    *
    * @return true si est� vac�o, false en caso contrario.
    */
    bool empty()const;

    /**
    * @brief Devuelve el tama�o del diccionario.
    *
    * @return Tama�o del diccionario.
    */
    size_t size()const;

public:
    class iterator{
    private:
        multiset<string>::iterator el_iterador;
    friend class Dictionary_multi;

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
        iterator(const iterator & other);
        /**
        * @brief Operador de asignaci�n.
        *
        * @param other el iterador que vamos a asignar.
        *
        * @post el objeto impl�cito se convierte en una
        * copia de other.
        *
        * @return referencia al objeto impl�cito.
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
        * @return el valor indicado por el objeto impl�cito.
        */
        string & operator*();
        /**
        * @brief Operador ++;
        *
        * @post el objeto impl�cito indicar� el siguiente
        * elemento almacenado.
        *
        * @return referencia al objeto impl�cito.
        */
        iterator& operator++();
        /**
        * @brief Operador --;
        *
        * @post el objeto impl�cito indicar� el
        * elemento anterior almacenado.
        *
        * @return referencia al objeto impl�cito.
        */
        iterator& operator--();

    };
public:
    /**
    * @brief Inserta una palabra en el diccionario.
    *
    * @param clave la palabra que se quiere insertar en el diccionario.
    *
    * @return Un iterador a la posición del multiset donde se ha insertado el elemento.
    */
    iterator insert(const string & clave) ;

    /**
    * @brief Elimina una palabra del diccionario.
    * @param clave la palabra que se quiere borrar del diccionario.
    *
    * @return Iterador a la posición del siguiente elemento al borrado
    */
    iterator erase(const string & clave);
    /**
    * @brief Devuelve un iterador al primer valor almacenado.
    *
    * @return iterador a la primera palabra del diccionario.
    */
    iterator begin() const;
    /**
    * @brief Devuelve un iterador al siguiente del �ltimo elemento almacenado.
    *
    * @return iterador a la palabra siguiente a la �ltima del diccionario.
    */
    iterator end() const;
    /**
     * @brief Agrupa en una estructura de la stl todas las palabras que tengan la longitud indicada por longitud.
     *
     * @param longitud Longitud de las palabras a agrupar
     * @return Vector con las palabras agrupadas.
     *
     * @post Se usan iteradores y no se modifica el objeto inicial.
     */
    vector<string> wordsOfLength(int longitud)const;

    int getOccurrences(char c)const;
public:
    class const_iterator{
    private:
        multiset<string>::const_iterator iter_const;
    friend class Dictionary_multi;
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
        * @brief Operador de asignaci�n.
        *
        * @param other el iterador que vamos a asignar.
        *
        * @post el objeto impl�cito se convierte en una
        * copia de other.
        *
        * @return referencia al objeto impl�cito.
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
        * @return el valor indicado por el objeto impl�cito.
        */
        const string& operator*() const;

        /**
        * @brief Operador ++;
        *
        * @post el objeto impl�cito indicar� el siguiente
        * elemento almacenado.
        *
        * @return referencia al objeto impl�cito.
        */
        const_iterator& operator++();

        /**
        * @brief Operador --;
        *
        * @post el objeto impl�cito indicar� el
        * elemento anterior almacenado.
        *
        * @return referencia al objeto impl�cito.
        */
        const_iterator& operator--();
    };

    /**
    * @brief Devuelve un iterador al primer valor almacenado.
    *
    * @return iterador a la primera palabra del diccionario.
    */
    const_iterator cbegin();

    /**
    * @brief Devuelve un iterador al siguiente del �ltimo elemento almacenado.
    *
    * @return iterador a la palabra siguiente a la �ltima del diccionario.
    */
    const_iterator cend();

    /**
     * @brief Realiza la union de dos diccionarios multiples
     * @pre Solo se aniaden aquellas palabras que no estén
     * @param other Diccionario con el que hacer la union
     * @post El objeto implicit queda modificado.
     */
    void Aniade(const Dictionary_multi & other);

    /**
     * @brief Carga de un diccionario
     * @param pathname Fichero a cargar
     * @post Se carga el diccionario con las palabras (repetidas o no) del fichero
     */
    void Load( const char* pathname);
};
/**
 * @brief Sobrecarga del operador de salida
 * @param output Flujo de salida
 * @param dictionary Diccionario multiple a imprimir
 * @return Referencia al flujo de salida
 */
ostream & operator<<(ostream& output, const Dictionary_multi& dictionary);


#endif //PRACTICA_SET_MAP_DICTIONARY_MULTI_H
