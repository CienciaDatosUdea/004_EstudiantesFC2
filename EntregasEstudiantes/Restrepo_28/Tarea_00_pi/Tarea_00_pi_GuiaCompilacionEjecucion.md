Este programa realiza el cálculo aproximado de PI de dos formas distintas usando la serie de Leibniz.
Se imprime PI, los dos valores y su error absoluto.

## Compilación
Usando `g++` ejecutar:|

    g++ -o Tarea_00_pi.out Tarea_00_pi.cpp
## Ejecución
Digite el comando

    ./Tarea_00_pi.out

La terminal le pedirá ingrese un número entero y lo continuará haciendo si no ingresa un número positivo. Si ingresa un número decimal este será truncado hacia abajo. Si ingresa una cadena de caracteres el número será cero.

Si se entregó un número válido la terminal devolverá algo como:

    Valor PI exacto:3.14159
    Aproximación Leibniz: 3.13159, error absoluto: 0.00999975
    Aproximación Separado: 4, error absoluto: 0.858407