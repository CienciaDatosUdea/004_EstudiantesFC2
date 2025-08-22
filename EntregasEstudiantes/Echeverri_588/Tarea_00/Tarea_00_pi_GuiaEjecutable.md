## Instrucciones de compilación y ejecución de `Tarea_00_pi.cpp`

El programa aproxima el valor de $\pi$ utilizando la serie de Leibniz:

$$
\pi \approx 4 \sum_{k=0}^{n} \frac{(-1)^k}{2k+1}
$$

donde $n$ es un número entero positivo que indica el número de términos a considerar.

### Funciones principales

- **`piLeibniz(int n)`**: calcula $\pi$ evaluando directamente la serie de Leibniz.  
- **`piSeparado(int n)`**: calcula $\pi$ separando los términos positivos y negativos.

**Entrada:** un entero positivo `n` que representa el número de términos.  
**Salida:** el programa muestra las aproximaciones obtenidas con ambos métodos y el error absoluto respecto al valor de $\pi$ real.

### Compilación

En sistemas Linux, abra una terminal y ubíquese en la carpeta que contiene el archivo `Tarea_00_pi.cpp` usando `cd`.  
Luego ejecute:

g++ -o Tarea_00_pi.out Tarea_00_pi.cpp

Y luego:

./Tarea_00_pi.out