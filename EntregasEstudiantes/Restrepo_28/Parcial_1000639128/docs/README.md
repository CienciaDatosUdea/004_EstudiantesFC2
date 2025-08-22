# Simulación FDTD 1D de Ondas Electromagnéticas

Este proyecto simula la propagación de ondas electromagnéticas en una dimensión usando el método de Diferencias Finitas en el Dominio del Tiempo (FDTD). Soporta diferentes condiciones de frontera y genera resultados para su visualización.

## Compilación

Para compilar el programa, la forma más rapida es usando `make`. En el directorio raíz del proyecto:
```sh
make
```
alternativamente se puede usar `g++` (o cualquier compilador de C++) desde la raíz del proyecto:

```sh
g++ -std=c++11 -o main main.cpp src/fdtd.cpp
```

Esto generará un ejecutable llamado `main`.

## Uso

Ejecuta el programa desde la raíz del proyecto. Puedes especificar los parámetros de simulación y opciones de salida mediante argumentos en la línea de comandos.

### Uso básico

```sh
./main
```

Esto ejecuta la simulación con los parámetros por defecto y guarda los resultados en `data.txt`.

### Parámetros personalizados

Puedes establecer el espaciamiento de la malla (`dz`), el paso temporal (`dt`), el número nodos de la malla (`K`), el número de pasos de tiempo (`N`) y la velocidad de la onda (`C`) usando la opción `-p` o `--params`:

```sh
./main -p <dz> <dt> <K> <N> <C>
```

Ejemplo:

```sh
./main -p 0.01 0.02 200 250 0.1
```

### Condiciones de frontera

Establece el tipo de condición de frontera usando `-bc` o `--boundary-condition`:

- `periodic` (por defecto)
- `dirichlet`
- `absorbtion`

Ejemplo:

```sh
./main -bc dirichlet
```

### Archivo de salida

Especifica el nombre del archivo de salida usando `-o` o `--output`:

```sh
./main -o resultados.txt
```
### Gif
Especifica si quiere que el programa lea los datos y construya un gif con la simulación usando `-v` o `--visualize`. Con este flag el programa correra un script de python y se creará el archivo `EMWave.gif`

### Ejemplo completo

```sh
./main -v -o resultados.txt -bc dirichlet -p 0.1 0.02 200 350 1
```

## Salida

La simulación escribe los resultados en el archivo especificado (por defecto: `data.txt`). Cada bloque contiene el tiempo y los valores de `z`, `E` y `H` en cada punto de la malla.

## Visualización

Si se desea visualizar algún archivo con los datos por separado (sin llamar main) puede usar el comando:

```sh
python3 python/plot_anim.py data.txt <dz> <dt> <K>
```

Ejemplo:

```sh
python3 python/plot_anim.py data.txt 0.01 0.02 200
```

Esto generará una animación de la propagación de la onda y la guardará como `EMwave.gif`. Asegurese que los parámetros `dz, dt, k` son los mismos que se usaron en la generación de los datos, por esto es más cómodo simplemente correr `main` con el flag `-v`, que entrega los parámetros correctos.

## Requisitos

- Compilador C++11 o superior.
- Python 3 con `matplotlib==3.9.0` y `numpy==1.26.4` para la visualización.
