# Simulación 1D de la Ecuación de Difusión de Calor

Este proyecto es una simulación computacional de la ecuación de difusión de calor en una dimensión, utilizando el método numérico de Diferencias Finitas (FTCS - *Forward-Time, Centered-Space*). El código está escrito en C++ para realizar la simulación y en Python para la visualización interactiva de los resultados.

## Algoritmo

El proyecto resuelve la ecuación de difusión de calor:

$$\frac{\partial u}{\partial t} = D \frac{\partial^2 u}{\partial x^2}$$

donde:

  - $u$ es la temperatura.
  - $t$ es el tiempo.
  - $x$ es la posición.
  - $D$ es el coeficiente de difusión de calor.

El método FTCS discretiza esta ecuación, aproximando las derivadas temporales y espaciales con diferencias finitas:

$$\frac{u_i^{n+1} - u_i^n}{\Delta t} = D \frac{u_{i+1}^n - 2u_i^n + u_{i-1}^n}{(\Delta x)^2}$$

Esto nos da la siguiente fórmula para actualizar la temperatura en cada paso de tiempo:

$$u_i^{n+1} = u_i^n + \alpha(u_{i+1}^n - 2u_i^n + u_{i-1}^n)$$

donde $\alpha = \frac{D\Delta t}{(\Delta x)^2}$. Este método es **condicionalmente estable**, lo que significa que el parámetro $\alpha$ debe ser menor o igual a 0.5 ($\alpha \le 0.5$) para que la solución no diverja.

-----

## Estructura del Proyecto

El proyecto está organizado en la siguiente jerarquía de directorios:

  - **`bin/`**: Contendrá el ejecutable compilado.
  - **`display/`**: Contiene los scripts y notebooks para la visualización de los datos.
      - **`datos/`**: Una subcarpeta que se creará al ejecutar la simulación, donde se guardarón los datos de temperatura en archivos de texto.
  - **`include/`**: Contiene los archivos de cabecera (`.h`).
  - **`src/`**: Contiene los archivos de implementación (`.cpp`).

-----

## Descripción de los Archivos

  - **`Makefile`**: Script para automatizar la compilación y ejecución del proyecto.
  - **`main.cpp`**: Punto de entrada del programa. Inicializa la simulación, ejecuta el cálculo FTCS y exporta los datos a la carpeta `display/datos`.
  - **`include/difusion_model.h`**: Archivo de cabecera que declara las clases `Geometria`, `Condiciones` y `DiffusionSolver`.
  - **`src/difusion_model.cpp`**: Implementación de las clases declaradas en `difusion_model.h`.
  - **`display/visualizacion_datos.ipynb`**: Un Jupyter Notebook para visualizar los datos generados por la simulación de forma interactiva.
  - **`display/visualizacion_funciones.py`**: Código Python con la lógica para cargar y graficar los datos en el notebook.

-----

## Uso

Para usar este proyecto, sigue estos pasos:

1.  **Compilar el código**: Abre una terminal en la raíz del proyecto y usa el **`Makefile`**.

    ```bash
    make
    ```

    Este comando compila los archivos `.cpp` y crea el ejecutable `solver` dentro de la carpeta `bin/`. También se asegura de que las carpetas `bin/` y `display/datos/` existan.

2.  **Ejecutar la simulación**: Una vez que el código haya sido compilado, ejecuta la simulación para generar los datos.

    ```bash
    make run
    ```

    Este comando ejecuta el archivo `solver`, el cual realiza la simulación y guarda los perfiles de temperatura en archivos de texto con el formato `datos_paso_*.txt` dentro de la carpeta `display/datos/`.

3.  **Visualizar los resultados**: Para ver la animación de la difusión de calor, navega a la carpeta `display/` y abre el Jupyter Notebook.

    ```bash
    cd display/
    jupyter notebook visualizacion_datos.ipynb
    ```

    Dentro del notebook, ejecuta las celdas para cargar los datos generados por la simulación y mostrar una gráfica interactiva donde puedes mover un control deslizante para ver la evolución temporal de la temperatura.

4.  **Limpiar archivos**: Si deseas eliminar los archivos compilados y los datos generados, puedes usar el siguiente comando:

    ```bash
    make clean
    ```

    Este comando borrará la carpeta `bin/` y la carpeta `display/datos/` junto con su contenido.
