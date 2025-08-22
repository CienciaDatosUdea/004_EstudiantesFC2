# Simulación de Flujo de Fluido y Visualización

Este proyecto implementa la lectura, procesamiento y visualización de campos de presión y velocidades a partir de archivos de datos (`.txt`).  
El objetivo es representar la evolución temporal de un campo de fluidos mediante un **mapa de presión (colormap)** y un **campo vectorial de velocidades (quiver plot)**, generando una animación en Python.

---

## 📂 Estructura del Proyecto

├── include/
│ └── simulacion.h # Archivo de cabecera con definición de funciones
├── src/
│ └── simulacion.cpp # Implementación de funciones principales
├── main.cpp # Programa principal
├── data/ # Carpeta con archivos de datos campos_XXX.txt
└── README.md # Este archivo


---

## ⚙️ Requisitos

- Compilador C++ (g++ recomendado)
- Python 3.x con librerías:
  - `numpy`
  - `matplotlib`

Instalación de librerías en Python:


pip install numpy matplotlib
---

## Cada archivo de datos (campos_XXX.txt) contiene:

Coordenadas espaciales: X, Y

Velocidades: U, V

Magnitud de la velocidad: |V|

Presión: P
---

