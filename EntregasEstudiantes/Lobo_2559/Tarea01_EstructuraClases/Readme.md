
# TAREA01: Simulación de partículas distribuidas en una circunferencia

Este proyecto contiene dos versiones de un programa en C++ que simula un sistema de partículas distribuidas aleatoriamente en un espacio bidimensional. Cada partícula tiene una posición y una fuerza asociada.

El primer paso de este código es inicializar las particulas en posiciones aleatorias dentro de un círculo. Se aplica una perturbación aleatoria a sus posiciones. Luego, se calculan la distancia máxima entre todas las partículas y la fuerza total del sistema.

# Contenido:
1. Tarea_01_estructuras.cpp: Se crea una estructura que representa una partícula. Las operaciones se aplican por medio de funciones globales.

2. Tarea_01_clases.cpp. Se crea las clases particula y Sistema para modelar el problema.


# ¿Cómo compilar?
Para complicar escribir en la terminal:
g++ Tarea_01_estructuras.cpp -o Tarea_01_estructuras.out
g++ Tarea_01_clases.cpp -o Tarea_01_clases.out


# Para ejecutar
./Tarea_01_estructuras.out   # Ejecuta la versión con struct
./Tarea_01_clases.out   # Ejecuta la versión con clases
