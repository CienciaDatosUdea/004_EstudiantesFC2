# Tarea 01 — Estructuras y Clases en C++

Este proyecto implementa un sistema de partículas con dos enfoques:
1. **Estructuras (`struct`)**
2. **Clases (`class`)**

## Funcionalidad
- Genera `N` partículas en una circunferencia unitaria.
- Aplica una perturbación aleatoria `[-Δ, Δ]` a cada partícula.
- Calcula distancias mínima y máxima entre partículas.
- Asigna fuerzas aleatorias en [0, 1] a cada partícula.
- Calcula la magnitud de la fuerza total del sistema.

## Archivos
- `Tarea_01_estructuras.cpp` → versión con `struct`.
- `Tarea_01_clases.cpp` → versión con `class`.
- `Tarea_01_estructuras.out` → salida de ejemplo para estructuras.
- `Tarea_01_clases.out` → salida de ejemplo para clases.

## Compilación
```bash
g++ Tarea_01_estructuras.cpp -o Tarea_01_estructuras
g++ Tarea_01_clases.cpp -o Tarea_01_clases

