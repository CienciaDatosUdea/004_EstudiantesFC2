Descripción
---
El siguiente programa es una implementación básica de los siguientes conceptos:
    - estructurar código en archivos diferentes que se juntan usando `include "<filename>"`
    - usar clases
    - usar el concepto de inherencia de clases
    - definir operadores para clases

En el archivo que termina en clases.h, se implementa una clase `complexBase` que define un número complejo. Contiene la información tanto expresada por (parte real, parte imaginaria) como expresada por (magnitud absoluta, ángulo en el plano complejo). Además, tiene dos métodos que se deben usar para que actualice el segundo (primero) par de coordenadas cuando hay habido un cambio en el primero (segundo).

Además, se define una *child class* `complex` de la *parent class* `complexBase`. Esta clase es la única que se va a usar en main.cpp. Hereda todas las variables y los métodos protectados o públicos de complexBase (en el caso implementado: todo). Esta clase contiene todos los demás métodos que se van a usar en main.cpp, entre otros funciones para imprimir el valor del número complejo en las coordenadas deseadas, operadorec para acceder directamente a las coordenadas deseadas (operator[] sobrecargado) y operadores para aritmética básica (+, -, *, /, +=, -=, *=, /=, ==).

En el archivo main.cpp, se usan las clases y los métodos definidos en clases.h y métodos.cpp para comprobar su funcionamiento. No se implementa ninguna clase nueva ni ningún método nuevo.

Este programa no requiere más interacción del usuario aparte de compilar el proyecto y ejecutar el ejecutable según la  guía siguiente.

Guía de Compilación
---
1. asegurar que esté instalado "make"
2. dirigirse a la carpeta que contiene el archivo "Makefile"
3. ejecutar desde la terminal "make" para compilar el código y crear el ejecutable y "make run" para ejecutarlo. (Note: la presente implementación de "make run" también crea el ejecutable antes de correrlo si es necesario.)