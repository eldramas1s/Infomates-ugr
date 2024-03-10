/**
 * @file maxstack.h
 * @brief  Archivo de especificación del TDA MaxStack
 * @author
 */

#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

/**
 * @brief Clase maxstack.
 * Consiste en la creación de una pila que mantenga siempre una gestión del máximo de la estructura, está implementada
 * con una cola de pares de elementos que son enteros ambos.
 *
 * @pre Se usa la librería STL
 *
 * @param pila Es una cola de pares <int,int> que se gestiona con la librería STL.
 *
 */
class maxstack{

private:

    /**
     * @brief contenedor cola que implementa una pila con maximo
     */
    queue <pair<int,int>> pila;

public:

    /**
     * @brief comprueba se el objeto implícito está vacío haciendo uso de la función empty de la queue de STL.
     *
     * @return true si está vacía y false si contiene al menos un elemento.
     *
     * @post No se modifica el objeto.
     */
    bool empty()const;

    /**
     * @brief Consiste en una selección del tope de la pila haciendo referencia al frente de la cola.
     *
     * @return Una referencia no constante al elemento del tope de la pila.
     *
     * @post Al no ser constante, permite la modificación del elemento del tope.
     */
    pair <int,int> &top();

    /**
     * @brief Consiste en una selección del tope de la pila haciendo referencia al frente de la cola.
     *
     * @return Una referencia constante al elemento del tope de la pila.
     *
     * @post No se modifica el objeto implícito.
     */
    const pair <int,int> &top()const;

    /**
     * @brief Método que añade un nuevo elemento a la pila maxstack haciendo un recorrido circular.
     *
     * @param p Nuevo elemento a insertar.
     *
     * @post La nueva pila tiene un elemento más y el máximo puede haberse cambiado. El objeto queda sí o sí modificado.
     */
    void push(pair<int,int> p);

    /**
     * @brief Método que elimina el elemto del tope de la pila, hace uso de la función pop de colas de la STL.
     *
     * @post La nueva pila tiene un elemento menos pero el máximo sigue estando bien actualizado gracias al método push.
     */
    void pop();

};
/**
 * @brief Sobrecarga del operador << que dado un método de salida escribe según ese método el par p.
 * @param modo variable que indica la salida.
 * @param p elemento a imprimir o escribir
 * @return referencia al elemento modo para así encadenar salidas de objetos.
 */
ostream& operator<<(ostream& modo,const pair <int,int> &p);