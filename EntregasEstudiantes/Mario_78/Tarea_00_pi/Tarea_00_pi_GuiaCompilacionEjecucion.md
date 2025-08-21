
### Tarea de Prueba: Aproximación del valor de π usando C++ y funciones

1. Una forma clásica de aproximar el valor de π es mediante la **serie de Leibniz**, de convergencia lenta:

\begin{equation}
\pi = 4 \left( 1 - \frac{1}{3} + \frac{1}{5} - \frac{1}{7} + \cdots  \right)= 4 \left( \sum_{k=0}^{n-1} \frac{(-1)^k}{2k+1} \right)   (1)
\end{equation}

2. Otra forma de representar el mismo cálculo, separando explícitamente los términos positivos y negativos, es:

\begin{equation}
\pi = 4 \left( \sum_{k=0}^{n-1}\left(\frac{1}{4k+1} - \frac{1}{4k+3} \right)\right)(2)
\end{equation}


El archivo en  C++ calcula el valor aproximado  de π utilizando la **serie de Leibniz**, para ello, se creraron 2 funciones


- La función `double calcularPiLeibniz(int n)`: que recibe el número de términos y devuelva el valor aproximado de π.


- La función `double calcularPiSeparado(int n)`: que calcula π **sumando los términos con denominadores de la forma 4k+1 y restando los de 4k+3**, como se muestra en la segunda fórmula.


En la función main():

Se solicita al usuario el número de términos `n` a usar.
- Validar que `n` sea positivo.
- Calcular e imprimir ambas aproximaciones.
- Comparar con el valor real de π (`M_PI` en `<cmath>`).
- Mostrar el **error absoluto** en cada caso.


Entrega:

Esta entrega  contiene los siguientes archivos:

- `Tarea_00_pi.cpp`: archivo fuente con la implementación en C++.
- `Tarea_00_pi.out`: archivo ejecutable generado tras la compilación.
- `Tarea_00_pi_GuiaCompilacionEjecucion.md`: archivo en formato Markdown con una guía clara sobre cómo compilar y ejecutar el código en sistemas Linux.

#### Compilación del código:

Para compilar, se abre el archivo `Tarea_00_pi.cpp` con la Terminal en Linux y se digita la expresión:  **g++ -o Tarea_00_pi Tarea_00_pi.cpp**, el cual creará el ejecutable `Tarea_oo_pi.exe`

#### Ejecución del del código:

Se escribe en la terminal la expresión:  **./Tarea_00_pi**, el cual ejecuta el programa.

Después aparecera la instrución: 

Número de términos --->  n =

Se escribe por ejemplo el número 1000000, el cual será validado y arrojará los resultados.

Si se escribe valores para n no permitidos (por ejemplo -10000; 5.7; 9,8 ó 4000b) aparecerá un mensaje de error.


