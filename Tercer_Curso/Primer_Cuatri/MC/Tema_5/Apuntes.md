# 5.Autómatas con Pila
---
## Índice
1. [Autómatas con pila no deterministas](#APND).
---
<a id="APND"></a>
## 5.1.Autómatas con Pila

Un __autñomata con pila no determinista__ (_APND_) es una septupla $(Q,A,B,\delta,q_0,Z_0,F)$ en la que:

- $Q$ es un conjunto finito de estados.
- $A$ es un alfabeto de entrada.
- $B$ es un alfabeto para la pila, consta de los símbolos que podremos almacenar en la pila.
- $\delta$ es la función de transición dada por:
    
$\delta : Q \times (A \cap$ \{ $\epsilon$ \}$) \times B \longrightarrow \wp (Q\times B^\*)$

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
