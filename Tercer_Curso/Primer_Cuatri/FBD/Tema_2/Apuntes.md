# TEMA 2.Arquitectura de un SGDB

## 2.1.Niveles generales de la aquitectura

Hay una serie de motivos por los cuales es interesante organizar el sistema gestor en niveles y son las siguientes:
    
    · Los usuarios pueden acceder a los mismos datos desde distintas perspecticas, es decir, cada usuario tendrá una visión distinta de la base de datos. De esta forma, el usuario soro verá la punta del iceberg de todo el pedrusco.
    · La organización global de los datos puede cambiarse sin afectar a los usuarios proporcionando, en ocasiones, independencia lógica. Estableciendo mecanismos de comunicación entre los distintos niveles conseguiremos esta independencia.
    · Los usuarios no tienen por qué gestionar los aspectos relaticos a la representación física de los datos. Esto quiere decir que el administrador de la base de datos puede cambiar la forma de representar los datos sin influir en los usuarios, esto se hará con mecanismos de conversión entre los niveles.

En definitiva, lo que se busca con estos niveles es que se usen mecanismos que obliguen a que se verifique la independencia de los datos.

### 2.1.1.Arquitectura ANSI/SPARC

Esta arquitectura se organiza en tres niveles bien diferenciados:

    · Nivel interno: se encuentra a más bajo nivel y es el más cercano a la infraestructura física. Básicamente contiene las estructuras de datos sobre las que se sustentan los niveles superiores.
    · Nivel Conceptual: En este nivel se encuentra la versión lógica global de los datos usando modelos de datos para representarlos (en oracle suele haber un conjunto de tablas que serán una abstracción de lo que hay por debajo , que son ficheros que se relacionan entre sí).
    · Nivel externo: es el único nivel no desarrollado por el Administrador y sí por los programadores pues serán aplicaciones que: para cada tipo de usuario, se dispone de una visión distinta. Cuando hablamos de visión, nos referimos a qué parte de la base de datos es la que puede visualizar el usuario.

Todo esto surgió a través de un precedente de dos niveles conocido como DDGT-CODASYL.

Lo que nosotros haremos será crear tablas en el nivel conceptual que se traducirán en ficheros en el nivel interno. Para proporcionar independencia usaremos las visiones pues cada usuario sólo verá los datos que debe conocer y ninguno otro.

### 2.2.2.Correspondencia entre niveles

Cuando tratemos de crear la base de datos también lo haremos por niveles de manera que una vez acabado un nivel inferior pasaremos al superior; no obstante, obviaremos este nivel ya creado pues así conseguimos que los distintos niveles no este ligados fuertemente provocando que un cambio en un nivel inferior ocasiones reprogramar niveles superiores.

Para conseguir esto, usaremos las __transformaciones entre niveles__ ,también llamadas correspondencias, que no son más que un conjunto de normas que establece cómo se definen los datos de un nivel en términos de uso.

___Conseguir la independencia física de los datos___

Para ello, deberemos establecer una transformación (comunicación en la introducción) entre los niveles _interno_ y _conceptual_ pues ya sabemos que esto tiene que ver con cómo estén los datos almacenados físicamente.

Esta transformación no es más que una tabla donde se guarda, para cada dato del nivel conceptual su posición en el almacenamiento físico de manera que caundo se cambie la posición física del elemento en cuestión, sólo necesitaremos cambiar la dirección almacenada en la tabla de correspondencia.

De esta manera, nos limitamos a expresar cómo se organizan las tablas del nivel conceptual en función de registros y ficheros en el nivel interno.

___Conseguir la independencia lógica de los datos___

Para ello, deberemos establecer una transformación (comunicación en la introducción) entre los niveles _conceptual_ y _externo_ pues ya sabemos que buscamos que un cambio en el esquema lógico no produzca la reporgramación de toda una aplicación.

#TODO: PReguntar por funciomaniento.

El funcionamiento consiste en describir cada visión interna en terminos del esquema conceptual global que hay en el nivel conceptual. Luego, cualquier cambio producido en dicho nivel solo deberá provocar la modificación de la tabla de correspondencia.

Cabe recalcar, que esto no es posible en algunas ocasiones pues si hago una modificación lo suficientemente sustanciosa puede ocurrir que deba reimplementar parte de la aplicación.

<div>
<p style='text-align:center;'>
<img src="./imagenes/Correspondencias.png" alt="JuveYell" width="500px" height="400px">
</p>
</div>

Por ejemplo; si en una base de datos representamos a una persona por su nombre (nombre y apellidos todo junto) y dado un tiempo necesitamos separar esto, crearíamos dos entidades más como _Apellido 1_ y _Apellido 2_. Entonces, si ya disponíamos de independencia lógica la principio, sólo deberemos añadir la regla a la tabla de corresponcencias como _nombre completo = nombre + apellido1 + apellido2_ y continuaremos teniendo dicha independencia.

### 2.2.3.Lenguajes de una Base de Datos

Veamos primero la recomendación ANSI/SPARC.

Se nos recomienda disponer de un lenguaje específico orientado a los datos, que permita definir,controlar y manipular datos. Además, se nos recomienda usar un _DSL_(_Domain Specific Language_) que no es más que no usar un estándar de manera que distintos SGDB no podrán leer algunas instrucciones de las que usemos; algunos ejemplos son _DDL_,_DML_ y _DCL_ que forman un lenguaje de este tipo.

En resumen, entre niveles encontramos las tablas de correspondencias, que contienen la ubicación de los datos en un nivel superior dentro del nivel inferior.
