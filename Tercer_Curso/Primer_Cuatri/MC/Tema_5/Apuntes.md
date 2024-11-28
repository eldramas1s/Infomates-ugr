# 5.Autómatas con Pila
---
## Índice
1. [Autómatas con pila no deterministas](#APND).
2. [Autómatas con pila deterministas](#APD).
3. [Lenguajes independientes del contexto deterministas](#LICD)
4. [Equivalencia entre autómatas y gramáticas](#EAG)
---
<a id="APND"></a>
## 5.1.Autómatas con Pila

Un __autómata con pila no determinista__ (_APND_) es una septupla $(Q,A,B,\delta,q_0,Z_0,F)$ en la que:

- $Q$ es un conjunto finito de estados.
- $A$ es un alfabeto de entrada.
- $B$ es un alfabeto para la pila, consta de los símbolos que podremos almacenar en la pila.
- $\delta$ es la función de transición dada por: $\delta : Q \times (A \cap$ \{ $\epsilon$ \} $) \times B \longrightarrow \wp (Q\times B^\*)$

- $q_0$ es el estado inicial.
- $Z_0$ es el símbolo inicial de la pila, pese a que no es necesario, nosotros supondremos que siempre está ese símbolo en el fondo de la pila.
- $F$ es el conjunto de estados finales.

___Anotación___

Con respecto a la función de transición cada movimiento depende de:

- Estado en el que se encuentre el autómata.
- Símbolo que se lea en ese instante.
- Símbolo del tope de la pila.

La imagen de la función de transición para un triple $(p,u,z)$ es un subconto de $(Q\times B^\*)$ que consiste en:

1. Leer el símbolo de entrada.
2. Sustituir el tope de la pila por los elementos de $B^\*$ imponiendo que se obtenga antes de la pila la parte izquierda de $B^\*$.

En cada paso sólo se aplicará un movimiento de todos los posibles; si nos fijamos, para hacer un `pop`  solo tendremos que tomar $\epsilon$ como símbolo de entrada en el lengaje.

<a id="formas"></a>
### 5.1.1. Forma de acabar la lectura de una palabra

Pare determina si se ha leído toda la palabra de un lenguaje deberemos saber si el lenguaje es:

- Aceptado por __pila__, es decir, cuando la pila se queda vacía la palabra que hayamos leído es la que está aceptada por el lenguaje.
- Aceptado por __estados finales__, es igual a lo que ya conocemos usando la pila como simple memoria.

De esta forma, un mismo _APND_ puede aceptar dos lenguajes distintos dependiendo del criterio de aceptación de palabras.

### 5.1.2.Algunas definiciones

___Descripción instantánea___

Sigue la misma definición ya vista en los _AFND_ y conciste en una tripleta:

$$(q,u,\alpha) \in Q \times A^\* \times B^\*$$ 

donde $q$ es el estado en el que se encuentra el autómata, $u$ es la parte de la cadena de entrada que queda por leer y $\alpha$ es el contenido del tope de la pila.

___Paso de cálculo___

Se dice que, de la configuración $(q,au,Z\alpha)$ se puede llegar mediante un __paso de cálculo__ a la configuración $(p,u,\beta \alpha)$ y se escribe $(q,au,Z\alpha) \vdash (p,u,\beta \alpha)$ si y solo si $(p,\beta) \in \delta(q,a,Z)$ donde $a$ puede ser cualquier símbolo de entrada o la cadena vacía.

___Sucesión de pasos de cálculo___

Si $C_1,C_2$ son dos configuraciones, se dice que se puede llegar de $C_1$ a $C_2$ mediante una __sucesión de pasos de cálculo___ y se escribe $C_1 \Vdash C_2$ si y solo si $\exists$ \{ $T_n$ \} $| C_1=T_1 \vdash T_2\vdash ... \vdash T_{n-1} \vdash T_n = C_2$.

___Configuración inicial___

Sean $M$ es un _APND_ y $u \in A$ se llema __configuración inicial__ correspondiente a esta entrada a  $(q_0,u,Z_0)$ donde $q_0$ es el estado inicial y $Z_0$ es el símbolo inicial de la pila.

### 5.1.3.Lenguaje Aceptado

Haciendo uso de cómo podemos [aceptar una palabra](#formas) determinamos los dos __lenguajes aceptados__ por el autómata con pila:

- Por __estados finales__: $L(M)=$\{ $w \in A^\* : (q_0,w,Z_0) \Vdash (p,\epsilon,\gamma),p\in F,\gamma\in B^\*$ \}.
- Por __pila vacía__: $N(M)=$\{ $w \in A^\* : (q_0,w,Z_0) \Vdash (p,\epsilon,\epsilon), p\in Q$ \}.

Queda ya claro que, un mismo autómata no determinista con pila podrá aceptar __dos__ lenguajes distinto según cada uno de los criterios y que, por lo general, esos lenguajes serán distintos. No obstante, aceptan la misma clase de lenguajes dando lugar al siguiente resultado.

___Teorema___

1. Si $L$ es el lenguaje aceptado por un autómata con pila $M=(Q,A,B,\delta,q_0,Z_0,F)$ por el _criterio de pila vacía_ entonces __existe__ un autómata con pila $M_f$ que acepta el mismo lenguaje $L$ por el _criterio de estados finales_.

2. Si $L$ es el lenguaje aceptado por un autómata con pila $M=(Q,A,B,\delta,q_0,Z_0,F)$ por el _criterio de estados finales_ entonces __existe__ un autómata con pila $M_n$ que acepta el mismo lenguaje $L$ por el _criterio de pila vacía_. 

_Demostración_

\[ $1.$ \]:

La _idea intuitiva_ será introducir un nuevo estado inicial y una nueva variable fondo en la fila para poder reiniciar la creación de la palabra cuando la pila se quede vacía de manera que dada una palabra, podrán generarse palabras que la incluyan.

Pasando a la _construcción_ del autómata $M_f$, se construirá a partir de $M$ siguiendo los siguientes pasos:

- Se añaden dos estados nuevos $q_0^n$ y $q_f$ de manera que el estado inicial será $q_0^n$ y el estado final será $q_f$.
- Se añade un nuevo símbolo a $B$ que será el nuevo símbolo inicial de la pila, será $Z_0^n$.
- Añadimos a las transiciones de $M$ las siguientes:
    + $\delta(q_0^n, \epsilon, Z_0^n)=$ \{ $(q_0,Z_0Z_0^n)$ \}
    + $\delta(q,\epsilon,Z_0^n)=$ \{ $(q_f,Z_0^n)$ \} $ \forall q \in Q

\[ $2.$ \]:

La _idea intuitiva_ será añadir un nuevo estado que representara el estado donde vaciaremos la pila en caso de que ya se haya leído la palabra al completo por el criterio de _estados finales_.

Pasando a la _construcción_ del autómata $M_n$, se construirá a partir de $M$ siguiendo los siguientes pasos:

- Se añaden dos estados, $q_0^n$ y $q_s$ donde el estado inicial será $q_0^n$ y el estado de vacío será $q_s$.
- Se añade un símbolo a $B$ que será el nuevo símbolo inicial de la pila, será $Z_0^n$.
- Se añaden las siguientes transiciones a las que ya tenía $M$:
    + $\delta(q_0^n, \epsilon, Z_0^n)=$ \{ $(q_0,Z_0Z_0^n)$ \}
    + \delta(q,\epsilon,H)=$ \{ $(q_s,H)$ \} $\forall q\in F, H \in B \cup$ \{ $Z_0^n$ \}
    + \delta(q_s,\epsilon,H)=$ \{ $(q_s,\epsilon)$ \} $\forall H \in B \cup$ \{ $Z_0^n$ \}

_Fin demostración_

<a id='APD'></a>
## 5.2.Autómatas con Pila Deterministas(_APD_)

Un autómata con pila $M=(Q,A,B,\delta,q_0,Z_0,F)$ se dice que es __determinista__ si y solo si se cumplen las siguientes condiciones:
1. $\delta(q,a,X)$ tiene a lo más un elemento, para todo $q\in Q, a\in A \cup$ \{ $\epsilon$ \}, $X\in B$.
2. Si $\delta(q,a,X)$  es no vacío para algún $a \in A$ entonces $\delta(q,\epsilon,X)=\emptyset$.

Una condición equivalente es que para cada configuración $C_1$, __existe__, a lo sumo una configuración $C_2$ tal que $C_1 \vdash C_2$.

Lo habitual es entender la segunda condición leyendo el contrarrecíproco, es decir, si existe una transisción de con ese estado $q$ y el símbolo $X$ que lea la palabra vacía  sin resultado vacío no puede haber otra leyendo una palabra no vacía.


<a id='LICD'></a>
## 5.3.Lenguajes Independientes del Contexto Deterministas

Un lenguaje independiente del contexto se dice que es __determinista__ si y solo si es aceptado por un autómata con pila determinista por el _criterio de estados finales_.

No obstante, el criterio podría ser otro, pero la cantidad de lenguajes aceptados por el criterio de _estados finales_ es mayor que la cantidad de lenguajes aceptados por el criterio de _pila vacía_.

Vimos anteriormente que se daba la equivalencia pero he de recalcar que eso era cierto en __autómatas con pila no deterministas__; en el caso de los deterministas, esto no es cierto pues cuando la pila se queda vacía no podremos seguir leyendo si aceptamos pro pila vacía. 

Todo esto es una restricción que viene de la definición de [autómata con pila](#APND) pues para nosotros debía contener un símbolo en el fondo.

De hecho, hay una implicación que sí se da: Si $L$ es un lenguaje aceptado por un autómata con pila __determinista__ por el _criterio de pila vacía_, entonces $L$ es aceptado por un autómata con el _criterio de estados finales_.

___Anotación___

Los autómatas con pila __no deterministas__ __no__ son equivalentes a los autómatas con pila __deterministas__.

Se corroboró en clase que __existen__ lenguajes que son aceptados por un tipo y no por otro.


___Definición___

Diremos que un lenguaje $L$ tiene la __propiedad prefijo__ si y solo si para cada palabra de $x\in L$ nungún prefijo de $x$ distinto de él está en $L$.

De esta propiedad surge un resultado bastante interesante.

___Teorema___

Un lenguaje puede ser aceptado por un autómata con pila determinista por el _criterio de pila vacía_ si y solo si es aceptado por un autómata con pila determinista por el _criterio de estados finales_ y tiene la _propiedad prefijo_.

En resumen, la distinción entre los dos criterios aplicados a lenguajes deterministas no es sustancial pues; si un lenguaje $L$ es determinista y __no__ cumple la _propiedad prefijo_, una sencialla tranformación lo convertiría en un lenguaje que sí cumple la propiedad; y por tanto, sería acpetado por un autómata determinista por el _criterio de pila vacía_.

La transformación de la que se habla consiste en añadir un nuevo símbolo que no esté en el alfabeto para añadirlo al final de todas las palabras. De esta manera, si $\ghi \notin A$ entonces consideramos $L$ \{ $u\ghi : u \in L$ \}.

<a id='EAG'></a>
## 5.4.Equivalencia entre Autómatas y Gramáticas

___Teorema___
 
Dada una gramática libre de contexto $G=(V,T,P,S)$ __existe__ un autómata con pila $M=(Q,A,B,\delta,q_0,Z_0,F)$ que acepta el mimso lenguaje que genera $G$, y recíprocamente, dado un autómata $M$ __existe__ una graática libre de contexto $G$ que genere el lenguaje que acepta $M$.

Cabe recalcar que el autómata no tiene por qué ser determinista.

_Demostración_

\[ $\Longrightarrow$ \]:

El autómata vendrá dado por:
- $Q=$ \{ $q$ \}
- $A=T$
- $B=V \cap T$
- $q_0 = q$
- $Z_0=S$
- $F=\emptyset$
- \delta viene determinada por las siguientes relaciones:
    + $\delta(q,\epsilon,B)=$ \{ $(q,\alpha):B\rightarrow \alpha \in P$ \}
    + \delta(q,a,a)=$ \{ $(q,\epsilon)$ \}

Este autómata acepta el mismo lenguajes por el _criterio de pila vacía_.

\[ $\Longleftarrow$ \]:

Sea $M=(Q,A,B,\delta,q_0,Z_0,\emptyset)$ un autómata con pila que acepta $L$ por el _criterio de pila vacía_, la idea básica será construir la grmática a partir de la variable $S$ y todas las variables de la forma \[ $q,X,p$ \] donde $p,q\inQ, X\inB$.

Donde la variable \[ $q,X,p$ \] debe generar aquellas palabras que son capaces de poder leerse de forma completa llevando el autómata con pila desde el estad $q$ al estado $p$, quitando la $X$ de la pila.

Después de eso, se deben añadir todas las producciones de la forma:

$$S \rightarrow \[q_0,Z_0,p\], p\in Q$$

### Resumen

La gramática que se genera se construye de la siguiente forma:
- __Variables__: $\[q,C,p\], p,q \in Q, C\in B$ además de la variable $S$ que será la inicial.
- __Producciones__:
    + $S \rightarrow \[q_0,Z_0,p\], \forall p\in Q$
    + $\[q,C,q_m] \rightarrow a\[p,D_q,q_1\]\[q_1,D_2,q_2\]...\[q_{m-1},D_m,q_m\] \forall q_1,...,q_m \in Q$, si $(p,D1D2...Dm)\in \delta(q,a,C) | a=\epsilon \lor a\neq \epsilon$. Si $m=0$, entonces la producción es $\[q,A,p\] \rightarrow a$.

### Conclusión

Con este procedimiento, haciendo las conversiones correspondientes, para cualquier autómata con pila podremos encontrar otro con un sólo estado, es decir, será minimal con respecto al numero de estados.

## Observación

Ahora que ya hemos dado todo el tema, cabe recalcar que las gramáticas en forma normal de gribach y los autómatas con pila deterministas tienen mucho en común.

[TODO]:preguntar al profesor.

