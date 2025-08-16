### `Complex_Spaghetti.cpp`

Este programa en C++ utiliza la programación orientada a objetos para realizar operaciones con números complejos. Define una clase base para representar un número complejo y una clase derivada que implementa las operaciones básicas de suma, resta, multiplicación y división.

#### 1\. Estructura del Código

El código está dividido en dos clases principales:

  - **`class complejos`**: Esta es la clase base que representa un número complejo. Almacena la parte **real** e **imaginaria** como miembros protegidos. Proporciona métodos para obtener los valores de la parte real e imaginaria y para imprimir el número complejo en la consola.
  - **`class op_complejos`**: Esta clase hereda de `complejos` y se encarga de las operaciones matemáticas. Sobrecarga los operadores `+`, `-`, `*` y `/` para realizar las operaciones correspondientes entre objetos de tipo `complejos`. También incluye un método para calcular la magnitud del número complejo.

#### 2\. Compilación y Ejecución

Para compilar y ejecutar el programa, necesitarás un compilador de C++ como `g++`.

  - **Compilación**:
    ```bash
    g++ Complex_Spaghetti.cpp -o Complex_Spaghetti
    ```
  - **Ejecución**:
    ```bash
    ./Complex_Spaghetti
    ```

#### 3\. Funcionalidad

El programa realiza los siguientes cálculos y muestra los resultados en la consola:

  - Crea dos números complejos: `a = 2 + 1i` y `b = 3 - 5i`.
  - Calcula y muestra la magnitud de `a` y `b`.
  - Realiza y muestra el resultado de las siguientes operaciones:
      - `a + b` (Suma)
      - `a - b` (Resta)
      - `a * b` (Multiplicación)
      - `a / b` (División)
  - Para cada resultado de operación, también calcula y muestra su magnitud.

#### 4\. Notas Adicionales

  - **Herencia**: La clase `op_complejos` hereda de `complejos`, lo que le permite acceder a las propiedades `real` e `imag` de la clase base y reutilizar su funcionalidad.
  - **Sobrecarga de Operadores**: El uso de la sobrecarga de operadores (`operator+`, `operator-`, etc.) permite que las operaciones con números complejos se escriban de una manera más intuitiva y similar a las operaciones con tipos de datos nativos.
