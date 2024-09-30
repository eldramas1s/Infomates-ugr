# Tema 1.Introducción a la computación

Como motivación, notamos que, en ocasiones, hay problemas que no pueden ser resueltos con un programa, es decir, no son computables, Un ejemplo de estos es el problema de la parada que se cita como sigue: 

_Problema:_

Supongamos que disponemos de un programa en un lenguaje cualquiera y nos incumbe saaber si dicho programa termina. Para ello, creamos un programa que, dado un programa y una entrada de datos nos dice en un tiempo finito si ese programa termina. Por ejemplo, llamémoslo "_Stops(P,x)_" donde _P_ es el programa y _x_ son los datos, podría ser de la siguiente forma que llamaremos "_Turing(P)_":

```
    1  if Stops(P,P) goto 1;
```    
Tomando un programa de ejemplo, si llamamos a _Turing_ consigo mismo pues no deja de ser una cadena de ceros y unos, lo cual es un conjunto de datos ocasionamos una contradicción pues:

    · Si _Stops(Turing,Turing)_ acabara, el programa origen no acabaría ocasionando la contradicción.
    · En caso contrario, el programa acabaría ocasionando de nuevo contradicción.
En conclusión, este programa no puede existir.

## 1.1.Algunas definiciones

__Alfabeto__

Un alfabeto es un conjunto finito _A_ que contiene una serie de símbolos o letras. 

__Palabra__ 

Una palabra generada por un alfabeto no es más que una secuencia finita de combinaciones de símbolos del alfabeto. Al conjunto formado por todas las palabras, incluyendo la palabra vacía ${\epsilon}$, se le denota por _A*_, en caso de no querer la palabra vacía, escribiremos _A⁺_.

Se pueden hacer algunas operaciones intuitivas con las palabras como el cálculo de la longitud denotada por $|·|: _A_ \rightarrow \math{N}$ que simplemente cuenta el número de letras que tiene cada palabra. Otra operación puede ser la concatenación de palabras denotada por el producto matemático(cumple la asociativa y posee a la palabra vacía como elemento neutro), la inversión de palabras denotada por $^{-1}$ y la iteración denotada por $^n$ con n un numero natural (consiste en escribir n veces lo denotado).

__Prefijos y sufijos__

Sea _u_ una palabra del alfabeto _A_, diremos que _v_ es un prefijo de _u_ si existe una palabra $w \in  _A*_ | vw=u$. Un prefijo sera propio si no es la palabra vacía ni la propia palabra.

Diremos que _v_ es un sufijo de _u_ si existe una palabra $W \in _A*_ | wv=u$. De la misma manera será propio o no.

__Lenguaje__

Un lenguaje sobre un alfabeto _A_ es un subconjuto de _A*_. Cabe recalcar que el conjunto que contiene a todos los lenguajes a crear por un alfabeto es infinito no numerable, mientras que _A*_ es infinito numerable pues es generado por un conjunto finito de símbolos y combinaciones.

Al igual que las palabras, los lenguajes soportan las misma operaciones donde la concatenación de lenguajes consiste en el lenguaje cuyas palabras se forman concatenando palabras de ambos lenguajes. Como curiosidad, si en ambos lenguajes se encuentra la palabra vacía, la unión de los lenguajes estará contenida en la concatenación. Esta operación cumple las siguientes características:

    · La concatenación de un lenguaje con el conjunto vacío no es más que el conjunto vacío.
    · Posee elemento neutro y es la palabra vacía.
    · Cumple la propiedad asociativa.

En el caso de la iteración, añadiendo a lo que ya se puede intuir, será el formado por las palabras que son concatenaciones finitas de palabras del lenguaje inicial.

Al igual que con el alfabeto, disponemos de las notaciones _L*_ y _L⁺_ que denotan lo mismo que ya sabemos.
Otro lenguaje resultante de una operación es el lenguaje inverso denotado por $L^{-1}$ y está formado por las palabras inversas del lenguaje original.
Un concepto importante es la cabecera de un lenguaje, es el conjunto de palabras del alfabeto de manera que existe una palabra del alfabeto que al concatenarla con la primera genera una palabra del lenguaje; la diferencia con el prefijo es que el prefijo no necesariamente tiene que pertenecer a _A*_ además de que este concepto es un conjunto.

Uno de los conceptos más importantes es el concepto de __homomorfismo__ que consiste en una aplicación entre dos conjuntos de palabras de un alfabeto de manera que se cumple:
                                        $h(uv) = h(u)h(v)$

Como consecuencias:
    i) $h(\epsilon) = \epsilon$

    ii) $h(a_1...a_n) = h(a_1)...h(a_n)$

Donde _h_ es una aplicacion que parte de _A*_ y llega a _B*_, $u,v,a_{i} \in _A*_$ 

## 1.2.Gramaticas Generativas

Una gramatica generativa es una cuadrupla $(V,T,P,S)$ en la que tenemos un alfabeto _V_ llamado alfabeto de variables, otro alfabeto _T_ llamado de símbolos terminales, una serie finita de reglas de producción _P_ y un símbolo inicial _S_ del cual derivarán todas las palabras.

Cuando disponemos de una gramatica generativa, esta generará un lenguaje formado por las palabras que podemos obtener mediante el proceso de derivación que consiste en comenzar por el símbolo terminal y aplicar las reglas de producción hasta obtener una combinación finita de símbolos terminales. De esta manera, diremos que una combinación de símbolos terminales y de variable es derivable a partir de otra cuando podemos partir de la primera y llegar a la segunda mediante un proceso finito de derivación (si lo conseguimos en un paso diremos que es derivable en un paso).

## 1.3.Jerarquía de Chomsky

Disponemos de cuatro tipos de gramáticas que generarán cuatro tipos de lenguajes que contendrán al posterior:

    · __Tipo 0__: Cualquier gramática, no tiene restricciones. Genera lenguajes recursivamente enumerables; de forma intuitiva, diremos que un lenguaje es de este tipo cuando para construir una palabra vamos contruyendo otras en el prodeso de derivación.
    · __Tipo 1__: Son aquellas gramáticas cuyas reglas de producción son de la forma:
                    $a_{1}_A_a_{2} \rightarrow a_{1}_B_a_{2}$

    donde la parte derecha es una combinación de palabras de símbolos de variable y terminales, A es un símbolo de variable y B no es la palabra vacía. A estos lenguajes se les llama lenguajes dependientes del contexto.
    · __Tipo 2__: Son aquellas gramáticas donde las reglas de producción sólo tienen una variable en la parte izquierda y cualquier combinación de variables y símbolos terminales a la derecha. generan lenguajes independientes del contexto.
    ·__Tipo 3__: Es muy parecida a la anterior diferenciándose sólo en que en la parte derecha de la regla de producción soólo pueden aparecer o una combinación de símbolos terminales o eso anterior junto a una única variable y en este orden. 
Dan lugar a lo que conocemos como conjuntos regulares. Estos lenguajes son reconocibles de forma sencialla pues son programas de memoria finita leyendo de izquierda a derecha, esto quiere decir que para reconocer una palabra no necesito disponer de demasiada memoria, es decir, no debo comprobar cosas que tengan que ver con número de (algo). 
Un ejemplo es el lenguaje formado por las palabras que contienen una sucesión finita de letras del mimso tipo de la _a_ a la _d_ en ese orden; en este caso, me da igual cuantas haya, simplemente deberé comprobar que se comple el orden, luego no necesito una barbaridad de memoria.
