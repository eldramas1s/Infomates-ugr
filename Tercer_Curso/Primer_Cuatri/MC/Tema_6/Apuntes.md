# 6.Propiedades de los lenguajes independientes del contexto

---
## Índice
1. [Lema de Bombeo](#LDB)
2. [Operaciones con lenguajes Independientes del Contexto](#ops)
    1. Complementario de un lenguaje independiente del contexto.
    2. Intersección de un lenguaje independiente del contexto y un lenguaje regular.
---

<a id='LDB'> </a>

## 6.1.Lema de Bombeo

Al igual que para lenguajes regulares disponíamos de una condición necesaria para que un lenguaje fuera regular, para lenguajes independientes del contexto disponemos de otro _Lema de Bombeo_.

___Enunciado___

Sea $L$ un lenguaje independiente del contexto, entonces existe una constante $n \in N$, que depende solo de $L$, tal que si $z \in L, |z| \geq n$, y $z$ se puede escribir de la forma $z=uvwxy$ verificando:
1. $|vx| \geq 1$
2. $|vwx| \leq n$
3. $\forall i \geq 0, uv^iwx^iy \in L$

Para la demostración del mismo necesitaremos la siguiente propiedad:
- Si en una gramática en forma normal de Chomsky existe una palabra que es derivada con un árbol de derivación en el que todos los caminos desde la raíz a una horja son de longitud menor o ingual a $2^{m-1}$, además en un camino de la raíz de la hoja de longitud $k$ aparecen $k$ variables.

_Demostración del lema de bombeo_

[TODO]:Hacer demostración

Al igual que el uso real del lema de Bombeo para lenguajes regulares consistía en probar que no era regular porque no cumplía la condición necesaria, en este caso la aplicación es la misma; es decir, mediante el incumplimiento de la condición necesaria, el lenguaje que no la cumple no será independiente del contexto. 

<a id='ops'> </a>

## 6.2.Operaciones con Lenguajes Independientes del Contexto

Los lenguajes independientes del contexto son cerrados para las siguientes operaciones:
- Unión: la demostración consiste en hacer la gramática que puede bifurcarse en el símbolo inicial para general la palabra de un lenguaje o de otro.

$$S \rightarrow S_1, S \rightarrow S_2$$

- Concatenación: la idea es similar a la anterior solo que permitiendo generar las dos palabras una seguida de la otra:

$$S \rightarrow S-1S_2$$

- Clausura: no deja de ser una concatenación de un lenguaje consigo mismo infinitas veces, luego se consigue así:

$$S \rightarrow S_1S$$

No obstante, hay otras operaciones para los que los lenguajes independientes del contexto no son cerrados, como por ejemplo:

- Intersección, esta clase de operaciones no es cerrada pues la intersección de independeintes del contexto puede no ser independiente del contexto, basta tomar los lenguajes $L=$ \{ $a^ib^ic^j \mid i,j \geq 1$ \} y $L'=$ \{ $a^ib^jc^j \mid i,j \geq 1$ \}.

- Complementario, es claro que no lo es pues si lo fuera podríamos deducir que la intesección lo es lo cual es una contradicción.

### 6.2.1. Complementario de un Lenguaje Independiente del Contexto Determinista

Cuando el lenguaje origen $L$ es independiente del contexto __determinista__ la cosa cambia.

En este caso, su complementario sí que será independiente del contexto determinista.

_Demostración_

La demostración no es simple debido a la existencia de transiciones nulas (por definición de lenguaje independiente del contexto determinista). La idea principal consiste en considerar un _APD_ que acepte $L$ por estados finales completo(esto quiere decir que se permita la lectura de palabras completas).

El problema fundamental es que después de leer la palabra de entrada completa, el autómata ¿inicial? tiene que pasar por todas las transicione snulas posibles y si nunca ha pasado por un estaod final, entonces acepta.

Para ello, hace tres copias de cada estado $q$: $(q,0),(q,1)(q,2)$ con el siguiente significado:
- $(q_0)$: significa que el autómata está en $q$, no ha pasado por ningún estado final desde el útlimo símbolo leído y con el contenido actual de la pula, pueden quedar transiciones nulas por hacer.
- $(q,1)$: está en $q$ y sí ha pasado por algún estado final desde el último estado leido.
-$(q,2)$: está en $q$, no ha pasado por ningún estado final desde el último símbolo leído y con el contenido actual de la pila, no quedan transiciones nulas por hacer.

Los finales serán los de este último tipo que no sean finales en el autómata inicial. El estado inicial es $(q_0,0)$ si $q_0 \notin F$ y $(q_0,1)$ si $q_0 \in F$.

Las transiciones vendrán dadas de la siguiente forma
- Si $(p,\alpha) \in \delta(q,\epsilon,X)$ entonces añadimos al autómata nuevo $((q,i),\alpha) \in \delta'((q,j),\epsilon,X) donde $j=0,1$ e $i=1$ si $j=1$ ó $p \in F$ e $i=0$ en caso contrario.
- Si $(p,\alpha) \in \delta(q,a,X)$ donde $a\in A$, entonces añadimos al autómata nuevo $((q,2),X \in \delta¿'?((q,0),\epsilon,X) para indicar que si la palabra termna aquí aceptamos(no hemos pasado por un estado final desde el último símbolo léido).
También se añade $((p,i),\alpha) \in \delta'((q,j),a,X) donde $j=1,2$ e $i=0$ si $p \notin F$ e $i=1$ en caso contrario, para poder seguir leyendo símbolos si la palabra no ha terminado.

El autómata así construido acepta el lenguaje complementario y es determinista.

_Fin demostración_

___Anotación___

Este resultado no implica que la intersección de lenguajes independientes del contexto deterministas sea determinista, ya que la unión de deterministas no tiene por qué ser determinista.

### 6.2.2.Intersección de un lenguaje independiente del contexto y un regular

___Resultado___

Si $L$ es un lenguaje independiente del contexto y $R$ es un lenguaje regular, entoences $L \cap R$ es independiente del contexto.

_Demostración_

La idea intuitiva se basa en que se puede controlar todo con un autómata con pila.

Supongamos un autómata con pila $M=(Q,A,B,\delta,q_0,Z_0,F)$ que acepta $L$ por el criterio de estados finales y un autómata finito determinista $M'=(Q',A,\delta',q_0',F')$. 

Construimos el sisguiente autómata ocn pila $M''=(Q'',A,B,\delta'',q_0'',Z_0,F'')$:

- $Q''=Q \times Q'$
- $q_0''=(q_0,q_0')$
- $F''=F \times F'$
- $\delta''((p,q),a,X)=$ \{ $((r,s),\alpha) \mid (r,\alpha) \in \delta(p,a,X), s=\delta'(q,a)$ \} donde $a\in A$.
- $\delta''((p,q),\epsilon,X)=$ \{ $((r,q),\alpha) \mid (r,\alpha) \in \delta(p,\epsilon,X)$ \}.

Este autómata acepta $L\cap R$ y por tanto es independiente del contexto.

_Fin demostración_


