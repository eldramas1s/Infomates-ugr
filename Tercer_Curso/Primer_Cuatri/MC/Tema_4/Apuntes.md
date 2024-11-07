# 4.Gramáticas Independientes del Contexto

## 4.1.Árboles y derivaciones

Definimos el __árbol de derivación__ como un árbol dirigido donde, dada una palabra $u \in A^\*$ donde $A^\*$ es la clausura de un alfabeto, se construye la palabra aplicando las reglas de derivación siguiendo los siguientes pasos:
    
    1. Comenzamos con el símbolo inicial siendo el nodo raíz del árbol.
    2. Cada vez que apliquemos una regla de derivación:
        
        - Creamos un nodo hijo por cada variable que aparezca en la regla.
        - Si quedan símbolos de variable volvemos a 2.
    
    3. Hemos conseguido la palabra buscada.

En el caso de que exista una regla de producción de la forma $A \rightarrow \epsilon$ tal que $A \in V$ sólo se crea un hijo con el valor $\epsilon$.

Como resultado deberemos obtener (3.) leyendo de izquierda a derecha los valores de las hojas del árbol que necesariamente deberán ser __símbolos terminales__.

Este concepto es muy importante en la compilación de programas, ya que para conocer si una palabra está correctamente escrita se genera su _árbol de derivación_.

![Árbol de derivacion](./imagenes/arbolder.png)

Algunas __propiedades__ de los _árboles de derivación_ son:
    
    · Dos procesos de derivación distintos pueden originar el mismo árbol de derivación.
    · Cuando al realizar el proceso de derivación aplicamos primero las reglas a la variable que aparece más a la izquierda, derivamos por la izquierda.

    · Cuando al realizar el proceso de derivación aplicamos primero las reglas sobre la variable que aparece más a la derecha, derivamos por la derecha.

Relacionado con los tipos de derivación, hay casos donde podemos realizar la misma cantidad de sustituciones, incluso de los mismos contenidos, y conseguir la misma palabra. Con esto me refiero, con ordenes distintos de derivación podemos conseguir la misma palabra con el mismo número de sustituciones.

![Invarianza respecto al orden](./imagenes/invarianza.png)

## 4.2.Gramáticas ambiguas y lenguajes inherentemente ambiguos

### 4.2.1.Gramáticas ambiguas

Diremos que una gramática es __ambigua__ cuando una misma palabra aceptada por el lenguaje generado por la gramática dispone de más de un _árbol de dervición_.

![Gramática ambigua](./imagenes/grambigua.png)

___Problema___

_Es claro que encontrar que la gramática sí es ambigua es algo computable, es decir, se puede hacer mediante algoritmos, pero... ¿qué ocurre si buscamos demostrar que la gramática no es ambigua?_

La  única solución vista hasta ahora sería probar con todas las palabras que acepta el lenguaje generado por dicha gramática que, normalmente, serán infinitas.

Este problema introduce el concepto de problema __semidecidible__, esto es cuando la respuesta positiva a la pregunta se resuelve mediante un algoritmo; pero, cuando la respuesta es negativa, el programa puede estar destinado a ciclar de forma indefinida.

<a id="corrección"></a>
En ocasiones, podremos eliminar una serie de reglas de producción que producen la ambigüedad. Estas reglas de producción no sabemos, por ahora, cómo encontrarlas pero, eliminandolas conseguiremos una gramática que no será ambigua.

![Corrección de ambigüedad](./imagenes/correcion_gram.png)
### 4.2.2.Lenguajes inherentemente ambiguos

Del concepto de _gramática ambigua_ pasamos al de __lenguaje inherentemente ambiguo__. Diremos que un lenguaje de __tipo 2__ es __inherentemente ambiguo__ si toda la gramática que lo genera es _ambigua_.

![Lenguaje no inherentemente ambiguo](./imagenes/lambiguont.png)

___Problema___

_Al igual que con gramáticas ambiguas... ¿cuándo podemos determinar que un lenguaje sea o no inherentemente ambiguo?_

En este caso, el problema ni siguiera es _semidecidible_, es completamente __indecidible__; es decir, no podemos determinar mediante algoritmos ninguna de las dos respuestas.La demostración de ello se basa en la reducción al absurdo usando que si existiera obtendríamos un problema que resolvería el _problema de la parada_.

Una propiedad que debe quedar clara es que __ningún lenguaje regular__ es __inherentemente ambiguo__, pues equivale a que sea generado por un _AFD_, o visto de otra manera, por una gramática _regular_ que sabemos que no puede ser _ambigua_.

No obstante, ya vimos una forma de la cual se peude conocer que un lenguaje __no__ es ambiguo usando la [corrección de ambigüedad](#corrección); pues, si al aplicarla conseguimos una gramática __no__ ambigua sabemos ya que el lenguaje dado no sería inherentemente ambiguo.

![Lenguaje inherenetemente ambiguo](./imagenes/lambiguo.png)

Con el ejemplo podemos deducir que los problemas se localizan en la __intersección__ de ambo lenguajes, es decir, las palabras que pertenecen a ambos. 

No obstante, darse cuenta de que hay una gramática ambigua que genera el lenguaje no demuestra nada salvo lo que ya se ha dicho, pues esto no implica que todas las gramáticas son ambiguas luego no nos dice que el lenguaje es inherentemente ambiguo.
