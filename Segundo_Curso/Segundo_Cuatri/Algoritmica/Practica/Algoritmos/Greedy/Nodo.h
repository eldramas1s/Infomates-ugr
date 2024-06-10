#include <list>;


struct Nodo{
   list<Nodo> adyacentes;
}

struct Arista{
   Nodo inicio,fin;
   int peso;
}



