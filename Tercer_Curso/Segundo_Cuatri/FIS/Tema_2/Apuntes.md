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
- Identificar y documentar las necesidades del cliente. Es decir, conocer con exactitud lo que necesitar el cliente.
- Analizar la viabilidad de las necesidades. A veces el cliente necesita algo que es demasiado costoso o poco escalable luego es necesario este estudio de la viabilidad para "pararle los pies". La pregunta clave es: ¿Dispongo de los elementos necesarios para proporcionar lo que quiere el cliente?
- Negociar una solución razonable. Relacionado con lo anterior, puede que no sea viable hacerlo a la escala que el cliente quiere pero puede conseguirse a menor escala.
- Crear un documento que describa un software que satisfaga las necesidades. Debe contener todo aquello que se necesita para crear el producto; entre otras cosas necesita: la lista estructurada de requisitos, el diagrama de casos de uso, el modelo de análisis(diagrama conceptual, diagrama de secuencia del sistema)...
- Analizar y validar el documento. Se trata de comprobar que lo que se ha especificado en el documento se correponde correctamente con lo que ha pedido el usuario, es decir, comprobar que hemos hecho lo que el cliente pide.
- Controlar la evolución de las necesidades.

Por tanto, la ingeniería de requisitos es el proceso de construcción de una **Especificación de Requisitos** en el que partiendo de especificaciones iniciales se llega a especificaciones finales *completas*, *documentadas* y *validadas*.

### Problemas de la ingeniería de requisitos

Algunos problemas, aunque son muchos, son:
- La complejidad del problema. El aumento de los problemas es directamente proporcional con esto.
- La forma de identificar los requisitos por parte del cliente. Puede que el cliente no conozca completamente sus necesidades o no sepa comunicar sus necesidades.
- Dificultades de comunicación entre desarrolladores y cliente.
- Dificultades de comunicación en el equipo de desarrollo.
- Requisitos que no se pueden obtener del cliente y de los usuarios. Para resolver este problema vamos a usar técnicas etnográficas, estos requisitos tienen que ver con la forma de trabajar del usuario; consiste en el que el programador observará al cliente y obtendrá información de esa situación.
- Naturaleza cambiante de los requisitos. Es algo imprevisible, siempre estarán en mayor o menor frecuencia.

Es importante recalcar que ninguna otra parte del desarrollo del producto afecta tanto al avance del producto como la comunicacion si se lleva a cabo de manera incorrecta. Es decir, debemos tener mucho hincapié en esta fase pues son los cimientos de todo lo que se va a construir.

### Concepto de requisito

Este concepto tiene varias definiciones posibles:
- Condición o capacidad que debe tener un producto software para resolver una necesidad expresada por un usuario.
- Representación en forma de documento de una capacidad o condición que debe tener un producto software. Ciertamente es equivalente a la anterior, simplemente se hace más hincapié en el desarrollo de un documento escrito donde aparecen estas condiciones.
- Característica de un producto software que es condición para su aceptación por parte del cliente. 
- Propiedad o restricción, determinada con precisión, que un producto software que debe satisfacer.

Todas estas definiciones son equivalentes.

### Propiedades de los requisitos

Por tanto, podemos concliur que para que los requisitos sean de calidad, es decir, sirvan durante el desarrollo del producto deben tener las siguientes cualidades, aunque hay más:
- Completos, es decir, todos los aspectos del sistema están representados en el modelo de requisitos, se puede entender como el concepto de completitud.
- Consistencia, es decir, no deben haber contradicciones entre requisitos.
- No ambigüedad, es decir, el lenguaje natural usado para la descripción de los mismos debe ser lo más claro posible.
- Corrección, es decir, deben representar exactamente al sistema que el cliente necesita y que le desarrollador construirá.
- Realismo, es decir, deben poderse implementar con la tecnología y presupuesto disponible.
- Verificación; consiste en que ese puedan diseñar pruebas para comprobar que el sistema satisface los requisitos.
- Trazabilidad; debe ser posible hacer un seguimiento de cada requisistos que permita conocer su estado en cada momento del desarrollo.
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
- **Funcionales**: Son los que describen la interacción entre el sistema y su entorno, indicando la manera en que éste reaccionará ante determinados estímulos, es decir, especifican funciones que el sistema, o componente del sistema, debe ser capaz de llevar a cabo.

Nota: Los requisitos funcionales suelen venir especificados a través de verbos de acción.

Estos requisitos son los que más adelante se transformarán en funciones de nuestro código, es decir, serán las funcionalidades del sistema. Por tanto, todo lo que se refiera a necesidades qu eluego se van a traducir en funciones van a ser de este tipo.

- **No funcionales**: describen cualidades o restricciones del sistema que no se relacionen de forma directa con el comportamiento funcional del mismo. Los requisitos de este tipo no son necesidades que representen funciones del sistema, sino que son restricciones que estamos imponiendo a la ejecución o funcionamiento del sistema. 

Estos requisitos pueden entenderse como limitaciones sobre servicios y funciones que ofrece el sistema, suelen aplicarse al sistema como un todo y como ejemplos tenemos:
+ Restricciones de los tipos de soluciones que se pueden tomar.
+ No describen funciones sino propiedades.
+ Son los encargados de garantizar la calidad del software.
+ Pueden ser requisitos del producto de la organización o externos.

Algunas dificultades para determinarlos son:
+ Las metodologías no proporcionan herramientas ni formas de obtener de manera directa su obtención. A diferencia de los funcionales que nos los proporciona el cliente en entrevistas puede que este tipo de requisitos no se consigan de forma clara.
+ Suelen aparecer al estudiar los posibles diseños.
+ Aumentan la complejidad del diseño.
+ Uso del lenguaje natural para su especificación.

En definitiva, cubrirán cuestiones tecnológicas o de rendimiento.

- **De información**: describen necesidades de almacenamiento de información en el sistema. 

### Clasificación FURPS+

Se basa en una clasificación estándar de los requisitos **no** funcionales:
- Funcionalidad: en este caso se encuentran los requisitos no funcionales que están asociados a algún requisito funcional.
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
1. **Estudio de viabilidad**, es una etapa previa que hay que hacer antes de todo pues nos va a permitir saber si es posible desarrollar el producto. En esta tarea se va a dar respuesta a la pregunta sobre si es conveniente realizar el desarrollo del sistema.
<div>
<p style='text_align:center;'>
<img src=./imagenes/rvi.png alt="Error" width=150px>
</p>
</div>


Una de las cosas importantes sobre esta etapa es saber si el software que se va a desarrollar va a producir muchos más problemas que beneficios.

Esta tarea, se obtendrá un *informe* de viabilidad que va a determinar el avance o no del proyecto.

2. **Obtención de requisitos**. Una vez que el estudio de viabilidad ha resultado positivo pasamos al trabajo con los clientes y usuarios para: 
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

3. **Análisis de requisitos**. En esta tarea, partiendo de la lista de requisitos e información proporcionada por el usuario podremos realizar la tarea más importante de todas que presenta como objetivos:
    - Detección de conflictos entre los requisitos, pues a pesar de conocer los requisitos puede que no conozcamos que sus dominios se intersequen.
    - Profundización en el conocimiento del sistema.
    - Establecimiento de las bases para el diseño.
    - Construcción de modelos abstractos, ya sean dinámicos o estáticos.
Esta tarea se puede ver como un ciclo de subtareas: 
<div>
<p style='text_align:center;'>
<img src=./imagenes/are.png alt="Error" width=400px>
</p>
</div>

4. **Especificación de requisitos**. Consiste en hacer una representación de los requisitos en base al modelo creado en la etapa anterior, haciendo uso de herramientas y estándares o manuales de usuario.

Los productos que se generan en esta fase son:
- Modelo arquitectónico para el cual vamos a usar los diagramas de paquetes.
- Modelo estático para el cual usaremos el diagrama de clases aunque el modelo conceptual no este modelo.
- Modelo dinámico para el cual vamos a usar el diagrama de secuencia junto a los contratos.
<div>
<p style='text_align:center;'>
<img src=./imagenes/ere.png alt="Error" width=150px>
</p>
</div>

5. **Revisión de requisitos**. Una vez que ya tenemos el documento de especificación de requisitos vamos a realizar las siguientes tareas:
    - Validación; que consiste en comprobar que los requisitos documentados representen el problema,
    - Verificación; que consiste en comprobar que la representación es correcta.
Este proceso de revisión es un proceso continuo durante todo el desarrollo, es decir, es una tarea que nunca termina.
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

Aunque parece un poco, trivial hay que delimitar el sistema en cada uno de los diagramas de casos de uso, para ello lo haremos mediante un rectángulo. Dentro de él aparecerán todos los casos de uso y fuera de él, los actores. 

Para representar las interacciones de los actores con el sistema se usarán líneas.

<div>
<p style='text_align:center;'>
<img src=./imagenes/interacciones.png alt="Error" width=500px>
</p>
</div>

### Actores

Los entendemos como abstracciones de entidades externas al sistema que interactúan directamente con él. Tienen las siguientes características:
- Especifican roles que adoptan esas entidades externas cuando interactúan con el sistema.
- Una entidad puede desempeñar varios roles simultáneamente a lo largo del tiempo.
- Un rol puede ser desempeñado por varias entidades, serán nombres cortos y representativos.

Para representarlos usaremos lo siguiente:

<div>
<p style='text_align:center;'>
<img src=./imagenes/actor.png alt="Error" width=200px>
</p>
</div>

Hay dos tipos de actores:
- **Principales**: son los encargados de iniciar un caso de uso del sistema, evidentemente interactúa con el caso de uso. Es aquel que, aunque principal y secundario forman parte del caso de uso, toma la iniciativa para que se active el caso de uso. 
- **Secundarios**: Sólo se encargan de interactuar con el caso de uso pero no son capaces de activarlo.

Además, pueden ser varias entidades:
- **Personas**: tienen el rol de usuario en el sistema.
- **Dispositivos de entrada/salida**: Sensores o mediadores, siempre que sean independientes de la acción de un usuario.
- **Sistemas informáticos externos**: Con los que el sistema se tiene que comunicar, por ejemplo, en casos de uso de sistemas de pago, tiene que haber externo al sistema algo que autorice esta transacción.
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

<div>
<p style='text_align:center;'>
<img src=./imagenes/relacionactores.png alt="Error" height=500px width=300px>
</p>


En este caso, en el que un actor generaliza a otro, las interacciones del generalizador se trasladan a las interaccioens del generalizado pero no es necesario representarlas; es algo que se entiende por la herencia. La redundancia en los diagramas será penalizada.

### Casos de uso

Un caso de uso especifica una secuencia de acciones, incluidas secuencias variantes y de error, que un sistema o susbsistema puede realizar al interactuar con actores externos.
<div>
<p style='text_align:center;'>
<img src=./imagenes/casodeuso.png alt="Error" width=200px>
</p>
</div>

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

<div>
<p style='text_align:center;'>
<img src=./imagenes/plantillactor.png alt="Error" width=500px>
</p>
</div>

Con respecto a las relaciones cabe destacar que se puede quedar en blanco pues solo representa las relaciones entre actores, si no hay quedará vacía.

### Descripción de casos de uso

En una descripción de un caso de uso se deben tener en cuenta que debemos cubrir los siguientes aspectos:
- El inicio: quién o qué lo produce.
- El fin: cuándo se produce y por qué.
- La interacción: qué mensajes intercambian los actores y el sistema.
- El objetivo: para qué se usó o qué intenta el caso de uso.
- Cronología y origen de las interacciones.
- Repeticiones de comportamiento: qué acciones se repiten.
- Situaciones opcionales o de error: qué situaciones alternativas se presentan en el caso de uso.

La descripción de los casos de uso se pueden hacer dependiendo de dos cosas:
- Del procesamiento
    + Básico; descripción general del procesamiento, daremos el nombre, los casos de uso con los que se relaciona, una breve descripción del caso de uso...
    + Extendido; descripción de la secuencia completa de acciones entre actores y sistema.
- Del nivel de abstracción (debe aparecer en la descripción básica)
    + Esencial; expresado de forma abstracta, contiene poca tecnología y pocos detalles de diseño.
    + Real, expresado en base al diseño actual, en el que aparecen las relaciones con la interfaz del usuario, suelen contener tecnicismos.

[NOTA]: Es importante que todas las descripciones que vamos a hacer en la practica van a ser esenciales pues no vamos a usar ningún tecnicismo. El que ponga que una descripción es real quita toda la práctica.

Para realizar la descripción básica seguimos la siguiente plantilla:

<div>
<p style='text_align:center;'>
<img src=./imagenes/basicauso.png alt="Error" width=500px>
</p>
</div>

En el caso de los actores, debemos determinar quién es el iniciador, asicomo si es primario o secundairio.

[NOTA]: En la práctica que hacemos serán todos básicos.

Tras la descripción básica, se realiza una descripción extendida donde trabajaremos con escenarios, cada uno será una secuencia específica y concreta de acciones e interacciones entre los actores y el sistema objeto de estudio. 

Normalmente, cada caso de uso tendrá dos escenarios, uno básico y otro ocasionado por situaciones de error, también llamados flujos alternoso escenarios secundarios.

Debemos añadir a la descripción básica de cada caso de uso la siguiente plantilla:

<div>
<p style='text_align:center;'>
<img src=./imagenes/extendidauso.png alt="Error" width=500px>
</p>
</div>

En el caso de los flujos alternos:

<div>
<p style='text_align:center;'>
<img src=./imagenes/alternouso.png alt="Error" width=500px>
</p>
</div>


### Relaciones en el modelo de casos de uso

Hablando un poco más sobre las relaciones en los modelos de casos de uso estudiando varios aspectos.

Las relaciones en un modelo de casos de uso tienen las siguientes finalidades:
- Organizar los casos de uso.
- Mejorar la comprensión.
- reducir la redundancia del texto.
- Mejorar la gestión de los documentos generados.

Además, las relaciones pueden ser de varios tipos según la siguiente tabla:
| **Tipo de Relación** | **Definición** | **Notación** |
|----------------------|---------------|-------------|
| **Asociación** | Comunicación entre un actor y un caso de uso en el que participa. | `———————` |
| **Inclusión** | Inserción de comportamiento adicional dentro del caso de uso base que explícitamente hace referencia al caso de uso de inclusión. | `<<include>>` <br> `--------------->` |
| **Extensión** | Inserción de fragmentos de comportamiento adicional sin que el caso de uso base sepa de los casos de uso de extensión. | `<<extend>>` <br> `--------------->` |
| **Generalización** | Relación entre un caso de uso general y otro más específico, que hereda y añade características al caso de uso general. | `———————▷` |

[NOTA]: recomienda no usar mucho la relacion de extensión

#### Inclusión

Es una relación de dependencia entre dos casos de uso que permite incluir el comportamiento de un caso de uso en el flujo de otro caso de uso. Al caso de uso que incluye se le denomina caso de uso base y al incluido caso de uso de inclusión. 

El caso de uso base se ejecuta hasta que se alcanza el punto en el que se encuentra la referencia al caso de uso de inclusión, momento en el que se pasa la ejecución a dicho caso. Cuando este se termina, el control regresa al caso de uso base. Además, para que le caso de uso base esté completo es necesario que contenga a los casos de uso de inclusión.

El caso de uso que está incluido es utilizado completamente por el caso de uso base; además, el caso de uso base no está completo sin el caso de uso de inclusión. Como añadido, puede ser compartido por varios casos de uso base y no es opcional sino necesario para que tenga sentido.

#### Extensión

La relación de extensión es una relación de dependencia que especifica que el comportamiento del caso de uso base puede ser extendido por otro caso de uso (caso de uso de extensión) bajo determinadas condiciones.

El caso de uso base declara uno o más puntos de extensión que son como anclajes en los que se pueden añadir nuevos comportamientos. A diferencia de la relación de inclusión, no sabe nada de los casos de uso de extensión y **sí** que estará completo sin sus extensiones; de hecho, no tienen numeración en el flujo de eventos en el flujo del caso de uso base.

Por su parte, el caso de uos de extensión define segmentos de inserción que pueden insertarse en los puntos de anclaje cuando se cumpla una determinada condición. En este caso, el caso de uso de extensión no podrá tener sentido de forma separada al caso de uso base.

<div>
<p style='text_align:center;'>
<img src=./imagenes/extension.png alt="Error" width=500px>
</p>
</div>

Si disponemos de condiciones podemos expresarlo de la siguiente manera:

<div>
<p style='text_align:center;'>
<img src=./imagenes/extensioncond.png alt="Error" width=500px>
</p>
</div>

Para indicar que se poroduce una extensión en la descripción del curso de eventos de un caso de uso, implementamos puntos de extensión:

<div>
<p style='text_align:center;'>
<img src=./imagenes/extensiondescrip.png alt="Error" width=500px>
</p>
</div>

La representación más usada para esta relación es la extendidda pero sin poner las condiciones, eso ya se one en la descripción de los casos de uso. Ademñás, no tienen idenficador pues no son casos de uso por sí mismos, es decir, sólo extenderán un caso de uso base.

La descripción de los casos de uso de extensión aparece a continuación de la plantilla del curso normal de eventos. Y se rige por la plantilla siguiente:

<div>
<p style='text_align:center;'>
<img src=./imagenes/extensioncase.png alt="Error" width=500px>
</p>
</div>

En el caso de que el caso de uso de extensión tenga más de un segmento, es decir, más de una acción para solucionar la extensión; en nuestor ejemplo, una vez puesta una multa, puede elegir pargarla o no. En este caso, habrá dos segmentos, uno hasta tomar la decisión y otro despues de tomarla.

<div>
<p style='text_align:center;'>
<img src=./imagenes/extensionmult.png alt="Error" width=500px>
</p>
</div>

##### Heurística de uso de relaciones
Una idea clara para usar una relación u otra puede ser:
- Usaremos la relación de **inclusión** para comportamientos que se compartan entre dos o más casos de uso, o bien para separar un caso de uso en subunidades.
- Usaremos la relación de **extensión** para comportamientos excepcionales, opcionales o que rara vez ocurran. En definitiva, suelen ser para ramas de ejecución alternas, es decir, no son de la ejecución de la traza principal

#### Generalización

Es una relación entre un caso de uso general, que llamaremos caso de uso padre, y otros más especializados, que llamaremos casos de uso hijos.

En el caso de los casos de uso hijo:
- Heredan todas las características del caso de uso general.
- Pueden añadir nuevas características.
- PUeden anular o reescribir características del caso de uso general, a excepción de relaciones, puntos de extensión y precondiciones.

En los diagramas de UML las relaciones de generalización siguen una notación similar a la notación usada para la generalización de actores:

<div>
<p style='text_align:center;'>
<img src=./imagenes/generalizacionUML.png alt="Error" width=500px>
</p>
</div>

Y para la descripción del caso de uso generalizado, usamos la plantilla de los casos de uso general, es decir, no se siguen ninguna plantilla especial.

En el caso de uso padre, si hay casos de uso inclusión debemos ponerlos en las referencias. En un caso de uso hijo, en las referencias deberán aparecer los casos de uso padre de los que disponga, indicando que lo son.

#### Recomendaciones de uso de las relaciones

Hay que tener siempre en cuenta que el modelado de casos de uso se realiza para que el cliente lo entienda mejor. Luego algunos consejos son:
- Usar la relaciones entre casos de uso cuando simplifiquen el modelo.
- Un sencillo modelo de casos de uso es preferible a uno con demasiadas relaciones ya que son más fáciles de entender.
- El uso de muchas relaciones de inclusión hace que se tengan que ver más de un caso de uso apra tener una idea completa.
- Las relaciones de extensión son complejas y difíciles de entender por la comunidad de usuarios o clientes.
- La generalizaciń de casos de uso debería evitarse a menos que se utilicen casos de uso apdre abstractos.

### Construcción del modelo de casos de uso

Hayq ue seguir una serie de pasos, resumen de todo lo anterior que hemos visto. Cabe aclarar, que no tienen por qué seguirse todos en caso de que no sea necesario:
1. Identificar actores, principales y secundarios.
2. Identificar los principales casos de uso de cada actor identificando sus objetivos y necesidades:
    - Cuáles son las tareas principales de cada actor.
    - ¿Qué información del sistema debe adquirir, producir o cambiar?
    - ¿Tiene que informar el actor sobre cambios ocurridos en el exterior del sistema?
    - ¿Qué información desea adquirir el actor del sistema?
    - ¿Desea el actor ser informado de cambios producidos en ele sistema?
3. Identificar nuevos casos de uso a partir de los existentes; analizar las siguientes situaciones:
    - Variaciones significatibas de lso casos de uso existentes.
    - Acciones opuestas, es decir, estudiar si existen casos de uso opuestos a los existentes.
    - Accioens opuestas deben realizarse antes o después de casos de uso existentes.
4. Hacer los diagrams de casos de uso y el diagrama de paquetes en el que se muestren la relacioens lógicas entre diagramas de casos de uso.
5. Hacer la descipción básica de cada caso de uso, usando la plantilla.
6. Definir prioridades y seleccionar casos de uso primarios.
7. Hacer la descripción extendida de cada caso de uso, completando la descripción básca con la plantilla extendida.
8. Realizar los diagramas de actividad.
9. Desarrollar prototipos de la interfaz de usuario.

### Otros aspectos del modelo de casos de uso

Vamos a estudiar dos de ellos:
- Diagramas de paquetes: es un diagrama UML usado para describir la estructuración de un sistema en base a agrupaciones lógicas. También muestra las dependencias entre agrupaciones. Se usa en el modelo de casos de uso para agrupar de forma lógica los diferentes diagramas de casos de uso. 
<div>
<p style='text_align:center;'>
<img src=./imagenes/diagpaq.png alt="Error" width=500px>
</p>
</div>
La relación que viene representada por cada una de las flechas es la relación << use >> que siginifica que tienen casos de uso en común, independientemente de hacia donde apunte la flecha.

-  Diagramas de actividad: es un diagrama UML para la descripción del comportamiento que tienen un conjunto de tareas. Se usan para representar los flujos de actividades de los procesos de negocio de una empresa y los flujos de acciones de uno o varios casos de uso de forma gráfica.

<div>
<p style='text_align:center;'>
<img src=./imagenes/diagacti.png alt="Error" width=500px>
</p>
</div>

<a id='2.4'><a/>
## 2.4.Análisis y especificación de requisitos

### 2.4.1.Introducción

#### El proceso de análisis
El análisis de requisitos es la fase de la ingeniería de requisitos en la que se examinan los requisitos para delimitarlos y definir exactamente cada uno de ellos. COmo objetivos fundamentales tenemos:
- Detectar y resolver conflictos entre requisitos.
- Delimitar el software y establecer con qué elementos externos interacciona.
- Elaborar los requisitos del sistema para obtener, a partir de ellos, los requisitos del software.
- Profundizar en el conocimiento del sistema, lo que conlleva a realizar modelos; aportarán facilidad de comprensión de los requisitos para los desarrolladores y una base para el diseño.
- Aumentar la formalización del conosimiento existente sobre el sistema para facilitar el mantenimiento.

#### Objetivo principal del análisis

<div>
<p style='text_align:center;'>
<img src=./imagenes/objan.png alt="Error" width=500px>
</p>
</div>

El objetivo principal del análisis es refinar, estructurar y describir los requisitos para conseguir una comprensión más precisa, más fácil de mantener y que ayude a estructurar el sistema completo.

Es importante rastrear los requisitos de usuario a travñes de los requisitos del software.

#### Diferencias entre modelos

| MODELO DE CASOS DE USO                                              | MODELO DEL ANÁLISIS                                                                 |
|---------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| Lenguaje del cliente                                                | Lenguaje del desarrollador                                                         |
| Vista externa del sistema estructurado en casos de uso             | Vista interna del sistema estructurado en clases y subsistemas                     |
| Contrato Clientes/Desarrolladores                                   | Con vistas a la solución                                                           |
| Puede contener redundancias e inconsistencias entre requisitos      | No debe contenerlas                                                                |
| Captura la funcionalidad del sistema                                | Esboza cómo llevar a cabo esta funcionalidad (primera aproximación a la arquitectura) |
| Se definen casos de uso que luego serán analizados en mayor profundidad | Define relaciones entre casos de uso                                           |

#### Actividades del análisis

Disponemos de 5 actividades:
- Clasificación de los requisitos: consiste en establecer un conjunto de categorías y situar cada requisito en ellas.
- Priorización de los requisitos: consiste en determinar la importancia relativa de cada requisito en relación con los demás.
- Modelo conceptual: representamos los requisitos con un lenguaje o notación que puedan comprenderlo todos.
- Situación de los requisitos en la arquitectura del sistema: deberemos establecer qué elementos del sistema software van a satisfacer los distintos requisitos. Puede que en esta actividad podamos descubrir nuebos requisitos.
- Negociación de los requisitos: consiste en detectar y resolver problema, definir de manera precisa los límites del sistema y cómo éste debe interaccionar con su entorno.

#### Especificación de requisitos

Obtendremos un documento que debe contener una completa descripción del sistema a desarrollar. Siguiendo un estándar impuesto por la *IEEE*, una especificación debe ser completa, verificable, consistente, modificable, susceptible de permitir seguimientos, utilizable durante las fases de operación y mantenimiento y no debe contener ambigüedades.

### 2.4.2.Análisis orientado a objetos

El análisis Orientado a Objetos examina y representa los requisitos desde la perspectiva de los objetos que se encuentran en el dominio del problema.

Hay una gran variedad de métodos AOO(Análisis orientado a objetos), pero todos ellos se centran en la obtención de modelos:
- Estáticos o de estructura
- Dinámicos o de comportamiento

Usaremos el lenguaje *UML* para representar los modelos.

Hay tres motivos fundamentales para usar *AOO*:
- Los tñerminos usados en los modelso están cercanos a los del mundo real.
    + Facilita y mejora la obtención de requisitos.
    + Acerca el espacio del problema al espacio de la solución.
- Se modelan tanto elementos y propiedades estáticas como dinámicas del ámbito del problema.
- Se manejan conceptos comunes durante el análisis, diseño e implementación del software.
    + Mejor transición entre fases.
    + Facilita el desarrollo iterativo.
    + Difumina la barrera entre el qué y el cómo.

<div>
<p style='text_align:center;'>
<img src=./imagenes/diap11.png alt="Error" width=500px>
</p>
</div>

### 2.4.3.Obtención del modelo estático

Es un modelo conocido por varios nombres como *diagrama de conceptos*, *diagrama del análisis*, *diagrama conceptual*, *Modelo conceptual*, *Modelo de dominio*; en el que se representan los principales conceptos del dominio del problema, sus propiedades y relaciones entre ellos. 

Esta obtención sería imposibles is no disponemos del modelo de casos de uso, pues es la base para obtener esta información para realizar el modelo.

Usaremos los *diagramas de clases de UML*, en el que podrá haber:
- Clases que se corresponderán con los conceptos del dominio del problema.
- Asociaciones entre conceptos.
- Generalizaciones de conceptos.
- Atributos de los conceptos.

Es importante concoer que aunque vayamos a usar los diagramas de clases de *UML*, el resultado de estos diagramas no serán diagramas de clases pues no habrá métodos ni navegabilidad.

#### Pasos a seguir

***Identificar e incorporar conceptos***

En este paso deberemos:
- Identificar los conceptos. Nosotros trabajaremos este aspecto estudiando los sustativos o frases nominales, esto nos dará una idea sobre los conceptos. No obstante, identificar conceptos tiene una serie de probelmas como son:
    + No se puede hacer de forma mecánica, es decir, no existe un algoritmo que nos pueda determinar cuáles son los sustantivos que podrán desembocar en un concepto.
    + Ambigüedad en el lenguaje natural, como la existencia de sinónimos o frases hechas.
- Seleccionar los conceptos relevantes en el dominio del problema. Para lo que podemos seguir los siguientes elementos:
    + Términos sinónimos.
    + Relaciones.
    + Atributos de conceptos o relaicones.
    + Fuera del ámbito del problema.
- Representarlos, como clases, en el diagrama de conceptos.

Para conseguir el objetivo de este paso podemos seguir las siguientes estrategias:
- Establecer una lista de categorías de conceptos y rellenarla a partir de la información de la qu edisponemos.
- Encontrar los términos que se corresponden con sustantivos o frases nominales, éstos van a ser candidatos a conceptos.

***Identificar y representar asociaciones***

Antes definimos lo que es una **asociación**, es una conexión siginificativa y relevante entre conceptos.

En este paso deberemos:
1. Identificar las posibles asociaciones. Usaremos la lista de categoriía de relaciones entre conceptos que aparece a continuación como guía:

| Categoría                                                             | Ejemplos                                       |
|----------------------------------------------------------------------|------------------------------------------------|
| A es una parte física de B                                           | Ala – Avión                                    |
| A es una parte lógica de B                                           | Tramo de vuelo – Ruta de vuelo                 |
| A está contenido físicamente en B                                    | Asiento – Avión                                |
| A está contenido lógicamente en B                                    | Vuelo – Programa de vuelo                      |
| A es una descripción de B                                            | Descripción de vuelo – Vuelo                   |
| A es un elemento de línea en una transacción B                       | Trabajo de mantenimiento – Mantenimiento       |
| A conoce / introduce / registra / presenta / captura B               | Reserva – Lista de pasajeros                   |
| A es miembro de B                                                    | Piloto – Tripulación                           |
| A es una sub-unidad organizacional de B                              | Unidad de mantenimiento – Compañía aérea       |
| A usa o dirige B                                                     | Piloto – Avión                                 |
| A se comunica con B                                                  | Agente de reserva – Pasajero                   |
| A se relaciona con una transacción B                                 | Pasajero – Billete                             |
| A es una transacción relacionada con otra transacción B              | Reserva – Cancelación                          |
| A está contiguo a B                                                  | Ciudad – Ciudad                                |
| A es propiedad de B                                                  | Avión – Compañía aérea                         |
2. Representarlas en el diagrama y seleccionar las que sean válidad.
[TODO]: seguir el proceso:
En esta parte aparecerán relaciones repetidas (mismos conceptos relacionados), pero no tiene por qué ocurrir que las relaciones sean semánticamente iguales.
3. Asignarles nombre.
4. Identificar la multiplicidad.

***Identificar e incorporar generalizaciones de concetos***

En este paso deberemos:
1. Identificar posibles generalizaciones.
    + A partir de la descripción del problema y de las clases conceptuales identificadas, encontrar clases conceptuales con elementos comunes.
    + Definir las relaciones de superclase y subclase.
2. Validar las estructuras encontradas. Para lo cual comprobaremos que cada subclase potencial estará de acuerdo con:
    + La regla del 100%(todo lo que está definido en la supercalse estará en la subclase).
    + La regla "es-un"(un elemento de la subclase es un elemento de la superclase).
3. Representarlas en el modelo conceptual. Algunas directrices para obtenerlas son:
  - Para crear subclases a partir de subclases deberemos comprobar que:
    + La subclase tiene atributos adicionales de interés.
    + La subclase tiene asociaciones adicionales de interés.
    + La subclase funciona, reacciona o se manupula de manera diferente a la superclase o a alguna subclase.
  - Para crear superclases a partir de subclases potenciales.
    + Cuando las subclases presentan variaciones de un concepto similar.
    + Las subclases cumplen con las reglas del "100%" y "es-un".
    + Todas las subclases tiene el mismo atributo que se puede factorizar en la superclase.
    + Todas las subclases tienen la misma asociación que se puede factorizar en la superclase.

Cabe destacar que este tipo de relaciones como son las generalizaciones se puedene entender como relaciones de "herencia" con muchas comillas, donde cada subclase es una especialización de una supercalse y las superclases son generalizaciones de subclases.

***Identificar e incorporar atributos de conceptos***

En este paso deberemos:
1. Identificar atributos desde:
    - Casos de uso y lista de requisitos.
    - Otras fuentes de información.
2. Representarlos en el diagrama, en los conceptos o en las relaciones que correspondan.

Los atributos de los que hablamos y tratamos como válidos son de dos tipos:
- Primitivos o valores puros de datos.
- No primitivo.

[TODO]: diap 38

***Estructurar el modelo***

Lo haremos mediante diagramas de paquetes, de manera que un paquete será una división del modelo agrupando conceptos que tienen una fuerte relación entre sí(facilita el modelado y la posterior representación mediante diagramas).

[TODO]: Repasar esto (diap 41)

Para estructurar el diagrama de conceptos:
- Elementos que están en el mismo área de interés
- Están juntos en una jerarquía de clases.
- Participan en los mismos casos de uso.
- Están fuertemente asociados.

### 2.4.4.Obtención del modelo de comportamiento

COnsiste en un estudio adicional del dominio del problema en el que se añaden los requisitos funcionales; podemos seguir la frase :"¿Qué hace el sistema sin explicar cómo lo hace?"

<div>
<p style='text_align:center;'>
<img src=./imagenes/modcomp.png alt="Error" width=500px>
</p>
</div>

Para representar los comportameinteos usaremos diagramas de secuencia de *UML* en los qu ese muestran cómo los eventos generados por los actores provocan la ejecución de una operación por el sistema, siendo éste visto como una caja negra.

<div>
<p style='text_align:center;'>
<img src=./imagenes/dss.png alt="Error" width=500px>
</p>
</div>

[TODO]: mensaje irina

Para elaborar un diagrama de secuencia seguimos los siguientes pasos:
1. Identificar los actores que inician las operaciones.
2. Asignar un nombre a todo el sistema.
3. Identificar y nombrar la operaciones principales del sistema, a partir de las descripciones de los casos de uso.
4. Determinar los parámetros de las operaciones.
5. Representarlas en el diagrama de secuencia del sistema.
6. Incluir las operaciones en la clase que identifica a todo el sistema.

***Identificar actres y asignar un nombre a todo el sistema***
 [TODO]: Imagen diap 47

 La profesora recomienda hacer un diagrama de secuencia del sistema para diagrama de caso de uso donde en cada uno de los sistemas debe aparecer una acción para cada caso de uso. No obstante, es probable que un caso de uso use varias acciones lo cual no es un inconveniente.

***Identificar operaciones y parámetros, representarlas***

[TODO]: imagen diap 48

Cabe destacar que las acciones se representan como si fueran métodos de clase con sus paréntesis y las respuestas (lo que se devuelve por el sistema) con una línea discontinua.

EN este momento, no es necesario que las operaciones que haya en el diagrama de secuencia disponga de un número de orden pues eso realmente no significa que sea ese orden el orden global.

***Incluir las operaciones en la clase del sistema***

[TODO]: imagen diap 49
Es importante saber que el único objeto que debe aparecer en el diagrama de secuencia es el sistema; a esto se le suma que no deben haber interacciones entre actores y no se debe representar en un diagrama de secuencia del sistema.

#### 2.4.4.5.Contratos

Un contrato se define como un documento que describe lo que una operación se propone lograr, sin decir cómo se conseguirá. Cumple dos requisitos:
- Define la especificación de una operación sin entrar en su implementación.
- Suele redactarse con un estilo declarativo.

[TODO]: Imagen diap 52 

- Nombre: nombre completo de la acción de la que hablamos.
- Responsabilidad: descripción de lo que se va a hacer.
- TIpo: sólo hay que poner el nombre de la clase que representa al sistema, en general, hacia qué ojeto va la operación.
- Notas: es opcional y solo son aclaraciones.
- Excepciones: debemos poner hechos que harán que la acción deje de ejecutarse.
- Salida: es lo que devuelve la operación como respuesta.
- Precondiciones: son condiciones que se deben de cumplir antes de que empiece a ejeutarse; pues si no se cumplen, la operación no debe cumplirse.

Para elaborar un contrato se siguen las siguientes restricciones:
- El nombre de la operación viene del DSS correspondiente.
- Comenzar con las responsabilidades, describiendo informalmente el propósito de la operación.
- Continuar con las poscondiciones y finalizar con las demás secciones, especialmente con las precondiciones y excepciones.
- Las poscondiciones deben escribir los cambios de estado de un sistema no sus acciones; estos son:
    + Creación y destrucción de objetos.
    + Creacción y destrucción de enlaces.
    + Modificación de atributos.
- Los objetos y enlaces que se pueden crear y destruir son los del modelo conceptual.
- Las poscondiciones deben expresarse mediante una frase verbal en pretérito.

***Poscondiciones del contrato***

Para especificar las poscondiciones, hay que identificar en el diagrama de conceptos los objetos que intervienen en la operación.

[TODO]: imagen diap 55

***Últimas aclaraciones***
- Poscondiciones siempre en pasado.
- Operaciones en poscondiciones (**SOLO**)
    - Crear/eliminar objetos/enlaces.
    - Modificar/actualizar atributos.
- Excepciones y precondiciones **NO** se repiten.
