# Proyecto: Operaciones con Números Complejos

Este proyecto implementa una jerarquía de clases en C++ para representar y realizar operaciones básicas con números complejos, como suma, resta, multiplicación, división y cálculo de la magnitud.

## Estructura del Proyecto

El código está organizado en tres partes principales para una mejor modularidad y reutilización:

### `include/complejos.h`

Este es el archivo de **encabezado** (`header`) que contiene las **declaraciones** de las clases `complejos` y `op_complejos`. Actúa como una interfaz, permitiendo que otros archivos sepan qué clases y métodos existen sin necesidad de conocer su implementación interna. También incluye las librerías necesarias para el proyecto. Para evitar duplicaciones, utiliza **guardas de inclusión** (`#ifndef`, `#define`, `#endif`).

### `src/complejos.cpp`

Este archivo contiene la **implementación** completa de los métodos declarados en `complejos.h`. Aquí es donde se escribe el código que define la funcionalidad de cada método de las clases `complejos` y `op_complejos`, siguiendo el principio de separar la declaración de la definición.

### `main.cpp`

El archivo `main.cpp` contiene la función principal del programa (`main`). Aquí se crean instancias de las clases `complejos` y `op_complejos` y se utilizan sus métodos y la sobrecarga de operadores para demostrar cómo funcionan las operaciones. Este archivo incluye `complejos.h` para acceder a las clases.

-----

## Uso del `Makefile`

Se ha proporcionado un `Makefile` para automatizar el proceso de compilación y ejecución del proyecto. Utiliza `g++` como compilador y organiza la construcción de los archivos para facilitar el desarrollo.

### Compilar el proyecto

Para compilar el código y generar el archivo ejecutable, simplemente abre una terminal en la carpeta principal del proyecto y ejecuta:

```bash
make
```

Este comando ejecuta la regla por defecto (`all`), que compila `complejos.cpp` y `main.cpp` y crea un ejecutable llamado `complejos`.

### Compilar y ejecutar

Para compilar el proyecto y ejecutar el programa en un solo paso, usa la regla `run`:

```bash
make run
```

Este comando se encarga de que el ejecutable esté actualizado y luego lo ejecuta, mostrando el resultado de las operaciones en la terminal.

### Limpiar archivos generados

Si deseas eliminar el ejecutable y los archivos objeto (`.o`) generados durante la compilación, usa la regla `clean`:

```bash
make clean
```

Este comando es útil para forzar una nueva compilación completa.
