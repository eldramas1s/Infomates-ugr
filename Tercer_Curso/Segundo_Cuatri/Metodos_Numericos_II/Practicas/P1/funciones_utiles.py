

"""
Módulo donde se encuentran las funciones para la resolución de ejercicios.
"""
import sympy as sp
import numpy as np

x=sp.Symbol('x')

def secante(f,x,z):
    '''
        y = secante(f,x,z)
        En este módulo se implementa la función que representa 
        al método de la secante con una iteración. 
        Para mejor comprensión, consideraremos que z aparece 
        en iteraciones posteriores a x.
        
        En caso de que haya una división por cero, se emite
        una excepcion
    '''
    num=(z-x)*f(z)
    den=f(z)-f(x)
    try:
        return z-num/den
    except ZeroDivisionError:
        print("División por cero en la derivada.")
        return None
    

def metodo_secante(f,x0,x1,tol=28,prec=28,max_iter=1000):
    '''
        Metodo de la secante
        
        Parámetros:
        - f: función f(x)
        - x0: primera semilla
        - x1: segunda semilla
        - tol: tolerancia
        - max_iter: número máximo de iteraciones 
               
        Return:
        - array: sucesion de aproximaciones de la raíz
        - iteraciones: número de iteraciones realizadas 
    '''
    array=[x0,x1]       # Con esto evitamos problemas de que el array este vacio
    er_abs=abs(x0-x1)
    for i in range(max_iter):
        array.append(secante(f,array[-2],array[-1]))
        if(abs(array[-1]-array[-2])<10**(-tol) or abs(f(array[-1]))<10**(-prec)):
            return array,i+1
    return array,max_iter

def wittaker(f,x,m):
    '''
        y = wittaker(f,x,m)
        Donde f es la funcion en cuestion, x el dato a evaluar y m es la constante que reemplaza a la derivada de la funcion en el punto x.
    '''
    try:
        return x-f(x)/m
    except ZeroDivisionError:
        print("División por cero en la derivada.")
        return None
    
    
def metodo_wittaker(f,x0,m,tol=28,prec=28,max_iter=1000):
    '''
        Metodo de Wittaker
        
        Parámetros:
        - f: función f(x)
        - x0: valor inicial
        - tol: tolerancia
        - max_iter: número máximo de iteraciones
        
        Return:
        - array: sucesion de aproximaciones de la raíz
        - iteraciones: número de iteraciones realizadas 
    '''
    if(m==0):
        m=1
    array=[x0]       # Con esto evitamos problemas de que el array este vacio
    for i in range(max_iter):
        array.append(wittaker(f,array[-1],m))
        if(abs(array[-1]-array[-2])<10**(-tol) or abs((array[-1]))<10**(-prec)):
            return array,i+1
    return array,max_iter


def newtonraphson(f,z):
    '''
        y = newtonraphson(f,z)
        Donde f es la funcion en cuestion y z el dato a evaluar
        
        Pre: Es necesario que la función sea simbolica pues
        dentro de la función es lambdificada, es decir, se crea una
        version numerica de ella.
        
        Si la funcion no es simbolica dara error.
    '''
    f_num = sp.lambdify(x, f(x), 'numpy')
    df_num=sp.lambdify(x, sp.diff(f(x),x), 'numpy')
    try:
        return (z-(f_num(z)/df_num(z)))
    except ZeroDivisionError:
            print("División por cero en la derivada.")
            return None
        
def metodo_nr(f,x0,tol=28,prec=28,max_iter=1000):
    '''
        Metodo de Newton-Raphson
        
        Parámetros:
        - f: función f(x)
        - x0: valor inicial
        - tol: tolerancia
        - max_iter: número máximo de iteraciones
        
        Pre: Es necesario que la función sea simbolica pues
        dentro de la función newton_raphson es lambdificada, es decir, se crea una
        version numerica de ella.
        
        Si la funcion no es simbolica dara error.
        
        Return:
        - array: sucesion de aproximaciones de la raíz
        - iteraciones: número de iteraciones realizadas        
    '''
    array=[x0]       # Con esto evitamos problemas de que el array este vacio
    for i in range(max_iter):
        array.append(newtonraphson(f,array[-1]))
        if(abs(array[-1]-array[-2])<10**(-tol)or abs(f(array[-1]))<10**(-prec)):
            return array,i+1
    return array,max_iter
   
def biseccion(f, a, b,tol=28,prec=28,max_iter=1000):
    '''
        Metodo de biseccion
        
        Parámetros:
        - f: función f(x)
        - a: extremo inferior del intervalo
        - b: extremos superior del intervalo
        - tol: tolerancia
        - max_iter: número máximo de iteraciones
        
        Pre: f(a)*f(b)<0
        Return:
        - array: sucesion de aproximaciones de la raíz
        - iteraciones: número de iteraciones realizadas

    '''
    array=[(a+b)/2]
    
    for i in range(max_iter):
        if(f(array[-1])*f(a)<0):
            b=array[-1]
            
        else:
            a=array[-1]
            
        array.append((a+b)/2) 
            
        if((abs(array[-1]-array[-2])<10**(-tol)) or abs(f(array[-1])) < 10**(-prec)):
            return array,i
    return array, max_iter


def metodo_steffensen(f, x0, tol=28,prec=28, max_iter=1000):
    '''
        Metodo de Steffensen
        
        array,iter=metodo_steffensen(f,x0,tol,max_iter)
        
        Parámetros:
        - f: función f(x)
        - x0: valor inicial
        - tol: tolerancia
        - max_iter: número máximo de iteraciones
               
        Return:
        - array: sucesion de aproximaciones de la raíz
        - iteraciones: número de iteraciones realizadas
    '''
    array=[x0]
    for i in range(max_iter):
        try:
            num=f(array[-1])**2
            denom = f(array[-1]+f(array[-1]))-f(array[-1])
            array.append(array[-1] - num / denom)
            if abs(array[-1] - array[-2]) < 10**(-tol) or abs(f(array[-1]))<10**(-prec):
                return array,i+1
        except ZeroDivisionError:
            print("División por cero en la derivada.")
            return None, i
        
    return array,max_iter


def newton_steffensen(f, x0, tol=28,prec=28,max_iter=1000):
    '''
        Método de Newton-Raphson con aceleración de Steffensen.
        
        Parámetros:
        - f: función f(x)
        - x0: valor inicial
        - tol: tolerancia
        - max_iter: número máximo de iteraciones
        
        Pre:
        - Al usar newtonraphson requiere que la funcion sea simbolica
        Return:
        - array: sucesion de aproximaciones de la raíz
        - iteraciones: número de iteraciones realizadas
    '''
    array=[x0]
    x=x0
    for i in range(max_iter):
        try:
            x1=newtonraphson(f,x)    #x1
            x2=newtonraphson(f,x1)    #x2
            
            # Evita división por cero
            den = x2+x-2*x1
            num=(x1-x)**2
            # Aceleración de Steffensen
            array.append(x-(num/den))

            x=array[-1]
            
            if (abs(array[-1]-array[-2]) < 10**(-tol) or abs(f(array[-1]))<10**(-prec)):
                return array, i+1

        except ZeroDivisionError:
            print("División por cero en la derivada.")
            return None, i
    return x,max_iter 

def aitken_accelerator(array):
    '''
    Aceleracion de Aitken
    
    Parámetros:
    - array: lista o array de valores [x0, x1, ..., xn]
    
    Retorna:
    - accelerated: array de valores acelerados (len = len(sequence) - 2)
'''
    n = len(array)
    if n < 3:
        raise ValueError("Se necesitan al menos 3 elementos para aplicar Aitken.")
    
    accelerated = []
    for i in range(n - 2):
        try:
            num=(array[i+1]-array[i])**2
            den=(array[i+2]+array[i]-2*array[i+1])
            accelerated.append(array[i]-num/den)
        except ZeroDivisionError:
            print("División por cero en la derivada.")
            return None, i
    
    return accelerated