# Sistema de N partículas

Estos códigos implementan un sistema de N partículas que yacen en una circunferencia de radio R. Cada partícula se inicializa en una posición aleatoria dentro de la circunferencia y luego se actualiza su posición con un desplazamiento aleatorio. El sistema calcula la distancia mínima entre las partículas y la fuerza neta que actúa sobre ellas.

El código está dividido en dos archivos: uno para las clases y otro para las estructuras. 

El archivo `Tarea_01_clases.cpp` define la clase `particula`, que representa una partícula en el sistema, y la clase `sistema`, que representa el sistema de partículas. La clase `particula` tiene métodos para inicializar su posición y actualizar su posición con un desplazamiento aleatorio. La clase `sistema` tiene métodos para inicializar todas las partículas, calcular la distancia mínima entre ellas y calcular la fuerza neta que actúa sobre ellas.

El archivo `Tarea_01_estructuras.cpp` define la estructura `particula`, que representa una partícula en el sistema, y la estructura `sistema`, que representa el sistema de partículas. Los métodos antes en las clases se implementan por funciones que realizan las mismas tareas. 

**Parámetros iniciales:**

N: Cantidad de partículas, 10.0 por defecto \
R: Radio de la circunferencia, 1.0 por defecto\
DELTA: Máximo desplazamiento aleatorio, 0.1 por defecto

**Parámetros de salida:**

Distancia mínima entre partículas\
Fuerza neta sobre el sistema

## Funcionamiento

Para compilar use:

    g++ -std=c++17 -Wall Tarea_01_clases.cpp -o Tarea_01_clases.out
    g++ -std=c++17 -Wall Tarea_01_estructuras.cpp -o Tarea_01_estructuras.out

Para ejecutar use:

    ./Tarea_01_clases.out 
    ./Tarea_01_estructuras.out 


