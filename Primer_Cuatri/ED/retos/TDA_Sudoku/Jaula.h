/* 
 * File:   Jaula.h
 * Author: mp
 *
 * Created on 7 de octubre de 2023, 18:18
 */

#ifndef JAULA_H
#define JAULA_H

#include <utility>


typedef std::pair<int,int> Posicion;

/**
 * @brief T.D.A Celda
 *
 * El struct Celda consiste en un registro de 2 campos que representa una celda de un tablero de sudoku.
 *
 * @param posicion Consiste en un par Posicion que guarda la fila y columna de la celda en
 * el propio tablero del sudoku.
 * @param siguiente puntero a la siguiente celda.
 *
 * @pre 0 <= posicion.first(), posicion.second() < 9
 *
 */
struct Celda{
    
    /**
     * @brief posición de la celda en el tablero de Sudoku killer.
     */
    Posicion posicion;
    
    /**
     * @brief puntero a la siguiente celda de la jaula.
     */
    Celda* siguiente;
    
    /**
     * @brief Constructor sin argumentos del tipo Celda.
     *
     * @post La celda queda inicializada a un valor imposible.
     */
    Celda() {
        
        posicion.first = -1;
        posicion.second = -1;
        siguiente = nullptr;
    }
    
    /**
     * @brief Constructor del tipo Celda. Recibe el @param fila y el
     * @param columna.
     * 
     * @pre fila y columna deben estar entre 0 y 8.
     *
     * @post La celda tiene una posicion pero no tiene un valor ni una celda siguiente a la que apunta.
     */
    Celda(int fila, int columna) {
        
        posicion.first = fila;
        posicion.second = columna;
        siguiente = nullptr;
    };
};

/**
 * @brief T.D.A Jaula
 *
 * Una instancia del tipo de dato abstracto Jaula representa un conjunto
 * de Celdas de un tablero de Sudoku killer, junto con la suma de los
 * valores almacenados en cada celda de la Jaula.
 *
 * @param inicial Puntero a una celda de la jaula, puede ser cualquiera de ellas.
 * @param suma  Suma de todas las celdas de la jaula
 * @param total_celdas Cantidad de celdas que forman la jaula
 *
 * @pre 0 <= total_celdas <= 81 (en caso de ser 81 se trataría como un sudoku normal)
 * @pre 0 < suma
 */
class Jaula {
public:
    
    /**
     * @brief Constructor por defecto de la clase Jaula. Crea una Jaula
     * de 0 celdas y con suma 0.
     */
    Jaula();
    
    /**
     * @brief Constructor de la clase Jaula. Recibe la primera celda que
     * forma parte de la Jaula y la suma de la jaula.
     * 
     * @pre suma_jaula debe ser mayor o igual a 0.
     */
    Jaula(Celda primera, int suma_jaula);
    
    /**
     * @brief Constructor de copia de la clase Jaula.
     * @param orig objeto jaula que queremos copiar
     * @post el objeto implicito resulta una copia de orig.
     */
    Jaula(const Jaula& orig);
    
    /**
     * @brief Operador de asignación de la clase Jaula.
     * @param orig objeto jaula que queremos asignar.
     * @post el objeto implicito resulta una copia de orig.
     */
    Jaula& operator=(const Jaula& orig);
    
    /**
     * @brief Destructor de la clase Jaula.
     */
    ~Jaula();
    
    /**
     * @brief Comprueba si una celda @param c pertenece a la jaula.
     * Diremos que una celda pertenece a la jaula si existe alguna
     * celda de la jaula con la misma posición que c.
     *
     * @param c celda que queremos ver si pertenece al sudoku.
     *
     * @return true si pertenece a la jaula, false en caso contrario.
     */
    bool Pertenece(Celda c) const;
    
    /**
     * @brief Comprueba si en la jaula hay alguna celda que contenga
     * la @param pos indicada.
     * @pre 0<= pos.first, pos.second() < 9
     * @throw std::invalid_arguments si no se cumple la precondición.
     * @return true si pertenece a la jaula, false en caso contrario.
     */
    bool Pertenece(Posicion pos) const;
    
    /**
     * @brief Añade una celda nueva a la Jaula. Si nueva ya
     * pertenecía a la jaula, no se hace nada.
     * @pre Una celda pertenece a la jaula si hay una celda de la jaula que contiene la misma posición.
     * @post nueva queda añadida a la celda en caso de cumplir las condiciones
     */
    void Aniade(Celda nueva);
    
    /**
     * @brief Número de celdas de la jaula.
     * @return total_celdas
     */
    int TotalCeldas() const;
    
    /**
     * @brief Suma de la jaula.
     * @return suma
     */
    int GetSuma() const;

    /**
     * @brief Método set del parametro suma.
     *
     * @param s Suma a introducir como dato.
     *
     * @pre 0 < s y en caso de no complirse, no se cambiaría la suma.
     *
     * @post El parámetro suma queda cambiado con valor s.
     */
    void SetSuma(int s);
    
    /**
     * @brief Número de celdas vacías en la jaula.
     *
     * @post El objeto implícito no queda modificado.
     *
     * @return el número de celdas vacías de la jaula.
     */
    int CeldasVacias() const;
    
private:
    
    /**
     * @brief Puntero a la Jaula.
     * 
     * inicial apunta a una celda de la Jaula, que actuará como la primera
     * celda. A partir de inicial, podremos acceder al resto de celdas.
     */
    Celda* inicial;
    
    /**
     * @brief Suma de todos los elementos de la Jaula.
     */
    int suma;
    
    /**
     * @brief Número de celdas que pertenecen a la Jaula.
     */
    int total_celdas;
    
    /**
     * @brief Libera la memoria dinámica reservada.
     */
    void LiberarMemoria();
    
    /**
     * @brief Copia los datos de una Jaula en el objeto implícito.
     */
    void CopiarDatos(const Jaula& otra);

};

/**
 * @brief Sobrecarga del operador == que realiza una comparación entre celdas.
 * @param c1 Primera celda a comparar.
 * @param c2 Segunda celda a comparar.
 * @pre c1 y c2 deben estar correctamente inicializadas.
 * @return true si ambas celdas contienen la misma posición.
 */
bool operator==(const Celda & c1, const Celda & c2 );

#endif /* JAULA_H */

