# Guía de uso del programa

## Compilación y ejecución

1. **Compilación**

   Para compilar los programas en C++, utiliza el compilador `g++`:

   - Para **estructuras**:

     ```bash
     g++ -o Tarea_01_estructuras Tarea_01_estructuras.cpp -lm
     ```

   - Para **clases**:

     ```bash
     g++ -o Tarea_01_clases Tarea_01_clases.cpp -lm
     ```

2. **Ejecución**

   Para ejecutar los programas:

   - Para **estructuras**:

     ```bash
     ./Tarea_01_estructuras
     ```

   - Para **clases**:

     ```bash
     ./Tarea_01_clases
     ```

3. **Salida esperada**

   El programa calculará la distancia máxima entre las partículas después de aplicar una perturbación aleatoria y mostrará el resultado en la consola.

## Notas

- El valor de `N` (número de partículas) está predefinido en 10, pero se puede modificar en el código fuente.
- El valor de `DELTA` controla el rango de las perturbaciones aleatorias.
