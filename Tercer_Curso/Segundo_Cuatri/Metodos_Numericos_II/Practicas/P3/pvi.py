"""
Módulo donde se encuentran las funciones para la resolución de ejercicios de problemas de valores iniciales.
"""

import sympy as sp
import numpy as np
from scipy.optimize import fsolve

def euler_explicito(f, a, b, mu, N):
    """
        Método de Euler explícito para resolver la ecuación diferencial
        x' = f(t,x) con condición inicial x(a) = mu en el intervalo [a,b]
        con N pasos.
    """
    h = (b - a) / N
    t = np.linspace(a, b, N + 1)
    x = np.zeros((N + 1,))
    x[0] = mu
    for n in range(N):
        x[n + 1] = x[n] + h * f(t[n], x[n])
    return t, x

def euler_implicito(f, a, b, mu, N):
    """
        Método de Euler explícito para resolver la ecuación diferencial
        x' = f(t,x) con condición inicial x(a) = mu en el intervalo [a,b]
        con N pasos.
    """
    h = (b - a) / N
    t = np.linspace(a, b, N + 1)
    x = np.zeros(N + 1)
    x[0] = mu
    # x1 = sp.symbols('x1')
    for n in range(N):
        # x[n + 1] = np.float64(sp.solve(x[n]+h*f(t[n+1],x1)-x1,x1)[0])
        x[n + 1] = fsolve(lambda x1: x[n] + h * f(t[n + 1], x1) - x1, x[n])[0]
    return t, x


def euler_punto_medio(f, a, b, mu, N):
    """
        Método de Euler del punto_medio para resolver la ecuación diferencial
        x' = f(t,x) con condición inicial x(a) = mu en el intervalo [a,b]
        con N pasos.
    """
    h = (b - a) / N
    t = np.linspace(a, b, N + 1)
    x = np.zeros(N + 1)
    x[0] = mu        
    for n in range(N):
        k1 = f(t[n], x[n])
        x_med = x[n] + (h / 2) * k1
        t_med = t[n] + h / 2
        k2 = f(t_med, x_med)
        x[n+1] = x[n] + h * k2
    return t, x

def euler_Heun(f,a,b,mu,N):
    '''
        Método de Euler de Heun para resolver la ecuación diferencial
        x' = f(t,x) con condición inicial x(a) = mu en el intervalo [a,b]
        con N pasos.
    '''
    h = (b - a) / N
    t = np.linspace(a, b, N + 1)
    x = np.zeros(N + 1)
    x[0] = mu
    for n in range(N):
        k1 = f(t[n], x[n])
        k2 = f(t[n] + h, x[n] + h * k1)
        x[n + 1] = x[n] + (h / 2) * (k1 + k2)
    return t, x

def RK4(f, a, b, mu, N):
    """
        Método de Runge-Kutta de orden 4 clásico para resolver la ecuación diferencial
        x' = f(t,x) con condición inicial x(a) = mu en el intervalo [a,b]
        con N pasos.
        Parámetros:
            f: función que define la ecuación diferencial
            a: límite inferior del intervalo
            b: límite superior del intervalo
            mu: valor inicial de x en a
            N: número de pasos
            alpha: coeficiente de la parte implícita (por defecto 1)
            beta: coeficiente de la parte explícita (por defecto 1/6)
        Devuelve:
            t_values: valores de t que se han usado
            x_values: aproximaciones obtenidas
    """
    h = (b - a) / N
    t_values = np.linspace(a, b, N + 1)
    x_values = np.zeros(N + 1)
    x_values[0] = mu
    for n in range(N):
        K1 = f(t_values[n], x_values[n])
        K2 = f(t_values[n] + 0.5 * h, x_values[n] + 0.5 * h * K1)
        K3 = f(t_values[n] + 0.5 * h, x_values[n] + 0.5 * h * K2)
        K4 = f(t_values[n] + h, x_values[n] + h * K3)
        x_values[n + 1] = x_values[n] + h/6 * (K1 + 2*K2 + 2*K3 + K4)
    return t_values, x_values

def RK2(f, a, b, mu, N, alpha=0.5, beta=1):
    """
        Método de Runge-Kutta de orden 2 para resolver la ecuación diferencial
        x' = f(t,x) con condición inicial x(a) = mu en el intervalo [a,b]
        con N pasos.
    """
    h = (b - a) / N
    t_values = np.linspace(a, b, N + 1)
    x_values = np.zeros(N + 1)
    x_values[0] = mu
    for n in range(N):
        K1 = f(t_values[n], x_values[n])
        K2 = f(t_values[n] + beta * h, x_values[n] + beta * h * K1)
        x_values[n + 1] = x_values[n] + h * ((1-alpha)*K1 + alpha*K2)
    return t_values, x_values

def predictor_corrector_AB5_AM4(f, a, b, x0, x1, x2, x3, x4, N):
    """
        Método predictor-corrector de 5 pasos (AB5-AM4) para resolver la ecuación diferencial
        x' = f(t,x) con condiciones iniciales x0, x1, x2, x3, x4 en el intervalo [a,b]
        con N pasos.

        Utiliza el método explícito de Adam-Bashforth de orden 5 (AB5) para la predicción
        y el método implícito de Adam-Moulton de orden 4 (AM4) para la corrección.
        
        Parámetros:
            f: función que define la ecuación diferencial
            a: límite inferior del intervalo
            b: límite superior del intervalo
            x0, x1, x2, x3, x4: valores iniciales de la solución en los puntos a, a+h, a+2h, a+3h y a+4h
            N: número de pasos
        Devuelve: 
            t_values: valores de t que se han usado
            x_values: aproximaciones obtenidas
    """
    h = (b - a) / N
    x_predict = np.zeros(N + 1)
    t_values = np.linspace(a, b, N + 1)
    x_values = np.zeros(N + 1)
    x_values[0] = x_predict[0]=x0
    x_values[1] = x_predict[1]=x1
    x_values[2] = x_predict[2]=x2
    x_values[3] = x_predict[3]=x3
    x_values[4] = x_predict[4]=x4
    
    # Predicción, usaremos la fórmula abierta de 4 pasos:
    for n in range(N-4):
        
        # Predicción, usaremos el método de Adam-Bashforth de orden 4:
        x_predict[n + 5] = x_values[n+4]+h/720*(1901*f(t_values[n+4],x_values[n+4])-
                                  2774*f(t_values[n+3],x_values[n+3])+2616*f(t_values[n+2],x_values[n+2])-
                                  1274*f(t_values[n+1],x_values[n+1])+251*f(t_values[n],x_values[n]))
        # Corrección, usaremos la regla de Simpson:
        x_values[n + 5] = x_values[n+4]+h/720*(251*f(t_values[n+5],x_predict[n+5])+
                                               646*f(t_values[n+4],x_values[n+4])-264*f(t_values[n+3],x_values[n+3])+
                                               106*f(t_values[n+2],x_values[n+2])-19*f(t_values[n+1],x_values[n+1]))
        

    return t_values, x_values


def getX(t_obj,sol):
    """
        Función para obtener el valor de x(t) a partir de la solución de un PVI.
        Parámetros:
            t_obj: valor de t para el cual se quiere obtener x(t)
            sol: solución del PVI, que debe contener los atributos 't' y 'y'
        Devuelve:
            x(t_obj): valor de x en t_obj
    """

    # Buscar el índice más cercano en sol.t
    indice = np.argmin(np.abs(sol.t - t_obj))

    # Obtener x(t_objetivo) aproximado
    x_t = sol.y[0][indice]

    return x_t
