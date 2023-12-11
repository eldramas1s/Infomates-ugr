11.Dado un camino de datos concreto, un posible formato de microprogramación se caracteriza como horizontal o vertical según tenga más o menos (señalar la respuesta falsa)
-()codificación
-()solapamiento
-(x)micro bifurcaciones
-()longitud relativa de microinstrucción

12.El control residual se utiliza para:
-()reducir el tiempo de ejecución de las instrucciones máquina
-()eliminarlos bits residuales de la ejecución de las microinstrucciones
-(x)reducir el tamaño de la memoria de control
-()ninguna de las anteriores es cierta

13.Un procesador está segmentado en las etapas F, D, E, M y W. Cada una de  ellas consume un tiempo t. La aceleración ideal (si no hay riesgos) al ejecutar n instrucciones respecto a un procesador no segmentado será:
-(x)5n/(4+n)_
-()(4+n)/5t
-()4n/(5+n)
-()(5+n)/4t

14.En un procesador con segmentación de cauce, aumentar el número de etapas (p.ej. de 2 a 4, o de 4 a 8), tiene en general como consecuencia:
-(x)Un Incremendo De Las Prestaciones.
-() Un mayor retraso en la ejecución de los programas debido al incremento del número de etapas.
-()Una disminución en la posible dependencia de datos.
-()Una disminución de la máxima frecuencia de reloj a la que puede operar el cauce.

15.En la secuencia de instrucciones siguiente, siendo el primer registro el destino, ¿cuántos riesgos se dan?
sub r2,r1,r3 or r8,r6,r2
-()Un riesgo estructural.
-(x)Un riesgo por dependencia de datos.
-()Un Riesgo Estructural Dos Po dependencia de datos.
-()Dos riesgos por dependencia de datos y uno de control.

16.La precaptación(cola de instrucciones) está relacionada con...
-(x)Los riesgos estructurales(intenta evitar el efecto de un fallo de cache)
-()Los riesgos de (dependencia de) datos (intenta que el dato esté disponible anticipadamente)
-()Los riesgos control(intenta determinar de antemano el flujo de control)
-()Los riesgos de transferencia(intenta agrupar las posibles transferencias de un conjunto de instrucciones).

17.Respecto a la segmentación, ¿cuál de las siguientes afirmaciones es falsa?
-()La técnica de register forwarding habilita una serie de cambios(buses) que se añaden al cauce para permitir que los resultados de una etapa pasen como entradas a la etapa donde son necesarias.
-()La reorganizacion del código y la introducción de instrucciones no permite evitar dependencias de datos.
-(x)Retrasar la fase de decisión saltar/no saltar de las instrucciones de salto condicional contribuye a mejorar el rendimiento del procesador.
-()Cuantas más etapas tenga un cauce, más instrucciones se estarán ejecutando en distintas fases y más posibilidades se presentan de que existan riesgos entre ellas.

18.¿Cuál de los siguientes modos de direccionamento es menos preferible para un procesador de 32 bits y con tamaño de instrucción de 32 bits?
-()registro.
-()indexado.
-()indirecto a través de registro.
-(x)directo (o absoluto)

19.La conexión entre un dispositivo de E/S y el procesador mediante bus:
-()Es difícil de expandir.
-(x)Permite conectar en paralelo varios dispositivos.
-()Requiere mucha circuitería.
-()Requiere multiplexores y demultiplexores para las señales de datos.

20.El fragmento de código ensamblador de un microprocesador de 8 bits:
lds IOBuf	; Apuntar puntero pila a ...área mem.intermedia
ldx Count	; Inicializar x-contador
poll lda a Status; Leer estado en A
bpl poll	; Signo (A) != 1 => repetir
lda a Data	; Leer dato en A
psh a		; transferir dato a pila
dex 		; decrementar contador x
bne poll	; Seguir leyendo si x!=0

corresponde a:

-(x)Entrada programada con consulta de estado.
-()Salida programada sin consulta de estado. 
-()Entrada programada sin consulta de estado.
-()Salida programada con consulta de estado.
