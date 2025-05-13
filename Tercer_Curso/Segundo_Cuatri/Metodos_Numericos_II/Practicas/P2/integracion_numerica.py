
"""
Módulo donde se encuentran las funciones para la resolución de ejercicios de integracion numerica.
"""

import sympy as sp
import numpy as np
from sympy.polys.polyfuncs import interpolate 
import matplotlib.patches as patches

def linea(x,xL,yL,xR,yR):
    """línea uniendo los puntos (xL,yL) y (xR,yR)"""
    return np.interp(x, [xL,xR], [yL,yR])  # Interpolación lineal entre los puntos (xL,yL) y (xR,yR)

def parabola(x,xL,yL,xM,yM,xR,yR):
    """parábola uniendo los puntos (xL,yL), (xM,yM) y (xR,yR)"""
    return np.interp(x, [xL, xM, xR], [yL, yM, yR])


def formula_rectangulo_derecha(f,a,b,n):
    """fórmula compuesta de los rectangulos a derecha"""
    h = (b-a)/n
    nodos = np.linspace(a, b, n+1)  # Genera los nodos de integración
    return h*np.sum(f(nodos[1:len(nodos)]))

def formula_rectangulo_medio(f,a,b,n):
    """fórmula compuesta de los rectangulos del punto medio"""
    h = (b-a)/n
    nodos = np.linspace(a, b, n+1)  # Genera los nodos de integración
    sum=0
    for i in range(1, len(nodos)):
        sum+=f((nodos[i-1]+nodos[i])/2)
    return h*sum