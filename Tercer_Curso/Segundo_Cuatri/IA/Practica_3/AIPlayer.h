#ifndef __AI_PLAYER_H__
#define __AI_PLAYER_H__

# include "../../include/model/Attributes.h"
# include "../../include/model/Player.h"
# include "../../include/model/Heuristic.h"

using namespace std;       //Por comodidad

/**
 * @brief Heurística para la valoración de las mejoras
 * 
 */
class ValoracionTest: public Heuristic{
   protected:
      virtual float getHeuristic(const Parchis &estado, int jugador) const;
};

/**
 * @brief Heurística que obtiene los mejores resultados que he conseguido
 * 
 */
class Simple: public Heuristic{
   protected:
      virtual float getHeuristic(const Parchis & estado, int player) const;
      bool isInDanger(const Parchis & estado, int jugador, color c, int id_piece)const;
      bool BarrierNear(const Parchis& estado, int jugador, color c, int id_piece, vector<color> &pColors, vector<color> &oColors)const;
      vector<pair<color,int>> PiecesinBarriers(const Parchis &estado, vector<color> &pColors, vector<color> &oColors)const;
};

/**
 * @brief Heurística que, en mi opinion es la más potente pues gana al ninja 5 (situación más difícil)
 * 
 */
class TheBestInMyOpinion: public Heuristic{
   protected:
      virtual float getHeuristic(const Parchis & estado, int player) const;
};

/**
 * @brief Heurística que gana al ninja 1 como jugador 2 de forma aplastante
 * 
 */
class GoForNinja1: public Heuristic{
   protected:
      virtual float getHeuristic(const Parchis & estado, int player) const;
      bool BarrierNear(const Parchis& estado, int jugador, color c, int id_piece, vector<color> &pColors, vector<color> &oColors)const;
      vector<pair<color,int>> PiecesinBarriers(const Parchis &estado, vector<color> &pColors, vector<color> &oColors)const;
};

class AnotherTry: public Heuristic{
   protected:
      virtual float getHeuristic(const Parchis & estado, int player) const;
      bool BarrierNear(const Parchis& estado, int jugador, color c, int id_piece, vector<color> &pColors, vector<color> &oColors)const;
      vector<pair<color,int>> PiecesinBarriers(const Parchis &estado, vector<color> &pColors, vector<color> &oColors)const;
};

class AIPlayer : public Player{
protected:
   //Id identificativo del jugador
   const int id;

public:
   /**
    * @brief Constructor de un objeto AIPlayer
    *
    * @param name Nombre del jugador
    */
   inline AIPlayer(const string& name): Player(name), id(1){
   };

   /**
    * @brief Constructor de un objeto AIPlayer
    *
    * @param name Nombre  del jugador
    * @param id Id del jugador
    */
   inline AIPlayer(const string& name, const int id): Player(name), id(id){
   };

   /**
    * @brief Función que percibe el el parchís y al jugador actual.
    * Asigna el tablero en actual y el id del jugador.
    *
    * @param p Instancia Parchis que se quiere percibir
    */
   inline virtual void perceive(Parchis& p){ Player::perceive(p); }

   /**
    * @brief Función abstracta que define el movimiento devuelto por el jugador.
    * Llama a la función movePiece con el valor asignado a los parámetros pasados
    * por referencia.
    *
    * @return true
    * @return false
    */
   virtual bool move();

   /**
    * @brief Función que se encarga de decidir el mejor movimiento posible a
    * partir del estado actual del tablero. Asigna a las variables pasadas por
    * referencia el valor de color de ficha, id de ficha y dado del mejor movimiento.
    *
    * @param c_piece Color de la ficha
    * @param id_piece Id de la ficha
    * @param dice Número de dado
    */
   virtual void think(color& c_piece, int& id_piece, int& dice) const;

   /**
    * @brief Método que determina si el player es inteligente (decide el mejor movimiento)
    * o no. True para AIPlayer.
    *
    * @return true
    * @return false
    */
   inline virtual bool canThink() const{ return true; }

   /************************************************/
   // Métodos del alumno
   /************************************************/
   /**
   * @brief Función que se encarga de decidir el mejor movimiento posible a
   * partir del estado actual del tablero. Asigna a las variables pasadas por
   * referencia el valor de color de ficha, id de ficha y dado del mejor movimiento.
   *
   * @param c_piece Color de la ficha
   * @param id_piece Id de la ficha
   * @param dice Número de dado
   */

   // Métodos del tutorial
   void thinkAleatorio(color &c_piece, int &id_piece, int &dice) const;
   void thinkFichaMasAdelantada(color &c_piece, int &id_piece, int &dice) const;
   void thinkMejorOpcion(color &c_piece, int &id_piece, int &dice) const;  
   float Minimax(const Parchis &actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece, int &dice,Heuristic *heuristic)const;
   float Minimax_Limitado(const Parchis &actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece, int &dice, Heuristic *heuristic)const;
   
   // Métodos implementados+

   /**
    * @brief Poda alfa beta simple
    * 
    * @param actual Estado actual de juego
    * @param jugador Jugador al que le toca mover
    * @param profundidad Nivel de exploracion del arbol de decisiones
    * @param profundidad_max Maximo nivel de exploracion
    * @param c_piece color de la pieza con el mejor movimiento
    * @param id_piece identificador de l apieza con mejor movimiento
    * @param dice dado del mejor movimiento
    * @param alpha cota inferior
    * @param beta cota superior
    * @param heuristic Heuristica a usar
    * @return float resultado a devolver
    */
   float Poda_Alfa_Beta(const Parchis &actual, int jugador, int profundidad,int profundidad_max, color &c_piece, int &id_piece, int &dice, float alpha, float beta, Heuristic *heuristic)const;
   
   /**
    * @brief Poda alfa beta con profundidad dinamica
    * 
    * @param actual Estado actual de juego
    * @param jugador Jugador al que le toca mover
    * @param profundidad Nivel de exploracion del arbol de decisiones
    * @param profundidad_max Maximo nivel de exploracion
    * @param c_piece color de la pieza con el mejor movimiento
    * @param id_piece identificador de l apieza con mejor movimiento
    * @param dice dado del mejor movimiento
    * @param alpha cota inferior
    * @param beta cota superior
    * @param heuristic Heuristica a usar
    * @return float resultado a devolver
    */
   float Poda_Alfa_Beta_Ramificacion(const Parchis&actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece, int &dice, float alpha, float beta, Heuristic *heuristic)const;
   
   /**
    * @brief Poda alfa beta con ordenacion en el primer nivel
    * 
    * @param actual Estado actual de juego
    * @param jugador Jugador al que le toca mover
    * @param profundidad Nivel de exploracion del arbol de decisiones
    * @param profundidad_max Maximo nivel de exploracion
    * @param c_piece color de la pieza con el mejor movimiento
    * @param id_piece identificador de l apieza con mejor movimiento
    * @param dice dado del mejor movimiento
    * @param alpha cota inferior
    * @param beta cota superior
    * @param heuristic Heuristica a usar
    * @return float resultado a devolver
    */
   float Poda_Alfa_Beta_Ordenacion(const Parchis&actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece, int &dice, float alpha, float beta, Heuristic *heuristic)const;
   
   /**
    * @brief Poda alfa beta probabilistica
    * 
    * @param actual Estado actual de juego
    * @param jugador Jugador al que le toca mover
    * @param profundidad Nivel de exploracion del arbol de decisiones
    * @param profundidad_max Maximo nivel de exploracion
    * @param c_piece color de la pieza con el mejor movimiento
    * @param id_piece identificador de l apieza con mejor movimiento
    * @param dice dado del mejor movimiento
    * @param alpha cota inferior
    * @param beta cota superior
    * @param heuristic Heuristica a usar
    * @return float resultado a devolver
    */
   float Poda_Alfa_Beta_Probabilistica(const Parchis&actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece, int &dice, float alpha, float beta, float umbral, Heuristic *heuristic)const;
   
   /**
    * @brief Poda alfa beta que considere definitiva, es un mix de ordenacion con profundidad dinamica
    * 
    * @param actual Estado actual de juego
    * @param jugador Jugador al que le toca mover
    * @param profundidad Nivel de exploracion del arbol de decisiones
    * @param profundidad_max Maximo nivel de exploracion
    * @param c_piece color de la pieza con el mejor movimiento
    * @param id_piece identificador de l apieza con mejor movimiento
    * @param dice dado del mejor movimiento
    * @param alpha cota inferior
    * @param beta cota superior
    * @param heuristic Heuristica a usar
    * @return float resultado a devolver
    */
   float Poda_Alfa_Beta_Definitiva(const Parchis&actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece, int &dice, float alpha, float beta, Heuristic *heuristic)const;


   /******************************/
   // Metodos auxiliares
   /******************************/
   /**
    * @brief Determina el grado de profundidad maxima de una iteracion.
    * 
    * @param profundidad Nivel de exploracion del arbol de decisiones
    * @param profundidad_max Maximo nivel de exploracion
    * @param ramificacio_actual Cantidad de hijos que debemos explorar en este momento
    */
   int calcular_profundidad_siguiente(int profundidad, int profundidad_max, int ramificacion_actual)const;
};

#endif
