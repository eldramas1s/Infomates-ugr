# Tema 4. Seguridad en redes

## Índice

1. Introducción
    1. Aspectos de seguridad.
    2. Tipos de ataques.
2. Cifrado
    1. Tipos de cifrado.
    2. Algoritmos de cifrado.
3. Autenticación

4. Funciones Hash

5. Firma Digital y Certificados Digitales

6. Protocolos Seguros


## 4.1.Introducción

Nuestro objetivo dentro de una comunicación entre dos extremos es que dicha cominucación sea __segura__; para ello uno de los tips imprescindibles es que nuestra _red de comunicaciones_ sea __segura__. 

Para cumplir este objetivo deberemos garantizar que se cumplen una serie de aspectos que llamaremos __aspectos de seguridad__.

### Definición

Un aspecto de seguridad es una característica que cumple un elemento para acersarse más a ser seguro.

### Tipos de aspectos de seguridad

Los aspectos de seguridad que veremos son:

- __Confidencialidad__: consiste en que el contenido de la información sea comprensible solo por las __entidades autorizadas__ para ello. No obstante, otras entidades podrán ver los paquetes siempre y cuando estén cifrados.

<a id="autenticación"></a>
- __Autenticación__: es un mecanismo que prohíbe el acceso a cualquier tipo de información privilegiada si no se dispone de posibilidad a ello o una acreditación que conceda ese privilegio.

- __Integridad__: deberemos asegurar que los datos que se manden lleguen al destino sin ser manipulados, es decir, tal y como se mandaron. Para evitar que surja la posibilidad de que se cometan estos delitos se usan las funcionas _hash_ y los compendios, que detectarán cualqueir modificación ocasionada al paquete de información.

- __No repudio__: consiste en evitar que un participante en una transacción consiga liberarse de su acto. Es decir, en caso de hacer cualquier transacción se dispone de un registro de transacciones parecido a una _auditoría_.

<a id="disponibilidad"></a>
- __Disponibilidad__: consiste en que los recursos que se ofrecen al público que cumplan todo lo anterior estén disponibles a los usuarios la mayor parte del tiempo posible. Esto puede reducirse a que el sistema sea fiable.

- __Control de accesos__: Ligado a la [autenticación](#autenticación) consiste en controlar que la [disponibilidad](#disponibilidad) de los recursos sea solo a _entidades autorizadas_.


Controlando que todos estos aspectos se cumplan en cada uno de los niveles del __modelo__ ___TCP/IP___ conseguiremos que nuestra red sea algo más segura; no obstante, siempre tendrá debilidades.

### Tipos de ataques

A modo de divulgación existen una serie de ataques, algunos de ellos son:

<a id="sniff"><a/>
- __Sniffing__: consiste en espiar una conversación obteniendo la información de sus paquetes sin alterarlos.
- __Spoofing__: consiste en una suplantación de identidad, es decir, mandar un paquete dañino a otro dispositivo dentro de una conversación tratando de suplantar la identidad de alguno de los participantes.
- __Man in de middle__: consiste en introducir un dispositivo que intercepte señales y, por tanto, paquetes para realizar cualquier tipo de maldad, es un ejemplo de [sniffing](#sniff).
- __DDoS__ o _Distruibuted Denial of Service_: consiste en provocar la denegación de un servicio, normalmente, a una persona autorizada.
- __Malware__: son los más conocidad y suelen ser elementos software que provocan daños en el sistema al que entran, alguno son: _troyanos, gusanos, spywares, bacdoors_.


Para conseguir defenderse de estos ataques se inventaron los __mecanismos de seguridad__.

### Mecanismos de seguridad

Algunos mecanismos de seguridad los veremos más adelante y son:

- Cifrado
- Autenticación con clave secreta
- __Intercambio de Diffie-Hellman__: consiste en realizar un intercambio de claves, esto no es tan trivial como parece pues todo esto debe ser legal y disponer de una prueba segura ante un juez en caso de vulnerabilidad de algunos aspectos legales.
- Funciones Hash
- Firma Digital
- Certificados digitales

## 4.2.Cifrado

Sabemos que el termino cifrado se entiende como una transformación realizada a una serie de datos para que __solo__ aquel que dispone de la forma de descifrarlo conozca el contenido, a esto lo llamamos __cifrado de datos__.

El _cifrado de datos_ se basa en la existencia de un algoritmo de cifrado/descifrado que puede ser, o no, el mismo que es conocido por los extremos y solo por ellos. Realmente, la dificultad de vulnerabilidad de este mecanismo reside en __cómo de compleja es la clave de cifrado/descifrado que se use__, que, de nuevo, pueden no ser la misma.

### Tipos de cifrado

A la hora de cifrar los datos hay dos posibilidades:

| | Clave | Función |
| :---: | :---: | :---: |
| Simétrico | Misma | Distinta |
| Asimétrico | Distinta | Misma |

- __Cifrado simétrico__: son algoritmos que siguen el estandar _DES_(_Data Encryption Standard_) donde se usa una clave $k$ tanto para cifrar como para descifrar. Por ejemplo, un algoritmo muy típico se basa en realizar permutaciones y funciones _XOR_ llegando a realizar una sustitución como resultado; por tanto, el resultado siempre será el mismo si la entrada es la misma.

![Ejemplo cifsim](./imagenes/cifsim.png)
*Ejemplo de algoritmo simétrico con resultado por sustitución*

