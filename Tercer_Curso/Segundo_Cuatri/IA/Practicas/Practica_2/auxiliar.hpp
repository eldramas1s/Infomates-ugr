#ifndef COMPORTAMIENTOAUXILIAR_H
#define COMPORTAMIENTOAUXILIAR_H

#include <chrono>
#include <time.h>
#include <thread>
#include <iostream>
#include <list>
#include <set>
#include <queue>
#include <math.h>

#include "comportamientos/comportamiento.hpp"

// Representación del estado del auxiliar
// (f,c,brujula,zapas)
struct EstadoA{
	int f;
	int c;
	int brujula;
	bool zapas;

  // comparadores
	bool operator==(const EstadoA &st) const{
		return f==st.f and c==st.c and brujula==st.brujula and zapas==st.zapas;
	}

  bool operator<(const EstadoA &st) const{
    if (f < st.f) return true;
    else if (f == st.f and c < st.c) return true;
    else if (f == st.f and c == st.c and brujula < st.brujula) return true;
    else if (f == st.f and c == st.c and brujula == st.brujula and zapas < st.zapas) return true;
    else return false;
  }
};

// Representación de un nodo del auxiliar
// (estado, coste, heurística, secuencia de acciones)
struct NodoA{
	EstadoA estado;
  int coste;
  int heuristica;

  vector<Action> secuencia;

  // comparadores
	bool operator==(const NodoA &node) const{
    return estado==node.estado;
  }

  bool operator<(const NodoA &node) const{
    return estado < node.estado;  
  }

  bool operator>(const NodoA &node)const{
    return node<(*this);
  }
};

// Comparador para la cola de prioridad
struct ComparadorA{
  bool operator()(const NodoA& a, const NodoA& b) {
    return a.coste + a.heuristica > b.coste + b.heuristica;  // menor valor tiene más prioridad
  }
};

class ComportamientoAuxiliar : public Comportamiento
{

public:
  ComportamientoAuxiliar(unsigned int size = 0) : Comportamiento(size)
  {
    // Inicializar Variables de Estado Niveles 0,1,4
    last_action = IDLE;
    giro45izq = 0;
    zap = false;
    giro180=0;
    frecuencias.resize(size, vector<int>(size, 0));
  }

  ComportamientoAuxiliar(std::vector<std::vector<unsigned char>> mapaR, std::vector<std::vector<unsigned char>> mapaC) : Comportamiento(mapaR,mapaC)
  {
    hayPlan = false;
    zap=false;
  }
  ComportamientoAuxiliar(const ComportamientoAuxiliar &comport) : Comportamiento(comport) {}
  ~ComportamientoAuxiliar() {}

  Action think(Sensores sensores);

  int interact(Action accion, int valor);

  Action ComportamientoAuxiliarNivel_0(Sensores sensores);
  Action ComportamientoAuxiliarNivel_1(Sensores sensores);
  Action ComportamientoAuxiliarNivel_2(Sensores sensores);
  Action ComportamientoAuxiliarNivel_3(Sensores sensores);
  Action ComportamientoAuxiliarNivel_4(Sensores sensores);
  Action ComportamientoAuxiliarNivel_E(Sensores sensores);

  /**********************************************************/
  // Métodos del alumno
  /**********************************************************/


  /****************************************/
  // Nivel 0 y 1
  /****************************************/

  /**
   * @brief Método auxiliar que determina si la casilla a acceder es viable por altura
   * 
   * @param dif Diferencia de altura entre la casilla actual y la que se quiere visitar
   * @return char Casilla a la que se puede acceder
   */
  bool ViablePorAlturaA(int dif);

  /**
   * @brief Método auxiliar que pinta la visión en los mapas de superficie y altura
   * 
   * @param sensores Sensores del rescatador
   * @param m Mapa de superficie
   * @param a Mapa de altura
   * @post Los mapas de superficie y altura se actualizan con la información de los sensores
   */
  void SituarSensorEnMapa(vector<vector<unsigned char>> &m, vector<vector<unsigned char>> &a, Sensores sensores);

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
   * @param fila pila de la casilla
   * @param col columna de la casilla
   * @param rumbo Orientacion del agente
   * 
   * @pre |fila|<=3 and |col|<=3
   * @return int Entero del 1 al 15
   */
  int GetPos(int fila,int col, Orientacion rumbo);

  /**
   * @brief Comprueba si hay un rescatador en la linera central de la visión del agente
   * 
   * @param ags sensores de agentes
   * @return true si hay un rescatador en las casillas {2,6,12}
   * @return false si no hay un rescatador en las casillas {2,6,12}
   */
  bool HayRescatador(const vector<unsigned char> & ags);

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
   * @brief Distancia Chebyshev, es una buena heurística para el problema
   * 
   * @param x1 fila de partida
   * @param y1 columna de partida
   * @param x2 fila objetivo
   * @param y2 columna objetivo
   * @return int 
   */
  int Heuristica(int x1, int y1, int x2, int y2){
    return max(abs(x1-x2),abs(y1-y2));
  }

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
   * @brief Algoritmo de A* aplicado a nuestro problema
   * 
   * @param inicio Estado inicial
   * @param final Estado final
   * @param terreno mapa de casillas
   * @param altura mapa de cotas
   * @param nivel Nivel de ejecucion
   * @return list<Action> plan de actuacion
   */
  list<Action> A_star(const EstadoA &inicio, const EstadoA &final, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);

  
  /**************************************/
  // Nivel adicional (tutorial II)
  /**************************************/


  list<Action> AnchuraAuxiliar(const EstadoA &inicio, const EstadoA &final, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);

  /**
   * @brief Comprueba si al estado al que vamos tras andar es correcto
   * 
   * @param st estado de partida
   * @param terreno mapa de casillas
   * @param altura mapa de cotas
   * @return true si el estado es correcto en cuanto a casilla pisada
   * @return false si el estado es incorrecto
   */
  bool CasillaAccesibleAuxiliar(const EstadoA &st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);

  /**
   * @brief Calcula el estado tras aplicar la accion de andar
   * 
   * @param st estado al que se le aplica
   * @return EstadoR estado resultado
   */
  EstadoA NextCasillaAuxiliar(const EstadoA &st);

  /**
   * @brief Calcula el estado resultante de aplicar una accion a otro estado
   * 
   * @param accion accion aplicada
   * @param st estado al que se le aplica
   * @param terreno mapa de casillas
   * @param altura mapa de cotas
   * @return EstadoA estado tras aplicar la accion
   */
  EstadoA applyA(Action accion, const EstadoA & st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);

  bool Find (const NodoA & st, const list<NodoA> &lista){
    auto it = lista.begin();
    while (it != lista.end() and !((*it) == st)){
      it++;
    }
    return (it != lista.end());
  }

  /**
   * @brief Pinta en el mapa el plan obtenido
   * 
   * @param st Estado de partida del plan
   * @param plan lista de acciones a seguir
   */
  void VisualizaPlan(const EstadoA &st, const list<Action> &plan);

  /**************************************/
  // Nivel 4 
  /**************************************/

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
  int FallaPlan(Sensores sensores,Action next_action, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura,bool energy_reload, int umbral_energia=500);

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
  void GetBasesA(set<pair<int,int>> &bases,int f, int c, const vector<vector<unsigned char>> &terreno,int k=3);


  /**
   * @brief Algoritmo de Dijkstra modificado para que tome el camino óptimo a la ocurrencia más cercana de un conjunto
   * 
   * @param inicio Estado inicial
   * @param bases conjunto de posiciones a las que llegar
   * @param terreno mapa de casillas
   * @param altura mapa de cotas
   * @return list<Action> plan de actuacion
   */
  list<Action> Dijkstra_mod(const EstadoA &inicio, const set<pair<int,int>> & bases, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);

  /**
   * @brief Extensión de HayRescatador para comprobar si hay un agente en la línea recta de visión
   * 
   * @param ags Sensor de agentes
   * @param flag true si estamos en comportamiento deliberativo
   * @return true  Hay algun agente en el camino
   * @return false  No hay ningun agente en el camino
   */
  bool HayAgente(const vector<unsigned char> & ags,bool flag);

  /**
   * @brief Obtiene el procentaje de mapa explorado 
   * 
   * @param terreno mapa de casillas
   * @return float porcentaje descubierto
   */
  float porcentajeA(const vector<vector<unsigned char>> &terreno);


  /**
   * @brief Determina si el auxiliar está viendo al herido
   * 
   * @param f fila del agente
   * @param col columna del agente
   * @param rumbo orientacion del agente
   * @param destf fila del herido
   * @param destc columna del herido
   * @return true si el auxiliar ve al herido
   * @return false si el auxiliar no ve al herido
   */
  bool VeoDestino(int f, int col, Orientacion rumbo, int destf, int destc);

  //Datos miembro
  private:
  int giro45izq;                   // Contador de giros a la izquierda(reactivo)
  bool zap;                        // Bandera de zapatillas(reactivo)
  Action last_action;              // Ultima accion realizada(reactivo)
  int giro180;                     // Contador de giros a la derecha(reactivo)
  vector<vector<int>> frecuencias; // Mapa de frecuencias de pisadas
  
  list<Action> plan;               // Plan de actuación(deliberativo)
  bool hayPlan;                    // Bandera de existencia de plan(deliberativo)

};

#endif
