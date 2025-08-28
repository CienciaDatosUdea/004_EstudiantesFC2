Una versión de este código que corre en la terminal se puede encontrar en [SimASCII](https://github.com/KevinRestrepo/SimASCII).

Lennard-Jones es uno de los potenciales más usados para testear simulaciones de dinámica molecular debido a su simplicidad y buenos resultados:

$$
4\epsilon \left[\left(\frac{\sigma}{r}\right)^{12}-\left(\frac{\sigma}{r}\right)^6\right].
$$

>Nota: La presente simulación usa unidades reducidas, en donde $\sigma = \epsilon = 1$. Tenga esto en cuenta para cambiar parámetros como la temperatura.
### Uso
Cambie los parámetros de la simulación dentro de `main.cpp`.
### Compilación
Con make, simplemente corra `make` sin argumentos.

Opcionalmente puede hacer 

```sh
g++  -std=c++17 -Iinclude -o main system.cpp main.cpp
```

### Ejecución
Correr el ejecutable `./main` creará un archivo `data.txt` y automáticamente correra `plot.py`, que los grafica, el último archivo de salida es `simulation.gif`

### Bugs
- Aveces, las colisiones en la gráfica no corresponden visualmente con el diamétro de las partículas. Esto cambia con el tamaño de la caja L y el dpi que usa matplotlib
- Las rápidas variaciones en la gráfica de energía son normales en este tipo de simulaciones, reducirlas implica tomar un paso temporal dt más pequeño. Lo importante es que la energía media (el centro de la oscilación) se mantenga constante.