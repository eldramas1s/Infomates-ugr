# 3. Diseño e implementación

---
## Índice

1. [Fundamentos del diseño software](#3.1)
2. [Diseño de la arquitectura](#3.2)
3. [Diseño de los casos de uso](#3.3)
4. [Diseño de la estructura de objetos](#3.4)

---

<a id=3.1></a>

## 3.1. Fundamentos del diseño software

### Definición y características

Hay varias formas de entender el diseño pero hay que tener claro que es una etapa en la que se está con un pie en ambos mundos, el de la tecnoogía y el de las personas y los propósitos humanos, que tratan de unificarse.

La definición correcta es la siguiente: "es el proceso de aplicar distintos métodos, herramientas y principios con el proósito de definir un dispositivo, proceso o sistema con los suficientes detalles como para permitir su realización física".

[TODO]: imag diap 5.

Por su parte, el **diseño de software** es el proceso de aplicar métodos, herramientas y principios de diseño para traducir el modelo de análisis a una representación del software que pueda modificarse.

[TODO]: imag diap 6.

El diseño dispone de las siguientes características:
- Implica una propuesta de solución al problema especificado en el análisis.
- Es una actividad creativa que se apoya en la experiencia del diseñador.
- Apoyado por principios, técinas, herramientas...
- Tarea clave para la calidad del producto software.
- Base para el resto de etapas del desarrollo.
- Proceso de refinamiento.
- Garantiza que un proceso funciona correctamente.

Es importante saber que **hacer un programa que funcione no es equivalente a hacer un programa que funcione correctamente**.

### Principios del diseño

Veremos **cuatro** principios de diseño.

#### División de problemas y modularidad

Esto consiste en dividir los problemas, pues se dice que cualquier problema complejo puede manejarse con más facilidad si se subdivide en elementos susceptibles de resolverse u optimizarse de manera independiente.

> "Un sistema software debe estar formado por piezas, que deben encajar perfectamente, que interactúan entre sí para llevar a cabo algún objetivo común."

[TODO]: explicacion matematica diap 10

No obstante, aunque esto nos puede hacer pensar que podemos realizar la división hasta que la complejidad del desarrollo sea mínima, esto no es así pues el esfuerzo de tener que juntarlos aumenta desproporcionadamente.

Estamos hablando de módulos pero, aún no hemos definido lo que es un **Módulo Software** es una uidad básica de descomposición de un sistema software y representa una entidad o un funcionamiento específico. 

Podrían ser módulos elementos de código como funciones, clases, paquetes,...

La modularidad dispone de unas ventajas:
- Son más fáciles de entender y documentar que el sistema al completo.
- Facilitan los cambios.
- Reducen la complejidad.
- Proporcionan implementaciones más sencillas
- Posibilitan el desarrollo en paralelo.
- Permiten la prueba independeinte(prueba de unidad).
- Facilitan el encapsulamiento.

[TODO]: imag 11


#### Abstracción 

Se conoce como el mecanismo que permite determinar qué es relevante y qué no lo es en un nuvel de detalles determinado, ayudando a obtener una modularidad adecuada para ese nivel de detalles.

Hay tres mecanismos de abstracción que nos van a ayudar a refinar el diseño, incorporando detalles conforme se vaya bajando el nivel de abstracción:
1. Abstracción procedimental. Se abstrae sobre el funcionamiento para conseguir una estructura modular basada en procedimientos.

> Se refiere a la secuencia de pasos que conforman un proceso determinado.

2. Abstracción de datos. Se abstrae tanto el funcionamiento como los atributos que definen el estado de una entidad, para obtener una estructura modular basada en el estado y funcionamiento de une entidad u objeto.

> Define un objeto (entidad) compuesto por un conjunto de datos.

3. Abstracción de control. Se abstrae sobre el flujo de control de cualquier proceso en general.

> Define un sistema de control sin recibir su funcionamiento interno.

#### Ocultamiento de información

> Un módulo debe especificarse y diseñarse de forma que la información (procedimiento y datos) contenida en el módulo sea accesible para otros módulos que no ncesiten esa información.

Los beneficios de este principio son los siguientes:
- Reduce la probabilidad de efectos colaterales.
- Limita el impacto global de las decisiones de diseño locales.
- Enfatiza la comunicación a través de interfaces controladas.
- Disminuye el uso de datos globales.
- Potencia la modularidad.
- Produce software de alta calidad.


#### Independencia modular

> El software debe diseñarse de manera que cada módulo resuelva un subconjunto específico de requisitos y tenga una interfaz sencilla cuando se vea desde otras partes de la estructura del programa.

La independencia de un módulo se mide con dos parámetros:
- Cohesión: un módulo es muy cohesivo cuanto menos funciones realice; por tanto, diremos que un módulo tiene una cohesión adecuada cuando tiene una serie de funcionaes (normalmente pocas) que están muy relacionadas entre ellas. 
    
Cabe destacar que no nos interesa que la cohesión sea la máxima posible pues eso no es realmente operativo.

[TODO]: diap 15 importante

- Acoplamiento: mide la forma de interactuar de los distintos módulos, por lo que es la medida de interdependecia entre módulos dentro de una estructura de software. Un módulo debe presentar un nivel de acplamiento, con los demás módulos, lo más bajo posible. 

Evidentemente, nunca hay que buscar el extremo pues en caso de que tenga el mejor acoplamiento no habrá interacción entre módulos y será poco operativo.

Por tanto, un grado adecuado de acoplamiento entre módulos es indispensable, y hay que:
    + Tratar de reducirlo siempre que sea posible.
    * Mostrarlo de forma explícita en todos los modelos de diseño.

En definitiva, el bajo acoplamiento proporciona módulos fáciles de entender, y con menos efectos colaterales.

### Herramientas de diseño

Son instrumentos qu eayudan a representar los modelos de diseño de software. Algunas de las más usuales son:
- Diagramas de UML.
- Cartas de estructura. (ya está anticuado)
- Tablas de decisión.
- Diagramas de flujo de control.
- Lenguajes de diseño de programas.

### Métodos de diseño

En la actualidad existen una gran variaedad de métodos orientados a objetos, aunque la mayoría de ellos usan como herramienta de modelado UML y como proceso de desarrollo el PU.

[TODO]: diap 20

#### Relación con el modelo de análisis

El modelo de diseño se puede considerar como una elaboración o refinamiento del modelo de análisis, en el que todos los artefactos están mejor definidos e incorpordan detalles técnicos que permiten su implementación.

[TODO]: tabla diap 21
[TODO]: diap 22

### Tareas del diseño

[TODO]: diap 23

[TODO]: diap 24,25,26

## 3.3.Diseño de los casos de uso

### Modelo de interacción de objetos

[TODO]: diap 3

### Patrones de diseño

Los patrones de diseño resuelven el problema de la **asignación de responsabilidades a objetos**; donde una responsabilidad es una obligación que debe tener un objeto en su comportamiento, y debe incluirse en algún método u operación. Pueden ser las siguientes:
- Conocer
    + Los datos privados encapsulados por él.
    + Los objetos relacionados con él.
    + La información que puede calcular o derivar.
- Hacer
    + Hacer algo él mismo.
    + Iniciar una acción en otros objetos.
    + Controlar y coordinar activades en otros objetos

[TODO]: Imagen diap 4

Hemos hablado de los problemas que resuelven pero no de lo que son, un **patrón de diseño** es una descripción de un problema con su solución en un determinado contexto. Las partes esenciales de un patrón son:
- Nombre: debe ser un identificador descriptivo.
- Problema: debe ser una descripción del problema que enuncie cuándo se puede aplicar el patrón.
- Solución: enunciado de la solución que se propone para un contexto determinado.
- Consecuencias: son las repercusiones que tiene el uso de un patrón; proporcionan ayuda en la comprensión de la factibilidad de uso del patrón en una situación particular.

### Patrones de diseño de Craig Larman

Los patrones de diseño de Craig Larman describen los principios fundamentales del diseño de objetos y la asignación de responsabilidades, expresados como patrones.

Tienes las siguientes características:
- No expresan nuevos principios de la ingeniería del software.
- Codifican conocimiento, expresiones y principios ya existentes.
- Negociar una solución razonable.
- Son un ejemplo de fuerza de abstracción porque dan nombre a una idea compleja.

#### Patrón experto en información

Resuelve el problema de la complejidad en la búsqueda de información y acoplamientos fuertes entre clases en estas búsquedas. La solución que propone es asignar responsabilidad a la clase que contiene la información necesaria para llevar a cabo dicha responsabilidad.

Las consecuencias son:
- Malas: en ocasiones va en contra de los principios de acoplamiento yo cohesión.
- Buenas: mantiene el ocultamiento de la información y distribuye el comportamiento.

[TODO]: imagen diap 8

<<L>>: estereotipo de visibilidad local.
<<A>>: estereotipo de visibilidad de asociación.

#### Patrón creador

Resuelve el problema de tener acoplamientos, mala encapsulación y reutilización, y poca claridad en la construcción de objetos. La solución que porpone es asignar a la clase B la responsabilidad de crear una instancia de A cuando B *agrega|contiene|registra|utiliza|tiene los datos de inicialización* objetos de A.

Las consecuencias son:
- Malas: no es conveniente su uso cuando se construye a partir de instancias existenetes.
- Buenas: produce bajo acoplamiento.

[TODO]: imagen diap 10

Las operaciones qu ese pueden enviar a un multiobjeto son:
- Incluir un objeto
- Eliminar un objeto
- Buscar
- Hacer un recorrido uno a uno para ir procesando los objetos
No podemos enviar ninguna otra. Además, los multiobjetos no pueden enviar operaciones, dicho de otra forma, deben ser objetos terminales de los envíos.

#### Patrón bajo acoplamiento

Resuelve el problema de elementos con demasiadas dependencias sobre elementos, ya que una modificación conlleva demasiadas modificaciones solaterales, difíciles de entender aisladamente y difíciles de reutilizar.

La solución propuesta es asignar responsabilidades de forma que se tengan elementos que dependena solamente de lo sñunicos elementos que necesite.

Las conscuencias son:
- Malas: LLevada al extremo puede ocasionar diseños pobres; en un conjutno de clases debe haber un nivel de acoplamiento moderado y adecuado.
- Buenas: No afectan los cambios en otros elementos, son fáciles de entender de manera aislada y provoca un aumento de la reutilización.

#### Patron alta cohesión

Resuelve el problema de disposición de elementos con pocas tareas o con muchas pero no relacionadas. Estos elementos son difíciles de entender, de reutilizar y de mantener, además se ven adfectados por continuos cambios.

La solución que propone es asignar responsabilidades de forma que todas las tareas de un elemento estén para lograr un objetivo común.

Las consecuencias osn:
- Malas: Ninguna, renuenar a la alta cohesión tan solo cuando esté muy justificado.
- Buenas: 
    + Claridad y facilidad de entendimiento del diseño.
    + Simplificación del manteimiento y de las mejoras.
    + Aumento de la reutilización.

[TODO]: imagen diap 13

#### Patrón controlador o fachada

Resuelve el problema de la comunicación entre los objetos de la capa del dominio de la solución y la capa de la interfaz. Como solución propone asignar responsabilidades de recepción o manejo de un mensaje de evento del sistema a una clase que represente:
- EL sistema global, dispositivo o subsistema (*controlador de fachada*)
- EL escenario de caso de uso en el que tiene lugar el evento del sistema(*controlador de caso de uso*)

Como consecuencias tiene:
- Malas: controladores saturados.
- Buenas:
    + Asegura que la lógica de la aplicación no se maneja en la interfaz.
    + Buena reutilización y bajo nivel de acoplamiento.
    + Posibilidad de razonar sobre el estado de los casos de uso.

[TODO]: diap 15

Para nosotros la clase *Controlador* será el sistema.

### Elaboración del modelo de interacción

[TODO]?: Diap 16

Seguiremos las siguientes directrices:
- Las bases principales para obtener los diagramas de interacción son los contratos y e l modelo conceptual.
- EL modelo conceptual sirve como un guía para saber qué objetos pueden interaccionar en una operación.
- Todo lo especificado en el contraro, especialmente las poscondiciones, las excepciones y las salidas tienen que satisfacerse en el correspondiente diagrama de interacción.
- Para la elaboración de cada diagrama de inteeracciń se aplican lo patrones de diseño Craig Larman.

Los pasos a seguir son lo siguientes:
1. Elaborar los diagramas de interacción, de forma que para cada operación especificada en los DSS:
    1. Tener presente el diagrama de conceptos y el contrato de dicha operación.
    2. Representar las relaciones del controlador con los objetos que intervienen en la interacción.
    3. asignar responsabilidades a objetos.
    4. Establecer tipo de enlaces entre objetos.
2. Inicialización del sistema
3. Establecer las relaciones entre el modelo y la Interfaz de Usuario.
