# Simulación de la Ecuación de Difusión 1D con el Método FTCS

Este proyecto implementa la ecuación de difusión 1D usando el método explícito FTCS (Forward Time Centered Space) en C++.  
La estructura del código está dividida en tres archivos para mantener modularidad:

1. `difusion_model.h` → Definición de las clases
2. `difusion_model.cpp` → Implementación de métodos
3. `main.cpp` → Configuración de parámetros y ejecución

---

## Estructura del proyecto

├── difusion_model.h # Archivo de cabecera con clases Geometria, Condiciones y DiffusionSolver
├── difusion_model.cpp # Implementación de los métodos definidos en el .h
├── main.cpp # Programa principal
└── README.md # Este archivo


## Descripción de las clases

### Geometria
- Define el dominio espacial 1D.
- Calcula dx y genera el vector de posiciones x.

### Condiciones
- Almacena el vector u (temperatura).
- Configura condiciones iniciales (gaussiana) y de frontera.

### DiffusionSolver
- Contiene parámetros físicos (D, dt, t_max).
- Verifica la condición de estabilidad (alpha <= 0.5).
- Resuelve la ecuación de difusión usando FTCS.
- Exporta resultados a un archivo .txt.

---

## Ecuación resuelta

La ecuación de difusión 1D es:

du/dt = D * d²u/dx²

El método FTCS discretiza como:

u_i^(n+1) = u_i^n + alpha * (u_{i+1}^n - 2*u_i^n + u_{i-1}^n)

donde:

alpha = (D * dt) / (dx²)

---

## Compilación y ejecución

### Compilar
Usando g++:
```bash
g++ main.cpp difusion_model.cpp -o difusion -std=c++11
