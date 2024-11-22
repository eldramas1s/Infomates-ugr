# 4.Nivel interno

## 4.1.Introducción

Nosotros hasta ahora hemos visto que una Base de Datos sirve para almacenar datos con un motivo concreto como motivo princial: la __consulta__ de la información que hemos almacenado.

Este hecho ocasiona una serie de consecuencias tanto en la organización lógica de los datos como en la organización física.

En este tema estudiaremos el __nivel interno__ teniendo en cuenta las siguientes características:

- Cuando realizamos una operación de forma lógica, esto se traduce a una seríe de operaciones a más bajo nivel dodne los operando son una serie de registros almacenados, realmente en la memoria del dispositivo,  en un sistema de almacenamiento externo.
- Provee al administrador de mecanismos para optimizar el almacenamiento y el acceso a los datos.
- Este nivel se encuentra implementado en el _SGBD_ salvo aquella parte que pertenece al nivel físico que es cedida al sistema operativo.

Hablando un poco más del nivel físico, destacamos las siguientes características.
- Se encuentra implementado en el __Sistema Operativo__ con llamadas al sistema y utilizando accesos a memoria que deberán minimizarse.
- Es el encargado de proporcionar al _SGBD_ una capa de abstracción sobre el hardware; de manera que, el _SGBD_ no percibe l acceso a los datos como una operación en memoria.
- Realiza el acceso a los medios de almacenamiento mediante llamadas a los servicios del sistema de archivos proporcionado por el _SO_; esto es lo que llamamos _llamadas al sistema_ referentes a la manipulación de memoria.

### Jerarquía de memoria

Tomaremos los siguientes criterios:
- Leyendo los nombres en orden decreciente de índice conseguimos:
    + Aumentar el coste.
    + Disminuir la cantidad de memoria de este tipo usada en los sistemas.
    + Disminuir el tiempo dedicado a acceder a un elemento de este tipo de memoria.
- Leyendo lso nombres en orden creciente de índice conseguimos:
    + Disminuir el coste.
    + Aumentar la cantidad de memoria de este tipo usada en los sistemas.
    + Aumentar el tiempo dedicada a acceder a un elemento de este tipo de memoria.

El orden es el siguiente:

1. Registros del dispositivo.
2. Memorias caché.
3. Memoria principal.
4. Memorias Flash.
5. Discos Magnéticos.
6. Cintas o Discos ópticos.

Como utilidad a explicar esta jerarquía, cabe destacar que los trs últimos niveles son los usados para almacenar la base de datos; pues al necesitar una gran cantidad de espacio que no sea volátil requerimos, por ejemplo _discos duros_.

Los tres primeros niveles son utilizados para minimizar los accesos a memoria externa que producen un gran retardo, es decir, la parte de la base de datos que está siendo usada en estos intantes es trasladada a la memoria principal con el fin de agilizar las operaciones.

### Memoria principal

Hablando un poco más sobre la memoria principal de un dispositivo es el dispositivo de almacenamiento primario de los ordenadores.

Como funcionalidad principal relacionada con las bases de datos dispone de hacer trabajos de caché de la porcion de la _BD_ de uso más reciente. Realizar trabajos de caché simplemente consiste en ser el elemento intermedio entre el almacenamiento secundario y las cachés: realmente, consiste en ubicar de forma temporal los datos afectados por las operaciones realizadas.

Para usar la memoria principal, el nivel interno del _SGBD_ debe oprimizar su uso pues, pese a ser rápida ya que acelera el procesamiento, es bastante cara. Además, como ya se ha comentado mucho, es volátil, entonces pierde su información una vez que deja de recibir señal eléctrica. 

Como resumen, el objetivo principal de la memoria principal en una _BD_ es reducir al máximo los accesos a memoria secundaria o externa.

### Discos Duros

Todos conocemos lo que es un __disco duro__, pero no todos conocemos que es el más usado para almacenar _BD_. Está formado por una serie de discos magnéticos donde cada cara se divide en pistas concéntircas para conseguir dividir cada pista concéntrica en sectores que representarán la unicada mínima de almacenamiento en el sistema, los __bloques__.

Al conjunto de pistas concéntricas del mismo radio en todas las caras se le suele llamar _cilindo_.

![El disco duro](.imagenes/DD.png)

En cada acceso a disco se pierde un tiempo, que ocasiona una pérdida de rendimiento si el acceso es muy frecuente.

Dicho tiempo se conoce con el nombre de __tiempo de acceso__ que es el tiempo medio transcurrido entre una isntraucción y la obtención de la información pedida. Este tiempo se divide en la suma de:
    
- __Tiempo medio de búsqueda__, es el tiempo que tarda el brazo del disco duro en posicionarse en la pista.
- __Tiempo de latencia rotacional__, es el tiempo medio que tarda el brazo del disco duro en posicionarse en el sector una vez posicionado en la pista.

En ocasiones, el acceso podrá ser erróneo añadiendo a este tiempo el __tiempo medio de fallo__.

## 4.2.Método de acceso a la _BD_

Los _SGBD_ montan una forma para hacer el trabajo con los dispositivos de almacenamiento, cada uno su forma, luego no está generalizada; no obstante, tomaremos una idea general.

Como idea general, se usan los siguientes elementos:
- Archivo almacenado: es un registro donde se encuentran una serie de páginas de archivo.
- Páginas del archivo almacenado: son una agrupación de registros que representan bloques del sistema operativo.
- Bloques del _SO_: son los que se corresponden con los bloques del dispositivo de almacenmaiento; estos pueden estar formados por distintos criterios:
<a id="organizacion"></a>    
    + Tomar las tuplas de la misma tabla juntas, de esta manera todo está muy organizado, como si fueran tablas, muy intuitivo pero que en ocasiones no será lo más eficiente.
    + Agrupando según las operaciones más frecuentes, con esto nos referimos a que los datos se almacenen de manera que al aplicar una operación el trabajo computacional sea menor; esto será útil cuando dicha operación es la operación más repetida de la base de datos.

![Esquema de correspondencia](./imagenes/esqcorr.png)

Las técnicas de corespondencia entre los loques de _SO_ y los bloques de almacenamiento pueden ser desde paginación, hasta técnicas mucho más avanzadas.

Todo el acceso está dividido en dos partes:
1. Realizada por el _SGBD_:
    - El _SGBD_ se encarga de solicicitar al __Gestor de archivos__ una página almacenada con cualquier fin de consulta o modificación.
    - El gestor de Archivos se comunica a través del gestor de Disco con la siguiente parte. Una vez recibe respuesta de esta parte, le pasa al _SGBD_ l apágina qu eha solicitado.
2. Realizada por el _SO_:
    - El Gestor de Disco recibe una petición reenviada por le Gestor de Archivos implementando al comunicación con el _SGBD_. 
    - El Gestor de archivos se encarga de traducir la petición de bloque que ha recibido a una operación de E/S a Disco para la _BD_.
    - La _BD_ devuelve los sectores de disco que se han pedido y están almacenados.
    - El Gestor de Disco recibe los bloques y los pasa al Gestor de Achivos que los enviará al _SGBD_.

![Esquema de acceso](./imagenes/acceso.png)

Se puede ver claramente, que es un 'toma y daca' entre el _SGBD_ y el _SO_ donde, en este último, es el Gestor de Disco quien se pelea con el hardware para recibir lo que se busca.

Todo esto puede resultar un lío pues, cómo sabe el gestor de almacenamiento cual es el bloque de disco asociado a un registro. Esto se consigue con una referencia del registro que es el __RID__; este elemento contiene un puntero a la página donde se encuentra el registro solicitado y un _offset_ que representa la posición dentro de la página del registro que se ha pedido.

### Requisitos de los accesos

A la hora de hacer un acceos debemos tener en cuenta una serie de información:
- Cada registro almacenado dispone de:
    + Una cabecera qu eindica el número y tipo de columnas que lo integran.
    + La información que contiene en las columnas.
- Las páginas o bloques de la _BD_ deben tener un tamaño múltiplo de los bloques del _SO_ que será la mínima unidad de E/S.
- Para recuperar un registro almacenado hay que determinar la página de la _BD_ que lo contiene, es decir, recuperar los bloques de disco que la integran.
- Hay que organizar la estructura de almacenamiento y lso métodos de acceso, de forma que se optimice la interacción con los dispositivos de almacenamiento secundario.
- Siempre hay que pensar en qu elas operaciones de E/S al almacenamiento secundario deben ser las mínimas.

### 4.2.1.Gestor de Disco del SO

Este elemento dentro de la comunicación entre el _SGBD_ y la _BD_ es el encargado de realizar presicsamente el puente entre estas dos estructuras de gran importancia:

- Organiza los datos en arvchivos, que realemtne son conjutnos de bloques, de _SO_.
- NO necesariamente debe haber un único Gestor de Disco por base de datos.
- Es el encargado de gestionar el espacio libre.
- Traduce la petición de bloques del _SO_ en operaciones de E/S.

Además de estas funcionalidaes tiene las funcionalidades básicas de un elemento de este tipo dentro de un _Sistema de Archivos_(_filesystem_).

### 4.2.2.Gestor de Archivos del _SGBD_

Es un componente del _SGBD_ que se encarga de:

- Realizar la comunicación con el _SO_ sobre los bloques que se quieren pedir, es decir, traduce la página solicirtada en el bloque del _SO_ pedido.
- [Organiza los datos](#organizacion) de manera que s eminimice el tiempo de recuperación, es decir, minimizar las E/S.

Como funciones básicas implementa:

- Creación de archivos almacenados asociándoles un conjunto de páginas o bloques de la _BD_.
- Eliminar archiivos almacenados.
- Recuperar registros almacenosdos de un archivo almacenado; para ello, el _sGBD_ propiciona el _RID_ del registro de manera que solo hay que obtener en memoria la página que contiene el registro para extraerlo.
- Añadir un nuevo registro almacenado a un archivo almacenado. Para ello hay que localizar la página de la _BD_ más apropiada de las pertenecientes al archivo almacenado. En caso de qu eno se pudiera, se solicita una nueva página y se devuelve al _SGBD_ el _RID_ nuevo.
- Eliminar un registro de un archivo almacenado; donde es necesario recuperar la página de la _BD_ que contiene ducho registro y marcar el espacio ocupado por el registro en dicha página ocmo disponibel.
- Actualizar un registro en un archivo almacenado; para ello, se debe recuperar la página de la _BD_ que contiene le registro que se desea actualizar. A continuación, se intenta sustituir la información y si no se puede intenta ubicar el contenido en otra página.
