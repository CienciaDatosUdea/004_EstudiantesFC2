# Examen Final FC2 – Método FDTD en 1D

Implementación del método de Diferencias Finitas en el Dominio del Tiempo (FDTD) para la propagación de ondas electromagnéticas en una dimensión, siguiendo el enunciado del examen de Física Computacional 2.

---

## 📂 Estructura del repositorio

include/
    fdtd.hpp
src/
    fdtd.cpp
main.cpp
Makefile
python/
    sim_fdtd.ipynb
    AnalisisRespuestas.ipynb
docs/
    README.md


---

## ⚙️ Compilación

Desde la raíz del proyecto:

```bash
make

./main <bc> <nsteps> <beta> <outfile> <dz>

```

## 📊 Visualización y análisis
1. Graficar evolución de E y H

Entra a la carpeta python/ y ejecuta:

```bash
python3 plot_evolution.py ../fields_periodic.dat --save
```

Esto genera figuras separadas de E y H para distintos tiempos, además de gráficas de la energía y la amplitud máxima.

## Notebook de análisis

En AnalisisRespuestas.ipynb se encuentran:

Evolución de E y H con fronteras periódicas.

Evolución con fronteras fijas (E=H=0 en bordes).

Estudio de estabilidad comparando casos con β estable (0.49) e inestable (0.55).

Discusión de la condición de Courant.

## 📌 Resultados esperados

Periódicas (1.1): las ondas se propagan indefinidamente y reingresan al dominio sin perder energía.

Fronteras anuladas (1.2a): aparecen reflexiones en los bordes y se forman ondas estacionarias.

Estabilidad (1.2b):

Si 𝛽 ≤ 0.5: energía y amplitud máxima constantes (simulación estable).

Si 𝛽 > 0.5: energía y amplitud crecen sin límite (explosión numérica → inestabilidad).
