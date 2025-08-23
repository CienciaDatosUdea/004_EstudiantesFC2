# Simulación de Difusión 1D

Este proyecto implementa una simulación numérica de la ecuación de difusión en una dimensión usando diferencias finitas explícitas. Permite definir condiciones iniciales tipo gaussiana y condiciones de frontera fijas, guardar resultados y generar animaciones GIF de la evolución temporal.

## Estructura del Proyecto

```
├── include/
│   └── difusion_model.h      # Definición de clases principales
├── src/
│   └── difusion_model.cpp    # Implementación de las clases
├── main.cpp                  # Programa principal (interfaz de usuario)
├── tests/
│   └── test.cpp              # Pruebas básicas
├── Makefile                  # Compilación automatizada
```

## Compilación

Puedes compilar el programa principal usando el Makefile:

```sh
make
```

Esto generará un ejecutable llamado `main` en el directorio raíz.

## Ejecución

Ejecuta el programa principal desde la terminal:

```sh
./main
```

El programa solicitará los siguientes parámetros por consola:

- Número de puntos espaciales (`N`)
- Valor inicial de `x` (`xmin`)
- Valor final de `x` (`xmax`)
- Tiempo total de simulación (`tmax`)
- Paso temporal (`dt`)
- Coeficiente de difusión (`D`)

**Ejemplo de entrada:**
```
Digite: Número de puntos espaciales (N),  x inicial,  x final,  tiempo de simulación (tmax),  espaciado temporal infinitesimal (dt)   y coeficiente de difusión (D)
20 0 10 1 0.01 1
```

### Opciones de línea de comandos

- `-g` o `--gif`: Genera una animación GIF de la evolución temporal usando gnuplot.
- `-o <archivo>` o `--output <archivo>`: Especifica el nombre del archivo de salida para los resultados finales.

**Ejemplo:**
```sh
./main -g -o resultado.txt
```

Esto guardará la solución final en `final_resultado.txt` y la animación en `resultado.gif`.

## Requisitos

- Compilador C++17 o superior
- [gnuplot](http://www.gnuplot.info/) (solo si usas la opción GIF)

## Notas

- El programa verifica automáticamente la condición de estabilidad numérica: `D*dt/dx^2 <= 0.5`.
- Los resultados se guardan en archivos de texto para su análisis posterior.
