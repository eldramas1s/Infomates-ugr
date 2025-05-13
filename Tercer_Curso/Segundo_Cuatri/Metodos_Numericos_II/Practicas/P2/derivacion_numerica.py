"""
Módulo donde se encuentran las funciones para la resolución de ejercicios de derivación numérica.
"""
import sympy as sp
import numpy as np
from sympy.polys.polyfuncs import interpolate 
import matplotlib.patches as patches

def formulador(f,x_values,simbolo,orden):
    """
    Función que devuelve el polinomio interpolador de Lagrange de grado n-1
    
    Parametros:
    - f: función a derivar
    - x_values: lista de puntos donde se evalúa la función
    - simbolo: punto en el que se evalúa la derivada
    - orden: orden de la derivada a calcular
    
    Return:
    - Polinomio interpolador de Lagrange de grado n-1
    """
    'Por seguridad:'
    x=sp.Symbol('x')  # utilizaremos x como variable simbólica
    
    y_values = [f(x) for x in x_values]
    data = list(zip(x_values, y_values))
    p = interpolate(data, x)
    
    for i in range(1, orden + 1):
        p = sp.diff(p, x)

    
    'Ya tenemos el polinomio derivado tantas veces como se ha indicado en el parámetro "orden"'
    
    'Ahora vamos a sustituir los valores de x por el punto _a_'
    
    return p.subs({x:simbolo}).simplify()

def derivada_numerica(f, x, formula=0, h=1e-5):
    """
    Calcula la derivada numérica de una función en un punto dado utilizando diferentes fórmulas.

    Parámetros:
    - f: función a derivar
    - x: punto en el que se evalúa la derivada
    - formula: tipo de fórmula a utilizar (0: centrada, 1: progresiva, 2: regresiva,3:centrada con dos nodos,4:centrada con cinco nodos)
    - h: paso para la aproximación
    
    Return:
    - Derivada numérica de la función en el punto x utilizando la fórmula especificada.
    - Si la fórmula no es válida, se lanza una excepción.
    """
    if formula == 0:
        # Fórmula centrada
        return (f(x + h) - f(x - h)) / (2 * h)
    elif formula == 1:
        # Fórmula progresiva
        return (f(x + h) - f(x)) / h
    elif formula == 2:
        # Fórmula regresiva
        return (f(x) - f(x - h)) / h
    elif formula == 3:
        # Fórmula centrada con tres nodos
        return (f(x + h) - f(x - h)) / (2 * h)
    elif formula == 4:
        # Fórmula centrada con cinco nodos
        return (-f(x + 2*h) + 8*f(x + h) - 8*f(x - h) + f(x - 2*h)) / (12 * h)
    else:
        raise ValueError("Fórmula no válida. Debe ser 0, 1, 2, 3 o 4.")