# Solución de la Ecuación de Schrödinger para Pozo Infinito 1D y 2D



### Yennifer Yuliana Guerrero Uchima

### Dayana Andrea Henao Arbelaez



## Introducción

Este proyecto resuelve numéricamente la ecuación de Schrödinger dependiente (TDSE) e independiente del tiempo (TISE) para un pozo potencial infinito en 1D y 2D.


### Ecuación de Schrödinger Time-Independent (TISE)

Para un pozo infinito, la ecuación time-independent es:

$$ -\frac{\hbar^2}{2m} \nabla^2 \psi(\mathbf{r}) = E \psi(\mathbf{r}) $$

con condiciones de frontera de Dirichlet: $\psi(\mathbf{r}) = 0$ en los bordes del pozo.


### Ecuación de Schrödinger Time-Dependent (TDSE)



Para la evolución temporal:

$$ i\hbar \frac{\partial}{\partial t} \psi(\mathbf{r}, t) = \left[ -\frac{\hbar^2}{2m} \nabla^2 + V(\mathbf{r}) \right] \psi(\mathbf{r}, t) $$

## Discretización del Espacio

Se discretiza un espacio rectangular donde el potencial es cero dentro del pozo e infinito en las fronteras. Las condiciones de frontera se implementan haciendo que la función de onda se anule en los bordes.



## Solución Numérica usando el Método de Crank-Nicolson

Para resolver la ecuación de Schrödinger numéricamente, discretizamos el espacio y el tiempo usando el método de diferencias finitas. El método de Crank-Nicolson proporciona un enfoque estable y preciso para resolver la ecuación de Schrödinger dependiente del tiempo.

En una dimensión, la forma discretizada de la evolución de la función de onda está dada por:

$$ (I + \frac{i \Delta t}{2 \hbar} H) \Psi^{n+1} = (I - \frac{i \Delta t}{2 \hbar} H) \Psi^n $$

donde:
- $\Psi^n$ representa la función de onda en el paso de tiempo $ n $
- $H$ es la matriz Hamiltoniana discretizada
- $\Delta t$ es el paso de tiempo
- $I$ es la matriz identidad

Este sistema de ecuaciones se resuelve en cada paso de tiempo usando técnicas de álgebra lineal numérica (por ejemplo, descomposición LU o solucionadores iterativos).




### Extensión a 2D

En dos dimensiones, la ecuación de Schrödinger toma la forma:

$$ i \hbar \frac{\partial}{\partial t} \Psi (x, y, t) = \left[ -\frac{\hbar^2}{2m} \left( \frac{\partial^2}{\partial x^2} + \frac{\partial^2}{\partial y^2} \right) + V(x, y, t) \right] \Psi (x, y, t) $$

Usando diferencias finitas, el Laplaciano se aproxima como:

$$ \frac{\partial^2 \Psi}{\partial x^2} \approx \frac{\Psi_{i+1,j}^n - 2\Psi_{i,j}^n + \Psi_{i-1,j}^n}{\Delta x^2} $$

$$ \frac{\partial^2 \Psi}{\partial y^2} \approx \frac{\Psi_{i,j+1}^n - 2\Psi_{i,j}^n + \Psi_{i,j-1}^n}{\Delta y^2} $$

Por lo tanto, el esquema de Crank-Nicolson en 2D conduce a una ecuación matricial similar al caso 1D, pero ahora con un sistema de ecuaciones más grande debido a la dimensión espacial adicional.




### 1D: Discretización
```cpp
// Malla 1D: N puntos internos, L longitud del pozo
double dx = L / (N + 1);
for (int i = 0; i < N; i++) {
    double x = (i + 1) * dx;
    // Condiciones: ψ(0) = ψ(L) = 0
}


´´

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
´´´




## Solución Numérica usando el Método de Jacobi para Autovalores....



Para resolver la ecuación de Schrödinger independiente del tiempo (TISE) numéricamente, discretizamos el espacio usando el método de diferencias finitas y diagonalizamos el Hamiltoniano para encontrar los estados estacionarios. El método de Jacobi proporciona un algoritmo estable para encontrar autovalores y autovectores de matrices simétricas.

### Formulación del Problema de Autovalores

La ecuación de Schrödinger independiente del tiempo se discretiza como:

$$ H \psi = E \psi $$

donde:
- $ H $ es la matriz Hamiltoniana discretizada (tridiagonal en 1D, dispersa en 2D)
- $ \psi $ es el autovector que representa la función de onda discretizada
- $ E $ es el autovalor que representa la energía del estado




### Método de Jacobi para Diagonalización

El método de Jacobi diagonaliza matrices simétricas mediante rotaciones sucesivas que anulan los elementos fuera de la diagonal. Cada rotación se define como:

$$ J(p,q) = \begin{bmatrix}
1 & \cdots & 0 & \cdots & 0 & \cdots & 0 \\
\vdots & \ddots & \vdots & & \vdots & & \vdots \\
0 & \cdots & \cos\theta & \cdots & \sin\theta & \cdots & 0 \\
\vdots & & \vdots & \ddots & \vdots & & \vdots \\
0 & \cdots & -\sin\theta & \cdots & \cos\theta & \cdots & 0 \\
\vdots & & \vdots & & \vdots & \ddots & \vdots \\
0 & \cdots & 0 & \cdots & 0 & \cdots & 1
\end{bmatrix} $$



El ángulo de rotación $ \theta $ se elige para anular el elemento $ H_{pq} $:

$$ \tan(2\theta) = \frac{2H_{pq}}{H_{qq} - H_{pp}} $$

### Algoritmo en 1D

Para el caso 1D, el Hamiltoniano es tridiagonal:

$$ H = \begin{bmatrix}
d_1 & u_1 & 0 & \cdots & 0 \\
u_1 & d_2 & u_2 & \cdots & 0 \\
0 & u_2 & d_3 & \cdots & 0 \\
\vdots & \vdots & \vdots & \ddots & u_{n-1} \\
0 & 0 & 0 & u_{n-1} & d_n
\end{bmatrix} $$

donde los elementos diagonales y fuera de la diagonal son:

$$ d_i = \frac{\hbar^2}{m \Delta x^2} + V(x_i) $$
$$ u_i = -\frac{\hbar^2}{2m \Delta x^2} $$



### Algoritmo en 2D

Para el caso 2D, el Hamiltoniano tiene una estructura de bloques:

$$ H = \begin{bmatrix}
A & B & 0 & \cdots & 0 \\
B & A & B & \cdots & 0 \\
0 & B & A & \cdots & 0 \\
\vdots & \vdots & \vdots & \ddots & B \\
0 & 0 & 0 & B & A
\end{bmatrix} $$

donde cada bloque $ A $ es tridiagonal y los bloques $ B $ son diagonales, reflejando el acoplamiento entre puntos vecinos en ambas direcciones.



### Implementación del Método

El algoritmo de Jacobi itera hasta que todos los elementos fuera de la diagonal son menores que una tolerancia especificada:

```python
while max_off_diagonal > tolerance:
    for p in range(n-1):
        for q in range(p+1, n):
            if abs(H[p,q]) > threshold:
                # Calcular ángulo de rotación
                theta = 0.5 * atan2(2*H[p,q], H[q,q]-H[p,p])
                c = cos(theta)
                s = sin(theta)
                
                # Aplicar rotación a H
                for i in range(n):
                    if i != p and i != q:
                        H_ip = c*H[i,p] - s*H[i,q]
                        H_iq = s*H[i,p] + c*H[i,q]
                        H[i,p] = H_ip
                        H[p,i] = H_ip
                        H[i,q] = H_iq
                        H[q,i] = H_iq
                
                # Actualizar autovectores
                for i in range(n):
                    V_ip = c*V[i,p] - s*V[i,q]
                    V_iq = s*V[i,p] + c*V[i,q]
                    V[i,p] = V_ip
                    V[i,q] = V_iq
                    
                    
## Solución Numérica usando el Método de Jacobi para Autovalores en 2D



### Formulación del Problema en 2D

Para el caso bidimensional, la ecuación de Schrödinger independiente del tiempo se discretiza en una malla de $N_x \times N_y$ puntos. El Hamiltoniano resultante es una matriz de gran dimensión ($N_xN_y \times N_xN_y$) con una estructura dispersa característica.

### Estructura del Hamiltoniano 2D

La matriz Hamiltoniana en 2D tiene una estructura de bloques tridiagonal:

$$ H = \begin{bmatrix}
T & V & 0 & \cdots & 0 \\
V & T & V & \cdots & 0 \\
0 & V & T & \cdots & 0 \\
\vdots & \vdots & \vdots & \ddots & V \\
0 & 0 & 0 & V & T
\end{bmatrix} $$

donde cada bloque $T$ es tridiagonal y representa el operador cinético en la dirección x, y los bloques $V$ son diagonales y representan el acoplamiento en la dirección y.

### Elementos de la Matriz

Para un punto $(i,j)$ en la malla 2D:

**Término diagonal principal:**
$$ H_{ij,ij} = \frac{\hbar^2}{m} \left( \frac{1}{\Delta x^2} + \frac{1}{\Delta y^2} \right) + V(x_i, y_j) $$

**Acoplamiento en dirección x:**
$$ H_{ij,(i+1)j} = H_{(i+1)j,ij} = -\frac{\hbar^2}{2m \Delta x^2} $$

**Acoplamiento en dirección y:**
$$ H_{ij,i(j+1)} = H_{i(j+1),ij} = -\frac{\hbar^2}{2m \Delta y^2} $$

### Implementación del Método de Jacobi para 2D

El algoritmo procesa sistemáticamente todos los pares de elementos fuera de la diagonal:

```cpp
void jacobi_eigenvalues_2d(double* A, int n, double tol, 
                          double* eigenvectors, double* eigenvalues) {
    
    // Inicializar matriz de autovectores como identidad
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            eigenvectors[i * n + j] = (i == j) ? 1.0 : 0.0;
        }
    }
    
    double* B = new double[n * n];
    for (int i = 0; i < n * n; i++) {
        B[i] = A[i];  // Copiar matriz original
    }
    
    double error = tol + 1.0;
    int max_iter = 1000;
    int iter = 0;
    
    while (error > tol && iter < max_iter) {
        error = 0.0;
        
        // Recorrer todos los pares (p,q) fuera de la diagonal
        for (int p = 0; p < n - 1; p++) {
            for (int q = p + 1; q < n; q++) {
                if (fabs(B[p * n + q]) > 1e-12) {
                    error = fmax(error, fabs(B[p * n + q]));
                    
                    // Calcular ángulo de rotación óptimo
                    double phi = 0.5 * atan2(2.0 * B[p * n + q], 
                                           B[q * n + q] - B[p * n + p]);
                    double c = cos(phi), s = sin(phi);
                    
                    // Actualizar filas y columnas p y q
                    for (int i = 0; i < n; i++) {
                        if (i != p && i != q) {
                            // Elementos fuera de las filas p,q
                            double B_ip = c * B[i * n + p] - s * B[i * n + q];
                            double B_iq = s * B[i * n + p] + c * B[i * n + q];
                            B[i * n + p] = B_ip;
                            B[p * n + i] = B_ip;  // Mantener simetría
                            B[i * n + q] = B_iq;
                            B[q * n + i] = B_iq;
                        }
                    }
                    
                    // Actualizar elementos diagonales
                    double B_pp = c*c*B[p*n+p] - 2.0*s*c*B[p*n+q] + s*s*B[q*n+q];
                    double B_qq = s*s*B[p*n+p] + 2.0*s*c*B[p*n+q] + c*c*B[q*n+q];
                    B[p * n + p] = B_pp;
                    B[q * n + q] = B_qq;
                    B[p * n + q] = 0.0;
                    B[q * n + p] = 0.0;
                    
                    // Actualizar autovectores
                    for (int i = 0; i < n; i++) {
                        double V_ip = c * eigenvectors[i * n + p] - s * eigenvectors[i * n + q];
                        double V_iq = s * eigenvectors[i * n + p] + c * eigenvectors[i * n + q];
                        eigenvectors[i * n + p] = V_ip;
                        eigenvectors[i * n + q] = V_iq;
                    }
                }
            }
        }
        iter++;
    }
    
    // Extraer autovalores de la diagonal
    for (int i = 0; i < n; i++) {
        eigenvalues[i] = B[i * n + i];
    }
    
    delete[] B;
}



## Algoritmo de Thomas para la Solución de Sistemas Tridiagonales

### Formulación del Problema

El algoritmo de Thomas resuelve sistemas de ecuaciones lineales con matrices tridiagonales de la forma:

$$
\begin{bmatrix}
b_0 & c_0 & 0 & \cdots & 0 \\
a_1 & b_1 & c_1 & \cdots & 0 \\
0 & a_2 & b_2 & \cdots & 0 \\
\vdots & \vdots & \vdots & \ddots & c_{n-1} \\
0 & 0 & 0 & a_n & b_n
\end{bmatrix}
\begin{bmatrix}
x_0 \\
x_1 \\
x_2 \\
\vdots \\
x_n
\end{bmatrix}
=
\begin{bmatrix}
d_0 \\
d_1 \\
d_2 \\
\vdots \\
d_n
\end{bmatrix}
$$

### Descripción del Algoritmo

#### Paso 1: Forward Elimination (Eliminación Hacia Adelante)

Para $i = 1$ hasta $n-1$:

$$
m = \frac{a_i}{b_{i-1}}
$$
$$
b_i = b_i - m \cdot c_{i-1}
$$
$$
d_i = d_i - m \cdot d_{i-1}
$$

#### Paso 2: Back Substitution (Sustitución Hacia Atrás)

Para $i = n-1$ hasta $0$:

$$
x_i = \frac{d_i - c_i \cdot x_{i+1}}{b_i}
$$

### Aplicación en la Ecuación de Schrödinger 1D

Para el método de Crank-Nicolson en 1D, el sistema a resolver es:

$$ (I + \frac{i \Delta t}{2 \hbar} H) \Psi^{n+1} = (I - \frac{i \Delta t}{2 \hbar} H) \Psi^n $$

Donde la matriz tridiagonal tiene los elementos:

- **Diagonal principal ($b_i$):**
$$ b_i = 1 + \frac{i \Delta t}{2 \hbar} \left( \frac{\hbar^2}{m \Delta x^2} + V(x_i) \right) $$

- **Subdiagonal ($a_i$) y superdiagonal ($c_i$):**
$$ a_i = c_i = -\frac{i \Delta t \hbar}{4m \Delta x^2} $$

### Implementación del Algoritmo de Thomas

```cpp
void thomas_algorithm(int n, double* a, double* b, double* c, double* d, double* x) {
    // Forward elimination
    for (int i = 1; i < n; i++) {
        double m = a[i] / b[i-1];
        b[i] = b[i] - m * c[i-1];
        d[i] = d[i] - m * d[i-1];
    }
    
    // Back substitution
    x[n-1] = d[n-1] / b[n-1];
    for (int i = n-2; i >= 0; i--) {
        x[i] = (d[i] - c[i] * x[i+1]) / b[i];
    }
}



## Implemmentación y estrcutura del proyecto 



```
ProyectoFinal/
├── include/                 
│   ├── TDSE.h               # TDSE 1D
│   ├── TDSE_2D.h            # TDSE 2D
│   ├── TISE.h               # TISE 1D
│   ├── TISE_2D.h            # TISE 2D
│   └── wavepacket.h
│
├── src/                     
│   ├── TDSE.cpp             # TDSE 1D
│   ├── TDSE_2D.cpp          # TDSE 2D
│   ├── TISE.cpp             # TISE 1D
│   ├── TISE_2D.cpp          # TISE 2D
│   └── wavepacket.cpp
│
├── resultados_1D/           
│   ├── TDSE/                # Resultados TDSE 1D
│   └── TISE/                # Resultados TISE 1D
│
├── resultados_2D/           
│   ├── TDSE/                # Resultados TDSE 2D
│   └── TISE/                # Resultados TISE 2D
│
├── python/                  
│   ├── TDSE_1D.py
│   ├── TDSE_2D.py
│   ├── TISE_1D.py
│   ├── TISE_2D.py
│   ├── TDSE_2D.ipynb
│   ├── TISE_1D.ipynb
│   ├── TISE_2D.ipynb
│   ├── evolucion_TDSE.gif
│   ├── evolucion_TDSE_h.gif
│   └── (otros scripts de visualización)
│
├── main_1d.cpp              
├── main_2d.cpp              
└── Makefile

```






###Visualizaciones 



![Evolución de la función de onda](ProyectoFinal/python/evolucion_TDSE.gif)



![Mapa de Calor de la Evolución temporal del módulo de la Función de onda](ProyectoFinal/python/evolucion_TDSE_heatmap.gif)




------------------------------------------------------------------------

## Estructura del proyecto

-   `include/` → Archivos de cabecera `.h`
-   `src/` → Archivos fuente `.cpp`
-   `python/` → Scripts de visualización en Python
-   `resultados_1D/` y `resultados_2D/` → Resultados numéricos de las
    simulaciones
-   `main_1d.cpp` y `main_2d.cpp` → Archivos principales para ejecutar
    las simulaciones
-   `Makefile` → Reglas de compilación y ejecución

------------------------------------------------------------------------

##  Requisitos

-   **Compilador C++17** (ej. `g++`)
-   **Python 3** con librerías:
    -   `numpy`
    -   `matplotlib`

------------------------------------------------------------------------

##  Compilación

Compilar ambos programas (1D y 2D):

``` bash
make all
```

Compilar solo el código de **1D**:

``` bash
make 1d
```

Compilar solo el código de **2D**:

``` bash
make 2d
```

------------------------------------------------------------------------

##  Ejecución de simulaciones

Ejecutar la simulación **1D**:

``` bash
make run-1d
```

Ejecutar la simulación **2D**:

``` bash
make run-2d
```

Los resultados `.dat` se guardarán en `resultados_1D/` o
`resultados_2D/`.

------------------------------------------------------------------------

## Visualización de resultados

Preparar y visualizar la simulación **1D**:

``` bash
make viz-1d
```

Preparar y visualizar la simulación **2D**:

``` bash
make viz-2d
```

Esto copiará los archivos de resultados a la carpeta `python/` y
ejecutará los scripts correspondientes.

------------------------------------------------------------------------

##  Limpieza

Para eliminar ejecutables, resultados y archivos temporales:

``` bash
make clean
```

------------------------------------------------------------------------

##  Ayuda

Puedes ver todas las opciones disponibles con:

``` bash
make help
```
