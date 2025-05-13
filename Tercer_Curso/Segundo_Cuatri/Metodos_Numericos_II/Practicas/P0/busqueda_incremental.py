# -*- coding: UTF-8 -*-
## modulo busqueda_incremental
'''
x1,x2 = busqueda_incremental(f,a,b,dx)
buscará dentro del intervalo [a,b] en incrementos de dx una acotación
de la forma [x1,x2] de la raíz más pequeña de f(x) en dicho intervalo.
Se devolverá x1 = x2 = None en caso de no encontrarse ninguna.
'''
# global f,a,b,dx

def busqueda_incremental(f,a,b,dx):
    x1, x2 = a, a + dx
    f1, f2 = f(x1), f(x2)
    while np.sign(f1) == np.sign(f2):
        if x1 >= b:
            return None,None   # se podría cambiar por x2 >= b
        x1, x2 = x2, x2 + dx
        f1, f2 = f2, f(x2)
    else: # si no se cumple la condición del while
        return x1,x2
