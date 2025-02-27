# 1.Introducción a la Ingeniería del Sorftware

___

## Índice
1. [Producto Software](#11)
2. [El concepto de Ingeniería del Software ](#12)
3. [El proceso de desarrollo del software](#13)
___

<a id='11'></a>
## 1.1.El producto software
Dentro de este apartado veremos varias partes.

### Naturaleza del software
El software es una abstracción que dispone de una naturaleza dual, es decir, dependiendo de como se utilice se comportará de una manera o de otra, dicha naturaleza dual está formada por:
- Producto: que se encarga de proporcionar el potencial de cómputo, es decir, proporciona capacidad de realizar operaciones. Además, es un transformador de información
- Vehículo: se puede encargar de distribuir un producto software; donde encontramos tres posibilidades:
    + Sistema Operativo: actúa como base para el control de la computadora.
    + Redes: actúa como una base para la comunicación de información.
    + Herramientas y ambientes de software: actúa como base para la creación y control de otros programas.

Obviando todo esto, hay que tener una idea muy clara, esta idea consiste en tener en mente que el software se encarga de manejar y distriubuir información, el producto más importante de nuestros tiempos.

### Definición de Software

Para nosotros, una buena definición de software es un conjunto de instrucciones que cuando se ejecutan proporcionan las funciones y características buscadas, un conjunto de estructuras de datos que permiten a los programas manipular la información adecuandamente, y un conjunto de información en papel o en forma virtual(conocido como documentación) que describe la operación y uso de los programas.

Todo esto se basa en que un programa no puede trabajar sin ninguna de las demás cosas, requiere de unos datos de entrada y de un conjunto de normas que le digan como actuar. Por tanto, cualquier tipo de definición que no contenga a los tres conjuntos no estará completa.

Cabe aclarar que la documentación no es solo lo que contiene el uso y operación con el software, sino que también contiene la información sobre el desarrollo del software.

### Características fundamentales del software

Las características son:
- Es un producto lógico, no es un producto tangible, no es algo que podamos tocar, ver o sentir. Se puede entender como un elemento abstracto; como no es tangible, no se puede fabricar sino que se desarrolla. De la misma forma, como no es tangible no se estropaa, sino que se deteriora

<div>
<p style='text_align:center;'>
<img src=./imagenes/deterioro.png alt="Error" width=500px>
</p>
</div>

Con respecto a la imagen del HArdware el índice de fallo desciende brutalmente desde su inicio de fabricación, es algo lógico pues es cuando el hardware está en buen estado o incluse recién vendido. No obstante, cuando aumentamos el tiempo, llegará un instante en el que el índice de fallos aumenta exponencial.

(Los nombres de las partes de las gráficas son así por muy raro que parezca)

Con respecto a la imagen del Software, disponemos de una curva idealizada pues no debe haber factores medio ambientales que se deteriore el software, comenzando igual que en el hardware debería llegar a estabilidzarse. 
No obstante, esto no es así, la curva real inicia como se prevee pero llega un momento donde se deben producir cambios a medida que se detectan fallos. El punto de cambio es importante pues puede producir efectos colaterales iniciando de nuevo la curva y repitiendo el proceso.
Es importante notar que, a medida que aumenta el tiempo los fallos se producen con mayor índice, esto refleja el deterioro.

- Crea modelos de la realidad; por ejemplo, un modelo de información de la realidad puede ser una base de datos, donde disponemos de la información almacenada en una estructura( que forma parte del software ) representando relaciones entre entidades.
- Está formado por múltiples piezas que deben encajar perfectamente, deben estar relacionadas entre sí.

### Tipos y dominios de aplicación

Haremos una clasificación u otra dependiendo del parámetro que estudiemos; según el parámetro:
- Estudiando el dominio de aplicación:
    + Software de sistemas: son aquellos que proporcionan servicio a otros programas.
    + Software de aplicación: son aquellos que resuelven una necesidad específica de negocios.
    + Software de ingeniería y ciencias: implementa algoritmos "devoradores" de mundos.
    + Software empotrado: ya los conocemos, encajados en sistemas del día a día, es decir, residen dentro de un producto o sistema e implementa y controla características y funciones para el usuario final y para el sistema en sí.
    + Software de gestión: proporciona una capacidad específica para el uso de muchos consumidores diferentes.
    + Aplicaciones Web: es un software centrado en redes que agrupa una amplica gama de aplicaciones.
    + Software de Inteligencia artificial: implementa algoritmos no numéricos para resolver problemas complejos de tratar computacionalmente o con análisis directo.

- Estudiando el destinatario:
    + Para distribución o también llamados genéricos: son sistemas autónomos producidos por una organización de desarrollo y vendido en el mercado abierto a cualquier cleitne que pueda comprarlo.
    + Usuario final o hecho a medida: son los sitemas desarrollados por una empresa especialmente para un cliente particular.

- Estudiando los derechos de autor:
    + De código abierto: su código fuente está disponible para que cualquiera pueda usarlo y dispone de derechos de autor.
    + De código cerrado: su código fuente no se encuentra disponible para cualquier usuario, evidentemente dispone de derechos de autor y muy restrictivos.
    + De dominio público: No dispone de derechos de autor y, además, el código fuente es de dominio público, es un caso especial de software libre sin copyleft(sin derechos de autor).

### Proceso de producción
El proceso de producción se rige según el siguiente esquema:

<div>
<p style='text_align:center;'>
<img src=./imagenes/pproduccion.png alt="Error" width=500px>
</p>
</div>

Dispone de tres grandes fases:
1. Fase de definición: tiene como principal objetico definit qué se desarolla y como principales tares tiene:
    + Ingeniería de sistemas
    + Planificación de proyectos
    + Ingeniería de requisitos
Nosotros nos centraremos en la ingeniería de requisitos.

2. Fase de construcción: tiene como principla objetivo determinar cómo se va a desarrollar el producto(software) definido en la fase de definición y tiene como principales tareas:
    + Diseño del software
    + Generación del código
    + Prueba del software
Nos centraremos en la primera y la tercera, la segunda la dejamos para otra asignatura.

3. Fase de evolución: forma parte de una fase de operación donde el producto ya está entregado, debemos determinar qué puede o va a cambiar. Como tareas tiene:
    + Corrección
    + Adaptación
    + Mejora
    + Prevención
Esta fase es también llamada fase de mantenimiento. Además, dispone del mayor esfuerzo pues el 45% aproximadamente del esfuerzo se dedica a los cambios den los requisitos del usuario.

Durante el proceso de producción pueden surgir una serie de problemas que pueden ser de varios tipos:
- Generados por fallos en la comunicación entre las personas, ya sea con el cliente como con los propios compañeros de equipo. Puede ser incluso, que este tipo de problemas de comunicación con el cliente nos obligue a aprender un nuevo campo de investigación. Además, el cliente puede no conocer elementos o tecnicismos que usemos; por tanto, hay que tener cuidado con el vocabulario que usamos.
- Generados por el incumplimiento de la planificación; normalmente antes de definir y construir un producto software debemos hacer una planificación que contengas aspectos como el tiempo empleado por actividad, personal necesario, préstamos... Siendo sinceros, suelen no cumplirse, como solución no se debe proponer la **horda mongoliana**, es decir, incrementar el número de personal a tutiplén, esto incrementa los fallos por comunicación y retrasar más el desarrollo del producto.
- Generados por la incorporación de cambios en etapas avanzadas del proceso, normalmente requiridos por el usuario de forma espontánea; el coste de realizar ese cambio aumenta a medida que progresa el desarrollo del producto, siendo menor en la fase de definición y siendo mucho mayor en la fase de mantenimiento.

<a id='12'></a>
## 1.2.El concepto de ingeniería del software

Dentro de este apartado veremos aspectos como la historia, algunas definiciones, terminología y principios generales de esta ingeniería.

### Historia y necesidad de la ingeniería del software

Como tal, el concepto de ingeniería del software es un concepto muy reciente, surge del remplazo de muchos calculadores de la NASA para obtener resultados mucho más precisos a través de "programas". 
Fue propuesto en 1968 para discutir la crisis del software a consecuencia de un nuevo hardware lo que llevo a los siguientes problemas:
- Software muy complejo
- Grandes proyectos con años de retraso
- Coste del software mucho más de lo previsto
- Software poco viable, difícil de manejar y de pobre ejecución
En esa discusión se concluyó que se debía entender el problema antes de desarrollar una aplicación, que el diseño era una actividad crucial, el software debía de tener alta calidad y debía ser fácil de mantener.

### Definición de Ingeniería del Software
Algunas de las definiciones usadas para referirse a esta rama de la ingeniería informática son:
    - Friz Bauer(1972): Establecimiento y uso de principios fundamentales de la ingeniería con objeto de desarrollar en forma económica software que sea fiable y que trabaje con eficiencia en máquinas reales.
    - B. Bohem(1976): Aplicación prática del conocimiento cientídico en el diseño y construcción de programas de computadora y la documentación asociada y requerida para el desarrollo, operación y mantenimiento del programa.
    - IEEE (1993): Aplicación de un enfoque sistemático, disciplinado y cuantificable al desarrollo, operación y mantenimiento del software; es decir, aplicación de la ingeniería al software.

### Terminología usada en ingeniería del software

Daremos una serie de términos que no deben confundirse, pues son totalmente diferentes entré sí pese a usarse en el mismo entorno. Estos aspectos son:
- Sistema: un sistema es un conjunto de elementos relacionados entre sí y con el medio, que forma una unidad o un todo organizativo.
- Sistema basado en computadora: es un sistema cuyos elementos están organizados para cumplir una meta predefinida al procesar información. La diferencia con el sistema es el hecho de procesar información. Un sistema basado en computadora está formado con la siguiente estructura que tiene asocida una documentación y unos procedimientos.

<div>
<p style='text_align:center;'>
<img src=./imagenes/scomputadora.png alt="Error" width=500px>
</p>
</div>

- Sistema software: es un sistema que forma parte de un sistema basado en computadora y está formado por elementos software relacionados entre sí y organizados en subsistemas.
<div>
<p style='text_align:center;'>
<img src=./imagenes/ssoftware.png alt="Error" width=500px>
</p>
</div>

- Modelo: es una representación de un sistema en un determinado lenguaje; cabe recalcar que de un mismo sistema se pueden construir muchos modelos. En definitiva, es una abstracción de una parte de la realidad en un sistema mediante un lenguaje de programación.
- Principio: es un conjunto de elementos adquiridos mediante el conocimiento, que definen las características que deben poseer un modelo para ser una representación adecuada de un sistema.
- Herramienta: cada uno de los instrumentos que nos permiten la representación de modelos es una herramienta. Por ejemplo, el propio lenguaje de programación es una herramienta.
- Técnica: es el modo de utilización de las herramientas.
- Heurísticas: conjunto de reglas empíricas, que al ser aplicadas producen modelos que se adecuan a los principios.
- Proceso: estructura que debe establecerse para la obtención eficaz de un producto de ingeniería. Establece el contexto sobre el cual vamos a aplicar las técnicas y las herramientas.
- Métodos: secuencia de actividades para la obtención de un producto(modelo), que describen cómo usar las herramientas y las heurísticas.

<div>
<p style='text_align:center;'>
<img src=./imagenes/resumen.png alt="Error" width=500px>
</p>
</div>

Junto a todo esto, se proporciona una definición de ingeniería del software, que será el estudio de principios, metodologías y herramientas que forman parte de un número finito de procesos para facilitar el desarrollo y mantenimiento de sistemas software de calidad.

Es importante conocer adecuadamente cada uno de los conceptos pues de ello dependerá la calidad de la documentación generada; si se usa bien, realizará una buena tarea de guía para la fase de mantenimiento.

### Principios generales
A la hora de diseñar un sistema software debemos tener en cuenta en todo momento los siguientes aspectos:
1. Un software solo existe para aportar valor a sus usuarios, es decir, si no aporta ningún valor no debemos hacerlo.
2. Debe primarse la smplicidad del diseño siempre y cuando no se pierda calidad.
3. Conserva la integridad conceptual durante todo momento, es decir, si disponemos de un objetivo para ese software, debemo sevitar distracciones y cumplirlo.
4. Lo que hacemos, debe ser entendible por los usuarios que lo vayan a usar y mantener.
5. Debemos diseñar sistemas adaptanles, listos para cambios y escalables.
6. Diseña pensando en componentes que sean o puedan ser reutilizables.
7. Reflexiona para lograr mejores resultados y aprender de los errores, es decir, cuando nos encontremos frente a un problema no debemos de abordarlo sin antes dedicar un tiempo a entenderlo.

<a id='13'></a>
## 1.3.El proceso de desarrollo del software
