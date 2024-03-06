/**
   @file Ordenaci�n por inserci�n
*/

   
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <fstream>

#include <chrono>
using namespace std::chrono;




/* ************************************************************ */ 
/*  M�todo de ordenaci�n por inserci�n  */

/**
   @brief Ordena un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
inline static 
void insercion(string T[], int num_elem);



/**
   @brief Ordena parte de un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
static void insercion_lims(string T[], int inicial, int final);



/**
   Implementaci�n de las funciones
**/

inline static void insercion(string T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
}


static void insercion_lims(string T[], int inicial, int final)
{
  int i, j;
  string aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((j > 0) && (T[j] < T[j-1])) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}



int main(int argc, char** argv)
{
    int n = strtol(argv[1], NULL, 10);

  string * T = new string[n];
  assert(T);

  srandom(time(0));

  /*for (int i = 0; i < n; i++)
    {
      T[i] = random();
    };*/
  std::ifstream ifs("/home/el_dramas/Desktop/Segundo_Curso/Segundo_Cuatri/Algoritmica/Practica_1/Datos/quijote.txt");
		if(!ifs.is_open()){
			throw std::ios::failure("wat");
		}
		int i=0;
		while(i < n && ifs){
			ifs >> T[i];
			++i;
		}
  ifs.close();
  high_resolution_clock::time_point tantes, tdespues;
  duration<double> transcurrido;

  tantes = high_resolution_clock::now();

  insercion(T, n);

  tdespues = high_resolution_clock::now();
  transcurrido = duration_cast<duration<double>>(tdespues - tantes);
  cout << n << " " << transcurrido.count() << endl;

  delete [] T;

  return 0;
};
