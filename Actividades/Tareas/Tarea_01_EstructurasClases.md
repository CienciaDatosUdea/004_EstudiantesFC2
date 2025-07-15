# Problema: Simulación de partículas distribuidas en una circunferencia

Diseñe un programa en C++ que simule un sistema de **N partículas distribuidas aleatoriamente sobre una circunferencia** (esfera en 2D) y que permita realizar las siguientes operaciones físicas:

## 🎯 Objetivos funcionales

1. **Inicialización de partículas:**
   - Genere `N` partículas distribuidas uniformemente sobre una circunferencia de radio 1, centrada en el origen.
   - Cada partícula tendrá una posición `(x, y)` calculada a partir de un ángulo aleatorio `θ ∈ [0, 2π]`.

2. **Perturbación aleatoria:**
   - Aplique a cada partícula una perturbación `(dx, dy)` con valores aleatorios pequeños en el intervalo `[-Δ, Δ]`, para simular ruido o movimiento térmico.

3. **Cálculo de distancia máxima:**
   - Calcule la **distancia máxima** entre cualquier par de partículas luego de la perturbación.

4. **Asignación de fuerzas:**
   - A cada partícula asígnesele un vector de fuerza `(fx, fy)` con componentes aleatorias en el intervalo `[0, 1]`.

5. **Cálculo de la fuerza total:**
   - Calcule la **fuerza total resultante del sistema**, sumando vectorialmente las componentes de todas las fuerzas y reportando su magnitud.

---

##  Requisitos de implementación

- El programa debe estructurarse utilizando C++ y debe ser modular y claro.
- Debe **implementar la solución usando:**
  - `struct` (estructura de datos tipo C)  
  - `class` 

###  En su entrega debe incluir:
- La **implementación completa** del programa llamada: 
    - Tarea_01_estructuras.cpp
    - Tarea_01_clases.cpp
    - Tarea_01_estructuras.out
    - Tarea_01_clases.out
    - Readme.md: Guia de uso de los programas 




##  Constantes sugeridas

```cpp
const int N = 10;         // Número de partículas
const double R = 1.0;     // Radio de la circunferencia
const double DELTA = 0.1; // Rango de perturbación aleatoria
```