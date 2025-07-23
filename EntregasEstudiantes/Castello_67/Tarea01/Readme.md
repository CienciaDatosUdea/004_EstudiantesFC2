Los presentes codigos son scripts de C++ que generan un conjunto de partículas en el plano, uniformemente
distribuidad en el circulo unitario, se les aplica una perturbación aleatoria y calcula la distancia mínima 
entre pares de partículas y la fuerza total del sistema.

## Archivos

- `Tarea_01_clases.cpp`
- `Tarea_01_struct.cpp`

El primero de los archivos implementa la solucion al sistema fisico anteriormente propuesto ultilizando clases de c++,
mientras que el segundo implementa la solucion ultilizando la estructura de datos de c++ `struct`.

## Requisitos

- **Compilador**: GCC (g++) versión ≥ 5.0  
- **Estándar C++**: C++17 o superior  
- Sistema operativo Linux, macOS o Windows con MinGW

## Compilación

Abre una terminal en la carpeta donde esten los archivos y ejecutar:

```bash
g++ -std=c++17 -Wall Tarea_01_clases.cpp -o Tarea_01_clases.out 
```

```bash
g++ -std=c++17 -Wall Tarea_01_struct.cpp -o  Tarea_01_struct.out
``` 


