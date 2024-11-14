# 3.Modelo de Datos. El modelo de datos relacional

Hasta ahora, hemos trabajado las fases de estudio de los datos sobre una organización concreta y hemos modelado de forma gráfica nuestra base de datos. 

En este tema vamos a centrarnos en modelos de datos que son implementables; concretamente, nos centraremos en el modelo de datos relacional impuesto por [Edgar F. Codd](https://es.wikipedia.org/wiki/Edgar_Frank_Codd).

Este modelo, para representar cualquier relación o entidad, usará tablas; de hecho, funciona tan bien porque se asemeja a la organización que realizaría un ser humano para consultar elementos.


## 3.1.Definición de modelo de datos.

Un modelo lógico de la base de datos es un esquema conceptual retocado de manera que pueda llegar a ser implementado en un _SGBD_; es decir, el administrador de la base de datos sólo tiene que proponer el método por el cual se traslada del esquema conceptual al esquema lógico de implementación.

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
    
- Estructuras para almacenarlos: el usuario percibe información de la base de datos estructurada en tablas.
- Integridad: las tablas deben satisfacer ciertas condiciones que preservan la integridad y coherencia de la información que contienen.
- Consulta y manipulación: se definen operadores que permiten hacer consultas mediante la definición matemática de los mismos basada en algebra relacional. Las consultas no serán más que operaciones que proporcionan tablas como resultado de composición de tablas obtenidas mediante dichos operadores.

Siguiendo un poco el concepto de álgebra relacional, cabe destacar que _SQL_ está muy ligado a este disponiendo, como aditivo, de otras herramientas. Como curiosidad, Codd vio que le cálculo de predicados de primer orden era equivalente a formalizar las tablas mediante el cálculo relacional.

___Algunos conceptos___

- Atributo -> cualquier elemento de información susceptible de tomar valores -> columna de una relación.
- Dominio -> rango de valores que puede tomar un atributo -> se considera finito
- Tipo de dato -> heramientra que se usa para definir el dominio de un atributo.
- Esquema -> definición de la relación desde un punto de vista estructural con atributos y dominios.
- Instancia -> conjunto de n-uplas de una relación en un momento de tiempo dado.
- Grado -> número de atributos de los que dispone una relación en su esquema.
- Cardinalidad -> número de n-uplas de las que dispone una relación en una instancia.
- Base de datos relacional -> esquema de base de datos relacional + instancias de la base de datos.

___Propiedades de una estructura de datos___

- Condición de normalización: todos los valores de los actributos de una relación deben ser atómicos(que no se pueden descomponer) <-> son no estructurados <-> los consideramos como un todo.

Cuando esta condición se cumple decimos que está en __primera forma normal__(las formas normales son condiciones que puede cumplir una BD para ser de mayor calidad llegando hasta la 5ª forma normal donde ya la BD es inmejorable).

___Consecuencias de la primera forma normal___

Debido a que no hay tipos de datos estructurados es imposible que haya valores de tipo conjunto,  registro o tabla ocasionando que todas las representaciones de los datos puedan ser extensivas. Es decir, una única intancia puede estar repetida con distintos atributos; no obtante, esto da facilidad en la consulta de datos.

Volviendo al trato de relaciones, cuando definimos una tabla, esta carece de orden tanto en filas como columnas; luego, si hay dos tabals donde apraecen esencialmente las mismas n-uplas del producto cartesiano en distinto orde, tenemos la misma instancia de la relación. 

De hecho, sería un error de principiante imponer las consultas mediante el orden de los atributos en la tabla pues estaríamos rompiendo la independiencia de los datos.

Si pensamos un poco sobre las claves primarias, en caso de no disponer de una clara, podrmos siempre usar la unión de todas ellas creando así, una clave primaria que determina una única tupla.

___¿Qué ocurre si un atributo no puede tomar un valor?___

Contestando a la pregunta, existe un tipo de valor llamado __valor nulo__ de un atributo que consiste en un valor especial que, si un atributo no puede ser aplicable o toma un valor desconocido, dicho valor nulo realizará la función de rellenarlo.

De hecho, no podremos conocer si el valor nulo aparece por no poder ser aplicable un valor o porque sea desconocido.

Este valor trae consecuencias de ruido a la hora de la consulta pues siempre aparecerá la tupla si buscamos por ese atributo.

Este valor tiene como condición que debe aparecer en todos los dominios, cada dominio dispone del suyo; sin embargo, pese a que exista en el dominio de la clave primaria, no puede aparecer en la relación.

### 3.2.2.Restricciones de integridad

La integridad es lo relativo a definir reglas que permitan garantizar la corrección semántica de la base de datos. Hay dos tipos:

- Específicas del problema -> son las relacionadas con la definición de dominios.
- Propias del papel de los atributos en el esquema -> restricciones de sentido común ligadas a la representación del atributo en el problema a estudiar. La restricción de que una clave primaria no tome el valor nulo es de este tipo.

*Definicion*

Una __superclave__ de un conjunto de atributos es un subconjunto de ellos que determina de forma unívoca  a cada tupla de la relación (tabla), en este caso, no debe ser minimal, es decir, eliminar un elemento de dicho subconjunto no debe provocar que se pierda la uniciadad.

En el caso de que haciendo la operación antes dispuesta se pierda la unicidad, estaremos ante una __clave__.

Como se puede intuir, una clave no deja de ser una superclave con una característica más; de manera que, el conjunto de las claves está contenido en el de las superclaves.

Normalmente, para una relación habrá varias claves que pueden identificar unívocamente a la tupla siendo además minimales. A estas claves se les denomina __claves candidatas__ de las cuales se elegirá una, lo habitual es hacerlo al azar salvo que haya restricciones del problema que nos indiquen cuál tomar, que será la __clave primaria__. 

Esta clave primaria nunca puede faltar y siempre debe tomar un valor distinto del nulo. Sin embargo, no es necesario rellenar siempre una clave candidata, incluso podrán tomar valores nulos. Por último, una clave candidata verificará que determina de forma unívoca la tupla pero puede no verficar que sea minimal.

De forma intuitiva, una __clave externa__ proviene de una relación y es la clave primaria de uno de los relacionados; debe cumplir ciertas restricciones:
    
- El conjunto de valores que tome la clave externa en la relación (__dominio activo__ ) debe estar contenido en el __dominio activo__ de la clave primaria de la entidad que procede.
- Puede haber más de una clave externa en la relación; de hecho, es lo habitual.
- En relaciones involutivas, una de las claves externas proviene de la misma relación en la que se encuentra.

___Conceptos generales___

Las __condiciones de integridad__ son reglas que se establecen para ayudar a determinar los elementos que pueden tomar parte de la base de datos de manera que lo que entre persevere la consistencia con lo que se está modelando de la realidad.

Por su parte, la __integridad genérica__ depende del papel que juega un atributo en el diseño de la tabla y se consigue a través de las siguientes metarreglas.
    
- Metarregla de integridad de entidad: consiste en la no ausencia de ninguna clave primaria en la base de datos; además, no permite valores nulos. A diferencia de las candidatas que pueden tomar valores nulos aunque se controle la unicidad.

- Metarregla de integridad referencial: esta metarregla provoca que todos los valores no nulos de una clave externa referencien valores reales de la clave referenciada en la otra relación. Esto se puede traducir como; " el dominio activo de la clave externa, sin incluir valores nulos, está contenido en el dominio activo de la clave primaria a la que referencia".

___El SGBD___

La manutención de alguna restricciones se deja al _SGBD_, estas restricciones son:

- La unicidad de la clave primaria y de las claves candidatas; consiste en evitar meter valores duplicados a la hora de actualizar o insertar la base de datos, para claves primarias o candidatas, en atributos normales esto no es así.
- La integridad de la identidad; consiste, en el caso de la integridad de entidad, impedir que las claves primarias tengan valores nulos. Y en el caso de la integridad referencia, impedir que las claves externas tomen un valor que no estén en el dominio activo de la clave primaria referenciada.

Uno de los problemas más comunes es el borrado de una clave primaria, pues deberá permanecer la consistencia de los datos; como las claves externas de dicha primaria tienen valores no nulos se deberá controlar dicha situación de incongruencia.


## 3.3.Otros modelos de datos

Todos los modelos que se van a ver son modelos estructurados.

### 3.3.1.Modelo jerárquico

Este modelo diseñado para el lenguaje _Cobol_ se basa en al utilización de ficheros y punteros en forma de árbol. 

En dicho árbol había un registro maestro de donde provenían los demás registros secundarios, entidad que representa, en el modelo de datos relacional, a una única tupla donde la clave primaria es al registro maestro y los atributos los registros secundarios.

Este modelo permitía representar muy bien las relaciones muchos a uno y uno a uno; no obstante, el fallo viene de cuando se intenat representar las relaciones muchos a muchos, pues la única solución que se encontró fue duplicar el árbol de forma simétrica desperdiciando mucho espacio.

COmo inconvenientes tenemos:
    
- Complicación de mantener la estructura con punteros y muchos tipos de registros.
- Dificultad de implementación y uso del DML.
- Dependencia existencial obligatoria de un registro secundario con su maestro, ya que no se podrá insertar un registro secundario si no hay un maestro creado.
- Redundancia para expresar relaciones muchos a muchos.

### 3.3.2.Modelo en red

Con la idea de solucionar el tema de las relaciones muchos a muchos se inventaron los modelos en red que no son más que modelos jerárquicos que, en lugar de usar una estructura de árbol, usaban una estructura de grafo.

Este modelo tiene dos tipos de nodos; los nodos conectores que servían para realizar la relación entre dos registros, y los registros corrientes que guardaban simplemente la información.

Como ventajes tenemos:
    
- Estructura más homogénea
- Inserción de nuevas entidades de forma independiente.

Como inconvenientes:
    
- La complejidad de los árboles se aumenta al trabajar con grafos, es imposible controlar los punteros.
- La existencia de enlaces entre los registros hace que las operaciones del DDL y DML sigan siendo difíciles de implementar.

### 3.3.3.Comparativa

En este apartado simplemente se va a realizar una comparativa de los distintos modelos ; como el modelo en __red__ no es más que una generalización más útil del modelo __jerárquico__, usaremos el primero para comparar.

|Aspecto|Modelo de red|Modelo de relacional|
|:-----:|:------------|:-------------------|
|Representación|- Dos elementos para la representación (nodo y puntero). <br> · Conexiones en el modelo físico subyacente. <br> · Representación de relaciones n:m imposibles o difíciles. <br>· Identidad por posición | · Un único elemento para la representación(tabla).<br> · Conexiones lógicas. <br>· Simetría n:m.<br> · Identidad por valor  |
|Consulta| · Obtención de la consulta como resultado global. <br> · Admite lenguajes declarativos y procedimentales.  | · Mecanismo de navegación por punteros. <br> · Sólo admite lenguajes procedimentales.| 

### 3.3.4.Modelo orientado a objetos

Como su nombre indica se basa en la orientación a objetos, es decir, en tratar cada entidad como un objeto. Si pensamos en _Java_, crearíamos una clase por entidad donde los datos miembro serían los atributos.

Con estos modelos seríamos capaces de suplir algunas de las debilidades del __modelo de datos relacional__:
    
- Dispone de una representación muy pobre de las entidades del mundo real.
- Produce una sobrecarga semántica de la estructura de la relación, todo son tablas.
- La estructura relacional es muy estricta:
    
    + Todas las tuplas deben tener los mismos atributos.
    + Los valores de un atributo dentro de una instancia deben pertenecer todos al mismo dominio.
    + Los atributos deben tener un valor atómico.

- SQL actuando de forma puramente relacional permite sólo un conjunto de operaciones limitadas, por ejemplo nos limita el modelaje del comportamiento de objetos del mundo real.
- Object-relational impedance mismatch: consiste en los problemas que pueden surgir a la hora de trabajar sistemas gestores de bases de datos relacionals desde aplicaciones que usan un modelo de datos orientado a objetos.

La filosofía de estos modelos es clara, consiste en tratar de abstraer una parte del mundo real mediante una serie de objetos que realizan acciones entre sí simbolizando las relaciones que hay entre ellos.

Como resultado final, viendo que tanto el _modelo de datos relacional_ como el _modelo de datos orientado a objetos_ disponían de las soluciones a los problemas del modelo opuesto, se buscó el __modelo de datos objeto-relacional__; no obstante, el _modelo de datos relacional_ continúa usándose en mayor medida en solitario.

### 3.3.5.Sistemas multidimensionales

Hasta ahora, sabemos tratar una cantidad de datos inmensa de forma que las relaciones entre esos datos son poco visibles, solución que proporcionan los sistemas multidimensionales.

Un sistema multidimensional se basa en la representacíon de los hechos de la vida cotidiana que se buscan estudiar en un hipercubo de dimensión tantos hechos como se estén estudiando. Hay de dos tipos:

+ Operacionales: son encargados de proporcionar información a la empresa de forma diaria.
    - Utiliza el procesamiento de datos en línea u OLTP necesitando de aplicaciones para dar soporte a operaciones diarias.
    - Requieren de datos actualizados al máximo nivel y detallados lo más posible.
    - Las operaciones realizadas necesariamente afectarán a pocos registros y se hacen mediante claves primarias.
    - Requiere que haya gran consistencia y que los sistemas sean fiables.
    - Para que el redimiento del sistema sea óptimo se debe optimizar la gestión de transacciones, es decir, las consultas que se hagan a la base de datos.

+ Analíticas, son sistemas de información creados para responder preguntas de asesoramiento para la evolución y toma de decisiones de una empresa.
    
    - Utiliza procesamiento de datos en línea u OLAP necesitando aplicaciones orientadas al soporte de decisiones.
    - Son sistemas donde debemos pensar en que los usuarios son de otro tipo al habitual, se responderán preguntas como "¿qué elemento es el que me produce más beneficio?".
    - Requieren que los datos que estén en la base de datos estén consolidados, resumitos y sean, en su mayoría, de tipo histórico.
    - Están creados para resolver consultas complejas, poco previsibles y que involucrean a grandes cantidades de registros.

___Modelo de datos multidimensional___

Cada una de las caras representará un hecho; de manera que si de una compra buscamos guardar la fecha, el precio y el producto, dispondremos de un cubo. 

La ventaja de estos sistemas revoca en poder aplicar _zoom_ durante la búsqueda de información pues en cada nivel del cubo podremos detercar una mayor profundidad en alguno de los atributos.

Por ejemplo, para entenderlo de forma intuitiva, si queremos guardar:

- La fecha: podremos hacerlo en mayor o menor profundidad luego cada celda de una cara representará mayor o menor profundidad.
- El precio: podremos hacerlo con más o menos detalle, incluso guardando el método de pago, esto se consigue de la misma manera que la fecha.
- El producto: podremos hacerlo en mayor o menos profundidad, guardando, incluso, el código de barras del producto para saber qué producto concretamente se compra, esto de nuevo se consigue de la misma manera que la fecha.

Con este _zoom_ que le permitimos hacer al usuario, le estamos dando tanta información como él necesite. 

Lo más cotidiano es que estos tipos de modelos se usen en el _nivel empresarial_ donde los usuarios son analistas y buscan el mayor rendimiento de la empresa.

