# Operaciones con números complejos

El objetivo de este proyecto es implementar computacionalmente operaciones básicas con números complejos, tales como suma, resta, producto, cociente y módulo. El código define una clase que crea un número complejo a partir de su parte real e imaginaria, e implementa las operaciones aritméticas y de impresión necesarias para manipularlos fácilmente.

### Estructura del proyecto

```
Tarea_02_Complejos/
|
├── espagueti/              ## código tipo espagueti
|   ├── complejos.cpp       
|   └── complejos.out           
|
└── ordenado/              ## código ordenado
    │
    ├── build/              ## ejecutables
    │   └── main.out
    │
    ├── include/            ## interfaz pública
    │   └── op_complejos.h
    │
    ├── src/                ## clases
    │   └── op_complejos.cpp
    │
    ├── main.cpp            ## archivo principal
    └── Makefile            ## compilación automática
```

### Clases y funciones

`complejos(x0, y0)`: constructor de un número complejo a partir de sus partes real `x0` e imaginaria `y0`.

`get_complejos()`: imprime el número complejo en la forma `a + bi`.

`get_real()`: devuelve la parte real.

`get_imag()`: devuelve la parte imaginaria.

`magnitud_complejo()`: devuelve el módulo del número complejo.

### Sobrecarga de operadores:

`+` suma de complejos.

`-` resta de complejos.

`*` producto de complejos.

`/` cociente de complejos.


## Compilación y ejecución

Para compilar el código espagueti, ubíquese en el directorio `espagueti` y ejecute en la terminal:

```
g++ -std=c++17 -Wall complejos.cpp -o complejos.out
```

Para ejecutar el código, ejecute en la terminal:

```
./complejos.out
```

Para compilar y ejecutar el código ordenado, ubíquese en el directorio `ordenado` y ejecute en la terminal:

```
make run
```

Esto creará los archivos `.out` necesarios y los ejecutará.

Al ejecutar cualquiera de los dos programas, verá en consola una salida de este estilo:

```
z = 3 + -4i 
w = 1 + 2i 
|z| = 5
|w| = 2.23607
z+w = 4 + -2i 
z-w = 2 + -6i 
z*w = 11 + 2i 
z/w = -1 + -2i 
```
