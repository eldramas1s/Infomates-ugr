# Tema 3.Capa de Transporte

## Objetivos

En este tema donde se estudiará la capa de __transporte__ se tiene como objetivos los siguientes puntos:

    1. Servicio de multiplexación y demultiplexación.
    2. Servicio orientado a conexión frente a servicio no orientado a conexión
    3. Transferencias de datos fiables.
    4. Control de flujo.
    5. Control de congestión.
    6. Implementación en Internet.

Además, se realizará un estudio detallado de los protocolos de transporte conocidos como __UDP__(_User Datagram Protocole_) y __TCP__(_Transimition Control Protocole_).

## 3.1.Introducción

Hasta ahora hemos visto que el nivel de __enlace__ se encarga sólo de la comunición _salto a salto_ sin preocuparse de quién es el destino final del paquete ni quién es el origin inicial del paquete.

Por otro lado, indagamos un poco en la comunicación _extremo a extremo_ utilizando la comunicación _salto a salto_ con el nivel de __red__ con protocolos como el _Protocolo IP_.

En este tema veremos cómo se realiza la comunicación _extremo a extremo_ sin pensar en la comunicación _salto a salto_ pues ciertamente no se produce.

Para recordar un poco la terminología, cada paquete del encapsulamiento recibe un nombre:
    
    - Enlace: frame.
    - Red: datagrama.
    - Transporte: datagrama(UDP) ó segmento(TCP).
    - Aplicación: mensaje.

Refiriendonos con pinceladas al protocolo __UDP__, debemos denotar que se encarga de la transmisión a nivel de transporte al igual que __TCP__ con la diferencia de que __UDP__ no tiene como principio la fiabilidad de la transmisión, es decir, es un protocolo que no garantiza que los paquetes lleguen correctamente; sino que, busca que la comunicación sea lo más veloz posible. De hecho, __UDP__ mandará los paquetes aunque el dispositivo esté apagado, no realiza ningún protocolo de 'hand-shaking'.

Por su parte, __TPC__ sí que es fiable pues realiza un protocolo de 'hand-shaking' con el objetivo de asegurar los paqeutes; además, establece una conexión concertada con un sólo dispositivo. Para ser fiable, realiza comprobaciones sutiles para conocer el estado del paquete, pero... ¿por qué se realizarían comprobaciones si el fallo de un cable es mínimo? El motivo es claro, para evitar fallos por __congestión__.

Una de las soluciones que propondrá el protocolo será realizar un control de __flujo__ para regular el envío de paquetes cuando los buffers de los dispositivos comiencen a llenarse.

___Esquema de comunicación extremo a extremo___

<div> 
<p style='text-align:center'>
<img src="./imagenes/comex.png" alt=Error>
</p>
</div>

Como nota, todos los servicios estudiados se basan en la multiplexación-demultiplexación de los paquetes.

## 3.2.UDP

También conocido como _User Datagram Protocole_, es un protocolo de nivel de __transporte__ referenciado en _RFC 768_ encargado de la comunicación _extremo a extremo_ con funcionalidad ___best_effort___, es decir, no es fiable.

La fiabilidad de _UDP_ es tan reducida que en caso de que el paquete no llegue, simplemente la capa de _transporte_ no avisará a la aplicación de que se ha producido algún error, sino que será otra capa la que se encargará de controlar esta casuítica. Esto nos puede recordar al protocolo _IP_ que también trabajaba con _datagramas_.

Además, ligado a que no es fiable y a que es un servicio no orientadoa conexión encontramos que no hay garantías de __entrega ordenada__ ni __control de congestión__.

Esto primero hace alusión a que los paquetes que se van mandando no tienen por qué llegar al destino en el orden mandado; de hecho, como no se fragmentan los paquetes, realmente no es algo imprescindible.

Por su parte el hecho de que no haya _control de congestión_ viene de que _UDP_ busca ser lo más veloz posible luego se mandarán tantos paquetes como se puedan mandar.

En resumen, las características de _UDP_ son, sabiendo que es _best-effort_:
    
    1. No es fiable.
    2. No es orientado a conexión.
    3. No asegura entrega ordendad.
    4. No proporciona control de congestión.

___Paquetes UDP(datagramas)___

Los paquetes se dividen en _cabecera_ y _datos_.

En el caso de _UDP_ cada paquete está compuesto por una _cabecera_ de 8 Bytes repartidos de la siguiente manera:
    
    - Puerto origen (2 Bytes): determina el puerto desde el cual se manda el datagrama UDP. Permite que el receptor, en caso de recibirlo, pueda realizar su respuesta. Como mucho podrá haber 65535 puertos, de los cuales algunos están reservados para servicios importantes.
    - Puerto destino (2 Bytes): determina el puerto hasta el cual debe llegar el datagrama una vez enviado. Como mucho podrá haber 65535 puertos, de los cuales algunos están reservados para servicios importantes.
    - Longitud UDP (2 Bytes): determina el número de bytes que ocupa el datagrama, concretamente, la cabecera junto con los datos.
    - Comprobación (2 Bytes): contiene un 'checksum' para saber si el paquete mandado es el que debe recibir el dispositivo, es decir, no sirve para comprobar que el paquete esté correcto. Dentro de este campo se encuentra la cabecera y la pseudocabecera (la cabecera IP), donde encontramos los siguientes campos:
        
        + IP origen: dirección IP del dispositivo que manda el datagrama.
        + IP destino: dirección IP a la que debe llegar el datagrama.
        + Protocolo que se usa, por ejemplo, ICMP.
        + Longitud UDP, para conocer si se ha recibido todo el paquete.

De este último campo, se puede deducir que cada datagrama _UDP_ está encapsulado en un datagrama _IP_.

_Datagrama UDP_

<div>
<p style='text-align:center'>
<img src=./imagenes/datagramudp.png alt=Error>
</p>
</div>

Con respecto a los __puertos UDP__, se dividen en dos rangos:
    
    - [0-1024]: guardados para protocolos importantes donde el usuario que lo usa tiene privilegios de administrador.

<div>
<p style=text-align:center>
<img src=./imagenes/puertosudp.png alt=Error>
</p>
</div>
    
    - [1024 - 65535]: destinados para el uso común de usuarios.

## 3.3.TCP

También conocido como _Transmition Control Protocole_ es un protocolo de transmisión a nivel de _transporte_, al igual que _UDP_, especializado en la conexión _punto a punto_ lo que significa que al realizar una transmisión, no es capaz de mandar paquetes a distintos dispositivos a la vez, pues para mandar un paquete debe asegurar la conexión con el dispositivo. Por tanto, __no__ es un servicio __multicast__.

Otra de las grandes diferencias es que los datos sí que se mandan __ordenados__; para garantizar ese orden se hará uso de un campo de la cabecera que indicará el byte por el que empieza el __segmento__. 

Junto a esto, dispone de un buffer donde se almacenan los paquetes en orden, es decir, se reserva espacio para paquetes que están entre otros dos dentro del buffer; de manera que, cuando llegue, habrá un hueco de su tamaño en el buffer entre dichos dos paquetes que intercala.

Y por último, es un mecanismo __full-duplex__, es decir, permite recibir y mandar paquetes a la vez, dispone de __mecanismos de detección y recuperación__ causados por errores basados en __ACK's acumulativos__ y __timeouts adaptables__ y realiza __piggybacking__, es decir, al mandar un paquete necesario aprovecha para mandar algún que otro paquete que avance en la comunicación.

En resumen, las características de _TCP_ son:

    1. Es fiable
    2. Es orientado a conexión.
    3. Comunicación punto a punto.
    4. No es un servicio multicast.
    5. Proporciona entrega ordenada.
    6. Dispone de mecanismos de detección de errores y recuperación.
    7. Realiza piggybacking.
    8. Es full-duplex.

Al igual que _UDP_, _TCP_ dispone de __segmentos__, similar a los _datagramas UDP_ donde aparece una cabecera _TCP_ de 20 Bytes seguida de los datos a mandar.

La __cabecera__ se divide en los siguientes campos:

    - Puerto origen: determina quién manda el paquete para poder facilitar la respuesta. Como mucho hay 65535 puertos, hay alguno de ellos reservados para protocolos importantes.
    - Puerto destino: determina a qué dispositivo debe llegar el segmento. Como mucho hay 65535 puertos, dentro de los cuales hay algunos reservados para protocolos importantes.
    - Número de secuencia: uno de los campos más importantes encargado de la comprobación del orden de llegada de los segmentos; además, determina el byte inicial del segmento que se ha decidido dentro del buffer del dispositivo de llegada. Tomará un papel importante en la sincronización de la conexión.
    - Número 'acuse': es útil en la comprobación del estaod del paquete, pues refleja hasta que bit se espera recibir correctamente, una vez cumplido esto, se asume que todo lo recibido hasta ese byte será correcto, de ahí que sean acumulativos.
    - Hlen: determina el tamaño de la cabecera TCP.
    - Reservado: es un mecanismo de protección del protocolo a futuro, ya que si se añadieran campos se haría ahí.
    - UAPRSF: son una serie de bits útiles para la comunicación que sirven como flags de estado:
            + U o bit de urgente: su utilidad es para hacer que un segmento no cumpla el orden del buffer (FIFO) y se procese antes que todos. Suele usarse en caso de que haya que solventar algún problema en la conexión.
            + A o bit de ACK: (preguntar al profesor)
            + P o bit de push: sirve para evitar la espera debido a que el segmento no esté lo más lleno posible, pues un segmento no se manda hasta que esté lleno.
            + R o bit de reset: se usa para que uno de los dispositivos de la conexión fuerce al otro a resetear la conexión si se ha detectado algún fallo.
            + S o bit de sincronización: determina que los paquetes mandados tienen el objetivo de realizar la sincronización de la conexión.
            + F o bit de fin: determina que ese paquete con el bit encendido es el último de la conexión.
    - Ventana de receptor: se encarga del control de flujo, es decir, la ventana de control de flujo máxima es de 65535 bits; básicamente, determina la velocidad mácxima a la que se puede trabajar.
    - Comprobación: contiene un 'checksum' del paquete, en este caso sí que es una comprobación de corrección de todo el paquete.
    - Puntero de datos urgentes: determina el Byte a partir del cual se encuentran los datos urgentes.

Después de todo esto se encuentra un campo opcional y los datos.

___Segmento TCP___

<div>
<p style=text-align:center>
<img src=./imagenes/segmentotcp.png alt=Error>
</p>
</div>

Con respecto a los __puertos TCP__, se dividen en dos rangos:
    
    - [0-1024]: guardados para protocolos importantes donde el usuario que lo usa tiene privilegios de administrador.

<div>
<p style=text-align:center>
<img src=./imagenes/puertostcp.png alt=Error>
</p>
</div>
    
    - [1024 - 65535]: destinados para el uso común de usuarios.

Por último, una conexión _TCP_ se determina por las parejas (puerto,_IP_) origen y destino.

### 3.3.1.Funcionalidades TCP

A lo largo de este apartado se discutirán las funcionalidades que sí provee _TCP_ a diferencia de _UDP_.

#### 3.3.1.1.Control de conexión

Una conexión _TCP_ se basa en tres partes donde __no se puede determinar que sean fiables las fases extremo__ ya que están basadas en el protocolo _IP_:

    1. Establecimiento de la conexión o apertura.
    2. Intercambio de datos.
    3. Cierre de la conexión.

___Establecimiento de la conexión___

Esta parte es un proceso llamado _three-ways handshake_ donde se siguen los siguientes pasos:
    
    1. El cliente siempre empieza la conexxión con la apertura activa, donde se manda un paquete de solicitud con el bit SYN(1) y numero de secuencia(x), por ahora, aleatorio.
    2. El servidor que recibe la solicitud realiza la apertura pasiva respondiendo con un paquete ACK, con número 'acuse'(x+1) especificando que ya sabe hasta que bit espera recibir, y aprovechando el 'piggybacking' manda el sincronismo opuesto con bit de SYN(1) y número de secuencia(y).
    3. El cliente devuelte un ACK confirmando la sincronización de los números de secuencia con número de 'acuse'(y+1).

_Proceso de apertura_

<div>
<p style=text-align:center>
<img src=./imagenes/apertura.png alt=Error>
</p>
</div>

Como no se puede asegurar que este intercambio sea fiable al estar basado en el protocolo _IP_, el cliente dipone de un contados o __timeout__ que determina a partir de que momento se vuelve a intentar la conexión, echando por los suelos el trabajo que ya se ha realizado.

Debido a esto disponemos de varias casuísticas:
    
    1. Casuística normal.
    2. Caso de intento de apertura simultánea: es un caso poco habitual pues no se da ccuando la conexión es cliente-servidor, sino cuando es cliente-cliente. Se resuelve simplemente mandando cada uno la respuesta ACK con el 'acuse' correspondiente.

<div>
<p style=text-align:center>
<img src=./imagenes/aperturasim.png alt=Error>
</p>
</div>
    
    3. Caso de sincronismo con retraso: este caso es más habitual y ocurre cuando hay un retraso en la red provocando que se descarte un segmento de apertura cuando sí que se ha mandado y ha llegado; esto es ocasionado por el 'timeout'. La solución es de nuevo no tener en cuenta la respuesta del servidor y mandar otra apertura activa para iniciar de nuevo la conexión.

<div>
<p style=text-align:center>
<img src=./imagenes/aperturaret.png alt=Error>
</p>
</div>

___Intercambio de datos___

Durante este proceso simplemente se produce una "conversación" donde sólo tma importancia el __número de secuencia__. 

El número de secuencia inicial es un valor denominado __ISN__(_Inicial Secuence Number_) que teóricamente se elige el azar y se usa para evitar confusiones con otras conexiones.

El ISN es elegido por el sistema (cliente o servidor). El estándar sugiere utilizar un contador entero incrementado en 1 cada 4 µs aproximadamente. En este caso el contador se da la vuelta (y el ISN reaparece) al cabo de 4 horas 46 min.

No obtante, pese a ser un mecanismo de elección fiable no protege frente a ataques de manera que s epuede calcular pudiendo suplantar alguna de las entidades de la conexión.

Por otro lado, una vez ya está avanzada la conexión, el número de secuencia va aumentando de forma parecida al _offset_ del protocolo _IP_ de manera que, en cada paquete, este número aumenta el tamaño del paquete recibido.


___Cierre de la conexión___

Esta parte también se basa en un proceso _three-ways handshake_ que sigue los siguientes pasos:
    
    1. Alguno de los dispositivos de la conexión realiza el cierre activo mandando un paquete de sincronización con bit de FIN(1) y un numero de secuencia(x).
    2. El otro dispositivo, haciendo el cierre pasivo, responde con un segmento ACK con numero de 'acuse'(x+1) y aprovecha el 'piggybacking' para mandar un segmento con número de secuencia(y) y bit de FIN(1).
    3. El dispositivo que inició el cierre responde con un segmento con número de 'acuse'(y+1).

El primero paso puede ser dado por el servidor o el cliente, esto dependerá de la implementación de la aplicación bajo la que se trabaja.

Asimismo, si una conexión dura menos que un tiempo conocido como (nombre¿?), la conexión no se cierra hasta que pase ese tiempo.

Al igual que en la apertura, el hecho de que se usen __timeouts__(_MSL_ o _Maximun Segment Lifetime_) para descartar intentos que han tardado bastante ocasiona que haya casuísticas problemáticas:

    1. Caso normal.
    2. Caso de intento de cierre simultáneo: es un caso poco común análogo a la apertura con intento simultáneo; de hecho, tiene la misma solución extrapolada a los cierres.
    3. Caso de sincronismo con retraso: se ocasiona cuando durante el cierre activo se avisa del fin de la conexión, ocasionando que si hay un retraso en la red, el dispositivo del cierre pasivo continúe mandando información. Esto se soluciona de forma similar a la apertura con sincronismo con retraso. (preguntar al profesor)

_Casuísticas_

<div>
<p style=text-align:center>
<img src=./imagenes/casostcp.png alt=Error>
</p>
</div>

Por útlimo, hablaremos del concepto de __tamaño máximo de segmento__ o _MSS_, que es útil para determinar cuánto puede ocupar la parte de datos de _TCP_ al crear un paquete, pues al haber encapsulamiento, al mandar un paquete _IP_ hay una parte de cabecera y una parte de datos _IP_ donde está englobado todo el segmento _TCP_. Como la parte de datos _IP_ es de 1480 Bytes y la cabecera _TCP_ son 20 Bytes, obtenemos que el _MSS_ será de 1460B.

#### 3.3.1.2.Control de errores.
