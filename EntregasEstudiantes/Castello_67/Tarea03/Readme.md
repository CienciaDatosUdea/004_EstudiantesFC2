# Simulación de la Ecuación de Calor 1D

Este proyecto resuelve numéricamente la ecuación de calor en una dimensión usando el método de diferencias finitas explícitas. Permite inicializar la barra con una condición gaussiana y visualizar la evolución temporal de la temperatura.

## Estructura del Proyecto

```
.
├── include/
│   └── Heat1d.h         # Definición de la clase Heat1d
├── src/
│   └── Heat1d.cpp       # Implementación de la clase Heat1d
├── test/
│   ├── test.cpp         # Pruebas unitarias
│   └── test_runner      # Ejecutable de pruebas (generado)
├── main.cpp             # Programa principal
├── Makefile             # Compilación automatizada
├── Gaussian_Solution.txt# Salida de la simulación (generado)
└── Animacion.py         # Script Python para animar la solución
```

## Compilación

Compila el proyecto y genera los ejecutables con:

```sh
make
```

Esto generará:
- `simulation`: ejecutable principal
- `test/test_runner`: ejecutable de pruebas

Simplemente escribir en la terminal: `./simulation`

Limpia los archivos intermedios y ejecutables con:

```sh
make clean
```

## Ejecución

Ejecuta la simulación principal:

```sh
./simulation
```

Esto generará el archivo `Gaussian_Solution.txt` donde cada fila es el vector solución para un instante de tiempo.

## Visualización

Para animar la evolución de la temperatura, usa el script de Python:

```sh
python3 Animacion.py
```
## Personalización

Puedes modificar los parámetros físicos y numéricos en `main.cpp`:
- `alpha = 1.`: coeficiente de difusión 
- `N = 100`: número de puntos espaciales
- `L = 1`: longitud de la barra
- `Max_U = 100`: temperatura máxima inicial
- `sigma = 0.1`: ancho de la gaussiana inicial
- `t_f = 0.5`: tiempo final de integración

## Autor

- Juan Felipe Castello Arango
