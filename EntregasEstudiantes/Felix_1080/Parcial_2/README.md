# Examen Fisica Computacional II


## Mario José Félix Rojas      
## 1017261080

Este proyecto implementa un simulador Finite Difference Time Domain para analizar la propagación de ondas electromagnéticas en un medio simple. Su diseño modular permite variar fácilmente las condiciones de frontera, ajustar parámetros de simulación y generar visualizaciones animadas de los resultados.


El archivo `fdtd.h`, define las estructuras principales del modelo y las herramientas para configurarlo. Este archivo describe la malla unidimensional con su número de nodos y espaciado.La implementación numérica detallada se encuentra en `fdtd.cpp`. Allí se codifican las actualizaciones de los campos $E_x$ y $H_y$ en cada paso temporal, de acuerdo con el esquema de Yee, junto con las rutinas que gestionan las condiciones de frontera.

La solución planteada incluye tres programas principales, cada uno pensado para un escenario de estudio distinto. El primero explora el comportamiento con fronteras periódicas, mostrando cómo la onda se propaga indefinidamente sin pérdidas. El segundo aplica condiciones de Dirichlet en los bordes, lo que permite analizar cómo se producen las reflexiones cuando la onda llega a los extremos del dominio. El tercero realiza un estudio de estabilidad variando el parámetro $\beta$, que está directamente relacionado con el paso temporal $dt$ y el espaciado $dz$, para evidenciar en qué condiciones el esquema mantiene estabilidad numérica y cuándo comienza a divergir.

Los resultados de cada simulación se guardan en archivos de texto dentro de la carpeta `output/`, organizados por escenario (`Punto1`, `Punto2a` y `Punto2b`). Cada archivo contiene bloques de datos para distintos instantes de tiempo, con columnas que representan la posición y los valores de los campos eléctrico y magnético. Esta estructura facilita el postprocesamiento y la animación de los datos.

El codigo en Python complementa el sistema al encargarse de procesar automáticamente los archivos de salida y generar animaciones en formato GIF y MP4. Recorre las subcarpetas de resultados, interpreta el contenido de cada archivo y construye animaciones en 3D que muestran la evolución de los campos en el tiempo. Al ser un script modular, permite ajustar parámetros como la velocidad de los vídeos, la cantidad de cuadros y la normalización de amplitudes, lo que lo hace ideal para comparar diferentes escenarios de simulación sin reescribir el código base.


La compilación se encuentra automatizada mediante un `Makefile` a tal punto que solo necesita moverse dentro del directorio raiz y ejecutar el comando `make` . 


## Resultados

Para obtener los resultados se debe dirigir al archivo en python y ejecutarlo.


En el primer caso (Punto 1), con condiciones periódicas, la propagación de la onda se visualiza de manera estable y sin pérdidas, confirmando que el esquema implementado reproduce correctamente el comportamiento esperado de un dominio cerrado. Los resultados pueden revisarse en la carpeta `Results/Punto1`, donde se encuentran los GIF y vídeos que muestran la evolución temporal de los campos.

En el segundo numeral (Punto 2a), con condiciones de frontera de Dirichlet, las animaciones evidencian las reflexiones totales en los extremos del dominio, con la onda rebotando de forma simétrica y conservando su energía a lo largo del tiempo.

El tercer caso (Punto 2b) permitió explorar el límite de estabilidad del modelo al variar el parámetro $\beta$, que relaciona el paso temporal $dt$ con el espaciamiento $dz$. Aunque la teoría presentada en el documento base indicaba que el esquema era estable para $\beta < 0.5$, las simulaciones demostraron que la condición de Courant en este caso particular se ajusta a $\beta \leq 1.0$.

Al analizar los resultados se observa que cuando $\beta$ supera el valor de 1.0, el sistema colapsa numéricamente, produciendo inestabilidades crecientes hasta que la simulación falla por completo.


Este trabajo se realizó en conjunto con Joan Sandoval.

