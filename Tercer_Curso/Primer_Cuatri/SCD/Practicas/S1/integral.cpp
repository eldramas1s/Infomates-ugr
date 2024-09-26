#include <iostream>
#include <thread>
using namespace std;

double f(double x){
    return 4/(1+x*x);
}

//Hacer una función para cada hebra repartiendo de una manera distinta.