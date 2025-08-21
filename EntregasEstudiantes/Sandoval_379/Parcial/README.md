# Examen Fisica Computacional II
## **Nombre**: Joan Sebastian Sandoval Parra        **Codigo¨¨: 1010057379

Este proyecto implementa un simulador **FDTD 1D** (Finite Difference Time Domain) para analizar la propagación de ondas electromagnéticas en un medio simple. Su diseño modular permite variar fácilmente las condiciones de frontera, ajustar parámetros de simulación y generar visualizaciones animadas de los resultados.

---

El corazón del sistema está en el archivo `em1d.h`, que define las estructuras principales del modelo y las herramientas para configurarlo. Este archivo describe la malla unidimensional con su número de nodos y espaciado, los arreglos que almacenan los campos eléctricos y magnéticos en un esquema *staggered*, así como el tipo de frontera a utilizar, que puede ser periódica —ideal para simular un dominio cerrado donde la onda que sale por un extremo vuelve a entrar— o de Dirichlet, donde los extremos se fijan en cero para simular reflexión total. También contiene la clase encargada de evolucionar el sistema, inicializar los campos con una perturbación senoidal y registrar los resultados de cada paso en archivos de texto.

La implementación numérica detallada se encuentra en `em1d.cpp`. Allí se codifican las actualizaciones de los campos $E_x$ y $H_y$ en cada paso temporal, de acuerdo con el esquema de Yee, junto con las rutinas que gestionan las condiciones de frontera. Su diseño busca claridad y versatilidad: cualquier ajuste en los parámetros del mallado, el número de pasos o el tipo de frontera se puede hacer sin modificar el núcleo del algoritmo.

---

El proyecto incluye tres programas principales, cada uno pensado para un escenario de estudio distinto. El primero explora el comportamiento con fronteras periódicas, mostrando cómo la onda se propaga indefinidamente sin pérdidas. El segundo aplica condiciones de Dirichlet en los bordes, lo que permite analizar cómo se producen las reflexiones cuando la onda llega a los extremos del dominio. El tercero realiza un estudio de estabilidad variando el parámetro $\beta$, que está directamente relacionado con el paso temporal $dt$ y el espaciado $dz$, para evidenciar en qué condiciones el esquema mantiene estabilidad numérica y cuándo comienza a divergir.

Los resultados de cada simulación se guardan en archivos de texto dentro de la carpeta `output/`, organizados por escenario (`Punto1`, `Punto2a` y `Punto2b`). Cada archivo contiene bloques de datos para distintos instantes de tiempo, con columnas que representan la posición y los valores de los campos eléctrico y magnético. Esta estructura facilita el postprocesamiento y la animación de los datos.

---

El script de Python complementa el sistema al encargarse de procesar automáticamente los archivos de salida y generar animaciones en formato GIF y MP4. Recorre las subcarpetas de resultados, interpreta el contenido de cada archivo y construye animaciones en 3D que muestran la evolución de los campos en el tiempo. Al ser un script modular, permite ajustar parámetros como la velocidad de los vídeos, la cantidad de cuadros y la normalización de amplitudes, lo que lo hace ideal para comparar diferentes escenarios de simulación sin reescribir el código base.

---

La compilación y ejecución están automatizadas mediante un `Makefile` sencillo. Usando "make run" se pueden compilar los programas, generar las carpetas necesarias y ejecutar cada caso de forma individual o secuencial. Esto facilita la experimentación, ya que no es necesario preocuparse por la organización de archivos o por crear manualmente las carpetas de salida.

En conjunto, el proyecto es **versátil y fácil de extender**. Cambiar la malla, ajustar los parámetros de tiempo o espaciales, o incorporar nuevas rutinas de análisis requiere modificaciones mínimas, y el flujo de trabajo completo —desde la simulación hasta la visualización— está pensado para que cualquier usuario pueda reproducir y entender los resultados con claridad.

Aquí tienes una propuesta clara y bien estructurada para la **sección de Resultados**, siguiendo el estilo narrativo del README anterior:

## Resultados

Las simulaciones se ejecutaron de forma satisfactoria en los escenarios planteados.

En el **primer caso (Punto 1)**, con condiciones periódicas, la propagación de la onda se visualiza de manera estable y sin pérdidas, confirmando que el esquema implementado reproduce correctamente el comportamiento esperado de un dominio cerrado. Los resultados pueden revisarse en la carpeta `Results/Punto1`, donde se encuentran los GIF y vídeos que muestran la evolución temporal de los campos.

En el **segundo caso (Punto 2a)**, con condiciones de frontera de Dirichlet, el sistema también se comportó como se anticipaba. Las animaciones disponibles en `Results/Punto2a` evidencian las reflexiones totales en los extremos del dominio, con la onda rebotando de forma simétrica y conservando su energía a lo largo del tiempo.

El **tercer caso (Punto 2b)** permitió explorar el límite de estabilidad del modelo al variar el parámetro $\beta$, que relaciona el paso temporal $dt$ con el espaciamiento $dz$. Aunque la teoría presentada en el documento base indicaba que el esquema era estable para $\beta < 0.5$, las simulaciones demostraron que la condición de Courant en este caso particular se ajusta a $\beta \leq 1.0$.

Al analizar los resultados —específicamente los archivos **`Sim_Pa_beta5.txt`** y **`Sim_Pa_beta6.txt`** en `Results/Punto2b`— se observa que cuando $\beta$ supera el valor de 1.0, el sistema colapsa numéricamente, produciendo inestabilidades crecientes hasta que la simulación falla por completo. Para valores ligeramente superiores a 1.0 el sistema aún puede ejecutar algunos pasos antes de divergir, pero en configuraciones más extremas, como $\beta = 1.2$, el cálculo se vuelve inmediatamente inestable e inutilizable.

Estos resultados no solo confirman la correcta implementación del esquema FDTD, sino que también permiten entender mejor los límites de estabilidad del modelo en la versión implementada, mostrando cómo los ajustes en el paso temporal pueden llevar el sistema desde un régimen perfectamente estable a un colapso numérico completo.


