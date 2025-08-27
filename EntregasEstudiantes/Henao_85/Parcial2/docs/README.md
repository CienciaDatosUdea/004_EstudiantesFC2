# Parcial #2

En este proyecto se estudia la propagación de ondas electromagnéticas en una dimensión empleando el método de diferencias finitas en el dominio del tiempo (FDTD).

El código implementa el esquema de malla escalonada propuesto por Yee, en el cual los campos eléctrico y magnético se intercalan en espacio y tiempo de la siguiente manera:

• Ex se define en posiciones enteras k y tiempos semi-enteros n + 1/2.
• Hy se define en posiciones semi-enteras k + 1/2 y tiempos enteros n.

Este desfase espacial y temporal garantiza la correcta propagación y acoplamiento entre los campos, además de facilitar la estabilidad numérica del método.

El programa permite simular dos tipos de condiciones de frontera:

Periódicas: la onda al llegar a un extremo de la malla reaparece en el otro extremo sin deformación, de manera que la propagación es indefinida.

Dirichlet: los campos se anulan en los bordes (E=H=0), provocando reflexión de las ondas y la eventual formación de ondas estacionarias.

Los resultados de cada caso se guardan en carpetas distintas (output_periodic/ y output_dirichlet/), en formato CSV, y pueden visualizarse posteriormente mediante gráficos de los campos a lo largo de la malla.

## Ejecución 

Como el proyecto cuenta con un Makefile, para hacer la compilación basta con abrir una terminal en la carpeta donde se encuentra el repositorio y ejecutar: make, Esto generará el ejecutable fdtd_sim.out, el cual puede correrse directamente con: ./fdtd_sim.out
