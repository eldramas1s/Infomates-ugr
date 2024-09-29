# 2.Autómatas finitos y expresiones regulares

Como motivación a la hora de estudiar un autómata finito, vamos a ver parte de su importacia:

    · Es útil como software de diseño y verficación de circuitos digitales.
    · Tiene un papel importante en la construcción de analizadores léxicos de compiladores; como veremos pueden usarse en la comprobación léxica de palabras de un lnguaje.
    · Añadido a lo anterior, se usa como software de análisis de grandes conjuntos de textos con el fin de buscar palabras, estructuras...
    · En la corrección de sistemas con un número finito de estados diferentes juegan un papel importante.


## 2.1.Autómata finito determinista.

Si buscamos una intuición, no es más que un "aparato" que sigue una secuencia finita de estados buscando llegar a un estado de fin. Este no tiene memoria, es decir, cumple la propiedad de __pérdida de memoria__ luego será útil en la comprobación de que una palabra pertenezca o no a un lenguaje de tipo 3. 

*Definición*:
Un autómata finito es una cuádrupla $M=(Q,A,\delta,q_0,F)$ donde $Q$ es un conjunto finito llamado _conjunto de estados_, $A$ es un alfabeto llamado _alfabeto de entrada_, $\delta$ es una aplicación que parte del conjunto $(qxA)$ donde a cada dupla le asigna otro estado, $q_0$ es un estado conocido como _inicial_ y; por último, $F$ es un subconjunto de estados llamado _estados finales_.

De forma más intuitiva, cuando nosotros recibimos una palabra, para comprobar que pertenece al lenguaje, partimos de la palabra al completo y el estado inicial. 
A partir de aqui, buscamos aplicar $\delta$ tantas veces como sea posible de manera que, mientras estemos en un estado válido y no estemos en un estado final, seguiremos aplicando $\delta$. 
En ocasiones llegaremos a un estado de error; en estos casos, diremos que la palabra no pertenece al lenguaje generado por el autómata.

*Definición*:
Dado un _autómata de estados finitos determinista_, definimos el **lenguaje generado por el autómata** como el conjunto de palabras generadas por el alfabeto del autómata y que él mismo da por válidas, lo denotaremos $L(M)) donde $M$ es el autómata.

___Diagrama de Transición___

Para que trabajar con autómatas sea más sencillo, usaremos __diagramas de transición__ que son grafos donde; cada nodo representa un estado, cada arco del grafo representa la aplicación $\delta(q,a)=p$ donde $q,p$ son estados y $a$ una palabra y los estados finales estarán rodeadas por dos cículos como en la imagen.

<div>
<p style = 'text-align=center;'>
<img src="./imagenes/grafos.png" alt="JuveYell" width="400px">
</p>
</div>

Veamos ahora algunas notaciones que nos ayudarán a agilizar el proceso de cálculo. Dado un autómata $M=(Q,A,\delta,q_0,F)$:

*Definiciones*:

Definimos la __descripción instantánea__ como la dupla $(q,a)$ donde $a$ no es una letra, sino una palabra del alfabeto $A$.

Definimos la __configuración incial__ como, dada una palabra cualquiera, la dupla formada por dicha palabra y el estado inicial.

Definimos la __relación de paso de cálculo__ entre dos configuraciones como:
                $$((q,au)\vdash(p,u)\leftrightarrow\delta(q,a)=p)$$
Donde repetimos los elementos que ya conocemos y $a\inA^\*$

En caso de querer escribir que partiendo de una configuración llegamos a otra en una cantidad finita de pasos, usaremos el símbolo $\Vdash$ (en clase se usa $\vdash$ con un asterisco en la parte superior). 
A su vez, se puede usar $\delta^\*(p,u)=q$ para representar lo ya definido. Esto útlimo tiene las propiedades:
Si $q \in Q$
$$\delta^\*(q,\epsilon)=q$$
$$\delta^\*(q,au)=\delta^\*(\delta(q,a),p)$$


