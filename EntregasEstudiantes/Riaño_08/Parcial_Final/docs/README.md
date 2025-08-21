### **Proyecto de Simulación FDTD 1D**

Este proyecto implementa el método de Diferencias Finitas en el Dominio del Tiempo (FDTD) para simular la propagación de ondas electromagnéticas en una dimensión. El objetivo principal es analizar la estabilidad del modelo y la dispersión numérica en función del parámetro de Courant (`beta = c Δt / Δz`).

#### **Estructura de Carpetas**

El proyecto está organizado en la siguiente estructura de directorios:

```
.
├── include/           # Archivos de encabezado (.h)
│   └── fdtd.h
├── src/               # Archivos de código fuente de la simulación (.cpp)
│   └── fdtd.cpp
├── python/            # Scripts de Python y datos de salida
│   └── sim_fdtd.py
│   └── AnalisisRespuestas.ipynb
├── Makefile           # Archivo para automatizar la compilación y ejecución
├── main.cpp           # Archivo principal del programa C++
└── README.md          # Este archivo
```

#### **Archivos del Proyecto**

  * **`main.cpp`**: Es el programa principal. Se encarga de configurar y ejecutar múltiples simulaciones FDTD con diferentes valores de `dz` y `dt`. Una vez que cada simulación finaliza, guarda los datos del último paso de tiempo en archivos de texto dentro de la carpeta `python/`.
  * **`fdtd.h` y `fdtd.cpp`**: Contienen la clase `FDTD`. Este es el corazón de la simulación. El archivo de encabezado (`fdtd.h`) define la interfaz de la clase, mientras que la implementación (`fdtd.cpp`) contiene la lógica del algoritmo FDTD, incluyendo las ecuaciones de actualización de los campos eléctricos y magnéticos y el manejo de las condiciones de frontera.
  * **`sim_fdtd.py`**: Es un script de Python auxiliar con funciones para cargar los datos de los archivos de texto y generar los gráficos de los campos. Es utilizado por el notebook para la visualización.
  * **`AnalisisRespuestas.ipynb`**: Un **Jupyter Notebook** interactivo. Carga los archivos de datos generados por el programa C++ y permite visualizar los resultados de la simulación para cada combinación de `dz` y `dt`.
  * **`Makefile`**: Un archivo de automatización que simplifica el proceso de compilación, ejecución y limpieza del proyecto.

#### **Cómo Ejecutar el Proyecto**

1.  **Abre una terminal** en el directorio principal del proyecto.

2.  **Compila y ejecuta la simulación** usando el `Makefile`. Este comando compilará el código C++ y luego ejecutará el programa, generando los archivos de datos en la carpeta `python/`.

    ```bash
    make
    ```

3.  **Visualiza los resultados**:

      * Navega a la carpeta `python/`.
      * Abre el notebook `AnalisisRespuestas.ipynb` en Jupyter Notebook o JupyterLab.
      * Ejecuta las celdas del notebook para cargar los datos y usar el menú desplegable interactivo para explorar los diferentes resultados.

#### **Limpieza del Proyecto**

Puedes usar el siguiente comando para eliminar los archivos compilados (`.o`), el ejecutable (`fdtd_sim`) y los archivos de datos de texto generados.

```bash
make clean
```
