# 2. Ingeniería de requisitos
---
## Índice
1. [Introducción al modelado de requisitos](#2.1)
2. [Obtención de requisitos](#2.2)
3. [Modelado de casos de uso](#2.3)
4. [Análisis y especificación de requisitos](#2.4)
---

<a id='2.1'><a/>
## 2.1.Introducción al modelado de requisitos

Como introducción y motivación estudiamos un poco el motivo de por qué es necesario este estudio de los requisitos; para ello, hablamos del informe **CHAOS**, que incluye un estudio sobre el conjunto de proyectos software que han concluido en el tiempo establecido con los presupuestos y personal planificados.

<div>
<p style='text_align:center;'>
<img src=./imagenes/chaos.png alt="Error" width=500px>
</p>
</div>

Los motivos principales por los cuales los proyectos no cumplieron los plazos son:
- Falta de información por parte de los usuarios. Es el motivo fundamental y consiste en que los usuarios que requieren el producto no se comunican bien con los profesionales. De esta forma, el desarrollador no conocerá lo que debe hacer.
- Especificación de requisitos incompleta. Ya veremos que la especificación será un documento general donde se encuentran los modelos de casos de uso y todos los requisitos necesarios.
- Continuos cambios de los requisitos. Provoca cambios en el sistema lo que retrasa el avance del proyecto.
- Pobres habilidades técnicas en la especificación de requisitos. Es decir, en la elaboración del documento de especificación no se usan las técnicas y conceptos adecuados.

Esto debe servir para introducir la ingeniería de requisitos que debe hacerse de forma adecuada.

### Ingeniería de requisitos

Se define el ingeniero de requisitos como aquella persona cualificada para usar técnicas y mecanismos adecuados para realizar las tareas relacionadas con:
- Identificar y documentar las necesidades del cliente. Es decir, conocer con exactitud lo que neceistar el cliente.
- Analizar la viabilidad de las necesidades. A veces el cliente necesita algo que es demasiado costoso o poco escalable luego es necesario este estudio de la viabilidad para "pararle los pies". La pregunta clave es: ¿Dispongo de los elementos necesarios apra proporcionarlo que quiere el cliente?
- Negociar una solución razonable. Relacionado con lo anterior, puede que no sea viable hacerlo a la escala que el cliente quiere pero puede conseguirse a menor escala.
- Crear un documento que describa un softweare que satisfaga las necesidades. Debe contener todo aquello que se necesita para crear el producto; entre otras cosas necesita: la lista estructurada de requisitos, el diagrama de casos de uso, el modelo de análisis(diagrama conceptual, diagrama de secuencia del sistema)...
- Analizar y validar el documento. Se trata de comprobar que lo que se ha especificado en el documento se correponde correctamente con lo que ha pedido el usuario, es decir, comprobar que hemos hecho lo que el cliente pide.
- Controlar la evolución de las necesidades.

Por tanto, la ingeniería de requisitos es el proceso de construcción de una **Especidificación de Requisitos** en el que partiendo de especificaciones iniciales se llega a especidicaciones finales *completas*, *documentadas* y *validadas*.

### Problemas de la ingeniería de requisitos

Algunos problemas, aunque son muchos, son:
- La complejidad del problema. El aumento de los problemas es directamente proporcional con esto.
- La forma de identificar los requisitos por parte del cliente. Puede que el cliente no conozca completamente sus necesidades o no sepa comunicar sus necesidades.
- Dificultades de comunicación entre desarrolladores y cliente.
- Dificultades de comunicación en el equipo de desarrollo.
- Requisitos que no se pueden obtener del cliente y de los usuarios. Para resolver este problema vamos a usar técnicas etnográficas, estos requisitos tiene que ver con la forma de trabajar del usuario; consiste en el que el programador observará al cliente y obtener información de esa situación.
- Naturaleza cambiante de los requisitos. Es algo imprevisible, siempre estarán en mayor o menor frecuencia.

Es importante recalcar que ninguna otra parte del desarrollo del producto afecta tanto al avance del producto como la comunicacion si se lleva a cabo de manera incorrecta. Es decir, debemos tener mucho hincapié en esta fase pues son los cimientos de todo lo que se va a construir.

### Concepto de requisito

Este concepto tiene varias definiciones posibles:
- Condición o capacidad que debe tener un producto software para resolber una necesidad expresada por un usuario.
- Representación en forma de documento de una capacidad o condición que debe tener un producto software. Ciertamente es equivalente a la anterior, simplemente se hace más hicapié en el desarrollo de un documento escrito donde aparecen estas condiciones.
- Característica de un producto software que es condición para su aceptación por parte del cliente. 
- Propiedad o restricción, determinada con precisió, que un producto software que debe satisfacer.

Todas estas definiciones son equivalentes.

### Propiedades de los requisitos

Por tanto, podemos concliur que para que los requisitos sean de calidad, es decir, sirvan durante el desarrollo del producto deben tener las siguientes cualidades, aunque hay más:
- Completos, es decir, todos los aspectos del sistema están representados en el modelo de requisitos, se pueden entender como el concepto de completitud.
- Consistencia, es decir, no deben haber contradicciones entre requisitos.
- No ambigüedad, es decir, el lenguaje natural usado para la descripción de los mismos debe ser lo más claro posible.
- Corrección, es decir, deben representar exactamente al sistema que el cliente necesita y que le desarrollador construirá.
- Realismo, es decir, deben poderse implementar con la tecnología y presupuesto disponible.
- Verificación; consiste en qu ese puedan diseñar pruebas para comprobar que el sistema satisface los requisitos.
- Trazabilidad; debe ser prosible hacer un seguimiento de cada requisistos que permita conoces su estado en cada momento del desarrollo.
- Identificables; cada requisito debe tener un identificador único que lo distinga y que permita referenciarlo sin ambigüedad, en cualquier punto del ciclo de vida del software.
- Cuantificabilidad, aunque es difícil de conseguir, es deseable que se pueda medir el grado de cumplimiento de un requisito en términos de uso.

Hay varios tipos de requisitos, pero puede depender del aspecto que midamos:
- Por el Ámbito:
    + Software
    + Hardware
    + Sistema
- Según la Audiencia:
    + Cliente
    + Usuarios (pueden ser los mismo que el cliente)
    + Desarrolladores
- Según el tipo(es la que más nos interesan):
    + No funcional
    + Funcional
    + De Información

### Tipos de requisitos según el tipo

Vamos a estudiar cada uno de los tipos de requisitos según el tipo:
- Funcionales: Son los que describen la interacción entre el sistema y su entorno, indicando la manera en que éste reaccionará ante determinados estímulos, es decir, especifican funciones que un sistema. o componente de un sistema, debe ser capaz de llevar a cabo.

Nota: Los requisitos funcionales suelen venir especificados a través de verbos de acción.

Estos requisitos son los que más adelante se transformarán en funciones de nuestro código, es decir, serán las funcionalidades del sistema. Por tanto, todo lo que se refiera a necesidades qu eluego se van a traducir en funciones van a ser de este tipo.

- No funcionales: describen cualidades o restricciones del sistema que no se relacionen de forma directa con el comportamiento funcional del mismo. Los requisitos de este tipo no son necesidades que representen funciones del sistema, sino que son restricciones que estamos imponiendo a la ejecución o funcionamiento del sistema. 

Estos requisitos pueden entenderse como limitaciones sobre servicios y funciones que ofrece el sistema, suelen aplicarse al sistema como un todo y como ejemplos tenemos:
    + Restricciones de los tipos de soluciones que se pueden tomar.
    + No describen funciones sino propiedades.
    + Son los encargados de garantizar la calidad del software.
    + Pueden ser requisitos del producto de la organización o externos.

Algunas dificultades para determinarlos son:
    + Las metodologías no proporcionan herrmientas ni formas de obtener de manera deirecta su obtención. A diferencia de los funcionales que nos los proporciona el cliente en estrevistas puede que este tipo de requisitos no se consigan de forma clara.
    + Suelen aparecer al estudiar los posibles diseños.
    + Aumentan la complejidad del diseño.
    + Uso del lenguaje natural para su especificación.
En definitiva, cubrirán cuestiones tecnológicas o de rendimiento.
- De información: describen necesidades de almacenamiento de información en el sistema. 
### Clasificación FURPS+

Se basa en una clasificación estándar de los requisitos no funcionales:
- Fiabilidad: en este caso se encuentran los requisitos no funcionales que están asociados a algún requisito funcional.
- Facilidad de uso: factores humanos, ayuda o documentación.
- Fiabilidad: Frecuencia de fallos, disponibilidad, capacidad de recuperación de un fallo y grado de previsión.
- Rendimiento: Tiempos de respuesta, productividad, precisión, velocidad de uso de los recursos...
- Soporte: Adaptabilidad, facilidad de mantenimiento, internacionalización, configurabilidad.
- Pseudorrequisitos o restricciones de diseño.
    + Implementación: limitación de recursos, lenguajes y herramientas...
    + Interfaz: restricciones impuestas para la interacción con sistemas externos.
    + Operación: gestión del sistema en su puesta en marcha y a nivel operacional.
    + Empaquetamiento: formas de distribución, restricciones de instalación...
    + Legales(son muy importantes): licencias, derechos de autor...

### Tareas de la ingeniería de requisitos
En este apartado vamos a estudiar varias tareas que están asociadas a la ingeniería de requisitos:
1. Estudio de viabilidad, es una etapa previa que hay que hacer antes de todo pues nos va a permitir saber si es posible desarrollar el producto. En esta tarea se va a dar respuesta a la pregunta sobre si es conveniente realizar el desarrollo del sistema.
<div>
<p style='text_align:center;'>
<img src=./imagenes/rvi.png alt="Error" width=500px>
</p>
</div>


Una de las cosas importantes sobre esta etapa es saber si el software que se va a desarrollar va a producir muchos más problemas que beneficios.

Esta tarea, dada una pequeña descripción del sistema va a producir un informe de viabilidad que va a determinar el avance o no del proyecto.

2. Obtención de requisitos. Una vez que el estudio de viabilidad ha resultado positiva pasamos al trabajo con los clientes y usuarios para: 
- Estudiar el funciamiento del sistema.
- Descubrir las necesidades reales.
- Consensuar los requisitos entre las distintas partes.
- Trabajo difícil apoyado por técnicas como entrevistas, escenarios, casos de usos, prototipos, análisis etnográficos...

Como productos generados de esta etapa tenemos:
- Documentos de entrevistas.
- Lista estructurada de requisitos.
- Diagramas de casos de uso junto a plantillas y diagramas de actividad.

<div>
<p style='text_align:center;'>
<img src=./imagenes/ore.png alt="Error" width=500px>
</p>
</div>

3. Análisis de requisitos. En esta tarea, partiendo de la lista de requisistos e información proporcionada por el usuario podremos realizar la tarea más importante de todas que presenta como objetivos:
- Detección de conflictos entre los requisitos, pues a pesar de conocer los requisitos puede que no conozcamos que sus dominios se intersequen.
- Profundización en el conoceimiento del sistema.
- Establecimiento de las bases para el diseño.
- Construcción de mosdels abstactos, ya sea dinámico o estático.
Esta tarea se puede ver como un ciclo de subtareas: 
<div>
<p style='text_align:center;'>
<img src=./imagenes/are.png alt="Error" width=500px>
</p>
</div>

4. Especificación de requisitos. Consiste en hacer una representación de los requisitos en base al modelo creado en la etapa anterior, haciendo uso de herramientas y estándares o manuales de usuario.

Los productos que se generan en esta fase son:
- Modelo arquitectónico para el cual vamos a usar los diagramas de paquetes.
- Modelo estático para el cual usaremos el diagrama de clases aunque el modelo conceptual no este modelo.
- Modelo dinámico para el cual vamos a usar el diagrama de secuencia junto a los contratos.
<div>
<p style='text_align:center;'>
<img src=./imagenes/ere.png alt="Error" width=500px>
</p>
</div>
5. Revisión de requisitos. una vez que ya tenemos el documento de especificación de requisitos vamos a realizar las siguientes tareas:
- Validación que consiste en comprobar que los requisitos documentados representen el rpoblema,
- Verificación que consiste en comprobar que la representación es correcta.
Este proceso de revisión es un proceso continuo durante todo el desarrollo, es decir, es una tarea qu enunca termina.
<div>
<p style='text_align:center;'>
<img src=./imagenes/rre.png alt="Error" width=500px>
</p>
</div>
Para facilitar la revisión disponemos de prototipos, simulaciones, revisiones automáticas, y herramientas.

### Actores 
Definimos como actores a aquellos roles que se pueden distinguir en el proceso de ingeniería de requisitos:
- Stakeholder; es cualquier persona que tenga una relación con el sistema.
- Ingeniero de requisitos.
- Analista de sistemas.
- Arquitecto de software, es el encargado de realizar el diseño.
- Documentalista.
- Diseñador de interfaces de usuario.
- Gestor de proyecto.
- Revisor.

<a id='2.2'><a/>
## 2.2.Obtención de requisitos


<a id='2.3'><a/>
## 2.3.Modelado de casos de uso


<a id='2.4'><a/>
## 2.4.Análisis y especificación de requisitos

