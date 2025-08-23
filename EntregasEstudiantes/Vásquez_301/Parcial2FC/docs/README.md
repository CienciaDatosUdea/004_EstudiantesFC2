# Simulación FDTD - Examen Final

Este repositorio contiene la implementación del algoritmo FDTD para simular la propagación de una onda electromagnética en 1D.

## Requisitos

* **g++** y **make**
* **Python 3** con las siguientes librerías:
    ```bash
    pip install numpy matplotlib jupyterlab
    ```

## Guía Rápida de Ejecución

1.  **Compilar el proyecto:**
    Abre una terminal en la carpeta raíz y ejecuta:
    ```bash
    make
    ```

2.  **Ejecutar la simulación:**
    Este comando generará los archivos `.txt` con los datos de la simulación.
    ```bash
    make run
    ```

3.  **Visualizar los resultados:**
    Inicia el entorno de análisis con:
    jupyter notebook


## Limpieza

Para borrar todos los archivos generados por la compilación (`obj/` y `bin/`), ejecuta:
```bash
make clean