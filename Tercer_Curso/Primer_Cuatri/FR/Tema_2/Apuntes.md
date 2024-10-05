# TEMA 2. Capa de red

hciendo un recordatorio sobre lo que ya hemos visto sabemos que si hay dos ordenadores con dos routers conectados por una red, si deseamos mandar un paquete, es necesario que este paquete atraviese las capase de forma vertical hasta la capa física para enviarse al siguiente dispositivo y repetir.

En este tema, nos centraremos en estudiar como un paquete cualquiera viaja de la __capa de Red__ a la __capa de Enlace__ dentro de un __mismo dispositivo__(en Ethernet, al resultado se llama dirección _MAC_). 

Para realizar este cometido necesitamos un __protocolo__ que me diga, dada una dirección _IP_, cuál es su dirección _MAC_ asociada.


## 2.1.Funcionalidades

Según el protocolo TCP/IP:
    
    · Proporcionar el encaminamiento.
    · Determinar cómo va a producirse la conmutación.
    · Da pinceladas sobre los mecanismos de interconexión de redes.
    · Siguiendo la abstracción OSI, debería proporcionar control de congestión

Un ejemplo de protocolo de red es _IP_.

## 2.2.Conmutación

Hablando un poco de historia, el término de __conmutación__ surgió cuando empezó la red de telecomunicaciones en las llamadas _centrales de comunicación_; lugares donde, para establecer una conexión debían cambiarse cables de sitio para dar paso a unas llamadas u otras consiguiendo retardos.

<div>
<p style='text_align:center;'>
<img src=./imagenes/historia.png alt="JuveYell" width=500px>
</p>
</div>

Esto era así pues cada individuo disponía de un cable de interconexión con una de las centrales de conmutación, cada usuario disponía de un único cable para él eliminando interferencias. No obstante, había muchos más usuarios que cables dentro de una central de conmutación, de ahí el intercambio de cables.

Una vez se conmutaban los cables y se producía la conexión por llamada, se decía que se había establecido un _camino_ que pasaría a llamarse __circuito__ más adelante.

Esto presentaba un problema claro, cuando un usuario no usaba su línea telefónica, nadie la usaba quedando inutilizada grandes períodos de tiempo; por tanto, era un método poco eficiente, poco escalable y poco fiable pues ante una guerra podría quedarse inutilizada de un ataque.

Una vez dicho esto, pasemos a hablar formalmente; a día de hoy, la __conmutación__ es la acción de establecer o determinar un camino que permita transmitir información extremo a extremo. De esto, derivan los esquemas de conmutación, formados por los __circuitos__ y los __paquetes__, ya sea por datagramas o circuitos virtuales.

### 2.2.1.Tipos de conmutación

Aunque ya hemos hablado de la conmutación de circuitos en la zona de historia, vamos a tratar la conmutación de paquetes, ya sea por datagrama o por circuito virtual.

La __conmutación de paquetes__ consiste en mandar datos, es decir, ceros y unos. En este caso, los elementos de conexión utilizados no son _centrales de conmutación_ sino que son _routers_ que usan colas para percibir y seguir el orden de llegada del paquete; además, de esta forma no se pierden bloques de datos o __paquetes__ (conjunto de datos que se manda a través de la red).
    
Hablemos ahora de la conmutación de paquetes por __datagrama__ partiendo de que uno de estos no es mas que un concepto proveniente de correos, consiste en que cuando el cartero recibe el paquete, este hará lo posible en que el paquete llegue a su destino; no obstante, si no lo consigue, no mandará mensaje de ello. Por tanto, el usuario solo sabrá que su paquete se ha enviado y nada más de él. Esta estrategia sigue el nombre de "_mayor esfuerzo_". Por ejemplo es seguida por el protocolo _IP_.

Normalmente, cada una de las capas recibe un nombre distinto para los paquetes divididos de la siguiente forma:
    
    · Enlace -> trapa
    · Red -> datagrama
    · Transporte -> En TCP "segmento" - En UDP "datagrama"
    · Aplicación -> mensaje

Como según la estrategia del _mayor esfuerzo_ no necesito saber si el paquete ha llegado, ni siquiera necesito comprobar si se ha realizado la conexión con el destino. Además, cada paquete es independiente de los demás luego, al realizar el _encaminamiento_ __paquete a paquete__ dos paquetes consecutivos pueden no tener el mismo camino y, de hecho, no llegar en el orden de lanzamiento.

Como si fuera poco, si quiero conocer el paradero del paquete, es necesario que esta funcionalidad la implemente otra capa superior.

En ocasiones, cuando el paquete es excesivamente grande, es necesario __fragmentar__ y gracias a que los paquetes se tratan de formas independientes, la división puede no realizarse en el origen y sí en un router. Añadido a esto, cada fragmento es independiente y el router desconoce qué fragmento de qué paquete que ha procesado o no es. Eso sí, una vez llega al destino, se produce sí o sí el ensamblado y sólo en este momento.

Como curiosidad, los paquetes tienen un dato origen que no es útil durante el encaminamiento y direccionamiento, su utilidad reside en la posibiidad de mandar respuestas. Por último, como el medio de transmisión es compartido, habrá una competición por el mismo a la hora de que los paquetes circulen dando paso a la necesidad de crear un mecanismo que resuelva estas colisiones.


<div>
<p style='text_align:center;'>
<img src=./imagenes/datagrama.png alt="JuveYell" width=500px>
</p>
</div>

Pasando al otro tipo de conmutación, es decir, la realizada con __circuitos virtuales__. En este caso, consiste en reservar los recursos que se van a usar durante el trayecto del paquete estableciendo así el camino del mismo. Esto puede conllevar la reserva de colas de un router permitiendo que la comunicación sea más rápida.

Aunque los recursos no son dedicados, virtualmente ocurre algo distinto pues la idea es establecer el camino del paquete durante su traspaso. Cabe recalcar que se llama virtual porque se realiza en el momento de forma dinámica; en este caso, todos los fragmentos del paquete siguen el mismo camino.

En ambos casos, todo lo que tiene que ver con recuperacion de paquetes se hace en la capa de transporte (OSI). 


## 2.3.Protocolo IP

Este protocolo no dispone de muchas funcionalidades:
    
    · Asignar direcciones IP y gestionarlas.
    · Dirigir el encaminamiento salto a salto asegurando que se llega a los extremos.
    · Proporcionar mecanismos de fragmentación de paquetes devido al MTU(máximo tamano de paquete ne la red).

Al se un protocolo de mayor esfuerzo, los paquetes se mandan y se trata que lleguen a su destino pero si esto último no ocurre, no se provee de ningún mecanismo de recuperación; no osbtante, el protocolo sí manda un mensaje de error a través del protocolo _ICMP_.

Antes de meternos de lleno en las versiones, vemos a definir algunos términos como:

    · Handshake: hace referencia a un intercambio de mensajes concreto entre dos entidades.
    · Protocolo: hace referencia a cómo dos entidades de la misma capa se transmiten información.
    · Router: se puede entender como un ordenador que dispone de una cantidad de tarjetas de red donde cada una de ellas dispone de una dirección _IP_. Estas direcciones _IP_ simplemente son interfaces de redes a las que se conecta. Además, se encarga de dividir redes e interconectarlas entre sí, luego cada "pata" del router es una red distinta; en ocasiones dispondrá de redes inalámbricas.


### 2.3.1.IPv4

Es una versión del protocolo _IP_ que está especificada en el _RFC 791_ y permite conectar redes, subredes y superredes.

En el encaminamiento, cada equipo dispone de una terjeta de red proporcionando una dirección _IP_ distinta; es vía datagrama perdiendo mucha de su fiabilidad pues no comprueba que lleguen los paquetes. Es importante aclarar que, pese a que nosotros nos referimos a los lugares destino con los nombres de dominio (_youtube_, _twitter_,...) a lo que realmente le mandamos la información es a la tarjeta de red que dispone de la dirección _IP_ asociada a la red por la que nos comunicamos. De hecho, el domino está asociado a varias direcciones _IP_ dependiendo del servidor del dominio que esté más cerca.

Debido a esto último, no requiere que se establezca conexión evitando incluso el 'handshaking' entre origne y destino. 

Una vez el paquete pasa a la capa de Red y obtiene su cabecera (PDU) lo llamamos datagrama; no obstante, permite la fragmentación y al paquete fragmentado es a lo que realmente llamaremos paquete en el ámbito de este protocolo de interconexión de redes.

___Direccionamiento___

Con respecto al direccionamiento del modelo, cada dirección dispone de __32 bits__ separados en __4 bytes__ por puntos, es decir, es de formato __A.B.C.D__ donde cada letra es un byte. 

Siempre se interpretarán de la misma forma, una cantidad de bits de la izquierda representarán la red y el restante representará el dispositivo que está conectado a la red. 

Para ello usamos las __máscaras__ que suelen estar formadas por el mismo número de bits que la dirección _IP_ y no son más que una cantidad, _n_, de bits a 1 seguidos de ceros hasta completar el tamaño. De esta manera, aplicando la función lógica _AND_ entre la dirección _IP_ y la máscara se obtiene la red a la que se conecta el dispositivo.

Por ejemplo:

    · 192.168.1.5 -(bin)--> 11000000.10101000.00000001.00000101
    · Mascara = /24 -(dec)--> 255.255.255.0 --> 11111111.11111111.11111111.000000000
    · Aplicamos la AND lógica, luego me quedo con los 24 bits iniciales de la izquierda.
    · Resultado(red a la que me conecto): 11000000.10101000.00000001.00000000 --(dec)->192.168.1.0=dir.real

La dirección que hemos obtenido en el ejemplo es importante, pues sólo la red dispone de esa dirección haciéndola única ya que no se asigna ningún equipo y es útil para encaminamiento. De la misma manera, la dirección 192.168.1.255 esta reservada como dirección de difusión, es decir, cualquier equipo la vería. Esto es útil para saber la localización de un servidor, pues la reacción del servidor ante un paquete delatará su posición.

Volviendo al tema del direccionamiento y habiendo entendido ya las máscaras, vamos a ver los distintos rangos en los que se clasifican las $2^{32}$ direcciones de las que disponemos:

Se dividen en clases:
    
    · Clase A: disponen de cabecera 0xxxxxxx.___x con rango [0.0.0.0/8 - 127.255.255.255/8]. Donde la máscara son 8 bits dando lugar a que haya $2^{7} redes con $2^{24}$ equipos por red.

    · Clase B: disponen de la cabecera 10xxxxxx.___x con rango [128.0.0.0/16 - 191.255.255.255/16]. Donde la máscara son 16 bits dando lugar a que haya $2^{14}$ redes con $2^{16} equipos cada una.

    · Clase C: disponen de la cabecera 110xxxxx.___x con rango [192.0.0.0/24 - 223.255.255.255/24]. Donde la máscara son 24 bits dando lugar a $2^{21}$ redes con $2^{8}$ equipos por red.

    · Clase D: Aunque estas redes no estaban en el origen son las que disponen de la cabecera 1110xxxx.___x con rango [224.0.0.0 - 239.255.255.255]. Esta clase suele usarse para mutidifusión y no dispone de una máscara pues no se usan para redes IP; cada dirección identifica un grupo de equipos, que son ciertos grupos de redes, un ejemplo el IGMP. Suele usarse para la televisión por suscripción como Movistar+. Luego para que le suministrador mande un paquete a todos los equipos primero iral al router de multidifución.

    · Clase E: Estas serían las que quedan, es decir, disponen de una cabera 11110xxx.___x con rango [240.0.0.0 - 255.255.255.255]. Tampoco disponen de máscara y es una red experimental, es decir, se usa para probar proyectos; a efectos prácticos, no se utiliza.

En conclusión, para crear redes y asignarlas a equipos se usan sólo las tres primeras clases.

Hasta ahora hemos estado hablando de direcciones _públicas_ que, como hemos podido denotar, se asignan públicamente... pero qué ocurre con las direcciones _privadas_. Solo se encuentran en intranets por lo que, en distintas intranets (redes de dominio privado) sí que se pueden repetir. En este último caso, es el usuario quien la asigna.

#TODO: De la diapositiva 25 a la 28 no se ha dado

### 2.3.2.IPv6



### 2.3.3.Subredes

Dada una red diremos que una __subred__ es una conexión entre varios dispositivos determinada por siwtches, luego si dos routers comparten switch, tendrán la misma red aunque las direcciones de los equipos sena distintas. 

Estas conexiones no dejan de ser redes, pero básicamente lo que tenemos es una estructura de red donde cada conexión de las que ya se han explicado forman una subred. Por tanto, dos sitches que estan conectados entre sí determinan la misma red (los switches, al ser nivel 2 no disponen de dirección _IP_).

<div>
<p style='text-align:center;'>
<img src="./imagenes/subredes.png" alt="Error" width="400px" height="200px">
</p>
</div>

