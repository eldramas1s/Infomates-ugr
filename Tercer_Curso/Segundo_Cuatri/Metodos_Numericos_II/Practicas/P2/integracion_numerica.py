
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

def Trapecio_simple(f,a,b):
    '''
    Fórmula simple del trapecio 
    Parametros:
    f: función a integrar
    a: límite inferior
    b: límite superior
    Devuelve:
    aproximación de la integración
    '''
    return (b-a)*(f(a)+f(b))/2
    
def Simpson_simple(f,a,b):
    '''
    Fórmula simple de Simpson
    Parámetros:
        f: funcion a integrar
        a: limite inferior
        b: limite superior
        Devuelve:
        aproximacion de la integral
    '''
    return (b-a)/6*(f(a)+4*f((a+b)*0.5)+f(b))

def Simpson_compuesta(f,a,b,n):
    """ 
    Fómula compuesta de Simpson
        Parametros:
        f: función a integrar
        a: límite inferior
        b: límite superior
        n: número de subintervalos
        Devuelve:
        resultado de la integración
    """
    
    h=(b-a)/n
    
    suma=f(a)+f(b)
    
    # Generaremos 2(n+1) nodos para la integración simulando ya que se han tomado los puntos medios.
    
    x_values = np.linspace(a, b, n+1)  # Genera los nodos de integración
    
    for i in range(1, len(x_values)-1):
        if i%2==0:
            suma+=2*f(x_values[i])
        else:
            suma+=4*f(x_values[i])
    return (h/3)*suma

def Trapecios_compuesta(f,a,b,n):
    """fórmula compuesta de los trapecios
        Parametros:
        f: función a integrar
        a: límite inferior
        b: límite superior
        n: número de subintervalos
        Devuelve:
        resultado de la integración
    """
    
    h=(b-a)/n
    
    suma=f(a)+f(b)
    
    # Generaremos 2(n+1) nodos para la integración simulando ya que se han tomado los puntos medios.
    
    x_values = np.linspace(a, b, n+1)  # Genera los nodos de integración
    
    for i in range(1, len(x_values)-1):
        suma+=2*f(x_values[i])
    return (h/2)*suma

def calcular_T2n(i, a, b, f, Ti):
    """
    Calcula el valor de T2n utilizando el método del trapecio.
    Parámetros:
    i: índice del nivel anterior
    a: límite inferior
    b: límite superior
    f: función a integrar
    Ti: Ti (nivel anterior)
    Devuelve:
    T2n: valor de T2n
    """
    n = 2**i
    h = (b - a) / n
    suma = 0

    for k in range(n):
        x_medio = a + (k + 0.5) * h
        suma += f(x_medio)

    return Ti *0.5 + h *0.5 * suma

def Integracion_Romberg(f,a,b,tol=5,max_iter=20):
    """
    Método de integración de Romberg.
    Parametros:
    f: función a integrar
    a: límite inferior
    b: límite superior
    N: número de pasos
    Devuelve:
    resultado de la integración
    """

    romberg0 = [Trapecios_compuesta(f, a, b, 1)]
    
    for n in range(1, max_iter):
        # Se calcula R(n,0)
        romberg1 = [Trapecios_compuesta(f, a, b, 2**n)]
        
        # Se calculan R(n,i) con 1 <= i <= n
        for i in range(1, n + 1):
            romberg1.append((4**i * romberg1[i - 1] - romberg0[i - 1]) / (4**i - 1))
        
        # Condición de parada usando los últimos elementos de la diagonal
        if abs(romberg1[n] - romberg0[n - 1]) < 10**tol:
            return romberg1[n]

        # Actualiza romberg0 para la siguiente iteración
        romberg0 = romberg1
    
    # Si se alcanza el máximo de iteraciones sin cumplir la condición
    print("Advertencia: no se alcanzó la tolerancia deseada.")
    return romberg1[-1]

def Integracion_adaptativa(f,a,b,eps):
    '''
    Metodo de integracion adaptativa
    Parámetros:
        f: funcion a integrar
        a: limite inferior
        b: limite superior
        eps: valor de acotación del error
        
    Devuelve:
    aproximación de la integral
    '''
    m=(a+b)/2
    valor_base=Simpson_simple(f,a,b)
    valor_izq=Simpson_simple(f,a,m)
    valor_dcha=Simpson_simple(f,m,b)
    
    if(abs(valor_base-valor_izq-valor_dcha)>=10*eps):
        return( Integracion_adaptativa(f,a,m,eps*0.5)+Integracion_adaptativa(f,m,b,eps*0.5))
    else:
        return valor_izq+valor_dcha