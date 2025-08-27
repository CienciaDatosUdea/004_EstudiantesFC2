# Solver de Difusión 1D 

Solucionador numérico para la **ecuación de calor (o difusión) en una dimensión**. Utiliza el método explícito **FTCS (Forward-Time Central-Space)** para simular la evolución de un perfil de temperatura a lo largo de un dominio espacial.

---
## Estructura del Proyecto

El código está organizado en las siguientes carpetas y archivos:

```
SolverDifusion1D/
├── include/
│   └── difusion_model.h      # Declaraciones de clases y funciones
├── src/
│   ├── Geometria.cpp         # Implementación de la malla espacial
│   ├── Condiciones.cpp       # Implementación de condiciones iniciales/frontera
│   └── DiffusionSolver.cpp   # Implementación del motor de simulación FTCS
├── main.cpp                  # Punto de entrada principal y configuración
├── Makefile                  # Script para automatizar la compilación
└── Readme.md                 # Este archivo
```

---
## Requisitos

Para compilar y ejecutar este proyecto, necesitarás:
* Un compilador de C++ que soporte el estándar C++17.
* La utilidad **`make`** para procesar el `Makefile`.

---
## Guía de Compilación y Ejecución

El proyecto utiliza un `Makefile` que automatiza todo el proceso de compilación.

### 1. Compilación

Para compilar el programa, abre una terminal en la carpeta raíz del proyecto (`Tarea_02/`) y ejecuta el comando:
```bash
make
```
Este comando leerá el `Makefile`, compilará todos los archivos `.cpp` necesarios y los enlazará para crear un único archivo ejecutable llamado **`difusion_model.out`**.

### 2. Ejecución

Una vez que la compilación haya finalizado, ejecuta el programa con el siguiente comando:
```bash
./difusion_model.out
```
Al ejecutarlo, el programa realizará la simulación numérica y, al finalizar, generará un archivo de salida en la misma carpeta.

### 3. Salida del Programa

El programa genera un archivo de texto llamado **`solucion_final.txt`**. Este archivo contiene la distribución de temperatura final en el dominio, con un formato de dos columnas: **posición (x)** y **temperatura (u)**.

```
x_0    u_0
x_1    u_1
...    ...
```

### 4. Limpieza del Proyecto

Para eliminar el archivo ejecutable y todos los archivos objeto (`.o`) generados durante la compilación, puedes usar el siguiente comando:
```bash
make clean
```
