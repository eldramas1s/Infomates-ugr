/**
   @file C�lculo de la sucesi�n de Fibonacci
*/

   
#include <iostream>
using namespace std;
#include <ctime>


/**
   @brief Calcula el t�rmino n-�simo de la sucesi�n de Fibonacci.

   @param n: n�mero de orden del t�rmino buscado. n >= 1.

   @return: t�rmino n-�simo de la sucesi�n de Fibonacci.
*/
int fibo(int n)
{
  if (n < 2)
    return 1;
  else
    return fibo(n-1) + fibo(n-2);
}


int main()
{

  int n;
  int f;
 
  cout << "�N�mero del t�rmino: ";
  cin >> n;

  f = fibo(n);

  cout << "El t�rmino " << n << "-�simo es: " << f << endl;

  return 0;
}
