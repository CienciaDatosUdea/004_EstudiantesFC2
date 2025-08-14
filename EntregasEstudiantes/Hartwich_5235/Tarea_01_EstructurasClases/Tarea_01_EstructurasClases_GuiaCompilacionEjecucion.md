Descripción
---
El siguiente programa es una implementación básica de los siguientes conceptos:
- estructurar código en archivos diferentes que se juntan usando `include "<public_interface_filename>.h"`
- `struct` para contener datos y `class` para contener y aplicar métodos (decidí incluir ambos conceptos en un proyecto en vez de separarlo en dos)

En el archivo que termina en clases.h, se implementa un `struct partícula` que define una partícula con las propriedades "número, coordenada x, coordenada y, componente de fuerza x, componente de fuerza y".

Además, se define una `class pSystem` que representa a un sistema de `N` partículas. El constructor del sistema inicializa automáticamente sus posiciones y les asigna números (consecutivos de 0 a N-1). Los métodos implementados pueden aplicar una perturbación aleatoria de `[-ds, ds]` a las coordenadas `x` y `y` de todas partículas, aplicar una fuerza con componentes `[0, df]` a cada partícula, calcular e imprimir las distancias mínimas y máximas de cualquier dos partículas y calcular e imprimir la magnitud de la fuerza total actuando sobre todo el sistema.

Los dichos métodos están implementados en el archivo que termina en metodos.cpp.

En el archivo main.cpp, se usan las clases y los métodos definidos en clases.h y métodos.cpp para comprobar su funcionamiento (imprimiendo informaciones sobre el procedimiento para el usuario que lo ejecuta). No se implementa ninguna clase nueva ni ningún método nuevo.

Este programa no requiere más interacción del usuario aparte de compilar el proyecto y ejecutar el ejecutable según la guía siguiente.

Guía de Compilación
---
1. asegurar que esté instalado "make"
2. dirigirse a la carpeta que contiene el archivo "Makefile"
3. ejecutar desde la terminal "make" para compilar el código y crear el ejecutable y "make run" para ejecutarlo. (Note: la presente implementación de "make run" también crea el ejecutable antes de correrlo si es necesario.)