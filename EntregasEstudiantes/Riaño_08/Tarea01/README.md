### Guía de Uso: Programas de Simulación de Partículas

Este repositorio contiene dos versiones de un programa en C++ que simulan el comportamiento básico de un conjunto de partículas. Ambas versiones realizan las mismas tareas: inicialización de partículas, perturbación de sus posiciones, cálculo de la distancia máxima entre ellas y cálculo de la fuerza total. La diferencia principal radica en el enfoque de programación utilizado.

  - **`Tarea_01_clases.cpp`**: Utiliza un enfoque de **Programación Orientada a Objetos (POO)**.
  - **`Tarea_01_estructuras.cpp`**: Utiliza un enfoque de **Programación Estructurada**.

#### 1\. Requisitos

Necesitas un compilador de C++ (como `g++`) para compilar y ejecutar los programas.

#### 2\. Compilación

Puedes compilar los programas desde la terminal. Abre tu terminal y navega hasta el directorio donde se encuentran los archivos.

  - **Compilar la versión de clases**:

    ```bash
    g++ Tarea_01_clases.cpp -o Tarea_01_clases -lm
    ```

    El `-lm` es necesario para enlazar la biblioteca matemática (`<cmath>`).

  - **Compilar la versión de estructuras**:

    ```bash
    g++ Tarea_01_estructuras.cpp -o Tarea_01_estructuras -lm
    ```

#### 3\. Ejecución

Una vez compilados, se crearán archivos ejecutables con los nombres `Tarea_01_clases` y `Tarea_01_estructuras`. Puedes ejecutarlos de la siguiente manera:

  - **Ejecutar el programa de clases**:

    ```bash
    ./Tarea_01_clases
    ```

  - **Ejecutar el programa de estructuras**:

    ```bash
    ./Tarea_01_estructuras
    ```

#### 4\. Salida esperada

Ambos programas imprimen en la consola los siguientes resultados en el mismo orden:

1.  **Posiciones Iniciales**: Las coordenadas `(x, y)` de cada una de las 10 partículas en el círculo de radio 1.
2.  **Posiciones Perturbadas**: Las nuevas coordenadas después de aplicar una pequeña perturbación aleatoria a cada partícula.
3.  **Distancia Máxima**: La distancia euclidiana más grande encontrada entre cualquier par de partículas perturbadas.
4.  **Fuerzas**: Los componentes de fuerza `(fx, fy)` asignados aleatoriamente a cada partícula.
5.  **Fuerza Total**: La suma vectorial de todas las fuerzas, mostrando las componentes `(Fx, Fy)` y la magnitud `|F|`.

#### 5\. Notas Importantes

  - **Diferencia de enfoque**: El código con clases agrupa los datos y las funciones en un solo objeto (`Particle`), lo que hace que el código sea más modular y reutilizable. El código con estructuras separa los datos (`struct particula`) de las funciones que los manipulan (`init_position`, `perturbation`, `forces`).
  - **Inicialización aleatoria**: La versión de estructuras (`Tarea_01_estructuras.cpp`) utiliza `srand(time(NULL))` para asegurar que los números aleatorios generados sean diferentes en cada ejecución, lo cual es una buena práctica. El código con clases no lo hace, por lo que los resultados pueden ser los mismos si no se inicializa la semilla.
  - **Gestión de memoria**: La versión de clases utiliza un arreglo dinámico (`new Particle[N]`) que no es liberado al final del programa, lo que resulta en una **fuga de memoria**. Para corregirlo, se debería añadir la línea `delete[] P;` antes de `return 0;`. La versión de estructuras usa un arreglo estático, por lo que no hay necesidad de gestionar la memoria explícitamente.
