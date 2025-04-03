<br>

# Métodos Numéricos II - Examen

**Autor:** Lucas Hidalgo Herrera - Grado en Matemáticas  
***

- **Asignatura:** Métodos Numéricos II
______

1. Sea \(g\) una función real continua en un intervalo \([a, b]\):
    - (x) Si \( g \) toma valores en \([ \frac{a+b}{2}, b ]\), entonces tiene al menos un punto fijo en \([a, b]\).
    - ( ) La ecuación \(x = g(x)\) tiene una única raíz en \([a, b]\).
    - (x) Si \(g\) toma valores en \([a, b]\) y es contráctil, entonces tiene un único punto fijo en \([a, b]\).
    - ( ) Si \(g\) toma valores en \([a, b]\) y es derivable con derivada menor que 1 en todo punto, entonces el correspondiente método de iteración funcional es convergente partiendo de un punto diferente de \(s\) pero suficientemente cercano.
    - (x) Si \( g \) toma valores en \([a, b]\), entonces tiene al menos un punto fijo en \([a, b]\).
    - ( ) La ecuación \( x = g(x) \) tiene al menos una raíz en \([a, b]\). No se dice que aplique el intervalo en el mismo.
    - ( ) Si \( g \) toma valores en \([a, b]\) y es derivable, entonces el correspondiente método de iteración funcional es convergente partiendo de un punto diferente de \( s \) pero suficientemente próximo a \( s \).

2. Sea \(f\) una función continua en \([a, b]\) con valores en \(\mathbb{R}\), tal que \(f(a)f(b) < 0\):
    - ( ) Si \(f\) es derivable en \([a, b]\) la ecuación \(f(x) = 0\) tiene una sola raíz en \([a, b]\).
    - (x) Si la derivada de \(f\) existe y en todo el intervalo abierto es negativa, entonces hay solo una raíz de \(f(x) = 0\) en el intervalo.
    - (x) Tanto el método de bisección como el de Regula Falsi convergentes, pero pueden converger a dos raíces diferentes de la ecuación \(f(x) = 0\).
    - (x) La ecuación \(f(x) = 0\) tiene al menos una raíz en el intervalo abierto \([a, b]\).
    - ( ) Si la derivada de \(f\) existe y en todo el intervalo abierto es negativa, entonces el método de NR converge a la única raíz de \(f(x) = 0\), partiendo del centro del intervalo.
    - (x) El método de la secante es aplicable pero no tiene garantía de convergencia a ninguna de las raíces de la ecuación \(f(x) = 0\).
    - (x) Si \(f\) es suficientemente derivable y en todo el intervalo abierto su primera derivada es negativa, entonces el método de NR converge a la única raíz de \(f(x) = 0\), partiendo de cualquier punto de algún subintervalo que contenga a la raíz.

3. Iteraciones:
    - (x) El método de Newton-Raphson requiere una semilla.
    - (x) El método de la Secante obtiene cada aproximación a partir de los dos anteriores.
    - ( ) El método de Newton-Raphson tiene siempre convergencia local cuadrática.
    - ( ) El método de la secante requiere una semilla.
    - (x) El método de iteración funcional requiere una semilla.
    - ( ) El método de Bisección requiere un intervalo donde se cumpla Bolzano.
    - (x) Si la raíz es simple, entonces el método de Newton-Raphson tiene convergencia local al menos cuadrática.
    - (x) Cuando las aproximaciones están muy próximas a la solución, el método de la Secante puede incurrir en división por cero al computar.

4. Toda fórmula de derivación numérica de tipo interpolatorio clásico para aproximar una derivada *k*-ésima en *a* ...
    - (x) tiene al menos un coeficiente positivo y al menos otro negativo.
    - (x) tiene unos coeficientes que pueden obtenerse resolviendo un sistema lineal del mismo orden que el número de nodos.
    - () tiene unos coeficientes que son idénticos.
    - (x) tiene unos coeficientes que son las derivadas *k*-ésimas, en *a*, de los polinomios de Lagrange correspondientes a los nodos.
    - (x) tiene unos coeficientes que suman cero.
    - () tiene unos coeficientes que son simétricos.

5. Si la función \(f(x)\) no es derivable, pero es continua y \((a)f(b)<0\), entonces puedo aplicar los métodos de 
    - () Bisección y Newton-Raphson
    - (x) Bisección, Secante y Regula Falsi
    - () Newton-Raphson y secante
    - () Sólo los métodos de iteración funcional
    - () Todos los métodos estudiados.
    - (x) Bisección

6. Una fórmula de tipo interpolatorio clásico para aproximar la derivada -ésima de en un punto ...
Usuaria Profesores
    - (x)  que use \(n\) nodos, puede tener como máximo orden de exactitud \(k+n-1\).
    - (x) no tiene interés si el número de nodos es menor o igual que \(k\) .
    - () que use \(n\) nodos, puede tener como máximo orden de exactitud \(n+k\).
    - () que use \(n\) nodos, puede tener como máximo orden de exactitud \(k\).
    - (x) debe tener al menos \(k+1\) nodos, para que tenga algún interés.
    - () que use \(n\) nodos, puede tener como máximo orden de exactitud \(n-1\).

7. Fórmulas de derivación numérica de tipo interpolatorio
    - (x) Una de las fórmulas de derivación numérica para aproximar \(f'(a)\) es \((f(a+h)-f(a-h))/(2h)\).
    - (x) Una de las fórmulas de derivación numérica para aproximar es \((f(a)-f(a+h))/(-h)\) .
    - () Las fórmulas de derivación numérica más habituales tienen un nodo, dos nodos o tres
nodos.
    - ()Las fórmulas de derivación numérica son imprescindibles para derivar funciones de las
que no se conoce una primitiva expresada en términos elementales.
    - () Las fórmulas de derivación numérica pueden ser simples o compuestas
    - () Una de las fórmulas de derivación numérica para aproximar más recomendable es \(f(a+h)-f(a-h)/(2h)\).
    - (x) Al aplicar una fórmula de derivación numérica, basada en los valores de la función en
los puntos \(a\) y \(a+h\), el valor de no puede ser nulo
    - () Al aplicar una fórmula de derivación numérica, basada en los valores de la función en
los puntos \(a\) y \(a+h\), el valor de no puede ser negativo
No hay ningún problema en que sea negativo

8. La fórmula \(f'(0)\approx0\)
    - (x) Es exacta para todo polinomio que sea una función par.
    - (x) Es una fórmula de tipo interpolatorio con un solo nodo, que puede ser el que se quiera.
    - () Es una de las fórmulas más precisas para aproximar el valor de la derivada de una función en cero.
    - () Es exacta para \(1,x, x^2, x^3, x^4\).
    - (x) Es exacta para las funciones: \(1, cos(x)\).
    - (x) Es exacta para \(1,x^2,x^3,x^4\).

9. Si tiene que resolver un sistema no lineal de dos ecuaciones, \(F(X) = 0\).
    - () Aplicaría Newton-Raphson a cada una de las dos ecuaciones.
    - (x) Necesitaría dos semillas, una para cada componente.
    - () Aplicaría primero el método de Bisección que es un método lento pero robusto.
    - (x) Si existe la matriz Jacobiana de orden \(2 \times 2\), asociada a \(F\), con determinante no nulo, aplicaría Newton-Raphson para sistemas.
    - (x) Lo más recomendable sería intentar resolverlo por el método de Newton-Raphson para sistemas, pero también se puede intentar escribir el sistema como \(X = G(X)\), que sea equivalente, y analizar si la correspondiente iteración funcional va a ser convergente.
    - () Necesitaría dos semillas si se quiere resolver por el método de la secante.

10. Para poder aplicar el método de Newton-Raphson, la función \(f(x)\) tiene que ser
    - () Dos veces derivable
    - () Con que sea continua es suficiente
    - () Creciente
    - (x) Derivable


