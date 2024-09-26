# Tema 1.Introducción a la computación

Como motivación, notamos que, en ocasiones, hay problemas que no pueden ser resueltos con un programa, es decir, no son computables, Un ejemplo de estos es el problema de la parada que se cita como sigue: 

_Problema:_

Supongamos que disponemos de un programa en un lenguaje cualquiera y nos incumbe saaber si dicho programa termina. Para ello, creamos un programa que, dado un programa y una entrada de datos nos dice en un tiempo finito si ese programa termina. Por ejemplo, llamémoslo "_Stops(P,x)_" donde _P_ es el programa y _x_ son los datos, podría ser de la siguiente forma que llamaremos "_Turing(P)_":

```
    1  `if Stops(P,P) goto 1;
```    
Tomando un programa de ejemplo, si llamamos a _Turing_ consigo mismo pues no deja de ser una cadena de ceros y unos, lo cual es un conjunto de datos ocasionamos una contradicción pues:

    · Si _Stops(Turing,Turing)_ acabara, el programa origen no acabaría ocasionando la contradicción.
    · En caso contrario, el programa acabaría ocasionando de nuevo contradicción.
En conclusión, este programa no puede existir.

## 1.1.Algunas definiciones

__Alfabeto__

Un alfabeto es un conjunto finito _A_ que contiene una serie de símbolos o letras. 

__Palabra__ 

Una palabra generada por un alfabeto no es más que una secuencia finita de combinaciones de símbolos del alfabeto. Al conjunto formado por todas las palabras, incluyendo la palabra vacía {$\epsilon$}, se le denota por _A*_, en caso de no querer la palabra vacía, escribiremos _A⁺_.

Se pueden hacer algunas operaciones intuitivas con las palabras como el cálculo de la longitud denotada por |·|: A --> $\N$ que simplemente cuenta el número de letras que tiene cada palabra. Otra operación puede ser la concatenación de palabras denotada por el producto matemático, la inversión de palabras denotada por $^{-1}$.
