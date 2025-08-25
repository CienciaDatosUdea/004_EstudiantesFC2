# Simulación de fluidos 2D (Ecuaciones de Navier-Stokes)

Este proyecto simula el flujo de un fluido incompresible y viscoso en 2D, resolviendo las ecuaciones de Navier-Stokes en un esquema de diferencias finitas. El programa fue escrito en C++ y la visualización de los resultados se realiza en Python.

## 1\. Teoría y Modelo Físico

El movimiento del fluido se describe mediante las **ecuaciones de Navier-Stokes**, que modelan el flujo de fluidos incompresibles:

1.  **Ecuación de continuidad (Conservación de masa):**
    $$\frac{\partial u}{\partial x} + \frac{\partial v}{\partial y} = 0$$
2.  **Ecuación de conservación de momentum (Navier-Stokes):**
    $$\frac{\partial \vec{V}}{\partial t} + (\vec{V} \cdot \nabla) \vec{V} = -\frac{1}{\rho}\nabla P + \nu \nabla^2 \vec{V} + \vec{f}$$

Donde:

  * $\vec{V} = (u, v)$ es el vector de velocidad del fluido.
  * $P$ es la presión.
  * $\rho$ es la densidad.
  * $\nu$ es la viscosidad cinemática.
  * $\vec{f}$ es una fuerza externa aplicada al fluido.

El modelo numérico utiliza un esquema de diferencias finitas en una grilla regular para discretizar y resolver estas ecuaciones paso a paso en el tiempo, a través de un método de proyección (fraccional-step).

## 2\. Estructura del Proyecto

El proyecto está organizado en las siguientes carpetas:

  * **`src/`**: Contiene el código fuente en C++.
      * `flow.cpp`: Implementa las clases y las lógicas de la simulación.
  * **`include/`**: Contiene los archivos de cabecera (.h).
      * `flow.h`: Declara las clases `Grid`, `CampoVelocidadesPresion`, `ComputePresion`, `ComputeCampo` y `FieldWriter`.
  * **`data/`**: Carpeta donde el programa en C++ guarda los archivos de datos de la simulación.
  * **`graph/`**: Contiene los archivos para visualizar la simulación.
      * `graficacion.ipynb`: Un *notebook* de Jupyter para generar la animación.
      * `simulacion_con_fuerza.gif`: Animación de la simulación con una fuerza inicial de 10.
      * `simulacion_sin_fuerza.gif`: Animación de la simulación sin fuerza inicial.
  * **`images/`**: Después de ejecutar `graficacion.ipynb`, se guardarán las imágenes generadas aquí.
  * **`Makefile`**: Archivo para automatizar la compilación y ejecución del código.
  * **`main.cpp`**: Contiene el bucle principal de la simulación.

## 3\. Modificando el Modelo

El valor de la fuerza inicial (`f`) que actúa sobre el fluido está definido como una constante en el constructor de la clase `ComputeCampo` en **`src/flow.cpp`**. Para modificarla, abre este archivo y cambia el valor de la variable `f` en la línea `f[i][j] = 10.0`. Por ejemplo:

```cpp
// src/flow.cpp
// ...
ComputeCampo::ComputeCampo(ComputePresion &omega_)
    : omega(omega_) {
    // Inicializar la fuerza constante
    // ...
    // Asignar un valor constante a la fuerza en la componente x
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            f[i][j] = 10.0; // Cambia este valor para modificar la fuerza inicial
        }
    }
}
// ...
```

## 4\. Cómo Correr el Proyecto

Sigue estos dos pasos para compilar, ejecutar la simulación y luego visualizar los resultados.

### Paso 4.1: Compilar y Ejecutar la Simulación

1.  Abre una terminal y navega hasta el directorio raíz del proyecto (`./simulacion-de-fluidos/`).

2.  Usa el **`Makefile`** para compilar y ejecutar el programa con un solo comando. El `Makefile` contiene la lógica para compilar los archivos C++ y generar un ejecutable llamado `flow.out`. Luego, la regla `run` lo ejecuta.

    ```bash
    make run
    ```

    > **Nota:** La primera vez que ejecutes este comando, el `Makefile` compilará el código. Las siguientes veces, solo compilará si detecta cambios en los archivos `.cpp`.

3.  El programa en C++ se ejecutará y comenzará a generar archivos de datos en la carpeta `data/` cada 10 iteraciones, a partir del paso 500.

### Paso 4.2: Visualizar la Simulación

1.  Abre el *notebook* de Jupyter **`graph/graficacion.ipynb`**.
2.  Ejecuta todas las celdas en el *notebook*. El código de Python leerá los archivos de datos generados en la carpeta `data/` y creará una animación interactiva en el navegador.
3.  Dentro de la misma carpeta `graph/` se incluyen dos ejemplos de la animación en formato GIF, uno mostrando el comportamiento del modelo sin fuerza inicial y otro con una fuerza inicial horizontal de valor 10. Puedes usarlos como referencia para verificar que tu simulación se está comportando de manera similar.
