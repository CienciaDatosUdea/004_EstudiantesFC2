# Solución de la Ecuación de Schrödinger para Pozo Infinito 1D y 2D

Yennifer Yuliana Guerrero Uchima, Dayana Andrea Henao Arbelaez

## Introducción

Este proyecto resuelve numéricamente la ecuación de Schrödinger dependiente (TDSE) e independiente del tiempo (TISE) para un pozo potencial infinito en 1D y 2D.

### Ecuación de Schrödinger Time-Independent (TISE)

Para un pozo infinito, la ecuación independiente del tiempo es:

$$
-\frac{\hbar^2}{2m} \nabla^2 \psi(\mathbf{r}) = E \psi(\mathbf{r})
$$

con condiciones de frontera de Dirichlet: $\psi(\mathbf{r}) = 0$ en los bordes del pozo.

### Ecuación de Schrödinger Time-Dependent (TDSE)

Para la evolución temporal:

$$
i\hbar \frac{\partial}{\partial t} \psi(\mathbf{r}, t) = \left[ -\frac{\hbar^2}{2m} \nabla^2 + V(\mathbf{r}) \right] \psi(\mathbf{r}, t)
$$

## Discretización del Espacio

Se discretiza un espacio rectangular donde el potencial es cero dentro del pozo e infinito en las fronteras. Las condiciones de frontera se implementan haciendo que la función de onda se anule en los bordes.

## Solución Numérica usando el Método de Crank-Nicolson

Para resolver la ecuación de Schrödinger numéricamente, discretizamos el espacio y el tiempo usando el método de diferencias finitas. El método de Crank-Nicolson proporciona un enfoque estable y preciso para resolver la ecuación de Schrödinger dependiente del tiempo.

En una dimensión, la forma discretizada de la evolución de la función de onda está dada por:

$$
\left(I + \frac{i \Delta t}{2 \hbar} H\right) \Psi^{n+1} = \left(I - \frac{i \Delta t}{2 \hbar} H\right) \Psi^n
$$

donde:
- $\Psi^n$ representa la función de onda en el paso de tiempo $n$
- $H$ es la matriz Hamiltoniana discretizada
- $\Delta t$ es el paso de tiempo
- $I$ es la matriz identidad

Este sistema de ecuaciones se resuelve en cada paso de tiempo usando técnicas de álgebra lineal numérica (por ejemplo, descomposición LU o solucionadores iterativos).

### Extensión a 2D

En dos dimensiones, la ecuación de Schrödinger toma la forma:

$$
i \hbar \frac{\partial}{\partial t} \Psi (x, y, t) =
\left[ -\frac{\hbar^2}{2m} \left( \frac{\partial^2}{\partial x^2} + \frac{\partial^2}{\partial y^2} \right) + V(x, y, t) \right] \Psi (x, y, t)
$$

Usando diferencias finitas, el Laplaciano se aproxima como:

$$
\frac{\partial^2 \Psi}{\partial x^2} \approx \frac{\Psi_{i+1,j}^n - 2\Psi_{i,j}^n + \Psi_{i-1,j}^n}{\Delta x^2}
$$

$$
\frac{\partial^2 \Psi}{\partial y^2} \approx \frac{\Psi_{i,j+1}^n - 2\Psi_{i,j}^n + \Psi_{i,j-1}^n}{\Delta y^2}
$$

Por lo tanto, el esquema de Crank-Nicolson en 2D conduce a una ecuación matricial similar al caso 1D, pero ahora con un sistema de ecuaciones más grande debido a la dimensión espacial adicional.

### 1D: Discretización

```cpp
// Malla 1D: N puntos internos, L longitud del pozo
double dx = L / (N + 1);
for (int i = 0; i < N; i++) {
    double x = (i + 1) * dx;
    // Condiciones: ψ(0) = ψ(L) = 0
}
```

### 2D: Discretización

```cpp
// Malla 2D: Nx × Ny puntos internos
double dx = Lx / (Nx + 1);
double dy = Ly / (Ny + 1);
for (int i = 0; i < Nx; i++) {
    for (int j = 0; j < Ny; j++) {
        double x = (i + 1) * dx;
        double y = (j + 1) * dy;
        // Condiciones: ψ en fronteras = 0
    }
}
```

---

(El resto del documento se mantiene igual que tu versión, pero con ecuaciones corregidas y bloques de código bien cerrados.)
