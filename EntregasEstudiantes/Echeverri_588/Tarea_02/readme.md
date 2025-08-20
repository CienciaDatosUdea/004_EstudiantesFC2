# 🌡️ Modelo de Difusión en 1D

Este proyecto implementa un **modelo numérico de difusión en una dimensión**, resolviendo la ecuación diferencial parcial:

$$
\frac{\partial u}{\partial t} = D \frac{\partial^2 u}{\partial x^2}
$$

donde:
- \(u(x,t)\) → temperatura o concentración en el punto \(x\) y tiempo \(t\).  
- \(D\) → coeficiente de difusión.  

El código utiliza una **discretización en diferencias finitas** para aproximar la evolución temporal.

---

## 📂 Estructura del proyecto

├── include/               # Archivos de cabecera (.h)
│   └── difusion_model.h
├── src/                   # Archivos fuente (.cpp)
│   ├── difusion_model.cpp
│   └── main.cpp           # Programa principal
├── Makefile
└── README.md

---

## 🏗️ Clases principales

### 1. `Geometria`
- Representa la **malla espacial** donde ocurre la difusión.  
- Define:  
  - Intervalo \([x_{\min}, x_{\max}]\).  
  - Número de nodos `N`.  
  - Espaciamiento `dx`.  
  - Vector `x` con las posiciones de cada nodo.  
 
### 2. `Condiciones:` 
- Contiene el **estado inicial** y las **condiciones de frontera**.  
- Tipos de frontera:  
  - **Dirichlet** → fijar el valor en los bordes (ejemplo: paredes a temperatura constante).  
  - **Neumann** → fijar el flujo en los bordes (ejemplo: aislamiento → gradiente nulo).  

### 3. `DiffusionSolver`
- Ejecuta la **evolución temporal** de la ecuación de difusión.  
- Parámetros:  
  - `D` → coeficiente de difusión.  
  - `dt` → paso de tiempo.  
  - `t_max` → tiempo total de simulación.  
- Usa diferencias finitas:  

\[
u_i^{n+1} = u_i^n + \frac{D \, dt}{dx^2} \left( u_{i+1}^n - 2u_i^n + u_{i-1}^n \right)
\]

Para compilar y ejecutar el proyecto simplemente escribe:  
```bash
make

