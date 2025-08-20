# Guía de compilación y ejecución

Este repositorio contiene dos programas en C++ que trabajan con **partículas en 2D** (coordenadas `x`, `y`) y fuerzas (`fx`, `fy`).  
Ambos programas generan posiciones aleatorias, aplican perturbaciones y calculan propiedades como la **distancia máxima** y la **fuerza neta**.

Los archivos son:

- **`Tarea_01_Structures.cpp`** → Implementación utilizando **estructuras (`struct`)**.  
- **`Tarea_01_Classes.cpp`** → Implementación utilizando **clases (`class`)**.

---

## Funcionalidades principales

1. **Generación de posiciones iniciales** de las partículas.  
2. **Perturbación** de las posiciones.  
3. **Cálculo de la distancia máxima** entre partículas.  
4. **Asignación de fuerzas aleatorias** a cada partículas.  
5. **Cálculo de la fuerza neta** del sistema.  

---

## Entrada y salida

- **Entrada:**  
  No requiere datos del usuario.  
  Los valores se generan aleatoriamente usando `rand()` con una semilla inicializada con `time(NULL)`.

- **Salida:**  
  El programa imprime en consola:
  - Posiciones iniciales de las partículas.  
  - Posiciones perturbadas.  
  - Distancia máxima entre partículas.  
  - Fuerzas asignadas a cada partícula.  
  - Fuerza neta del sistema.  


---

## Compilación

En sistemas Linux, abra una terminal y ubíquese en la carpeta que contiene los archivos `Tarea_01_Classes.cpp` y `Tarea_01_Structures.cpp` usando `cd`.  

Luego ejecute:

g++ -std=c++17 Tarea_01_Structures.cpp -o Tarea_01_Structures.out
g++ -std=c++17 Tarea_01_Classes.cpp -o Tarea_01_Classes.out

Y luego:

./Tarea_01_Structures.out
./Tarea_01_Classes.out


