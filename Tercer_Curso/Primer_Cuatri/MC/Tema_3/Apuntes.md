# 3.Propiedades de los Conjuntos Regulares

Diremos que un conjunto es __regular__ cuando todos sus elemenots se pueden formar mediante las operaciones de __unión__,__concatenación__ y __cierre__; además, cada uno de estos conjuntos tendrá asociada una __expresión regular__.

Como añadido, el __conjunto vacío__ se considera conjunto regular.

## 3.1.Lema de Bombeo

Sea $L$ un conjunto regular, entonces _existe_ un $n \in N$ tal que $\forall z \in L$, si $|z| \geq n$, entonces $z$ se puede expresar de la forma $z = uvw$ donde:

i) $|uv|\leq n$

ii) $|v| \geq 1$

iii) $uv^iw \in L \forall i \geq 0$

además $n$ puede ser el número de estados de cualquier autómata que acepte el lenguaje.

_Demostración_

Sea $M=(Q,A,\delta,q_0,F)$ un _AFD_ que acepta el lenguaje $L$ y $n$ su número de estados. SUpongamos qeue $z\in L|z=a_1a_2...a_m$ con $m \geq n$. 

Sabemos que $M$ acepta el lenguaje $L$ luego al leer $z$ en $M$ debemos llegar a un estado final. 

Tomando ahora $z'=a_1a_2...a_n$, la palabra formada por los $n$ primeros símbolos de $z$, y considerando el vecotr de estados $(q_{i0},q_{i1},...,q_{in})$ donde $q_{ij}$ es el estado al que llegamos al leer el estado $q_{ij-1}$ con el símbolo $a_j$.

Nosotros sabemos que el autómata dispone de $n$ estados distintos y el vector dispone de $n+1$ estados; luego, alguno de ellos se debe repetir. Vamos a suponer que se repiten $q_{ik}=q_{il}$.

Entonces, la descomposición de $z$ se haría en las siguientes componentes:

$$u=a_1a_2...a_k, v=a_{k+1}...a_l, w=a_{l+1}...a_m$$

Donde claramente, al pasar por $v$ estamos repitiendo $l-k+1$ veces el mismo estado obteniendo un _ciclo_; como $M$ acepta $L$ tenemos que al acabar de leer $z$ también deberá acabar de leer la palabra $uv^iw$; y por tanto, $uv^iw$ \in L$.

_Fin demostración_

De forma intuitiva, buscaremos encontrar una palabra que tenga una longitud mayor que el número de estados que el autómata que acepta el lenguaje para tratr de desmostrar que el lenguaje __no__ es regular.

De hecho, este lema nos proporciona una condición __necesaria__ pero __no suficiente__ que debe cumplir un lenguaje para ser regular. En ocasiones, el lenguaje podrá no ser regular y cumplir la condición para el lema de Bombeo para algún $n$.

Cuando busquemos probar que un lenguaje $L$ es regular deberemos proporcionar la gramática regular que genera el lenguaje, el autómata o la expresión regular asociada el lenguaje pero __nunca__ lo probaremos haciendo uso del lema de Bombeo.

Es fácil ver que, si el lenguaje es finito, la condición del lema es trivialmente cierta pues vbasta tomar $n=max{|u| | u\in L}$ luego no existen palabras de longitud mayor que $n$ consiguiendo que sea trivialmente cierta.

### 3.1.1.Un lenguaje no es regular

La idea que perseguimos para demostrar que un lenguaje no es regular, es tratar de encontrar una palabra del lenguaje que, tras repetir un número de veces una subcadena que se encuentra en los $n$ primeros símbolos, la palabra deja de pertenecer al lenguaje.

Formalemente, lo que buscatemos probar es lo siguiente: $\forall n \in N$, existe una palabra $z \in L | |z|\geq n$ cumpliendo que para toda composición $z=uvw$; si se verifican i) y ii) entonces

$$\exists i\in N | uv^iw \notin L$$

Debe quedar muy claro que el __Lema de Bombeo__ es una condición necesaria pero no suficiente; para ello, tomamos como contraejemplo $L=\{a^lb^jc^k : (l=0)\lor (j=k)\}$ que verifica la condición del lema para $n=2$ tomando $l=0$ ó $j=k$ ($u=\epsilon$,$v=$primer símbolo de z y $w=$ resto palabra).

### 3.2.Operaciones de los conjuntos regulares

Las operaciones con conjuntos de las que hablaremos son cerradas para el conjunto de los conjuntos regulares, es decir, el lenguaje resultante de la operación es también un lenguaje tegular; estas operaciones son la __unión__, la __concatenación__, la __clausura de Kleene__, la __diferencia simétrica__(y por consecuencia la __intersección__), el __lenguaje inverso__ y el __cociente__ entre otras. 

Para probar que son cerradas puede hacerse mediante dos algoritmos; el primero de ellos consiste en trabajar con _AFD_ y realizar las operaciones que se vieron en el tema anterior ya que se mantendrá el autçomata finito determinista. El segundo algoritmo consistirá en trabajar con las _expresiones regulares_ de cada lenguaje y aplicarle las operaciones extrapoladas a dichas expresiones.

Otra operación que se cumple es que la imagen por un __homomorfismo__ de un lenguaje regular es también regular pues, si entendemos que un homorfismo no es más que una codificación de nuestro lenguaje, al ser una aplicación cerrada para la concatenación obtenemos claramente que la expresión regular de la codificación es la expresión regular de origen con cada símbolo codificado concatenado con la codificación del siguiente. 

En definitiva, basta con codificar la expresión regular para obtener que la imagen por el homomorfismo es regular.

Esta última propiedad puede usarse para probar que un lenguaje es, o no, regular pues aplicando un homomorfismo podemos llevar nuestro lenguaje a otro lenguaje conocido que sea, o no, regular pues la inversa de un homomorfismo es un homomorfismo.

Para deducir como obtener el lenguaje imagen del homomorfismo inverso dejo por aquí un ejemplo, que simplemente consiste en copiar el autómata del lenguaje imagen, poniendo en cada transición  uno de los elementos que se consiguen al aplicar el autómata del lemguaje imagen a la codificación:

<div>
<p style='text-align:center'>
<img src="./imagenes/finverso.png" alt=Error>
</p>
</div>

___Cociente___

Hablemos un poco más del lenguaje cociente con un teorema:

_Teorema_

Si $R$ es un conjunto regular y $L$ es un lenguaje cualquiera, entonces el cociente de lenguajes $R/L=\{u\in A^\* : \exists v \in L \land uv \in R \}$ es un conjunto regular.

_Fin Teorema_

El autómata resultados del cociente es aquel con la misma estructura que $R$ con la ligera diferencia de que los estados finales son aquellos a partir de los cuales podemos leer una palabra de $L$ llegando a un estado final.

El problema real reside en definir cómo leer el lenguaje $L$ pues es un lenguaje cualquiera, de forma general sólo podemos trabajar con graáticas tipo 0 luego no podemos encentrar un algoritmo que haga este cometido tan fácil. 

De hecho, aunque se restrinja $L$ al conjunto de los lenguajes recursivamente enumerables no podemos decidirlo (implementarlo con un algoritmo).


## 3.3.Algoritmos

En este apartado vamos a conocer una serie de algoritmos que nos van a permitir identificar ciertas propiedades entre autómatas como __aceptar el mismo lenguaje__, __lenguaje vacío es el aceptado__, __el autómata minimal__...

Comencemos con el __lenguaje vacío es el aceptado__:

Para ello, deberemos eliminar los estados inaccesibles siguiendo un recorrido por el grafo a partir del estado final; entendemos por estados inaccesibles aquellos que, al leer una palabra, es imposible llegar a ellos; y comprobar finalmente si quedan estados finales. 

De forma parecida se puede determinar si el lenguaje aceptado es __finito__ o __infinito__; para ello, suponemos eliminados los estados inaccesibles y los estados de error o aquellos desde los que no se puede llegar a estados finales. Por último, si quedan ciclos en el grafo entonces el lenguaje es infinito.

Continuamos con __aceptar el mismo lenguaje__:

