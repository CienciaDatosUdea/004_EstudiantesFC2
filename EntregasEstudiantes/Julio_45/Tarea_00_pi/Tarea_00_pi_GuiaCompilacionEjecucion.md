## Guía de compilación y ejecución de Tarea_00_pi.cpp

Este código aproxima el valor de $\pi$ a partir de la serie de Leibniz

$$
\pi = 4\sum_{k=0}^n \dfrac{(-1)^k}{2k+1}
$$

donde $n$ es un entero positivo de escogencia del usuario.

### Funciones

`calcularPiLeibniz(int n)`: aproxima $\pi$ con la serie de Leibniz.
`calcularPiSeparado(int n)`: aproxima $\pi$ con la serie de Leibniz separando los términos positivos y negativos.

INPUT: `int n` número de términos de la serie

OUTPUT: el programa imprime los valores de pi aproximados con las dos funciones y el error absoluto con el valor de $\pi$ de la librería `cmath`.

Para compilar este programa en sistemas Linux, abra la terminal y use el comando `cd` para moverse al directorio donde se encuentre el archivo `Tarea_00_pi.cpp`. Aquí, use el comando

```
g++ -o Tarea_00_pi.out Tarea_00_pi.cpp
```

para generar el archivo ejecutable. Una vez generado el ejecutable, puede ejecutarlo desde la terminal con el comando

```
./Tarea_00_pi.out
```
