
# TEMA 1.Introducción.

## 1.1.Concepto intuitivo de base de datos

Como motivación, es importante conocer cuál es la ventaja de usar bases de datos (BD). 
    · La primera de ellas consiste en que al tener que manejar una gran cantidad de datos dentro de una empresa, las bases de datos provocan que estos datos sean manipulados de forma más sencilla y rápida.
    · La segunda de ellas es la accesibilidad que permiten estas estructuras, pues se podrá accedder a los datos desde varios dispositivos. No obstante, será importante conocer que cualquier organización importante debe manejar una gran cantidad de datos necesitando de estas aplicacione spara manejarlos.

*Ejemplo*

Un ejemplo de organización donde se deberían usar estas estructuras es un hospital, podría haber una base de datos donde se guarden los horarios de los médicos, las citas de los pacientes, la disponibilidad de los laboratorios, las consultas ocupadas en cada instatnte de tiempo...

**Características de los datos para que las bases de datos sean útiles**

    · No deberán ser redundantes pues provocará que los datos no sean fáciles de manipular, es decir, un cambio en un dispositivo o estado del dato puede ser difícil de mantener. Luego, es necesario que no estén duplicados en distintos estados, me refiero a que sean entens distintos. Esto puede derivar en problemas de memoria ocupando más memoria de la disponible o necesaria.
    · Los datos deben estar actualizados, no puede ocurrir que haya dos estados de un dato que den información contradictoria provocando una inconsistencia en el sistema de datos.
    · Derivada de lo anterior, no habrá reutilización pues para cada instante habrá una copia, que llevará también a ocupar más memoria y problemas de actualización.

Para evitar que ocurran estos problemas se usarán aplicaciones de manera que **no** se provoquen dichas situaciones. Es decir, para cada subparte de una organización **no** deberá haber una aplicacion; por tanto, deberemos usar el mínimo número de aplicaciones posibles buscando **globalizar** los datos.

Con este objetivo se crearon las aplicaciones de bases de datos.

## 1.2.Soluciones al problema

Como primera solución se pensó en un sistema de archivos manipulado manualmente por algún usuario; no obstante, esto ocasionaba las siguientes tareas de complejidad:

· Tener la necesidad de crear de forma activa los archivos de una estructura determinada, es decir, para poder manejarla deberiamos crear un archivo para cada concepto, lo que es un trabajo muy tedioso.
    · Deberíamos hacer de forma manual la consulta y la actualización de los archivos imponiendo condicionantes; además, para la actualización de un dato que puede estar en varios archivos por necesidad sería un trabajo tedioso y complicado con conjuntos de datos de orden mayor.
    · Como ya se ha dejado ver en el punto anterior, la modificación dinámica de la estructura frente a un pequeño cambio puede producir dolores de cabeza; en resumen, no sería escalable.
    · Aunque no presenta un quebradero de cabeza, la seguridad de la base de datos también es un problema que resolver, con esto me refiero a que debemos proteger los datos de usuarios no autorizados. Este problema también se presentará en la solución más correcta que aparece a continuación.
    · Por último, necesitamos permitir el acceso desde distintas aplicaciones, con distintos lenguajes y sistemas operativos.

Por tanto, todo esto provocó el desarrollo de un software especial que nos permitiera guardar los datos en almacenes centralizados dando lugar a las *Bases de Datos(BD)*.

*Definición*
Una Base de Datos es un fondo común de información almacenada en una computadora para que cualquier persona o programa autorizado pueda acceder a ella, independientemente del lugar de procedencia y del uso que haga de la misma. Un usuario de una base de datos no necesariamente será una perdona; de hecho, lo más usual es que sea una aplicación.

Este software debe proveer de **operaciones con los datos**, gestionándolos de forma transparente (en la practica será necesario saber bien cómo se van a representar); **inserción de datos** , **obtención de datos**, **modificación de datos** o **borrado de datos**.

Un acrónimo que se suele usar es **CRUD**(*Create, Read , Update, Delete*); vemos que, en general, se busca determinar al completo la vida de un dato útil.

## 1.3. Sistemas de Gestión de Bases de Datos

Como ya se ha comentado, es importante que no haya redundacia; sin embargo, en la vida no siempre es así, sino que a veces e snecesario que haya datos duplicados o redundantes con el objetivo de proveer als sistema con una cierta seguridad. (En esta asignatura, cualquier tipo de redundancia será penalizada).

Un SGDB(*Sistema de Gestión de Bases de Datos*) debe permitir:
    · Definción de estructuras de almacenamiento.
    · Acceso eficiente y seguro a los datos.
    · Organización de las actualizaciones de los datos.
    · Acceso multiusuario.
    ·...
