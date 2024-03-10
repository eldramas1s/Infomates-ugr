/*
 * Autor: Juan Manuel Fernández García
 * Autor: Lucas Hidalgo Herrera
 * Fecha: Noviembre, 14, 2023
 * Fichero: RETO3
 */


#include <iostream>
#include <algorithm>
#include <list> 
#include <iomanip>

using namespace std;

/**
* @brief El T.D.A Intervalo representa un intervalo cerrado [a,b],
* donde a,b son números enteros tales que a <= b.
*/
typedef pair <int,int> Intervalo; // intervalo.first <= intervalo.second
typedef list <Intervalo> ListaIntervalos;

/**
* @brief Imprime el intervalo.
*/
void ImprimeIntervalo(Intervalo inter) {
    
    cout << "[ "<< inter.first << ", " << inter.second << "]";
}

/**
* @brief Imprime el contenido de una lista de intervalos.
*/
void ImprimeListaIntervalos(ListaIntervalos lista) {
    
    for(list<Intervalo>::iterator it= lista.begin(); it != lista.end(); ++it)
    {
        ImprimeIntervalo(*it);
        cout << " ";
    }
}

/**
* @brief Functor que permite ordenar los intervalos de menor a mayor.
* Diremos que el intervalo [a,b] es menor que el intervalo [c,d] si
* b < c.
*/
class EsMenor {

    public:
    
        bool operator()(Intervalo i1, Intervalo i2) {
            
            return (i1.second < i2.first);
        }
};

/**
* @brief Comprueba si un intervalo está contenido en otro.
*
* @param inter_1 intervalo el cúal queremos ver si está contenido.
* @param inter_2 intervalo en el que comprobamos si el primero está contenido.
*
* @return true si inter_1 está contenido en inter_2, false en caso contrario.
 *
 * @post Ningún intervaloq ueda modificado
*/
bool EstaContenido(Intervalo inter_1, Intervalo inter_2) {
            
    return ((inter_2.first <= inter_1.first) &&
    (inter_1.second <= inter_2.second));
}

/**
* @brief Elimina un subintervalo de una lista de intervalos, ajustando
* el intervalo que se modifique si fuera necesario. Si dicho
* subintervalo no perteneciera a la lista, no se hace nada.
*
* @param lista lista de intervalos.
* @param x subintervalo a eliminar.
*
* @pre x pertenece a un único intervalo de la lista.
*
* @return true si lo ha eliminado, false en caso contrario.
*
* @post En caso de que se elimine el intervalo, los subintervalos restantes
* tras su eliminación se mantienen en la lista.
*/
bool EliminaSubintervalo(ListaIntervalos& lista, Intervalo x)
{   
    ListaIntervalos::iterator it = lista.begin();
    bool encontrado = false;
    
    // El bucle while se podría sustituir con find_if, pero hace falta
    // montar otro functor que haga el trabajo.
    
    while(it != lista.end() && !encontrado) {
        
        if(EstaContenido(x, *it)) encontrado = true;
        else ++it;
    }
    
    if(encontrado) {
        
        ListaIntervalos::iterator siguiente = it;
        ++siguiente;
        
        Intervalo inter_original = *it;
        lista.erase(it, siguiente);
        
        // Añadimos los intervalos que resultan de eliminar
        // el subintervalo x del intervalo que lo contenía.
        
        if(inter_original.first < x.first) { // Hay un trozo de intervalo a la izda.
            
            Intervalo izda;
            izda.first = inter_original.first;
            izda.second = x.first-1;
            
            lista.push_back(izda);
        }
        
        if(inter_original.second > x.second) { // Hay un trozo de intervalo a la dcha.
            
            Intervalo dcha;
            dcha.first = x.second+1;
            dcha.second = inter_original.second;
            
            lista.push_back(dcha);
        }
        
        lista.sort(EsMenor());
        
    }
    
    return encontrado;  
}

/**
* @brief Comprueba si dos intervalos se solapan.
*
* @param i1
* @param i2
*
* @return true si se solapan, false en caso contrario.
* @post Ningún intervalo queda modificado
*/
bool SeSolapan(Intervalo i1, Intervalo i2) {
    
    return ( ((i2.first <= i1.second) && (i1.first <= i2.second)) || 
           ((i1.first <= i2.second) && (i2.first <= i1.second)) ||
           EstaContenido(i1, i2) || EstaContenido(i2, i1) );
}

/**
* @brief Añade un intervalo x a una lista de intervalos lista,
* fusionándolo con los intervalos con los que se solapen.
*
* @param x intervalo a añadir a la lista.
* @param lista lista de intervalos.
*/
void AniadeIntervalo(Intervalo x, ListaIntervalos& lista) {
    
    ListaIntervalos::iterator inicio = lista.begin();
    ListaIntervalos::iterator fin = lista.end();
    --fin;
    
    // Buscamos el primer y último intervalo de la lista con
    // los que haya solapamiento.
    Intervalo inicial, final;
    
    // Recomiendo hacer un functor para aplicar find_if.
    bool seguir_inicio = true, seguir_final = true;
    
    // Inicio.
    while(inicio != lista.end() && seguir_inicio) {
        
        if(SeSolapan(x, *inicio)) seguir_inicio = false;
        else ++inicio;
    }
    
    // ImprimeIntervalo(*inicio); cout << endl;
    
    // Final.
    ListaIntervalos::iterator aux = lista.begin();
    --aux;
    
    while(fin != aux && seguir_final) {
        
        if(SeSolapan(x, *fin)) seguir_final = false;
        else --fin;
    }
    
    Intervalo solapado;
    
    solapado.first = (x.first < (*inicio).first)?x.first:(*inicio).first;
    solapado.second = (x.second > (*fin).second)?x.second:(*fin).second;
    
    // Borramos los intervalos innecesarios y añadimos el solapado.
    ++fin;
    lista.erase(inicio, fin);
    lista.push_back(solapado);
    
    lista.sort(EsMenor());
    
}

/**
* @brief Extrae un subintervalo x de una lista L1
* y lo pasa a otra lista L2.
* y lo pasa a otra lista L2.
*
* @param x subintervalo de L1
* @param L1 lista de donde se extrae x
* @param L2 lista donde se introduce x
*
* @pre x pertenece a un único subintervalo de L1.
*
* @post Ningún intervalo de L1 contendrá los valores inicial
* y final de x y x se introduce en L2, solapándose con los
* intervalos de L2 que sea necesario para formar un único intervalo.
*
* @return true si ha sido posible realizar la extracción
* y false en caso contrario.
*/
bool Extraer(ListaIntervalos& L1, Intervalo x, ListaIntervalos& L2) {
    
    bool hay_extraccion = EliminaSubintervalo(L1, x);
    if(hay_extraccion) AniadeIntervalo(x, L2);
    
    return hay_extraccion;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

int main() 
{
    // Datos
    
    const int TAM1 = 4; const int TAM2 = 3; const int TAM3 = 3;
    
    Intervalo x1(12,14), x2(12,20);
    
    Intervalo intervalos_L1[TAM1] = {Intervalo(1,7),Intervalo(10,14),
                                     Intervalo(18,20),Intervalo(25,26)};
    
    Intervalo intervalos_L2[TAM2] = {Intervalo(0,1),Intervalo(14,16),Intervalo(20,23)};
    Intervalo intervalos_L3[TAM3] = {Intervalo(1,7),Intervalo(10,22),Intervalo(25,26)};
    
    // Rellenamos los intervalos correspondientes.
            
    ListaIntervalos lista1, lista2, lista3;
    
    for(int i = 0; i < TAM1; ++i) lista1.push_back(intervalos_L1[i]);
    for(int i = 0; i < TAM2; ++i) lista2.push_back(intervalos_L2[i]);
    
    ListaIntervalos lista4 = lista2;
    
    for(int i = 0; i < TAM3; ++i) lista3.push_back(intervalos_L3[i]);
    
    cout << "Listas antes: " << endl << endl;
    
    cout << "L1 = ";
    ImprimeListaIntervalos(lista1);
    cout << endl;
    
    cout << "L2 = ";
    ImprimeListaIntervalos(lista2);
    cout << endl;
    
    cout << "L3 = ";
    ImprimeListaIntervalos(lista3);
    cout << endl;
    
    cout << "L4 = ";
    ImprimeListaIntervalos(lista4);
    cout << endl;
    
    cout << endl;
    
    cout << "X1 = ";
    ImprimeIntervalo(x1);
    cout << endl;
    
    cout << "X2 = ";
    ImprimeIntervalo(x2);
    cout << endl;
    
    // Extraemos los subintervalos.
    
    Extraer(lista1, x1, lista2);
    Extraer(lista3, x2, lista4);
    
    // Mostramos los resultados.
    
    cout << endl << "Listas despues: " << endl << endl;
    
    cout << "L1 = ";
    ImprimeListaIntervalos(lista1);
    cout << endl;
    
    cout << "L2 = ";
    ImprimeListaIntervalos(lista2);
    cout << endl;
    
    cout << "L3 = ";
    ImprimeListaIntervalos(lista3);
    cout << endl;
    
    cout << "L4 = ";
    ImprimeListaIntervalos(lista4);
    cout << endl;
    
    return 0;
}
