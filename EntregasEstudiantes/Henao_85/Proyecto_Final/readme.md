# Proyecto: Simulaciones Cuánticas Numéricas

## Resumen

Este proyecto implementa simulaciones numéricas de sistemas cuánticos unidimensionales, incluyendo:

1. Evolución temporal de un **paquete gaussiano** libre (Wavepacket)  
2. Resolución de la **Ecuación de Schrödinger dependiente del tiempo (TDSE)** usando el método de Crank-Nicolson  
3. Resolución de la **Ecuación de Schrödinger independiente del tiempo (TISE)** para un **pozo infinito** usando el método de Jacobi

El código está escrito en **C++** y modularizado en varios archivos `.cpp` y `.h`. Todas las salidas se guardan en la carpeta `resultados/` organizada por simulación.



## 1. Teoría

### 1.1 Paquete Gaussiano Libre

Un paquete gaussiano se define como:

\[
\psi(x,0) = \frac{1}{(2\pi\sigma^2)^{1/4}} \exp\Big[-\frac{(x-x_0)^2}{4\sigma^2} + i k x \Big]
\]

- \(x_0\) = posición inicial  
- \(\sigma\) = ancho del paquete  
- \(k\) = número de onda  

La evolución temporal de este paquete puede calcularse **analíticamente** o mediante propagación **numérica**.



### 1.2 Ecuación de Schrödinger dependiente del tiempo (TDSE)

\[
i \hbar \frac{\partial \psi(x,t)}{\partial t} = -\frac{\hbar^2}{2m} \frac{\partial^2 \psi(x,t)}{\partial x^2} + V(x) \psi(x,t)
\]

- Se usa el **método Crank-Nicolson** (implícito, estable)  
- Discretización:

\[
\left( I + \frac{i \Delta t}{2\hbar} H \right) \psi^{n+1} = \left( I - \frac{i \Delta t}{2\hbar} H \right) \psi^n
\]

- Se resuelve iterativamente en cada paso de tiempo usando **Gauss-Seidel**.


### 1.3 Ecuación de Schrödinger independiente del tiempo (TISE)

Para un pozo infinito:

\[
-\frac{\hbar^2}{2m} \frac{d^2 \psi_n(x)}{dx^2} = E_n \psi_n(x)
\]

- Discretización usando **diferencias finitas**  
- Construcción de la **matriz Hamiltoniana tridiagonal**  
- Cálculo de autovalores y autovectores mediante **método de Jacobi**  
- Normalización de los primeros N autovectores y guardado en archivos.



## 2. Estructura del proyecto


- **include/** → headers de las simulaciones  
- **src/** → implementaciones en C++  
- **main.cpp** → ejecuta las tres simulaciones de forma secuencial  
- **resultados/** → contiene los archivos de salida



## 3. Funciones principales

| Función | Archivo | Descripción |
|---------|---------|-------------|
| `run_wavepacket(...)` | wavepacket.cpp | Inicializa y evoluciona un paquete gaussiano, guarda resultados en `wave_*.dat` |
| `run_TDSE(...)` | TDSE.cpp | Resuelve la TDSE mediante Crank-Nicolson, guarda `wave_*.dat` |
| `create_Hamiltonian(...)` | TISE.cpp | Construye la matriz Hamiltoniana para pozo infinito |
| `jacobi_eigenvalues(...)` | TISE.cpp | Calcula autovalores y autovectores de la matriz Hamiltoniana |
| `normalize_and_save_wavefunctions(...)` | TISE.cpp | Normaliza y guarda las primeras N funciones de onda en un archivo |



## 4. Salidas de archivos

- **Wavepacket** → `resultados/wavepacket/wave_*.dat`  
- **TDSE** → `resultados/TDSE/wave_*.dat`  
- **TISE** → `resultados/TISE/wavefunctions.dat` + impresión de los primeros 5 autovalores en consola  

Cada archivo contiene la posición \(x\) y \(|\psi(x)|\).


## 5. Compilación y ejecución

```bash
# Compilar todo
make

# Ejecutar simulación completa
./quantum_sim.out

# Limpiar archivos generados
make clean
