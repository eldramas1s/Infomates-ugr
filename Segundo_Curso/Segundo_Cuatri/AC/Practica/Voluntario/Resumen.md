# Introducción

En esta sesión de prácticas voluntaria se ha trabajado el uso de la GPU para agilizar la ejecución de los programas. Estas son las características de la GPU:

      - Nodo: atcgrid4
      - Modelo: Nvidia Quadro RTX 5000
      - Núcleos de procesamiento paralelo: 3072
      - Número de SIMT:	48
      - Maximo de threads por SM(también llamado CUDA Block): 1024
      - Número de threads en un warp(unidad de planificación): 32
      - Memoria de la GPU en la tarjeta: GDDR6 de 16 GB
      - Bus para conexión con el host: PCI Express 3.0 x 16

# 1.Estructura de la Arquitectura junto a un coprocesador de la GPU

Como se ve en el dibujo del pdf de esta carpeta, cada SM dispone de una cache y un organizador de wraps a parte de una agrupacion de nucleos SP también llamada núcleo CUDA. La caché L1 es compartida por todos los SP y la caché L2 es compartida por todos los SM, agrupaciones de SP. Además, dispone de una memoria principal de GPU conectada a la al coprocesador por un bus de memoria.

La conexion entre Host,en nuestro caso el FrontEnd,se realiza mediante un bus de entrada salida conectado con la memoria del multiprocesador de host.

## 1.1.Uso del coprocesador y un poco de funcionamiento interno

El host o anfitrión es el dispositivo que maneja el cotarro, si este necesita de ayuda creará más flujos de instrucciones que le ayudarán a la ejecución de una región del programa. A aquellos dispositivos usados para acelerar la ejecución de una región de código se les suele llamar coprocesadores o target devices. 

Es importante aclarar que los flujos de instrucciones creados por el host, si se ven sobrepasados y necesitan más potencia tomarán la decisión (realmente la toma el usuario) de crear mas flujos que usaran como target devices y ejecutarán una porción de la región de código asignada al flujo que los crea. Estos flujos que crean otros se llaman initial threads. El primer flujo que se ejecuta en el host es el initial thread del host.

Referente a esto, cada dispositivo solo dispone de un número fijo de flujos de instrucciones a usar, es decir el número de entradas que tiene el procesador, lo que equivale al número de instrucciones que puede procesar de forma simultánea.

En caso de querer ejecutar algo de código en un dispositivo específico, se creará un initial thread asociado a este dispositivo.

Con respecto a la gestión de datos, la memoria no tiene un estado estático sino que puede estar compartida o no dependiendo del momento. Para gestionarlo se usa el mapeo, que denomina qué variables son compartidas y cuáles no. Esto no significa necesariamente que haya tranferencia de datos entre dispositivos.

# 2.Directivas para usar en coprocesadores

Veamos las directivas que se pueden usar en el código para hacer uso de coprocesadores:

## 2.1.Directivas de dispositivos

### pragma omp target

Se encarga de delimitar el código a ejecutar por un dispositivo coprocesador. Para determinar el entorno de datos, se usa la cláusula map que más adelante quedará explicada.

Esta directiva debe ir seguida de un bloque estructurado.

### pragma omp target data

Es la encargade de realizar lo mismo que la directiva anterior añadiendo al tarea de crear un ámbito de datos del dispositivo. Es decir, es la encargada de reservar memoria en el coprocesador para almacenar la svariables que se vayan a usar; normalemente, va seguida del mapeo de variables.

Esta directiva también puede manejar el envío al host de datos de memoria del coprocesador usando la clásula map con el argumento from.
### pragma omp target enter data / target exit data / target update

La ~primera~ de las opciones es la encargada de realizar todo lo de las directivas anteriores pero sólo realiza la reserva de memoria

## pragma omp declare target



## 2.2.Directivas de equipos

### pragma omp teams

Provoca que se cree una liga de equipos de trabajo, en particular, crea los initial threads de cada equipo. Estos equipos de trabajo serán los encargados de realizar las tareas del código.

### pragma omp distribute

Cuando imponemos esta directiva causamos el reparto de las iteraciones de un bucle entre los equipos que haya creados en la liga de equipos. Por tanto, debe estar seguida de un bucle.

# 3.Cómo trabajar

Ahora que ya sabemos cómo funcionan las directivas y cláusulas de trabajo con los coprocesadores, estamos en disposición de iniciar nuestro trabajo. Para ello, seguiremos estas pautas.

   - Cada vez que queramos hacer uso del coprocesador, se lo indicaremos con la directiva tardet o sus derivadas dejando claro qué parte del código es la que debe ejecutar.
   - Mapearemos las variables que vayamos a usar con la cláusula map y haciendo uso de los argumentos to y from.
   - Creamos una liga de equipos entre los cuales dividiremos el trabajo con la directiva teams, y en caso de ejecutar un bucle, usaremos la directiva distribute para repartir el trabajo.
   - (HIPOTESIS) Las variables no necesitan ser desmapeadas pues al terminar la ejecución del código se eliminan, lo que no sé (y si alguien lo sabe que me lo diga) es si se borran los valores o se guardan en las varibale que haya en el host. (HIPOTESIS)

Todo esto puede llegar a hacerse en una única directiva dando lugar a que tengamos menos control sobre lo que ocurre pues será la herramienta de programación la que realizará más trabajo a medida que juntamos más directivas en una. Por ejemplo: 
      
      # pragma omp target teams distribute parallel for num_teams(nteams) thread_limit(mthreads)\	 map(to:N,alpha,x[:N],y[:n]) map(from:z[:N]

que realiza todo lo anterior y delimita el número de equipos a crear junto con el número límite de hebras a crear por equipo. 
