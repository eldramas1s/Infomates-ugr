#ifndef COMPORTAMIENTORESCATADOR_H
#define COMPORTAMIENTORESCATADOR_H

#include <chrono>
#include <time.h>
#include <thread>
#include <list>
#include <set>
#include <queue>
#include <math.h>
#include <cmath>

#include "comportamientos/comportamiento.hpp"

// Representación del estado del rescatador
// (f,c,brujula,zapas)
struct EstadoR{
  int f; 
  int c; 
  int brujula; 
  bool zapas;

  // comparadores
  bool operator==(const EstadoR &st) const{
		return f==st.f and c==st.c and brujula==st.brujula and zapas==st.zapas;
	}

  bool operator<(const EstadoR &st) const{
    if (f < st.f) return true;
    else if (f == st.f and c < st.c) return true;
    else if (f == st.f and c == st.c and brujula < st.brujula) return true;
    else if (f == st.f and c == st.c and brujula == st.brujula and zapas < st.zapas) return true;
    else return false;
  }
};


// Representación de un nodo del rescatador
// (estado, coste, heurística, secuencia de acciones)
struct NodoR{
	EstadoR estado;
  int coste;
  int heuristica;
  vector<Action> secuencia;

  // comparadores
	bool operator==(const NodoR &node) const{
    return estado==node.estado and node.coste>=coste;
  }

  bool operator<(const NodoR &node) const{
    return estado < node.estado;  
  }

  bool operator>(const NodoR &node)const{
    return node<(*this);
  }
};

// Comparador para la cola de prioridad
struct ComparadorR{
  bool operator()(const NodoR& a, const NodoR& b) {
    return a.coste + a.heuristica > b.coste + b.heuristica;
  }
};


class ComportamientoRescatador : public Comportamiento
{

public:
  ComportamientoRescatador(unsigned int size = 0) : Comportamiento(size)
  {
    // Inicializar Variables de Estado Niveles 0,1
    last_action = IDLE;
    giro45izq = 0;
    zap = false;
    giro180_izq = false;
    frecuencias.resize(size, vector<int>(size, 0));
    hayPlan=false;

  }

  ComportamientoRescatador(std::vector<std::vector<unsigned char>> mapaR, std::vector<std::vector<unsigned char>> mapaC) : Comportamiento(mapaR,mapaC)
  {
    hayPlan = false;
    zap=false;
  }
  ComportamientoRescatador(const ComportamientoRescatador &comport) : Comportamiento(comport) {}
  ~ComportamientoRescatador() {}

  Action think(Sensores sensores);

  int interact(Action accion, int valor);

  Action ComportamientoRescatadorNivel_0(Sensores sensores);
  Action ComportamientoRescatadorNivel_1(Sensores sensores);
  Action ComportamientoRescatadorNivel_2(Sensores sensores);
  Action ComportamientoRescatadorNivel_3(Sensores sensores);
  Action ComportamientoRescatadorNivel_4(Sensores sensores);
  

  /**********************************************************/
  // Métodos del alumno
  /**********************************************************/


  /****************************************/
  // Nivel 0 y 1
  /****************************************/

  /**
   * @brief Método auxiliar que determina si la casilla a acceder es viable por altura
   * 
   * @param dif Diferencia de altura entre la casilla actual y casilla
   * @return true si la casilla a la que accedemos es viable por altura
   */
  bool ViablePorAlturaR(int dif); 

  /**
   * @brief Método auxiliar que determina si hay un agente en la linea central de vision
   * 
   * @param ags Matriz de agentes
   * @param flag true si estamos en comportamiento deliberativo
   * @return true si hay una auxiliar en las casillas {2,6,12}
   * @return false si no hay un auxiliar en las casillas {2,6,12}
   */
  bool HayAgente(const vector<unsigned char> & ags,bool flag);

  /**
   * @brief Método auxiliar que pinta la visión en los mapas de superficie y altura
   * 
   * @param sensores Sensores del rescatador
   * @param m Mapa de superficie
   * @param a Mapa de altura
   * @post Los mapas de superficie y altura se actualizan con la información de los sensores
   */
  void SituarSensorEnMapa(vector<vector<unsigned char>> &m, vector<vector<unsigned char>> &a, vector<vector<unsigned char>>& e,Sensores sensores);
  

  /**
   * @brief Determina la casilla con menor frecuencia de las disponibles en la vision del agente
   * 
   * @param sensores sensores del agente
   * 
   * @return int casilla de la vision con menor frecuencia de pisada
   */
  int LessFreq(const Sensores &sensores);

  /**
   * @brief Obtiene la posicion sobre el sensor de vision de la casilla (fila,col)
   * 
   * @param fila pila de la casilla (relativa al agente)
   * @param col columna de la casilla (relativa al agente)
   * @param rumbo Orientacion del agente
   * 
   * @pre |fila|<=3 and |col|<=3
   * @return int Entero del 1 al 15
   */
  int GetPos(int fila,int col, Orientacion rumbo);

  /**
   * @brief Obtiene por referencia las posiciones sobre la matriz de frecuencias de los caminos posibles
   * 
   * @param f fila del agente
   * @param c columna del agente
   * @param sensores Sensores del agente
   * @param camino vector con pares de posiciones en la matriz
   */
  void GetPaths(int f, int c, const Sensores & sensores, vector<pair<int,int>> &camino);

  /**
   * @brief Comprueba si la casilla es una de las que queremos y es viable por altura
   * 
   * @param sensores Sensores del agente
   * @param casilla casilla que queremos comprobar
   * @param deseadas vector de casillas deseadas
   * 
   * @pre 0 < casilla < 16
   * @return true si la casilla es deseada 
   */
  bool CasillaDeseada(const Sensores & sensores, int casilla, const vector<unsigned char> & deseadas);

  /**
   * @brief Determina el comportamiento del agente, delega en LessFreq salvo para detectar zapatillas
   * 
   * @param sensores Sensores del agente
   * @return int posicion del sensor de vision a la que moverse
   */
  int Andar(const Sensores & sensores);


  /**
   * @brief Determina si hay existencias de un elemento en un vector
   * 
   * @param v vector 
   * @param x elemento a buscar
   * @return true si el elemento x esta en v.
   */
  bool IsIn(const vector<unsigned char> &v, char x){
      for (auto it=v.begin(); it!=v.end(); it++){
        if(*it==x) return true;
      }
      return false;
  }

  /**
   * @brief Actualiza el mapa de frecuencias de pisadas
   * 
   * @param fila fila del agente 
   * @param col columna del agente
   * @param rumbo orientacion del agente
   * 
   * @post la frecuencia de pisada de la casilla (fila,col) se incrementa dependiendo de su tipo
   */
  void ActualizarFrecs(int fila, int col, Orientacion rumbo);
  
  /**
   * @brief Establece el valor a sumar para cada tipo de casilla
   * 
   * @param casilla tipo de casilla
   * @return int valor de la casilla
   */
  int selector(char casilla);
  
  /**************************************/
  // Nivel 3 
  /**************************************/
  
  /**
   * @brief Pone a 0 todas las posiciones de la matriz
   * 
   * @param m matriz a anular
   * 
   * @post la matriz queda a 0
   */
  void AnularMatrizR(vector<vector<unsigned char>> &m){
    for (int i = 0; i < m[0].size(); i++){
      for (int j = 0; j < m.size(); j++){
        m[i][j] = 0;
      }
    }
  }

  /**
   * @brief Pinta en el mapa el plan obtenido
   * 
   * @param st Estado de partida del plan
   * @param plan lista de acciones a seguir
   */
  void VisualizaPlan(const EstadoR &st, const list<Action> &plan);

  /**
   * @brief Calcula el estado resultante de aplicar una accion a otro estado
   * 
   * @param accion accion aplicada
   * @param st estado al que se le aplica
   * @param terreno mapa de casillas
   * @param altura mapa de cotas
   * @return EstadoR estado tras aplicar la accion
   */
  EstadoR applyR(Action accion, const EstadoR & st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);
  
  /**
   * @brief Calcula el estado tras aplicar la accion de correr
   * 
   * @param st estado al que se le aplica
   * @return EstadoR estado resultado
   */
  EstadoR afterRun(const EstadoR &st);

  /**
   * @brief Calcula el estado tras aplicar la accion de andar
   * 
   * @param st estado al que se le aplica
   * @return EstadoR estado resultado
   */
  EstadoR afterWalk(const EstadoR &st);

  /**
   * @brief Calcula el coste de una accion desde un estado según el terreno y la diferencia de altura
   * 
   * @param my_f fila actual
   * @param my_c columna actual
   * @param new_f fila de llegada
   * @param new_c columna de llegada
   * @param accion accion realizada
   * @param terreno mapa de casillas
   * @param altura mapa de cotas
   * @return int coste de la accion
   */
  int whatCost(int my_f, int my_c, int new_f, int new_c, Action accion, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);

  /**
   * @brief Comprueba si al estado al que vamos tras la accion es correcto
   * 
   * @param accion accion a realizar
   * @param st estado de partida
   * @param terreno mapa de casillas
   * @param altura mapa de cotas
   * @return true si el estado es correcto en cuanto a casilla pisada
   * @return false si el estado es incorrecto
   */
  bool CasillaAccesibleRescatador(Action accion, const EstadoR &st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);

  /**
   * @brief Algoritmo de Dijkstra aplicado a nuestro problema
   * 
   * @param inicio Estado inicial
   * @param final Estado final
   * @param terreno mapa de casillas
   * @param altura mapa de cotas
   * @return list<Action> plan de actuacion
   */
  list<Action> Dijkstra(const EstadoR &inicio, const EstadoR &final, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);

  /**
   * @brief Comprueba que podamos correr
   * 
   * @param st Estado del que partimos
   * @param terreno mapa de casillas
   * @return true Si podemos correr, es decir, saltamos una casilla transitable
   * @return false Si no podemos correr, es decir, saltamos una casilla no transitable o a una casilla no transitable
   */
  bool CanRun(const NodoR &st, const vector<vector<unsigned char>> &terreno);

  /***********************************************/
  //  NIVEL 4
  /***********************************************/

  /**
     * @brief Algoritmo de A* aplicado a nuestro problema
     * 
     * @param inicio Estado inicial
     * @param final Estado final
     * @param terreno mapa de casillas
     * @param altura mapa de cotas
     * @return list<Action> plan de actuacion
     */
  list<Action> R_Star(const EstadoR &inicio, const EstadoR &final, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);

  /**
     * @brief Heurística monótona para el Rescatador
     * 
     * @param x1 fila de partida
     * @param y1 columna de partida
     * @param x2 fila objetivo
     * @param y2 columna objetivo
     * @return int 
     */
  int R_Heuristica(int x1, int y1, int x2, int y2){
    return ceil(max(abs(x2-x1),abs(y2-y1))/2);
  }

  /**
   * @brief Determina si el plan elegido produce algun problema.
   * 
   * @param sensores Sensores del rescatador
   * @param next_action Acción que se va a realizar en el siguiente paso
   * @param terreno Mapa de casillas
   * @param altura Mapa de cotas
   * @param energy_reload flag sobre si se busca recargar energía 
   * @param umbral_energia Umbral de energía que produce una búsqueda de fuente de energía
   * @return Depende:
   *         - 0 -> si no hay causa de fallo
   *         - 1 -> si la casilla a la que se va o por la que se pasa no es posible ir
   *         - 2 -> si hay un agente que lo impide
   *         - 3 -> si disponemos de menor energía que el umbral
   */
  int FallaPlan(Sensores sensores,Action next_action, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura, bool energy_reload, int umbral_energia=500);

  /**
   * @brief Obtiene las bases de recarga conforme las va viendo en la ejecución
   * 
   * @param bases Conjunto de posiciones de las bases
   * @param f fila del agente
   * @param c columna del agente
   * @param terreno mapa de casillas
   * @param k radio según la distancia de Chebyshev
   * 
   * @post Las bases encontradas se añaden al conjunto de bases
   */
  void GetBasesR(set<pair<int,int>> &bases,int f, int c, const vector<vector<unsigned char>> &terreno,int k=3);

  /**
   * @brief Algoritmo de Dijkstra modificado para que tome el camino óptimo a la ocurrencia más cercana de un conjunto
   * 
   * @param inicio Estado inicial
   * @param bases conjunto de posiciones a las que llegar
   * @param terreno mapa de casillas
   * @param altura mapa de cotas
   * @return list<Action> plan de actuacion
   */
  list<Action> Dijkstra_mod(const EstadoR &inicio, const set<pair<int,int>> & bases, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);

  /**
   * @brief Obtiene el procentaje de mapa explorado 
   * 
   * @param terreno mapa de casillas
   * @return float porcentaje descubierto
   */
  float porcentajeR(const vector<vector<unsigned char>> &terreno);

  /**
   * @brief Impone que haya precipicios en la casilla en la que está el auxiliar si 
   *        esta en un radio de 3 casillas segun la distancia de Chebyshev
   * @param terreno mapa de casillas
   * @param entities mapa de entidades
   * @param f fila del agente
   * @param c columna del agente
   * @param destf fila del herido
   * @param destc columna del herido
   * @param k radio de influencia segun la distancia de Chebyshev
   * 
   * @post Se imponen precipicios en el mapa de casillas
   */
  void MapaMentiroso(vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> & entities, int f, int c, int destf, int destc, int k=3);


//Datos miembro
private:
  int giro45izq;                   // Contador de giros a la izquierda(reactivo)
  bool zap;                        // Bandera de zapatillas(reactivo)
  Action last_action;              // Ultima accion realizada(reactivo)
  int giro180_izq;                     // Contador de giros a la derecha(reactivo)
  vector<vector<int>> frecuencias; // Mapa de frecuencias de pisadas

  list<Action> plan;               // Plan de actuación(deliberativo)
  bool hayPlan;  
};

#endif
