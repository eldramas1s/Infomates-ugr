#2. Ingeniería de requisitos
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
<img src=./imagenes/rvi.png alt="Error" width=150px>
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
<img src=./imagenes/ore.png alt="Error" width=100px>
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
<img src=./imagenes/are.png alt="Error" width=400px>
</p>
</div>

4. Especificación de requisitos. Consiste en hacer una representación de los requisitos en base al modelo creado en la etapa anterior, haciendo uso de herramientas y estándares o manuales de usuario.

Los productos que se generan en esta fase son:
- Modelo arquitectónico para el cual vamos a usar los diagramas de paquetes.
- Modelo estático para el cual usaremos el diagrama de clases aunque el modelo conceptual no este modelo.
- Modelo dinámico para el cual vamos a usar el diagrama de secuencia junto a los contratos.
<div>
<p style='text_align:center;'>
<img src=./imagenes/ere.png alt="Error" width=150px>
</p>
</div>
5. Revisión de requisitos. una vez que ya tenemos el documento de especificación de requisitos vamos a realizar las siguientes tareas:
- Validación que consiste en comprobar que los requisitos documentados representen el rpoblema,
- Verificación que consiste en comprobar que la representación es correcta.
Este proceso de revisión es un proceso continuo durante todo el desarrollo, es decir, es una tarea qu enunca termina.
<div>
<p style='text_align:center;'>
<img src=./imagenes/rre.png alt="Error" width=150px>
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

### Proceso de obtención de requisitos
Es la fase inicial de la ingeniería de requisitos, y está encaminada a la obtención del conjunto de requisitos del sistema a desarrollar. Como objetivo buscamos obtener:
- Las necesidades y características del sistema.
- Un informe que englob el alcance del sistema o producto.
- La lista de los participantes.
- Descripción del entorno.
- Lista de los requisitos agrupados por su funcionalidad junto con las restricciones que se aplicarán a cada uno.

Esta fase se divide en varias subfases que se tratarán a continuación siguiendo el sistema de adjudicación de proyectos.

**Descripción inicial del problema**

Pese a que en las diapositivas se trata con un ejemplo, aquí aparecerán anotaciones que se hayan dicho en clase.

**Proceso a seguir**

Se describen las pautas a seguir para realizar el proyecto o producto.

**Restricciones a tener en cuenta**

Se determinan las restricciones que se deben cumplir en el producto o en el proceso de su desarrollo.

Tras eso se realiza la obtención de los objetivos, requisitos funcionales y requisitos no funcionales.

**Tareas recomendadas**

Además se plantean una serie de tareas que son recomendables hacer, por el siguiente orden:
1. Obtener información sobre le dominio del problema y el sistema actual; como resultado se obtiene una introducción al sistema y el glosario de términos. Para ello, se consiguen los siguientes aspectos:
    - Conocer el vocabulario propio.
    - Conocer las características principales del dominio.
    - Recopilar información sobre el dominio.
    - Facilitar la comprensión de las necesidades del sistema.
    - Favorecer la confianza del cliente.
2. Preparar las reuniones de elicitación y negociación; necesitaremos realizar una actividad creítica pues ni el usuario ni nosotros sabemos lo que necesitamos. Para ello, se consiguen los siguientes aspectos:
    - Identificar a los implicados.
    - Conocer las necesidades de clientes y usuarios.
    - Resolver posibles conflictos.
3. Identificar y revisar los objetivos del sistema; aquí se redactarán los objetivos que se desean alcanzar una vez que el software esté en explotación; además, si el sistema es muy complejo se podría necesitar realizar una jerarquía de objetivos donde de cada objetivo se puede describir:
    - Su importancia.
    - Su urgencia.
    - Su estado durante el desarrollo.
    - Su estabilidad.
4. Identificar y revisar los requisitos de información; donde se recopila toda la información relevante para el cliente que debe gestionar y almacenar el sistema software. De cada requisito se puede describir:
    - Objetivos y requisitos asociados.
    - Descripción del requisito.
    - Contenido.
    - Tiempo de vida.
    - Ocurrencias simultáneas.
    - Su importancia, urgencia, estado y estabilidad.
5. Identificar y revisar los requisitos funcionales. Se determina qué es lo que debe hacer el sistema y existen varias notaciones para su descripción. De cada requisito:
    - Objetivos y requisitos asociados.
    - Secuencia de acciones.
    - Frecuencia de uso de la función especificada.
    - Rendimiento.
    - Su importancia, urgencia, estado y estabilidad.
6. Identificar y revisar los requisitos no funcionales. Consiste en obtener las restricciones aplicables a los requisitos de información y a los requisitos fucnionales; para cada requisito se puede incluir:
    - Descripción.
    - Objetivos y requisitos asociados.
    - Su importancia, urgencia, estado y estabilidad.

Para captarlos puede ser interesante resolver una serie de preguntas en cada uno de los tipos de requisitos no funcionales. Para conocerlas, [pulse aquí](./Presentacion2_2.pdf) para acceder al archivo, busque las transparencias 24 y 25.
Como resultado obtenemos la lista estructurada de requisitos.

### Técnicas de obtención de requisitos

Con estas técnicas vamos a ser capaces de obtener los requisitos. Ha varios tipos de métodos:
- Tradicionales:
    + Entrevistas individuales y en grupo.
    + Realización de cuestionarios.
    + Taller de requisitos; en lugar de realizar una entrevista se realiza un taller grupal.
    + Análisis de protocolos.
    + Recopilar y estudiar los documentos e informes generados; puede que le sistema tenga atos docmentados que nos puedan servir de guía para obtener los requisitos.
- Otros métodos:
    + Técnicas orientadas a los puntos de vistas.
    + Escenarios y casos de uso.
    + Análisis etnográfico.

Para muchos de ellos necesitamos comunicación con los usuarios o implicados en el desarrollo del sistema; los llamaremos _StakeHolders_, estos son cualesquiera que directamente o indirectamente se beneficie del sistema a construir o que posea información sobre su funcionamiento o desarrollo, concretamente:
- Responsables de su desarrollo.
- Con interés financiero.
- Responsable de la gestión del sistema.
- Con interés en su utilización.

### Técnicas de entrevistas

Consisten en técnicas encaminadas a obtener información sobre el sistema mediante el diálogo con los expertos en el dominio del problema. 

Se conseguirán realizando entrevistas que las hay varios tipos:
- Estructuradas o no estructuradas.
- Formales o no formales.

Una entrevista tiene varias fases:
1. Preparación de la entrevista
    + Estudiar el dominio del problema.
    + Seleccionar a los entrevistados.
    + Determinar el objetivo y contenido de la entrevista.
    + Planificar las entrevistas.
2. Realización de la entrevista.
    + Apertura; se realiza una breve presentación y un informe sobre los objetivos de la entrevista.
    + Desarrollo: Realización de la entrevista propiamente dicha.
    + Terminación: Recapitulación de la información obtenida.
3. Análisis de la entrevista.
    + Reorganización de la información.
    + Contraste con otras informaciones.
    + Documentar la entrevista.
    + Enviar copia al entrevistado.
    + Preparar nuevas entrevistas.

Aunque las entrevistas pueden ser un gran recurso para obtener información sobre el producto, presentan una serie de limitaciones:
- Requiere mucho tiempo.
- La información que se obtiene depende de las preguntas realizadas así como de las respuestas obtenidas del cliente.
- La dificultad de resolución de las colisiones entre respuestas de clientes es bastante alta.
- Lo que los entrevistados dicen no es siempre lo que los entrevistados hacen.
- Aunque no es tan grave, algunos entrevistados pueden tener mayor timidez a la hora de establecer una conversación presencial.

No obstante, esta técnica presenta ciertos beneficios:
- La información obtenida es de primera mano.
- La exigencia de detalle la determina el entrevistador.
- Permite localizar áreas en las que profundizar.
- Los clientes se sienten involucrados en el desarrollo.
- Los clientes formulan problemas y pueden aportar soluciones.

### Técnicas de análisis etnográfico

Consiste en realizar un análisis del entorno en el que podria usarse el producto pedido por el usuario, es decir, no existen de forma aislada, sino que están inmersos en un contexto social y de organización. Por tanto, el contexto afecta a los requisitos.

Buscamos evaluar dos tipos de requisitos:
- Requisitos sociales y de organización.
- Requisitos reales y formales.
En ambos casos, buscamos emplear técnicas basadas en la observación de la forma de trabajo de los clientes y no en cómo el sistema los hace trabajar.

Hay varias formas de realizar este tipo de observaciones:
- Directas: donde el observador directamente está inmerso en el sistema.
- Indirectas: se realizan mediante el uso de entornos de observación.

Por último, estas técnicas son efectivas para dos tipos de requisitos:
- Los que se derivan de la forma en que trabajn realmente y no de cómo se han definido los procesos.
- Los que se derivan de la cooperación y el conocimiento de las actvidades de la gente.

No obstante, estas técnicas no proporcionan un enfoque completo sino que tiene que apoyarse en otras técnicas como diagramas de casos de uso, entrevistas y prototipados.

<a id='2.3'><a/>
## 2.3.Modelado de casos de uso

El modelado de casos de uso es una técnica de ingeniería de requisitos que permite varios aspectos:
- Delimitar el sistema a estudiar.
- Delimitar el contexto de uso del sistema.
- Describir el punto de vista de los usuarios del sistema.

Este modelo se usa en distintas etapas del desarrollo con el objetivo de:
- Obtener requisitos.
- Analizar y especificar requisitos.
- Como base para el proceso de diseño y su validación.
- Guiar el diseño de la interfaz de usuario y facilitar la construcción de prototipos.
- Validar el software y asegurar la calidad durante el proceso de desarrollo.
- Como punto de inicio de las ayudas en línea y el manual de usuario.

Los idagramas están compuestos por actores, casos de uso y relaciones entre:
- Actores
- Actores y casos de uso.
- Casos de uso.

Aunque parece un poco, trivial hay que delimitar el sistema en cada uno de los diagramas de caoss de uso, para ello lo haremos mediante un rectángulo. Dentro de él aparecerán todos los casos de uso y fuera de él, los actores. 

Para representar las interacciones de los actores con el sistema se usarán líneas.

[TODO]: imagen diap 5

### Actores

Los entendemos como abstracciones de entidades externas al sistema que interactúan directamente con él. Tienen las siguientes características:
- Especifican roles que adoptan esas entidades externas cuando interactúan con el sistema.
- Una entidad puede desempeñar varios roles simultáneamente a lo largo del tiempo.
- Un rol puede ser desempeñado por varias entidades, serán nombres cortos y representativos.

Para representarlos usaremos lo siguiente:

[TODO]: imagen diap 6

Hay dos tipos de actores:
- **Principales**: son los encargados de iniciar un caso de uso del sistema, evidentemente interactúa con el caso de uso. Es aquel que, aunque principal y secundario forman parte del caso de uso, toma la iniciativa para que se active el caso de uso. 
- **Secundarios**: Sólo se encargan de interactuar con el caso de uso pero no son capaces de activarlo.

Además, pueden ser varias entidades:
- **Personas**: tienen el rol de usuario en el sistema.
- **Dispositivos de entrada/salida**: Sensores o mediadores, siempre que sean independientes de la acción de un usuario.
- **Sistemas informáticos externos**: Con los que el sistema se tiene que comunicar, por ejemplo, en casos de uso de sistemas de pago, tiene qu ehaber externo al sistema algo que autorice esta transacción.
- **Temporizador o reloj**: Cuando se haco algo como respuesta a un evento de tiempo periódico o en un momento determinado, sin que haya un actor que lo active.

Para poder identificar a los actores podemos tratar de contestar las siguientes preguntas:
- ¿Quién y qué utiliza el sistema?
- ¿Qué roles desempeñan en la interacción?
- ¿Quién instala el sistema?
- ¿Quién o qué inicia y cierra el sistema?
- ¿Quién mantiene el sistema?
- ¿Qué otros sistemas interactúan con el sistema?
- ¿Quién o qué proporciona información al sistema?

Cabe destacar que no todos los implicados tienen que ser actores, de hecho, tampoco todos los actores tienen que ser implicados.

#### Relación entre actores

una relación entre actores expresa un comportamiento común entre actores, es decri, se relacionen de la misma forma con los mismos casos de uso. Como símil, se puede entender como herencia en programación orientada a objetos.

En este caso, en el que un actor generaliza a otro, las interacciones del generalizador se trasladan a las interaccioens del generalizado pero no es necesario representarlas; es algo que se entiende por la herencia. La redundancia en los diagramas será penalizada.

### Casos de uso

Un caso de uso especifica una secuencia de acciones, incluidas secuencias variantes y de error, que un sistema o susbsistema puede realizar al interactuar con actores externos.
[TODO]: imagen diap 11

Donde el nombre debe ser una frase verbal descriptiva y breve.

Dependiendo de la importancia de los casos de usos, hay da varios tipos:
- Primarios: son los mas importantes, probablemente se convertirán en funciones que se codifiquen en la primera versión. Es decir, el sistema no puede funcionar correctamente sin ellos.
- Secundarios: suelen ser procesos de error o poco comunes, suelen llamarse 'procesos internos' y no se codifican en las primeras versiones.
- Opcionales.

#### Características
Son las siguientes:
- Iniciados por un actor, que intercambian datos o control con el sistema a través de él.
- Descritos desde el punto de vista de los actores.
- Describen el proceso de alcance de un objetivo de uno o varios actores.
- Tienen una utilidad real y concreta para un actor.
- Acotan una funcionalidad del sistema, es importante entender que deben representar uno o varios requisitos funcionales; y no necesariamente debe ser un solo requisito funcional. Sin embargo, todos los requisitos funcionales deben estar representados en algún caso de uso.
- Describen un fragmento de la funcionalidad del sistema de principio a fin. Tienen que acabar y dar algún resultado.
- La documentación usa un lenguaje poco formal; no se debe hacer con pseudocódigo.

Para identificar los casos de uso podemos tratar de responder las siguientes preguntas:
- ¿Qué objetivos o necesidades tendrá un actor específico?
- ¿El sistema almacena y recupera información? Si es así, ¿qué actores activan este comportamiento?
- ¿Qué sucede cuando el sistema cambia de estado?¿Se notifica algún error?
- ¿Afecta algún evento externo al sistema?¿Qué se notificará sobre estos eventos?
- ¿Interactúa el sistema con algún sistema externo?
- ¿Genera el sistema algún informe?

### Descripción de actores

Para describir a los actores usaremos una plantilla del siguiente tipo:
[TODO]: imagen diap 16

Con respecto a las relaciones cabe destacar que se puede quedar en blanco pues solo representa las relaciones entre actores, si no hay quedará vacía.

### Descripción de casos de uso

[TODO]: diap 18

La descripción de los casos de uso se pueden hacer dependiendo de dos cosas:
- Del procesamiento
    + Básico; descripción general del procesamiento, daremos el nombre, los casos de uso con los que se relaciona, una breve descripción del caso de uso...
    + Extendido; descripción de la secuencia completa de acciones entre actores y sistema.
- Del nivel de abstracción (debe aparecer en la descripción básica)
    + Esencial; expresado de forma abstracta, contiene poca tecnología y pocos detalles de diseño.
    + Real, expresado en base al diseño actual, en el que aparecen las relaciones con la interfaz del usuario, suelen contener tecnicismos.

[NOTA]: Es importante que todas las descripciones que vamos a hacer en la practica van a ser esenciales pues no vamos a usar ningún tecnicismo. El que ponga que una descripción es real quita toda la práctica.

Para realizar la descripción básica seguimos la siguiente plantilla:
[TODO]: imagen diap 20

En el caso de los actores, debemos determinar quién es el iniciador, asicomo si es primario o secundairio.

[NOTA]: En la práctica que hacemos serán todos básicos.

Tras la descripción básica, se realiza una descripción extendida donde trabajaremos con escenarios, cada uno será una secuencia específica y concreta de acciones e interacciones entre los actores y el sistema objeto de estudio. 

Normalmente, cada caso de uso tendrá dos escenarios, uno básico y otro ocasionado por situaciones de error, también llamados flujos alternoso escenarios secundarios.

Debemos añadir a la descripción básica de cada caso de uso la siguiente plantilla:

[TODO]: imagen diap 23

En el caso de los flujos alternos:

[TODO]: imagen diap 24


### Relaciones en el modelo de caoss de uso

### Construcción del modelo de casos de uso

### Otros aspectos del modelo de casos de uso

<a id='2.4'><a/>
## 2.4.Análisis y especificación de requisitos

