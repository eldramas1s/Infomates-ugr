
# TEMA 1.Introducción.

## 1.1.Concepto intuitivo de base de datos

Como motivación, es importante conocer cuál es la ventaja de usar bases de datos (BD). 
    
- La primera de ellas consiste en que al tener que manejar una gran cantidad de datos dentro de una empresa, las bases de datos provocan que estos datos sean manipulados de forma más sencilla y rápida.
    
- La segunda de ellas es la accesibilidad que permiten estas estructuras, pues se podrá accedder a los datos desde varios dispositivos. No obstante, será importante conocer que cualquier organización importante debe manejar una gran cantidad de datos necesitando de estas aplicacione spara manejarlos.

*Ejemplo*:
Un ejemplo de organización donde se deberían usar estas estructuras es un hospital, podría haber una base de datos donde se guarden los horarios de los médicos, las citas de los pacientes, la disponibilidad de los laboratorios, las consultas ocupadas en cada instatnte de tiempo...

En resumen, como objetivo principal de realizar una base de datos tenemos que, sirve principalmente para consultar datos.

**Características de los datos para que las bases de datos sean útiles**

- No deberán ser redundantes pues provocará que los datos no sean fáciles de manipular, es decir, un cambio en un dispositivo o estado del dato puede ser difícil de mantener. Luego, es necesario que no estén duplicados en distintos estados, me refiero a que sean entens distintos. Esto puede derivar en problemas de memoria ocupando más memoria de la disponible o necesaria.
- Los datos deben estar actualizados, no puede ocurrir que haya dos estados de un dato que den información contradictoria provocando una inconsistencia en el sistema de datos.
- Derivada de lo anterior, no habrá reutilización pues para cada instante habrá una copia, que llevará también a ocupar más memoria y problemas de actualización.

Para evitar que ocurran estos problemas se usarán aplicaciones de manera que **no** se provoquen dichas situaciones. Es decir, para cada subparte de una organización **no** deberá haber una aplicacion; por tanto, deberemos usar el mínimo número de aplicaciones posibles buscando **globalizar** los datos.

Con este objetivo se crearon las aplicaciones de bases de datos.

## 1.2.Soluciones al problema

Como primera solución se pensó en un sistema de archivos manipulado manualmente por algún usuario; no obstante, esto ocasionaba las siguientes tareas de complejidad:

- Tener la necesidad de crear de forma activa los archivos de una estructura determinada, es decir, para poder manejarla deberiamos crear un archivo para cada concepto, lo que es un trabajo muy tedioso.
- Deberíamos hacer de forma manual la consulta y la actualización de los archivos imponiendo condicionantes; además, para la actualización de un dato que puede estar en varios archivos por necesidad sería un trabajo tedioso y complicado con conjuntos de datos de orden mayor.
- Como ya se ha dejado ver en el punto anterior, la modificación dinámica de la estructura frente a un pequeño cambio puede producir dolores de cabeza; en resumen, no sería escalable.
- Aunque no presenta un quebradero de cabeza, la seguridad de la base de datos también es un problema que resolver, con esto me refiero a que debemos proteger los datos de usuarios no autorizados. Este problema también se presentará en la solución más correcta que aparece a continuación.
- Por último, necesitamos permitir el acceso desde distintas aplicaciones, con distintos lenguajes y sistemas operativos.

Por tanto, todo esto provocó el desarrollo de un software especial que nos permitiera guardar los datos en almacenes centralizados dando lugar a las *Bases de Datos(BD)*.

*Definición*:
Una Base de Datos es un fondo común de información almacenada en una computadora para que cualquier persona o programa autorizado pueda acceder a ella, independientemente del lugar de procedencia y del uso que haga de la misma. Un usuario de una base de datos no necesariamente será una persona; de hecho, lo más usual es que sea una aplicación.

Este software debe proveer de **operaciones con los datos**, gestionándolos de forma transparente (en la practica será necesario saber bien cómo se van a representar); **inserción de datos** , **obtención de datos**, **modificación de datos** o **borrado de datos**.

Un acrónimo que se suele usar es **CRUD**(*Create, Read , Update, Delete*); vemos que, en general, se busca determinar al completo la vida de un dato útil.

## 1.3.Sistemas de Gestión de Bases de Datos

Como ya se ha comentado, es importante que no haya redundacia; sin embargo, en la vida no siempre es así, sino que a veces es necesario que haya datos duplicados o redundantes con el objetivo de proveer al sistema de una cierta seguridad. (En esta asignatura, cualquier tipo de redundancia será penalizada).

Un SGDB(*Sistema de Gestión de Bases de Datos*) es un conjunto de elementos __software__ que debe tener capacidad para:
    
- Definir
- Mantener
- Utilizar

una base de datos con el objetivo de que se cumplan siempre las tres caráctirísticas de los datos con la mayor seguridad y consistencia posible.

## 1.4.Elementos de una base de datos

Como elementos de una base de datos encontramos:

- Datos: Pueden ser de dos tipos:
    + Inetgrados y sin redundancia: en ocasiones la redundancia será beneficiosa.
    + Útiles y compartidos: datos disponibles para varias aplicaciones reduciendo la memoria utilizada y facilitando la comunicacion entre ellos

- Hardware: Gracias a él podemos disponer de:
    + BD centralizada: menos útil y más local.
    + BD distribuida: permite que varios usuarios tengan acceso facilitando la comunicacion y versatilidad. 

- Software: Tienen los programas que usamos para definir las estructuras y gestionar la información de la BD.
 
- Usuarios en jerarquía de uso y desarrollo (a mas uso menos desarrolla): Usuario final - Programador de apps - Administrador (jefecillo)

*Definición*:
Un **dato operativo** es una pieza de información básica que necesita un organización para su funcionamiento; dicha organización consiste en disponer de un *item básico* o elemento sobre el que se puede pedir información, un *atributo* o característica del item básico (pueden ser varios) y una *relación* o conexión lógica entre dos o más item báscico.

Cuando se determinan y clasifican de esta forma todos los datos operativos, se obtiene el esquema lógico de la base de datos, esto es aquel diseño que seguirá nuestra base de datos.

## 1.5.Objetivos del SGBD

Cuando se dellarrola un software se persiguen unos objetivos, pero cada sistema los consigue con una profundidad distinta:

- Independencia de los datos(IMPORTANTISIMO). Los datos no dependen de las aplicaciones.
          
    + Física: el diseño lógico no debe depender de cómo se almacenan los datos de forma fisica. Nosotros seguiremos un modelo E/R como diseño lógico pero estarán en una memoria fisica; no nos va a importar cómo esten físicamente. De hecho, si nos importara, las bases de datos no tendrían sentido. (Ejemplo: ferreteria y organizacion, como mejora: poner lo que mas se vende cerca del mostrador). Es decir, buscamos que los datos más usados estén cerca y la reorganizacion sea sencilla. De hecho, esto no puede parar el funcionamiento de la base de datos. Buscamos que las aplicaciones no tengan que saber dónde estan los datos almacenados físicamente pues se tendría que reprogramar la aplicación para que sepan dónde están.(Esta ultima fras es clave). En conclusión, aunque podamos hacer reorganizaciones físicas para que la búsqueda de los datos sea mas sencilla, debemos tener en cuenta que el diseño de la base de datos no debe depender de ello. Luego, para diseñar la base de datos no pensaremos en la organización física.
  
    + Logica: no la proporciona el SGBD pero sí da herramientas para conseguirlas. Busca que cuando haya cambios en el esquema lógico, no necesariamente se tengan que reprogramar las aplicaciones.

 
- Que el usuario sea capaz de utilizar el SGDB de forma sencilla luego una mayor cantidad de personas sean capaces de usarlo. El sgdb relacional es el más utilizado para datos estructurados y lleva usándose desde finales de los 70 y se basaba en utilizar tablas.
 
- Que los datos estén centralizados, es decir, que los datos deban gestionarse de forma centralizada e independiente de las aplicaciones. Los usuarios tienen que percibir que hay un solo almacén en el que están todos los datos pese a que la implementación interna no sea así.
 
- No redundancia, recalcamos otra vez que los datos no deben estar duplicados y deberá gestionar el acceso concurrente de los usuarios (SCD).
 
- Los datos deben ser consistentes pues no deben haber fallos lógicos, es decir, se deben respetar las reglas definidas en la organización. El sistema debe mantener las restricciones y, establecer y cumplir las reglas de mantenimiento de la integridad. Además, cuando se realice una operación que parte de un estado válido, debe acabar tras hacer la operación a otro estado válido y nunca a un estado inválido.
 
- Fiabilidad: Es decir, que los datos están protegidos contra cualquier catástrofe, luego tienen que proprocionar mecanismos de recuperación y relanzamiento de operaciones con los mismos, este punto esta relacionado con el siguiente pues la redundancia es usada para proporcionar fiabilidad pero tambien proporciona seguridad.

- Seguridad: El sistema debe ser un sistema seguro, luego los sistemas deben ser accesibles a todos los usuarios luego habrá mecanismos de gestión de usuarios y privilegios (quién accede y a qué accede, estas seguridades se dan muchas veces en las aplicacione de gestion, en oracle no ocurre esto, lo hace en la propia base de datos, solo veo lo que debo ver) y mecanismos de protección de datos (el mas burdo es la redundancia pero es el mas útil y seguro.)

## 1.6.Ventajas de la utilización de un SGDB

En el caso del usuario, dependerá dle tipo de usuario del que hablemos:
   
- Usuario final o cliente: Podrá acceder a los datos.
    
- Programador: Elimina problemas en el diseño físico y lógico, en la depuración de errores, y en el mantenimiento general al hacer copias de seguridad o recuperación de fallos.
    
- Administrador: Este es el encargado de tomar decisiones y de mantener la base de datos facilitando el manejo de los datos y la toma de decisiones en la empresa.

En el caso del sistema:

- Proporcionar un control centralizado(fiabilidad, consistencia, seguridad).
- Criterios de uniformización: todas las partes del diseño del esquema lógico y d elas aplicaciones se rigen por los mismos criterios provocando que no se usen distintas clasificaciones en los datos.
- Generación de nuevas aplicaciones.
- Equilibrio entre requerimientos conflictivos.

