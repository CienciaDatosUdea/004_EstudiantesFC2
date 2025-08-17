# Solución numérica de la ecuación del calor en una dimensión

El objetivo de este proyecto es implementar computacionalmente la solución numérica de la ecuación del calor unidimensional:

$$
\dfrac{\partial T}{\partial t}=D\dfrac{\partial^2 T}{\partial x^2}
$$

a través del método _forward time-centered space_ (FTCS) de diferencias finitas, en el que la evolución temporal de la cantidad $T$ es dada por:

$$
T_i^{n+1} = T_i^n+D\dfrac{\Delta t}{\Delta x^2}(T_{i+1}^n-2T_i^n+T_{i-1}^n)
$$

donde la etiqueta $n$ corresponde al tiempo en que se evalúa la función, la etiqueta $i$ corresponde a la posición en la que se evalúa la función, $D$ es el coeficiente de difusión y $\Delta t$ y $\Delta x$ son los pasos temporal y espacial, respectivamente.

### Estructura del proyecto

```
Tarea_03_DiffusionSolver/
│
├── build/                        ## ejecutables
│   └── Condiciones.out           ## clases
│   └── DiffusionSolver.out
│   └── Geometria.out
│   └── main.out                  ## archivo principal
│   └── test_diffusionsolver.out  ## tests
│   └── test_geometry.out
│   └── test_temperature.out
│
├── data/                         ## archivos .txt de salida
│   └── solucion_final.txt
│   └── test.txt
|
├── include/                      ## interfaz pública
│   └── difusion_model.h
│
├── pars/                         ## archivos de parámetros
│   └── data_test.par
│   └── params.par
|
├── src/                          ## clases
│   └── Condiciones.cpp           
│   └── DiffusionSolver.cpp
│   └── Geometria.cpp
│
├── test/                         ## tests
│   └── test_geometry.cpp
│   └── test_temperature.cpp
│   └── test_diffusionsolver.cpp
│
├── anim.gif                      ## animación
├── graphs.ipynb                  ## generación de la animación con Python
├── main.cpp                      ## archivo principal
└── Makefile                      ## compilación automática
```
### Clases y funciones

* `Geometry(x_min,x_max,N)`: permite grear un vector de posiciones con `N` puntos entre `x_min` y `x_max`.
* `Temperature(G)`: dada una geometría, genera un vector de temperaturas de la misma dimensión.
  * `applyInitialCondition(f)`: impone la condición inicial, dada por una función `f`, sobre el vector de temperaturas.
  * `applyBoundaryCondition(TL,TR)`: impone las condiciones de frontera `TL` y `TR` en los extremos izquierdo y derecho, respectivamente, del vector de temperaturas.
* `FieldWriter(filename)`: crea el archivo `filename` que almacenará los datos de la temperatura.
  * `writeTemperature(G,Campo)`: escribe la información de la geometría `G` y el campo de temperaturas `Campo` en el archivo `filename`.
* `DiffusionSolver(field,D,dt,t_max,TL,TR,f,filename)`: integrador de la ecuación del calor por FTCS para un campo de temperaturas `field` con coeficiente de difusión `D` en pasos `dt` hasta `t_max`, sujeto a las condiciones de frontera `TL` y `TR` y a la condición inicial `f`. La solución se almacenará en el archivo `filename`.
  * `step()`: evoluciona el campo de temperaturas en un paso.
  * `run()`: evoluciona el campo de temperaturas asta `t_max`.
 
## Compilación y ejecución

Para compilar el proyecto completo, ejecute la siguiente línea de comando en la terminal:

```
make
```

esto creará el directorio `build` con los archivos ejecutables.

Para ejecutar los archivos siga las instrucciones respectivas:
* `main`
  Ingrese en la terminal el comando:
  ```
  ./build/main.out pars/params.par
  ```
  donde el archivo `params.par` contiene laos siguientes parámetros, que serán leídos por el código
  * xmin: límite izquierdo de la geometría.
  * xmax: límite derecho de la geometría.
  * N: número de puntos.
  * D: coeficiente de difusión.
  * dt: paso temporal.
  * tmax: tiempo máximo.
  * x0: media de la gaussiana para la condición inicial.
  * filename: ruta donde se escribirá el archivo.
  * sigma: ancho de la gaussiana para la condición inicial.

  Si los parámetros satisfacen la condición de estabilidad
  
  $\alpha=D\dfrac{\Delta t}{\Delta x^2}\leq 0.5$
  
  no verá nada en consola y podrá acceder al archivo `solucion_final.txt` en el directorio `data`. De lo contrario, verá un mensaje de error y la ejecución se detendrá.
* `test_geometry`y `test_temperature`
  Ingrese en la terminal el comando:
  ```
  ./build/test_testname.out xmin xmax N
  ```
  reemplace `testname`por el test que desea ejecutar y `xmin`, `xmax` y `N` por los parámetros que inicializarán la geometría.
  
  Para `test_geometry`, verá en consola el arreglo de posiciones con los parámetros escogidos y los valores de `N, dx` y la longitud del vector, que debe coincidir con `N`.

    Para `test_temperature`, verá en consola una tabla con las posiciones y su respectiva temperatura una vez aplicadas las condiciones de frontera e inicial definidas en el código.
* `test_diffusionsolver`
  Ingrese en la terminal el comando:
  ```
  ./build/test_diffusionsolver.out pars/data_test.par
  ```
  donde el archivo `params.par` contiene laos siguientes parámetros, que serán leídos por el código
  * xmin: límite izquierdo de la geometría.
  * xmax: límite derecho de la geometría.
  * N: número de puntos.
  * D: coeficiente de difusión.
  * dt: paso temporal.
  * tmax: tiempo máximo.
  * filename: ruta donde se escribirá el archivo.
  Si los parámetros satisfacen la condición de estabilidad

  $\alpha=D\dfrac{\Delta t}{\Delta x^2}\leq 0.5$
  
  verá en consola los valores de `alpha, D, dt, dx` y podrá acceder al archivo `test.txt` en el directorio `data`. De lo contrario, verá un mensaje de error y la ejecución se detendrá.

### Visualización

En el archivo `graph.ipynb` podrá usar el norebook de Python para generar una animación con los datos obtenidos de la función principal (o de `test_diffusionsolver` cambiando el nombre del archivo).
