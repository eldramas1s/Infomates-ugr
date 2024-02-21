/**
 * @file maxqueue.h
 * @brief  Archivo de especificación del TDA MaxQueue
 * @author
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <fstream>

using namespace std;
/**
 * @brief Clase maxqueue.
 * Consiste en la creación de una cola que mantenga siempre una gestión del máximo de la estructura, está implementada
 * con una pila de pares de elementos que son enteros ambos.
 *
 * @pre Se usa la librería STL
 *
 * @param cola Es una pila de pares <int,int> que se gestiona con la librería STL.
 *
 */
class maxqueue{
private:

    /**
     * @brief contenedor pila que implementa una cola con maximo
     */
    stack <pair<int,int>> cola;

public:

    /**
     * @brief Función que vuelca la pila(dato miembro de la clase) del objeto implícito en la pila c
     *
     * @param c pila que pasa a ser el contenedor de los datos
     *
     * @post la pila implícita queda vacía y c contiene todos los elementos de la pila implícita en orden inverso.
     */
    void volcar(stack <pair<int,int>> &c);

    /**
     * @brief comprueba se el objeto implícito está vacío haciendo uso de la función empty de la stack de STL.
     *
     * @return true si está vacía y false si contiene al menos un elemento.
     *
     * @post No se modifica el objeto.
     */
    bool empty()const;

    /**
     * @brief Consiste en una selección del tope de la pila haciendo referencia al frente de la cola.
     *
     * @return Una referencia no constante al elemento del frente de la cola.
     *
     * @post Al no ser constante, permite la modificación del elemento del frente.
     */
    pair <int,int> &front();

    /**
     * @brief Consiste en una selección del tope de la pila haciendo referencia constante al frente de la cola.
     *
     * @return Una referencia constante al elemento del frente de la cola.
     *
     * @post No se modifica el objeto implícito.
     */
    const pair <int,int> &front()const;

    /**
     * @brief Método que añade un nuevo elemento a la cola maxqueue haciendo uso de una estructura auxiliar de stack
     * sobre la cual se vuelca la implícita para añadir el nuevo elemento y hacer una gestión del máximo de la estructura
     * tras ese insertado. Se inserta al final de la cola.
     *
     * @param p Nuevo elemento a insertar.
     *
     * @post La nueva cola tiene un elemento más y el máximo puede haberse cambiado. EL objeto queda sí o sí modificado.
     */
    void push(pair<int,int> p);

    /**
     * @brief Método que elimina el elemto del frente de la cola, hace uso de la función pop de pilas de la STL.
     *
     * @post La nueva cola tiene un elemento menos pero el máximo sigue estando bien actualizado gracias al método push.
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