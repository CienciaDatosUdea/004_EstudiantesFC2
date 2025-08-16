# Parcial 2

#### Laurent Hartwich

## Guía de Compilación

1. asegurar de que esté instalado "make"
2. dirigirse a la carpeta que contiene el archivo "Makefile"
3. ejecutar desde la terminal "make" para compilar el código y crear el ejecutable y "make run" para ejecutarlo. (Note: la presente implementación de "make run" también crea el ejecutable antes de correrlo si es necesario.)

## Tarea 1

La siguiente descripción se refiere a las cinco gráficas bajo el punto "Comparación Condiciones Reflexivas / Periódicas" en el notebook visualization.ipynb.

La primera gráfica muestra la condición inicial del sistema como punto de partida.

Las gráficas 2 y 3 muestran el sistema evolucionando para dos tiempos con condiciones periódicas (es decir, calculando el campo eléctrico en los bordes usando un componente del campo magnético que está al otro extremo de la geometría 1D).

Las gráficas 4 y 5 muestran el sistema evolucionando para los mismos dos tiempos, pero con condiciones reflexivas (es decir, enforzando E = 0 y H = 0 en los extremos de la geometría 1D).

Aquí, es evidente como mantener las condiciones E = 0 y H = 0 enforza una reflexión:

En el caso periódico, las ondas evolucionan "libremente" en el tiempo (y se puede observar que las condiciones periódicas están implementados correctamente y se mantienen durante la evolución).

En el caso con E = 0 y H = 0, los extremos de la geometría reflexionan las ondas, así que se puede observar interferencia.

Notablemente, las magnitudes de los dos campos ya no coinciden: mientras que para la condición periódica, se puede observar |E(z)| = |H(z)|, ya no es el caso en el caso reflexivo.

En la última gráfica, también se puede observar claramente que la integral de los campos cambia. Mientras que (para las condiciones iniciales escogidas) las integrales de E y H sobre dz son iguales a 0, respectivamente, en la última gráfica se puede observar que la reflexión también rompe esta simetría.

## Tarea 2

La siguiente descripción se refiere a las cuatro gráficas bajo el punto "Investigación de la Estabilidad" en el notebook visualization.ipynb.

Aquí, el sistema se evoluciona hasta el mismo tiempo final para diferentes pares de parámetros dz y dt.

La primera gráfica sirve como punto de partida y muestra la combinación de dz y dt que se usó en la Tarea 1 (que corresponde exactamente al valor mínimo de dt para un dz dado según el criterio de estabilidad de Courtrand).

La última gráfica muestra los resultados para tanto dz como dt divididos por 2. Aquí, se puede observar que el resultado coincide con la primera gráfica: se confirma que según el criterio de Courtrand, si se disminúan dz y dt por el mismo factor, el comportamiento de estabilidad permanece lo mismo (en el caso presente: estable).

La segunda gráfica muestra los resultados para el mismo dt, pero un dz más fino (dividido por 3). La tercera gráfica mustrea los resultados para el mismo dz, pero un dt más grueso (multiplicado por 3). En cuanto al criterio de Courtrand, estos dos casos son equivalentes.

La razón por la cual no se ven plots en las gráficas es que, como se puede comprobar en los archivos .txt, todos los valores de los campos son "nan". En otras palabras, aunque se escogió un tiempo muz pequeño, ya este tiempo bastó para que divirgieran tanto los valores de los campos que C++ ya no podía continuar con las calculaciones de manera normal. De esta forma, se confirma que si el criterio de Courtrand no se cumple, el sistema FDTD no evoluciona de manera estable, y no importa si sea por un dz demasiado fino o un dt demasiado grueso, solo importa el ratio.