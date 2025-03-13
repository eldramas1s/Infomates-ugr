import sys
from heapq import heappush, heappop

# Definición de la clase Nodo para representar cada estado del puzzle
class Nodo:
    def __init__(self, estado, padre, movimiento, profundidad, costo):
        self.estado = estado
        self.padre = padre
        self.movimiento = movimiento
        self.profundidad = profundidad
        self.costo = costo

    def __lt__(self, otro):
        return self.costo < otro.costo

    def __eq__(self, otro):
        return self.estado == otro.estado

# Función para calcular la distancia de Manhattan
def distancia_manhattan(estado):
    distancia = 0
    for i in range(9):
        if estado[i] != '0':
            fila_actual, col_actual = divmod(i, 3)
            fila_objetivo, col_objetivo = divmod(int(estado[i]) - 1, 3)
            distancia += abs(fila_actual - fila_objetivo) + abs(col_actual - col_objetivo)
    return distancia

# Función para generar los movimientos posibles
def generar_movimientos(estado):
    movimientos = []
    indice = estado.index('0')
    fila, col = divmod(indice, 3)

    if fila > 0:
        nuevo_estado = list(estado)
        nuevo_estado[indice], nuevo_estado[indice - 3] = nuevo_estado[indice - 3], nuevo_estado[indice]
        movimientos.append(('Arriba', ''.join(nuevo_estado)))

    if fila < 2:
        nuevo_estado = list(estado)
        nuevo_estado[indice], nuevo_estado[indice + 3] = nuevo_estado[indice + 3], nuevo_estado[indice]
        movimientos.append(('Abajo', ''.join(nuevo_estado)))

    if col > 0:
        nuevo_estado = list(estado)
        nuevo_estado[indice], nuevo_estado[indice - 1] = nuevo_estado[indice - 1], nuevo_estado[indice]
        movimientos.append(('Izquierda', ''.join(nuevo_estado)))

    if col < 2:
        nuevo_estado = list(estado)
        nuevo_estado[indice], nuevo_estado[indice + 1] = nuevo_estado[indice + 1], nuevo_estado[indice]
        movimientos.append(('Derecha', ''.join(nuevo_estado)))

    return movimientos

# Función para resolver el 8-Puzzle usando A*
def resolver_8puzzle(estado_inicial):
    objetivo = '123456780'
    abiertos = []
    cerrados = set()

    nodo_inicial = Nodo(estado_inicial, None, None, 0, distancia_manhattan(estado_inicial))
    heappush(abiertos, nodo_inicial)

    while abiertos:
        nodo_actual = heappop(abiertos)

        if nodo_actual.estado == objetivo:
            camino = []
            while nodo_actual.padre:
                camino.append((nodo_actual.movimiento, nodo_actual.estado))
                nodo_actual = nodo_actual.padre
            camino.reverse()
            return camino

        cerrados.add(nodo_actual.estado)

        for movimiento, estado in generar_movimientos(nodo_actual.estado):
            if estado not in cerrados:
                nuevo_nodo = Nodo(estado, nodo_actual, movimiento, nodo_actual.profundidad + 1, nodo_actual.profundidad + 1 + distancia_manhattan(estado))
                heappush(abiertos, nuevo_nodo)

    return None

# Función para imprimir el estado en una cuadrícula de 3x3
def imprimir_estado(estado):
    for i in range(0, 9, 3):
        print(estado[i:i+3])
    print()

# Función principal
def main():
    if len(sys.argv) != 2:
        print("Uso: python 8puzzle.py <configuracion_inicial>")
        sys.exit(1)

    estado_inicial = sys.argv[1]
    if len(estado_inicial) != 9 or not all(c in '012345678' for c in estado_inicial):
        print("La configuración inicial debe ser una cadena de 9 caracteres con dígitos del 0 al 8.")
        sys.exit(1)

    solucion = resolver_8puzzle(estado_inicial)
    if solucion:
        print("Solución encontrada:")
        for movimiento, estado in solucion:
            print(f"Movimiento: {movimiento}")
            imprimir_estado(estado)
    else:
        print("No se encontró solución.")

if __name__ == "__main__":
    main()
