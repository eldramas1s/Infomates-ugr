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

Con respecto a la imagen del Hardware el índice de fallo desciende brutalmente desde su inicio de fabricación, es algo lógico pues es el instante en el que el hardware está en buen estado o incluso recién vendido. No obstante, cuando aumentamos el tiempo, llegará un instante en el que el índice de fallos aumenta exponencialmente.

(Los nombres de las partes de las gráficas son así por muy raro que parezca)

Con respecto a la imagen del Software, disponemos de una curva idealizada pues no debe haber factores medio ambientales que deterioren el software, comenzando igual que el hardware, debería llegar a estabilizarse. 
No obstante, esto no es así, la curva real inicia como se prevee pero llega un momento donde se deben producir cambios a medida que se detectan fallos. El punto de cambio es importante pues puede producir efectos colaterales iniciando de nuevo la curva y repitiendo el proceso.
Es importante notar que, a medida que aumenta el tiempo, los fallos se producen con mayor índice, esto refleja el deterioro.

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
    + Aplicaciones Web: es un software centrado en redes que agrupa una amplia gama de aplicaciones.
    + Software de Inteligencia artificial: implementa algoritmos no numéricos para resolver problemas complejos de tratar computacionalmente o con análisis directo.

- Estudiando el destinatario:
    + Para distribución o también llamados genéricos: son sistemas autónomos producidos por una organización de desarrollo y vendidos en el mercado disponibles para cualquier cliente que pueda comprarlo.
    + Usuario final o hecho a medida: son los sistemas desarrollados por una empresa especialmente para un cliente particular.

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
1. Fase de definición: tiene como principal objetivo definir qué se desarolla y como principales tares tiene:
    + Ingeniería de sistemas
    + Planificación de proyectos
    + Ingeniería de requisitos
Nosotros nos centraremos en la ingeniería de requisitos.

2. Fase de construcción: tiene como principal objetivo determinar cómo se va a desarrollar el producto(software) definido en la fase de definición y tiene como principales tareas:
    + Diseño del software
    + Generación del código
    + Prueba del software
Nos centraremos en la primera y la tercera, la segunda la dejamos para otra asignatura.

3. Fase de evolución: forma parte de una fase de operación donde el producto ya está entregado, debemos determinar qué puede o va a cambiar. Como tareas tiene:
    + Corrección
    + Adaptación
    + Mejora
    + Prevención
Esta fase es también llamada fase de mantenimiento. Además, dispone del mayor esfuerzo pues el 45% aproximadamente del esfuerzo se dedica a los cambios de los requisitos del usuario.

Durante el proceso de producción pueden surgir una serie de problemas que pueden ser de varios tipos:
- Generados por fallos en la comunicación entre las personas, ya sea con el cliente como con los propios compañeros de equipo. Puede ser incluso, que este tipo de problemas de comunicación con el cliente nos obligue a aprender un nuevo campo de investigación. Además, el cliente puede no conocer elementos o tecnicismos que usemos; por tanto, hay que tener cuidado con el vocabulario que usamos.
- Generados por el incumplimiento de la planificación; normalmente antes de definir y construir un producto software debemos hacer una planificación que contengan aspectos como el tiempo empleado por actividad, personal necesario, préstamos... Siendo sinceros, suelen no cumplirse, como solución no se debe proponer la **horda mongoliana**, es decir, incrementar el número de personal a tutiplén, esto incrementa los fallos por comunicación y puede retrasar más el desarrollo del producto.
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
- B. Bohem(1976): Aplicación prática del conocimiento científico en el diseño y construcción de programas de computadora y la documentación asociada y requerida para el desarrollo, operación y mantenimiento del programa.
- IEEE (1993): Aplicación de un enfoque sistemático, disciplinado y cuantificable al desarrollo, operación y mantenimiento del software; es decir, aplicación de la ingeniería al software.

### Terminología usada en ingeniería del software

Daremos una serie de términos que no deben confundirse, pues son totalmente diferentes entre sí pese a usarse en el mismo entorno. Estos aspectos son:
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
En este apartado veremos varios aspectos relacionados con las distintas etapas que recorre el producto hasta ser un producto disponible a la venta.

### Concepto de proceso de desarrollo
Veremos algunas definiciones:
- **Proceso de desarrollo del software**: se define como el conjunto de actividades, acciones y tareas que se realizan cuando va a crearse un producto o sistema software; en definitiva, es el marco donde se va a trabajar. Se diferencia del método en que no busca un objetivo, el método es algo que usamos para desarrollar o hacer una actividad.
- **Actividad**: son una serie de elementos abstractos con los que se busca alcanzar un objetivo amplio y se aplica sin importar el dominio de aplicación, tamaño del proceso o complejidad. Un ejemplo de esto es comunicarse con los usuarios. Habrá dos tipos:
    + Estructural: decimos que una tarea es estructural cuando están dedicadas a obtener el producto. Estas actividades serán las mismas independientemente del producto a desarrollar y son las siguientes: **Comunicación** (hablar con el cliente para conocer los objetivos y requisitos), **planificación** (definir el plan del proyecto en el que se describen todo tipo de riesgos, recursos necesarios, productos obtenidos y se programan las actividades, acciones y tareas), **modelado** (representar el producto mediante modelos del sistema propuesto junto con la solución o soluciones apropiadas), **construcción** (general el código y probarlo) e **implementación** (entregar al cliente y recibir la evaluación del mismo).
    + Sombrilla: se llaman así porque cubren todo el proceso y pueden aparecer en cualquier otro tipo de actividad realizada durante el proceso, de hecho no siempre tienen que aparecer en un proyecto. Son varias: **Siguimiento y control del proyecto** (evaluar el progreso y lo compara con el plan del proyecto para ver si se está cumpliendo), **gestión de riesgos** (evaluar los riesgos que pueden afectar al resultado del proyecto o la calidad del producto), **aseguramiento de la calidad** (comprobar el cumplimiento de los aspectos de calidad esperados), **revisiones técnicas** (evaluar los productos para descubrir y eliminar errores), **medición** (definir mediciones del proceso y del producto para entregar software que cumpla con las encesidades del cliente), **gestión de la configuración** (destionar los efectos de cambio a lo largo del proceso), **gestión de reutilización** (definir los critarios para la reutilización del producto de trabajo y establece los mecanismos para obtener componentes reutilizables) y **preparación y producción del producto de trabajo** (actividades requeridas para crear productos de trabajo).
- **Acción**: es un conjunto de tareas que generan un producto de trabajo, es decir, una serie de tareas relacionadas entre sí que nos dan un objetivo sobre el que trabajar.
- **Tarea**: son aspectos que se centran en un objetivo pequeño, pero bien definido que produce un resultado tangible. Una prueba de unidad consiste en probar cada una de las partes de forma individual, otra tarea podría ser unificar dichas partes.

### Modelo de proceso
Hay dos tipos de modelo de proceso:
#### Modelo genérico
Se divide en varias partes:
- Estructura del proceso: la estructura del proceso está formada por cada una de las atividades, acciones y tareas que forman parte de un proceso, reside dentro de un marco de trabajo que define su relación con el proceso en sí. 

No obstante, hay que tener en cuenta que se pueden desarrollar actividades sombrilla en cada parte del proceso.

 <div>
<p style='text_align:center;'>
<img src=./imagenes/modgen.png alt="Error" width=500px>
</p>
</div>

Además, cada actividad del marco de trabajo está formada por un conjunto de acciones de ingeniería. Donde cada acción de ingeniería del software está definida por un conjunto de tareas
- Flujo del proceso; este aspecto describe la forma en que se organizan las actividades estructurales, además de las tareas y acciones que ocurren dentro de cada actividad estructural con respecto a la secuencia de uso; los más usuales son:
<div>
<p style='text_align:center;'>
<img src=./imagenes/flujos.png alt="Error" width=500px>
</p>
</div>

Dentro de estas imágenes, cada flecha determina un paso posible a dar, cuando se toma una flecha se da por terminada, por ahora aunque dependerá del flujo usado, la etapa dejada atrás.

La idea de esto es que dentro de una actividad realmente podemos dar muchas vueltas , no solo en cada etapa del flujo sino en cada una de las actividades de la etapa.
- Acciones y tareas de actividades estructurales: 
    + **obtención de requisitos**: indagar para obtener información sobre qué es lo que debe realizar el software; es una acción fundamental pues es aquella que nos permite conocer el problema.
    + **estimación y planificación del proyecto**: estimar el tiempo y los costes de desarrollo software.
    + **análisis de requisitos**: analizar el problema a resolver, documentar qué debe hacer el sistema software; también es una etapa fundamental pues permitirá a los usuarios o compañeros conocer qué es lo que hay que conseguir.
    + **diseño**: en esta fase buscaremos la solución al problema describiendo los componentes, relaciones y funciones que dan la solución al problema.
    + **implementación**: crear el código. 
    + **prueba del software**: debemos validar el producto, es decir, que haga lo que se ha pedido; y por otro lado, revisar o verificar el producto, lo cual consiste en comprobar que algo funciona correctamente.
    + **evaluación y aceptación**: evualuar el producto y conseguir la aceptación por parte de los interesados del producto.
    + **entrga y asistencia**: sistema operando y asistencia para su funcionamiento correcto.

#### Modelo prescriptivo
Es un modelo específico que cumple las características del modelo genérico y definen un conjunto predefinido de elementos del proceso y un flujo de trabajo que será predecible. 

Además, buscan la estructura y el orden en el desarrollo de software. Por último, las actividades y tareas ocurren de manera secuencial con alineamientos definidos para el proceso.

Hay algunos aspectos de estos modelos que no son determinísticos pues dependiendo del producto a desarrollar serán apropiados para cambios.

##### Modelo en cascada(o ciclo de vida clásico)
 <div>
<p style='text_align:center;'>
<img src=./imagenes/modcas.png alt="Error" width=500px>
</p>
</div>
Dispone de una estructura secuencial y flujo de proceso lineal. No obstante, presenta una serie de problemas como la falta de adaptación de proyectos reales al flujo secuencial, la dificultad de indicar todos los requisitos de forma explícita al principio de un proyecto, la no disposición de una versión funcional de los programas hasta etapas avanzadas del proyecto o la poca detección de errores hasta que se revise el programa funcional.

##### Modelo de prototipos
Como su nombre indica trabajamos con prototipos; donde un prototipo es una representación limitada de un producto, se usa para probar opciones de diseño y entender mejor el problema y sus posibles soluciones. 

Siguen el siguiente esquema:
<div>
<p style='text_align:center;'>
<img src=./imagenes/modpro.png alt="Error" width=500px>
</p>
</div>
Cabe recalcar que un prototipo no contiene todos los requisitos del usuario, o no suele hacerlo. Por tanto, es claro que dispone de un funcionamiento limitado en cuanto a su capacidad, confiabilidad o eficiencia.
    
Realmente el prototipo nos va a servir para recabar los requisitos del usuario, algo rápido que no sea muy perfeccionado ni perfectamente diseñado. Es una especie de esbozo del proyecto que nos servirá para recaudar información por parte del usuario que probará este prototipo y nos dará su evaluación.
    
Este modelo se usa para facilitar la obtención y validadción de requisitos, estudios de viabilidad, propuestas de soluciones o diseños alternativ@s y en casos muy concretos nos servirán como producto final, pero cabe recalcar que el prototipo no debe ser el producto final. 

Además, su uso vendrá determinado por el tipo y complejaidad de la aplicación, características del cliente o disponibilidad de herramientas para su construcción.
    
No obstante, tiene una serie de inconvenientes como crear falsas expectativas por parte del cliente e incluir decisiones del diseño del prototipo pasen a formar parte del producto final  por falta de tiempo, por ejemplo.

##### Modelos evolutivos
Son muchos y todos son iterativos; surgen debido a la existencia de tiempo de entrega muy limitado, la necesidad de facilitar la incorporación de cambios o la necesidad de satisfacer al usuario. 
    
En definitiva, estos modelos se basan en crear versiones que vayan mejorándose, nosotros a las versiones las llamaremos incrementos. No obstante, cada versión es un producto terminado y operativo.

Son modelos que afrontan los riesgos lo antes posible (en la siguiente versión), retroalimentan al usuario de forma constante con mejoras (lo cual lo satisface), permite un mayor manejo de la complejidad pues se dan pasos cortos y sencillos, permiten que una mejora dentro de una versión se use en las siguientes (incluso se pueden eliminar) y, por último, involucran continuamente al usuario pues el usuario valida el producto en cada versión.

Un ejemplo de modelo es el **Modelo de Boehm**:

<div>
<p style='text_align:center;'>
<img src=./imagenes/boehm.png alt="Error" width=500px>
</p>
</div>

En este ejemplo, hay que entender que el tiempo dedicado aumenta en cada fase segúnnos alejamos del inicio.

Como mayores características de estos modelos, nos encontramos que está centrado en el análisis de riesgos haciendo uso de su construcción de prototipos para su estudio, la espiral puede continuar una vez finalizado todo el proceso y entregado el producto, es un enfoque adecuado para el desarrollo de sistemas a gran escala.

Por otro lado, también dispone de inconvenientes como la falta de adaptabilidad a la complejidad o al tipo de sistema; así como el requerimiento de un equipo de desarrollo con gran experiencia en el análisis de riesgos.

### Proceso unificado

El proceso unificado es el que usaremos nosotros en clase y es un proceso evolutivo que sigue el siguiente esquema de 5 etapas antes de cada versión o incremento:

<div>
<p style='text_align:center;'>
<img src=./imagenes/procun.png alt="Error" width=500px>
</p>
</div>

Las fases son las siguientes:
- Concepción: comprende la parte de comunicación y parte de planificación. En ella se lleva a cabo la comunicación y la planificación dcon el cliente; ademá, los requisitos fundamentaes se describen a través de casos de uso que describen las características y funciones de cada clase principal de usuarios. Por último, la planificación identifica recursos, evalúa riesgos importantes y define un calendario preliminar para los incrementos de software.
- Elaboración: comprende la fase de planificación restante y diseño. Conlleva los siguientes aspectos:
    + Incorpora las actividades de planificación y modelado del modelo genérico.
    + Se refinan y expanden los casos de uso.
    + Incluye cinco perspectvas del software: el modelo de casos de uso, de análisi, de diseño, de implementación y de despliegue, esto último se refiere a cosas más técnicas y físicas.
    + Modificaciones al plan determinado.
- Construcción: coincide con la etapa de construcción. Conlleva los siguientes aspectos:
    + Incorpora la actividad de construcción definida para el modelo genérico.
    + Las características y funciones requeridas para el incremento de software se implementan en código fuente.
    + Se diseñan y ejecutan pruebas unitarioas para cada componente y se llevan a cabo actividades de integración.
    + Se emplean casos de uso para derivar pruebas de aceptación.
- Transición: está contenida en el final de la actividad de construcción genérica y el inicio de la  actividad de implementación. Conlleva los siguientes aspectos:
    + Se proporciona el software y la documentación a los usuarios finales para la prueba beta; esto es, proporcionar el software al público auqnue no esté terminado al completo para recibir una evaluación del público.
    + La retroalimantación del usuario reporta los defectos y cambios del sistema.
    + El incremento de software se convierte en una versión de software utilizable.
- Producción: coincide con la actividad de implementación dle modelo genérico. Conlleva los siguientes aspectos:
    + Se supervisa el uso continuo del software.
    + Se proporciona soporte para el entorno operativo.
    + Se envían y evalúan informes de defectos y solicitudes de cambios.

### Desarrollo ágil

Es uno de los modelos que está surgiendo ahora; no obstante, tiene seguidores y haters a partes iguales. 

Este modelo surgió como búsqueda de cumplir tiempos, evitar derramas de dinero y pérdida de poder monetario.

Pero, aún no sabemos qué es la agilidad; para nosortos será el principal impulso que conlleva la preponderancia del cambio y tiene una serie de consecuencias:  
- Fomento de estructuras y actitudes de equipo que faciliten la comunicación.
- Hace incapié en la entrega rápida de software operacional.
- Resta importancia a los productos de trabajo intermedios.
- Adopta al cliente como parte del equipo de desarrollo-
- Un plan de proyecto debe ser flexible.

Por último, diremos qu eun proceso es ágil cuando:
- Sea adaptable para gestionar la imprevisibilidad.
- La adaptabilidad sea incremental.
- Requiera retroalimetación del cliente.
- Los incrementos de software deban entregarse en períodos cortos.
- El enfoque interactivo permita al cliente evaluar el incremento de software.
