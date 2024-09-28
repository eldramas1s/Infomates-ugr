# Tema 1.Introducción a los fundamentos de redes

## 1.1.Sistemas de comunicación y redes

Un **sistema de comunicación** es una infraestructura sftware y hardware que permite el intercambio de información y tiene la siguiente estructura:

<div>
<p style = 'text-align:center;'>
<img src="./imagenes/Sistema_Comunicacion.png" alt="JuveYell" width="300px">
</p>
</div>

Donde la fuente es el punto de emisión de información, el transmisor modela la señal para que sea compatible con el canal de comunicación siguiendo el modelo que tenga la red implementado, el receptor y el destino haría un trabajo análogo a la fuente y el transmisor. 

Dentro del canal de comunicación encontramos una estructura de red que no es más que un sistema de comunicación con sistemas finales autónomos (capaz de procesar información) que facilita el intercambio _eficaz_ y _transparente_ de información.

Pero...¿qué razones tenemos para usar las redes? Algunas de ellas son la compartición de recursos, la escalabilidad, la fiabilidad y robusted que nos da seguridad de que los datos van a llegar o nos evita de estar incomunicados frente a desastres naturales o humanos y el ahorro de costes al usar computación distribuida (AC).

Como objetivos al tener una red, buscamos que presente una cierta __autonomía__ (capacidad para procesar información), una gran capacidad para __interconectar__ puntos mediante un sistema de comunicacióny la capacidad de __intercambiar__ información con eficacia y transparencia.

Una red clásica se basa en dos partes, el __hosts__ compuesto por todos los equipos finales o destinos, que a la vez también son fuentes, y una __subred__ que consta de toda la infraestructura útil para el tranporte de información como pueden ser _lineas de transmision_ y _nodos o elementos de conmutación_; esta última parte se corresponde con el transmisor, el canal y el receptor.

Centrandonos un poco más en los __medios de transmisión__ haremos un barrido de cuál ha sido el medio de transporte de datos. En un principio, se usaban _cables de pares_, disponían de un ancho de banda (cantidad de información transmitida en un instante de tiempo) de 4KHz debido a que se usaba para redes telefónica. Con forme avanzó la tecnología se comenzó a usar el _cable coaxial_ llevando más tarde a la utilización de _cables de par trenzado_ donde surgieron los tipos _UTP_,_STP_,_FTP_ y se desarrollo l aestrategia del _ADSL_. A día de hoy, se usa un medio lumínico a diferencia de los eléctricos que son más lentos, este medio e sla _fibra óptica_; es un medio muy utilizado debido a que no sufre interferencias y permite que varias señales circulen a la vez por el mismo canal pues si no tienen el mismo ángulo de aceptación no sufrirán interferencias.

Los sistemas de redes suelen estructurarse según distintas __topologías__, es decir, siguen un patrón diferente entre sus nodos, encontramos la física y la lógica:
    
    · En bus: Todos los dispositivos están conectados al mismo bus luego todos ven toda la información causando problemas de privacidad; además, el congestionamiento de la red es muy común asicomo la pérdida de información por interferencias. Es la más barata y sencilla.

<div>
<p style = 'text-align:center;'>
<img src="./imagenes/bus.png" alt="JuveYell" width="300px">
</p>
</div>

    · En anillo: Cada dispositivo se coneca a dos más de manera que, para mandarle la información a ellos, se hará de forma inmediata. Si se busca mandar información a un tercero, se deben usar los demás dispositivos como routers de manera que seguirá habiendo congestión. 

    · En estrella: Todos los dispositivos se conectan a un router o switch central de manera que toda la información pasa por él. No obstante, cada conexión entre dispositivos distintos es directa pues el switch tiene una boca por dispositivo impidiendo que dos dispositivos envíen información a la misma boca. Es fácil de escalar y de manejar.

<div>
<p style = 'text-align:center;'>
<img src="./imagenes/estrella.png" alt="JuveYell" width="300px">
</p>
</div>

    · En árbol: Los dispositivos se dividen en niveles de manera que cada nivel del árbol representa un nivel de la realidad; de esta manera, dispositivos superiores reciben la información de inferiores y la redirigen a su destino. Es útil en la dirección de empresas.

    · Mallada: consiste en que un dispositivo esté conectado a varios de ellos dando lugar a que haya varios caminos para el mismo detino proporcionando mayor seguridad. 

<div>
<p style = 'text-align:center;'>
<img src="./imagenes/malla.png" alt="JuveYell" width="300px">
</p>
</div>

    · Híbrida: Consiste en identificar los puntos fuertes de cada lugar donde se pone la red y utilizar una topología u otra según dichos puntos fuertes obteniendo la mejor red posible.

La redes se __clasifican__ de varias formas(En comprobación):

    · Según el tamaño y la extensión. PAN (carácter personal, engloba bluetooth, móvil,  ordenado...), LAN (Local) , MAN(Metropolitana como en una ciudad) y WAN (World como en un país o continente).

    · según la tecnología de tranmisión; puede usarse Difusión (todos mandan y todos reciben todo lo que pasa por la red) o Punto a Punto (la comunicación es entre dos dispositivos solamente).

    · Según el tipo de transferencia de datos. Simple (solo manda o solo recibe), Half-duplex (hace ambas cosas pero no de forma simultánea) o Full-duplex (permite recibir y mandar de forma simultánea).

## 1.2.Diseño y estandarización de redes

Cuando nosotros diseñamos una red, buscamos solucionar los problemas por capas luego seguiremos un __Modelo de referencia__ de los cuales existen muchos como _OSI_ o _TCP/IP_, nosotros nos centraremos en este último.

<div>
<p style = 'text-align:center;'>
<img src="./imagenes/modelos.png " alt="JuveYell" width="250px">
</p>
</div>

Donde los dos niveles más bajos están implementados en hardware.

Debemos saber que el hecho de que esté dividido en capas debe usarse para implementar funcionalidades distinta en capas distintas asicomo para minimizar el flujo de información entre capas.

Con respecto a cada capa, veamos algunos problemas que presentan:

    - A nivel físico, debemos ver como se comparten los datos, es decir, no siempre el bit será 5V. Debemos saber la codificación de canal; normalmente, se suele añadir redundancia ayudando a mejorar la seguridad.
  
    - A nivel de enlace, se encarga de cómo manejarse con el medio, es decir, si leo, si escucho, si limpio el medio,etc. Un ejemplo es de dos capas LLC(se encarga de comprobar que los paquetes están bien y MAC (buscarlo).
  
    - A nivel de red, ya soy capaz de transmitir cosas que no tienen error; el objetivo es poder llegar al extremo; para ello, debemos saber el direccionamiento (saber a quien mando) y el encaminamiento (si tengo varias formas de ir, debemos saber por donde ir y si es más rapido mejor).
  
    - A nivel de transporte, aqui nos encargamos de la fiabilidad, es decir, si hay congestión(acumulación de paquetes en la llegada de paquetes) se arregla, control de flujo (cómo de rapido voy); además, se encarga de la multiplexación de datos (en la entrada llegan paquetes con diversos servicios, luego debemos saber a qué aplicación mando los datos). A su vez, es la encargada de garantizar que todo llega bien asicomo que la entrega de los mensajes es ordenada.
 
    - A nivel de aplicación, es lo que quiero hacer visual pero hay que saber cómo los usuarios se van a comunicar entre ellos, es decir, las notificaciones, los mensajes entre ellos, la interfaz...
