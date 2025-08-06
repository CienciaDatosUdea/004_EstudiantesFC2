
# Tarea 01: Simulación de Partículas en una Circunferencia

Este proyecto implementa una simulación en C++ de partículas distribuidas aleatoriamente sobre una circunferencia. Se presentan dos versiones del programa:

- `Tarea_01_estructuras.cpp`: Implementación usando `struct`.
- `Tarea_01_clases.cpp`: Implementación usando `class`.

 Objetivos de la simulación

1. Inicializar N partículas en posiciones aleatorias sobre una circunferencia de radio R.
2. Aplicar perturbaciones aleatorias pequeñas a cada partícula.
3. Calcular la distancia máxima entre cualquier par de partículas.
4. Asignar fuerzas aleatorias a cada partícula.
5. Calcular la fuerza total vectorial del sistema.

Constantes utilizadas

const int NUM_PARTICULAS = 10;
const double RADIO = 1.0;
const double DELTA = 0.1;
const uint64_t SEMILLA = 42;

Instrucciones de compilación y ejecución

Desde una terminal, compila los archivos con:

g++   -std=c++17 -Wall Tarea_01_estructuras.cpp -o Tarea_01_estructuras.out
g++   -std=c++17  -Wall Tarea_01_clases.cpp -o Tarea_01_clases.out
Luego ejecuta cada versión con:

./Tarea_01_estructuras.out
./Tarea_01_clases.out
