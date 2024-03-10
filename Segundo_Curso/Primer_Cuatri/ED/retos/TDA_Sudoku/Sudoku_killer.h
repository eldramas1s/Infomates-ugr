/* 
 * File:   Sudoku_killer.h
 * Author: mp
 *
 * Created on 7 de octubre de 2023, 18:59
 */

#ifndef SUDOKU_KILLER_H
#define SUDOKU_KILLER_H

#include "Jaula.h"
#include <utility>
#include <vector>

/**
 * @brief T.D.A Sudoku_killer
 * 
 * Una instancia del tipo de dato abstracto sudoku killer consiste en una
 * partición del tablero por Jaulas; es decir, de un conjunto de Jaulas
 * disjuntas de tal manera que cada Celda del tablero esté en una Jaula.
 *
 * @param Tablero Consiste en una matriz estática de enteros donde se guardan los elementos de cada celda dando lugar
 * al tablero del sudoku.
 * @param celdas_iniciales Vector de Jaulas donde se guardan las distintas sumas repartidas por el tablero.
 * @param TAMANIO_TABLERO Constante estática que guarda el tamanio del tablero, en este caso es 9 por ser un sudoku dando
 * lugar a un tablero 9x9.
 * @param SUMA Constante estática que almacena el resultado de sumar todos los números naturales entre 1 y 9 incluyendo ambos
 * es útil para averiguar qué numero poder colocar en una posición de una región, columna o fila.
 *
 * Algunas reglas del sudoku killer son las siguientes:
 *          - No se pueden repetir números en una columna
 *          - No se pueden repetir números en una fila
 *          - No se pueden repetir números en una región (cruadrícula 3x3 del tablero)
 *          - No se pueden repetir números en una jaula
 * Cabe destacar que las tres primeras reglas son propias de un sudoku ordinario dando así paso a la regla del 45.
 *
 * @pre El tablero siempre debe ser de 9x9, así viene determinado mediante la constante TAMANIO_TABLERO
 *
 */
class Sudoku_killer {
public:
    
    /**
     * @brief Constructor por defecto de la clase Sudoku_killer. Crea un
     * sudoku killer vacío.
     * @post el objeto implícito queda inicializado con las jaulas a 0.
     */
    Sudoku_killer();
    
    /**
     * @brief Constructor de la clase Sudoku_killer.
     * @param jaulas contiene todas las jaulas en las que hemos dividido el tablero.
     * 
     * @pre el conjunto de las jaulas almacenadas en jaulas debe ser
     * una partición del tablero.
     *
     * @post El objeto implícito queda inicializado con las distintas jaulas.
     */
    Sudoku_killer(const std::vector<Jaula>& jaulas);
    
    /**
     * @brief Constructor de copia de la clase Sudoku_killer.
     * @param orig sudoku del cual queremos hacer la copia.
     *
     * @post El objeto implícito queda inicializado con los valores de orig.
     */
    Sudoku_killer(const Sudoku_killer& orig);
    
    /**
     * @brief Operador de asignación de la clase Sudoku_killer.
     * @param orig sudoku sobre el cual queremos hacer la asignación.
     *
     * @pre En caso de que orig y *this sean el mismo no se procesa la asignación
     *
     * @post El objeto implícito queda como una copia de orig.
     */
    Sudoku_killer& operator=(const Sudoku_killer& orig);
    
    /**
     * @brief Destructor de la clase Sudoku_killer.
     * @post pone el tablero a 0.
     */
    ~Sudoku_killer();
    
    /**
     * @brief Devuelve la suma de la jaula indicada.
     *
     * @param pos Posición de una celda perteneciente a la jaula.
     *
     * @pre 0 <= pos.first, pos.second() < 9
     *
     * @throw std::invalid_arguments si pos no cumple su precondición
     * @post No se modifica el objeto
     *
     * @return la suma de todos los elementos de la jaula.
     */
    int SumaJaula(Posicion pos) const;

    /**
     * @brief Devuelve la suma de la jaula indicada.
     *
     * @param i Posición de una celda_inicial del vector de jaulas.
     *
     * @pre 0 <= i < jaulas.size()
     *
     * @throw std::invalid_arguments si i no cumple su precondición.
     *
     * @post El objeto implícito no queda modificado
     *
     * @return la suma de todos los elementos de la jaula.
     */
    int SumaJaula(int i) const;
    /**
     * @brief Suma de los elementos de la fila o columna i-esima.
     *
     * @pre i debe estar entre 0 y 8, ambos incluidos.
     * @pre modo debe ser 'c' o 'f'.
     *
     * @throw std::invalid_arguments si modo no cumple su precondición.
     * @throw std::invalid_arguments si i no cumple su precondición.
     *
     * @return la suma de los elementos de la fila.
     */
    int SumaFila(int i, char modo='f') const;

    /**
     * @brief Comprueba si la fila o columna i-ésima está completa.
     *
     * @param i Indice de la fila o columna a analizar.
     * @param modo Si modo es 'f' se analiza la fila i, si es 'c' se haría lo propio con la columna.
     *
     * @pre Diremos que la fila o columna está completa cuando contenga a todos los números del 1 al 9,
     * sin repetir ninguno.
     * @pre i debe estar entre 0 y 8, ambos incluidos.
     * @pre modo debe ser 'c' o 'f'.
     *
     * @throw std::invalid_arguments si modo no cumple su precondición.
     * @throw std::invalid_arguments si i no cumple su precondición.
     *
     * @return true si la fila o columna i-esima está completa, false en caso contrario.
     */
    bool EstaCompleta(int i, char modo='f') const;
    
    /**
     * @brief Número de celdas vacías en una fila o columna i-esima.
     *
     * @param modo Si modo es 'f' se analiza la fila i, si es 'c' se haría lo propio con la columna.
     * @param i Indice de fila o columna según modo.
     *
     * @pre Diremos que una celda está vacía si el dato que almacena es 0.
     * @pre i debe estar entre 0 y 8, ambos incluidos.
     * @pre modo debe ser 'c' o 'f'.
     *
     * @throw std::invalid_arguments si modo no cumple su precondición.
     * @throw std::invalid_arguments si i no cumple su precondición.
     *
     * @return el número de celdas vacías de la fila o columna i-esima.
     */
    int CeldasVacias(int i, char modo='f') const;

    /**
     * @brief Calcula el numero restante de una fila o columna aplicando la regla del 45.
     *
     * @param modo Si modo es 'f' se analiza la fila i, si es 'c' se haría lo propio con la columna.
     * @param i Indice de la fila o columna que queremos solucionar
     *
     * @pre 0 <= @param i < 9
     * @pre @param modo debe ser 'c' o 'f'.
     * @pre CeldasVacias(@param i,modo)==1;
     *
     * @throw std::invalid_arguments si @param modo no cumple su precondición.
     * @throw std::invalid_arguments si @param i no cumple su precondición.
     *
     * @post El elemento calculado es añadido a su celda correspondiente.
     * @return Devuelve la posicion donde ha añadido el elemento
     */
    Posicion CalculaPosicionFC(int i, char modo='f');

    /**
     * @brief Resuelve el sudoku killer de forma recursiva Para ello, utiliza
     * el método privado RellenarCeldas.
     * @post El sudoku killer queda resuelto.
     */
    void ResolverSudokuKiller();

private:
    
    /*
     * @brief Dimensión del tablero. Un tablero de sudoku killer es
     * una cuadrícula de tamaño 9x9.
     */
    static const int TAMANIO_TABLERO = 9;
    
    /**
     * @brief Constante SUMA: Todos los elementos de cada fila, cada columna
     * y de cada cuadrícula de tamaño 3x3 en las que está dividido el tablero
     * de un sudoku killer suman 45.
     */
    static const int SUMA = 45;
    
    /**
     * @private Tablero del sudoku killer.
     */
    Celda tablero[TAMANIO_TABLERO][TAMANIO_TABLERO];
    
    /**
     * @brief vector de Jaulas. Contiene a todas las jaulas
     * en las que hemos dividido el tablero.
     */
    std::vector<Jaula> jaulas;
    
    /**
     * @brief Inicializa un tablero vacío, poniendo todas las casillas
     * a cero.
     *
     * @post El tablero queda inicializado a 0.
     */
    void Inicializar();

    /**
     * @brief Rellena todas las celdas del sudoku killer a partir de la indicada por
     * f y c.
     *
     * Si ( f, c) es la celda correspondiente a la fila f y columna c,
     * procedemos de la siguiente forma:
     * 
     * a) Si f==9, queremos resolver la fila siguiente a la última, por lo que el
     *   sudoku killer estaría resuelto.
     * 
     * b) Si f != 9 y c==9, queremos resolver la celda siguiente a la última
     *   de la fila f, por lo que la fila f estaría resuelta
     *   y pasaríamos a resolver la celda (f+1,0).
     * 
     * c) Si la celda ( f, c) no está vacía, pasaríamos a resolver
     *   la celda ( f, c+1), pues ( f, c) ya está llena.
     *
     * d) Si la celda ( f, c) estuviera vacía, se realiza un proceso de
     * prueba y error con los posibles valores de la celda de forma que si un candidato
     * se muestra incorrecto, se retorna al último paso antes de rellenar la celda
     * con dicho valor. Este proceso se realiza hasta resolver el sudoku killer completamente
     * o hasta encontrar un error.
     *
     * Para cada uno de los posibles valores de la celda, se haría lo suguiente:
     *
     *      - Se comprueba que no incumple ninguna de las restricciones básicas del sudoku killer
     *      (No se repiten números en las filas, columnas, subcuadrantes 3x3 y jaulas).
     *
     *      - Si no se cumplen todas las restricciones, se pasa a probar con el siguiente
     *      valor. Si el valor con el que se está probando cumple con las restricciones
     *      anteriores, supondremos que es el correcto, se rellena la celda con ese valor
     *      y pasamos a resolver el resto de celdas.
     * 
     *      - Si al tratar de resolver el resto de celdas ocurre que descartamos todos los
     *      posibles valores de una celda, entonces el valor colocado en la celda
     *      (@param f,@param c) sería incorrecto, por lo que vaciaríamos todas las celdas
     *      que hemos rellenado tras resolver la celda (@param f,@param c) (incluida) y
     *      probaríamos el siguiente valor.
     *
     * @param f la fila de la celda a partir de la cual resolveremos las demás.
     * @param c la columna de la celda a partir de la cual resolveremos las demás.
     *
     * @pre El sudoku killer no está completamente resuelto.
     * @post El sudoku killer quedará completamente resuelto.
     */
    bool RellenarCeldas(int f=0, int c=0);
};


#endif /* SUDOKU_KILLER_H */

