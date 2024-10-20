# 3.Modelo de Datos. El modelo de datos relacional7

Hasta ahora, hemos trabajado las fases de estudio de los datos sobre una organización contrera y hemos modelado de forma gráfica nuestra base de datos. 

En este tema vamos a centrarno en modelos de datos que son implementables; concretamente, nos centraremso en el modelo de datos relacional impuesto por Edgar F. Codd.

Este modelo, para representar cualquier relación o entidad, usará tablas; de hecho, funciona tan bien porque se asemeja a la organización que realizaría un ser humano para consultar elementos.


## 3.1.Definición de modelo de datos.

Un modelo lógico de la base de datos es un esquema conceptual retocado de manera que peuda llegar a ser implementado en un _SGBD_; es decir, el administrador de la base de datos sólo tiene que proponer el método por el cual se traslada del esquema conceptual al esquema lógico de implementación.

Está bastante claro que, para implementarlo debemos usar el _DSL_ y la sintáxis que este disponga.

Veamos ahora la definición de __modelo de datos__; es un mecanismo formal que sirve para representar y manipular la información de manera general y sistemática que debe contener la siguiente notación:

    - Para describir datos.
    - Para describir operaciones.
    - Para describir restricciones de integridad.

No obstante, aún no sabemos la necesidad que surgió para que se inventará este modelo:
    
    - Cada esquema se describe utilizando un lenguaje de definición de datos.
    - Este lenguaje es de muy bajo nivel, está muy ligado al SGBD.
    - Luego hacen falta otros mecanismos de más alto nivel que permitan describir datos de una forma no ambigua y entendible por los usuarios implicados en cada paso del proceso de implantación.

Este modelo tiene un ojetivo claro, conseguir describir modelos que representen los datos y los describan de una forma entendible y manipulable.

Veamos ahora que relación tiene con la arquitectura _ANSI/SPARC_ dependiendo de los niveles. Aunque en las transparencias aparezca que cada nivel dispone de un modelo de datos con su mismo nombre, en clase se comentó que, realmente, el nivel _externo_ y el nivel _conceptual_ disponen del mismo modelo de datos mientras que, para el nivel _interno_, se suele implementar con un modelo diferente al resto.

Los modelos de datos suelen clasificarse en tres tipos:
    
    - Basados en registros
    - Basados en objetos
    - Físicos

Cabe destacar que los dos primeros suelen usarse para el nivel _externo_ y _conceptual_, y el último para le nivel _interno_.

## 3.2.Modelo de datos relacional

### 3.2.1.Estructura de datos
Este modelo creado por Edgar F. Codd consiste en que todos los elementos se representan en tablas; de hecho, las relaciones son tablas.

Para Codd, las relaciones (tablas) no son más que conjuntos de n-uplas(fila) donde cada elemento representa un atributo(columnas). Como cada atributo visto como columna dispone de un dominio vemos que cada n-upla es un elemento del producto cartesiano de los dominios explicando así el nombre de __relación__ a las tablas.

COmo restricción, cada relación debe disponer de un único nombre; de esta manera, no habrá dos relaciones con el mismo nombre evitando confusiones.

El modelo de datos relacional abarca tres ámbitos distintos de los datos:
    
    - Las estructuras para almacenarlos dondel el usuario percibe información de la base de datos estructurada en tablas.
    - La integridad donde las tablas deben satisfacer ciertas condiciones que preservan la integridad y coherencia de la información que contienen.
    - COnsulta y manipulación donde se definen operadores que permiten hacer consultas mediante la definición matemática de los mismos basada en algebra relacional. Las consultas no serán más que operaciones que proporcionan tablas como resultado de composición de tablas obtenidas mediante dichos operadores.

Siguiendo un poco el concepto de álgebra relacional, cabe destacar que _SQL_ está muy ligado a este disponiendo, como aditivo, de otras herramientas. Como curiosidad, Codd vio que le cálculo de predicados de primer orden era equivalente a formalizar las tablas mediante el cálculo relacional.

___Algunos conceptos___

    · Atributo -> cualquier elemento de información susceptible de tomar valores -> columna de una relación.
    · Dominio -> rango de valores que puede tomar un atributo -> se considera finito
    · Tipo de dato -> heramientra que se usa para definir el dominio de un atributo.
    · Esquema -> definición de la relación desde un punto de vista estructural con atributos y dominios.
    · Instancia -> conjunto de n-uplas de una relación en un momento de tiempo dado.
    · Grado -> número de atributos de los que dispone una relación en su esquema.
    · Cardinalidad -> número de n-uplas de las que dispone una relación en una instancia.
    · Base de datos relacional -> esquema de base de datos relacional + instancias de la base de datos.

___Propiedades de una estructura de datos___

    - Condición de normalización: todos los valores de los actributos de una relación deben ser atómicos <-> son no estructurados <-> los consideramos como un todo.

Cuando esta condición se cumple decimos que está en __primera forma normal__(las formas normales son condiciones que puede cumplir una BD para ser de mayor calidad llegando hasta la 5ª forma normal donde ya la BD es inmejorable).
___Consecuencias de la primera forma normal___

Debido a que no hay tipos de datos estructurados es imposible que haya valores de tipo conjunto,  registro o tabla ocasionando que todas las representaciones de los datos puedan ser extensivas. Es decir, una única intancia puede estar repetida con distintos atributos; no obtante, esto da facilidad en la consulta de datos.

Volviendo al trato de relaciones, cuando definimos una tabla, esta carece de orden tanto en filas como columnas; luego, si hay dos tabals donde apraecen esencialmente las mismas n-uplas del producto cartesiano en distinto orde, tenemos la misma instancia de la relación. 

De hecho, sería un error de principiante imponer las consultas mediante el orden de los atributos en la tabla pues estaríamos rompiendo la independiencia de los datos.

Si pensamos un poco sobre las claves primarias, en caso de no disponer de una clara, podrmos siempre usar la unión de todas ellas creando así, una clave primaria que determina una única tupla.

___¿Qué ocurre si un atributo no puede tomar un valor?___

Contestando a la pregunta, existe un tipo de valor llamado __valor nulo__ de un atributo que consiste en un valor especial que, si un atributo no puede ser aplicable o toma un valor desconocido, dicho valor nulo realizará la función de rellenarlo.

Este valor trae consecuencias de ruido a la hora de la consulta pues siempre aparecerá la tupla si buscamos por ese atributo.

Esta valor tiene como condición que debe aparecer en todos los dominios, cada dominio dispone del suyo; sin embargo, pese a que exista en el dominio de la clave primaria, no puede aparecer en la relación.

### 3.2.2.Restricciones de integridad

La integridad es lo relativo a definir reglas que permitan garantizar la corrección semántica de la base de datos. Hay dos tipos:

    - Específicas del problema -> son las relacionadas con la definición de dominios.
    - Propias del papel de los atributos en el esquema -> restricciones de sentido común ligadas a la representación del atributo en el problema a estudiar. La restricción de que una clave primaria no tome el valor nulo es de este tipo.
