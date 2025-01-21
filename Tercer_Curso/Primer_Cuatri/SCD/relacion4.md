# Relación 4.

91.
Th = mcm(Ti) = 240

20 = max{Ci} <= Ts <= min{Di} = 40
Y además debe ser un divisor del hiperperiodo:
Ts = Th / k = {25, 20, 40}

1 2 3
1 4
1 2
1 2
1 2

92.
Th = mcm = 24
max{Ci} = max{2,3} = 3 <= Ts <= min{Di} = min{6,8,12} = 6
Ts divisor de 24 => por ejemplo, 4.

var inicio : time_point := now();
while true do begin
   T1; T2; sleep_until(inicio + 4);
   T3; sleep_until(inicio + 8);
   T1; sleep_until(inicio + 12);
   T1; sleep_until(inicio + 16);
   T3; sleep_until(inicio + 20);
   T1; T2; sleep_until(inicio + 24);
   inicio := now();
end

93.
Calculo el factor de utilización del procesador:
U = 2/6 + 2/5 + 3/12 = 3/4 = 0.75 < 0.779 = U_0(N=3)
Es planificable por el test RMS.

94.
U = 1/4 + 1/3 + 1/4 = 5/6 = 0.83 (periodo 3) \not <= 0.779
No pasa el test RMS, no podemos saber si es planificable o no.

La única forma es hacer el diagrama con el algoritmo RMS:


T1   T1             |T1             |T1             |T1             |T1             |T1             |T1 
                    |               |               |               |               |               |
T2       T2  T2     |       |T2  T2 |               A               |       |       |               A  
                    |       |       |               |               |       |       |               |
T3               T3 |    T3 |       A               |               A       |       |               A  
    0  10  20  30  40  50  60  70  80  90 100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250
    
R1 = 10, consigue terminarse completamente en su primera activación en T 10
R2 = 30, consigue terminar primera activación en T30.
R3 = 60, consigue terminar en T 60.

Si hay dos activaciones de igual prioridad no hay nada definido.

96.
U = 97/100 = 0.97 not <= 0.743 = U_0(5)
Sin embargo, es planificable.
La condición necesaria se cumple, ya que U < 1.

El periodo de cualquier tarea es el doble del periodo anterior, luego si demostramos que es planificable con RMS e intentramos planificar con EDF:
El límite más cercano va a coincidir con el límite de la tarea más prioritaria, luego planificable con RMS => planificable con EDF (plazo límite más cercano).

T1   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |    |                    
T2   |   A   |   A   |   A   |   A   |   A   |   A   |   A   |   A   |   A   |    A                    
T3   |   |   |   A   |   |   |   A   |   |   |   A   |   |   |   |   |   |   |    |                    
T4   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |    |                    
T5   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |    |                    
     5  10  15  20  25  30  35  40  45  50  55  60  65  70  75  80  85  90  95  100
     
Sale:
R1 = 1          R2 = 2          R3 = 4      R5 = 79
Planificable por RMS y como el ciclo de cada tarea es el doble de la anterior, RMS => EDF.

97.
U = 1/5 + 1/10 + 2/10 + 11/20 + 5/100 = 110/100 > 1 
NO ES PLANIFICABLE por ningún método.

98.
mcm{3,6,13} = 78 (?)

U = 1/3 + 1/2 + 2/13 = 75/78 not <= 0.779

Diagrama de Gant:

T1 cada 3, hace 1.
T2 cada 6
T3 cada 13

T1                                                                                                                                             
T2                                                                                                                                            
T3                                                                                                                                           
         5      10      15      20      25      30      35      40      45      50      55      60      65      70      75      80      85
         
R1 = 1
R2 = 5
R3 = 12

Interferencias:
T1 a T3: floor[ T3 / T1 ] = 4
T1 a T2: floor[ T2 / T1 ] = 2

102. F V V F V F

103. 
Up = 1/5 + 2/8 = 1/5 + 1/4 = 0.45
    n = 2:
Us \leq 2 (n/(Up+n))^n - 1 = 0.33
