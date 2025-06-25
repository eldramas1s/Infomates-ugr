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

def derivada_numerica_iterativa(f, a, formula, n=1, h=0.001):
    
    '''
    Función que calcula la derivada numérica de una función en un punto dado utilizando una fórmula específica.
    Procede de forma iterativa para calcular la derivada de orden n.
    Parámetros:
    - f: función a derivar
    - a: punto en el que se evalúa la derivada
    - formula: fórmula a utilizar para calcular la derivada
    - n: orden de la derivada a calcular (por defecto 1)
    - h: paso a utilizar para la derivada numérica (por defecto 1e-5)
    Retorna:
    - Derivada numérica de orden n de la función en el punto dado
    '''
    
    if n==0:
        return f(a)
    else:
        fn = f          # Derivada n-ésima de f según la aproximación.
        for i in range(n):
            fn = lambda x, fn=fn: formula(fn, x, h)
    
    return fn(a)
    
   
def derivada_numerica_recursiva(f, a, formula, n=1, h=1e-5):
    
    '''
    Función que calcula la derivada numérica de una función en un punto dado utilizando una fórmula específica.
    Procede de forma recursiva para calcular la derivada de orden n.
    Parámetros:
    - f: función a derivar
    - a: punto en el que se evalúa la derivada
    - formula: fórmula a utilizar para calcular la derivada
    - n: orden de la derivada a calcular (por defecto 1)
    - h: paso a utilizar para la derivada numérica (por defecto 1e-5)
    Retorna:
    - Derivada numérica de orden n de la función en el punto dado
    '''
    
    if n==0:
        return f(a)
    else:
        return formula(lambda x: derivada_numerica_recursiva(f,x,formula,n-1,h),a,h)