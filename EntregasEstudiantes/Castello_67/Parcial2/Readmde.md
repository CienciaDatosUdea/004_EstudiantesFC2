# Proyecto FDTD 1D

Este proyecto implementa un esquema de diferencias finitas en el dominio del tiempo (FDTD) para simular la evolución de campos electromagnéticos en 1D. Incluye dos programas principales (`main1` y `main2`) y scripts de Python para visualizar los resultados.

### Compilacion 
Para compilar el proyecto, simplemente ejecuta en la terminal, desde la raíz del proyecto:

```make```

Esto generará los ejecutables main1, main2 y los ejecutables de test en la carpeta test. Para limpiar todos los archivos generados (incluyendo archivos .o, ejecutables y archivos .txt de salida), escribe en la misma raiz del proyecto:

```make clean```

### Ejecución de los programas principales

Los ejecutables `main1`, `main2` y `main3` deben ejecutarse por separado. Cada uno genera un archivo de salida (`main1.txt` , `main2.txt` y `main3.txt`) con la evolución temporal de los campos.Para ejecutar cada uno:

```
./main1
./main2
./main3
```

### Visualización de las soluciones
En la carpeta `/python` encontrarás un script para animar y visualizar los resultados generados por los ejecutables. Ubicado en dicha carpeta solo tienes que escribir

```python3 sim_fdtd.py```

**ADVERTENCIA: LA PRODUCCIÓN DE LAS ANIMACIONES PUEDE TOMAR UN PAR DE SEGUNDOS. POR FAVOR, TEN PACIENCIA MIENTRAS SE GENERAN LOS GIFS.**

Las unicas dependencias de python que necesitas para el proyecto son:

- **NumPy** → `2.3.2` 
- **pandas** → `2.3.2`  
- **matplotlib** → `3.10.5` 
  - Incluye: `mpl_toolkits.mplot3d` y `matplotlib.animation.FuncAnimation`  
- **gc** → módulo estándar de Python (sin versión independiente)  
- **os** → módulo estándar de Python (sin versión independiente)

### Descripción de los programas principales
**main1:**
* Inicialización: El programa main1 inicializa ambos campos (E y H) con una onda sinusoidal idéntica en todos los puntos del espacio.
* Condiciones de frontera: Utiliza condiciones de frontera periódicas.
* Nota física: Si ambos campos son iguales en todos los puntos y se inicializan de forma idéntica, no habrá evolución temporal, ya que la solución es estacionaria bajo estas condiciones.
* Salida: El resultado se guarda en main1.txt.

**main2:**
* Condiciones de frontera: En main2, los campos se anulan en los extremos de la caja (condiciones de frontera de tipo Dirichlet).
* Visualización: Por cuestiones de visualización, en las animaciones generadas se omiten las flechitas (vectores) en los extremos del gráfico, ya que los valores en los bordes son siempre cero.
* Salida: El resultado se guarda en main2.txt.

**main3:**
* Estudio de la condición de Courant: En main3 se estudia el efecto de elegir parámetros de simulación que NO cumplen con la condición de Courant, lo que puede llevar a inestabilidades numéricas o resultados no físicos. Demostrando asi experimentalmente la validez de dicha condicion al tomar un valor que difiere solamente en 0.005 del valor minimo de 0.5 para la estabilidad!.
* Salida: El resultado se guarda en main3.txt.


**Autor:** Juan Felipe Castello Arango - Universidad de Antioquia.