Sistema de Partículas en Circunferencia


Descripción del Problema
Este proyecto simula un sistema de N partículas que se mueven dentro de una circunferencia de radio R. Cada partícula:

Se inicializa en una posición aleatoria dentro de la circunferencia

Experimenta oscilaciones mediante desplazamientos aleatorios en cada paso de tiempo

Interactúa con las demás partículas a través de fuerzas aleatorias

El sistema calcula:

La distancia mínima entre partículas

La fuerza neta resultante del sistema

La magnitud de la fuerza total

Objetivo Científico

Simular el comportamiento oscilatorio de partículas confinadas en una geometría circular, representando fenómenos físicos como:

Partículas en potenciales armónicos

Sistemas oscilatorios acoplados

Dinámica de partículas en trampas magnéticas

 Estructura del Proyecto
text
particulas-circunferencia/
│
├── particulas_clases.cpp    # Versión orientada a objetos con clases
├── particulas_estructuras.cpp # Versión procedural con estructuras
├── Makefile                 # Archivo para compilación automatizada
└── README.md               # Este archivo

 Compilación
Requisitos
Compilador C++17 (g++ 7.0 o superior)

Sistema Linux/Unix (recomendado) o Windows con WSL

Compilación Manual
Versión con Clases:

bash
g++ -std=c++17 -Wall -O2 particulas_clases.cpp -o particulas_clases
Versión con Estructuras:

bash
g++ -std=c++17 -Wall -O2 particulas_estructuras.cpp -o particulas_estructuras
Usando el Makefile
bash
# Compilar ambas versiones
make all

# Compilar solo versión con clases
make clases

# Compilar solo versión con estructuras
make estructuras

# Limpiar archivos compilados
make clean
Ejecución
Parámetros por Defecto
bash
./particulas_clases
# o
./particulas_estructuras
Valores por defecto: N=10, R=1.0, DELTA=0.1

Parámetros Personalizados
bash
./particulas_clases [N] [R] [DELTA]
./particulas_estructuras [N] [R] [DELTA]
Ejemplos:

bash
# 20 partículas, radio 2.0, delta 0.05
./particulas_clases 20 2.0 0.05

# 50 partículas, radio predeterminado, delta 0.2
./particulas_estructuras 50 1.0 0.2
Parámetros del Sistema
Parámetro	Descripción	Valor por Defecto
N	Número de partículas	10
R	Radio de la circunferencia	1.0
DELTA	Máximo desplazamiento aleatorio	0.1


Output del Programa
El programa muestra:

Estado inicial de las partículas

5 iteraciones con perturbaciones aplicadas

Por cada iteración:

Posiciones de todas las partículas

Distancia mínima entre partículas

Magnitud de la fuerza resultante

Ejemplo de output:

text
Parámetros: N=10, R=1.0, DELTA=0.1

Estado inicial:
Partícula 0: (0.342, 0.940) Fuerza: (0.123, 0.456)
...
Distancia mínima: 0.234
Magnitud fuerza resultante: 5.678

Después de la perturbación 1:
...


 Análisis del Comportamiento
Oscilaciones
Las partículas exhiben movimiento oscilatorio debido a:

Perturbaciones aleatorias limitadas por DELTA

Confinamiento en la circunferencia de radio R

Fuerzas aleatorias que actúan sobre cada partícula

Estabilidad del Sistema
DELTA pequeño: Oscilaciones suaves, sistema más estable

DELTA grande: Movimientos más bruscos, mayor variabilidad

N grande: Mayor probabilidad de interacciones entre partículas



 Solución de Problemas
Error de Compilación
bash
# Si falta std=c++17
error: ‘std::optional’ has not been declared
Solución: Asegurar que el compilador soporta C++17

Errores de Ejecución
bash
# Si los parámetros no son números
Segmentation fault (core dumped)
Solución: Verificar que los argumentos sean numéricos


