# Aproximación de $\pi$ con la serie de Leibniz


En este programa se encuentra la aproximación de la constante $\pi$ utilizando la serie de Leibniz.


### Explicación del código:

1. **Funciones `calcularPiLeibniz` y `calcularPiSeparado`**:
   - Ambas funciones calculan la aproximación de π usando las series de Leibniz y la fórmula separada.
   - En `calcularPiLeibniz`, la fórmula estándar es utilizada con un signo alterno en cada término.
   - En `calcularPiSeparado`, los términos con denominadores de la forma `4k+1` se suman y los de la forma `4k+3` se restan, separando explícitamente los términos positivos y negativos.

2. **Función `main`**:
   - Solicita al usuario el número de términos `n` para calcular la aproximación de π.
   - Se valida que `n` sea un número positivo.
   - Calcula e imprime la aproximación de π con ambas fórmulas y también muestra los errores absolutos.

3. **Compilación y Ejecución**:
   - En el archivo `Tarea_00_pi_GuiaCompilacionEjecucion.md`, se describe cómo compilar y ejecutar el programa en sistemas Linux.

Con esto, tu tarea estará lista para ser entregada, con el código bien estructurado, modular y comentado.


# Guía de Compilación y Ejecución en Linux

## Compilación

1. Abre una terminal en el directorio donde se encuentra el archivo `Tarea_00_pi.cpp`.
2. Utiliza el siguiente comando para compilar el código:

   ```bash
   g++ -o Tarea_00_pi Tarea_00_pi.cpp -lm




