# Solucionador de la Ecuación de Poisson en 3D

## 📋 Descripción del Problema

La **ecuación de Poisson** es fundamental en electrostática, mecánica de fluidos y física computacional. Se necesitaba un solver numérico eficiente para resolver:

\[
\nabla^2 \phi = -\rho
\]

**Aplicaciones directas:**
- Diseño de capacitores y dispositivos electrónicos
- Modelado de plasmas en reactores de fusión nuclear
- Simulación de semiconductores y uniones p-n
- Estudio de nubes de plasma interestelar

## 🧮 Modelo Físico

### **Formulación Matemática**
- **Ecuación:** \(\nabla^2 \phi = -\rho\) (formato físico)
- **Dominio:** Cubo 3D \([0,1] \times [0,1] \times [0,1]\)
- **Condiciones de frontera:** \(\phi = 0\) en todas las caras (Dirichlet)
- **Densidad de carga:** \(\rho = -1.0\) constante en todo el volumen

### **Justificación del Modelo**
- **Geometría cartesiana:** Más simple para discretización inicial
- **ρ constante:** Caso analíticamente soluble para validación
- **Condiciones Dirichlet:** Físicamente relevantes (paredes conectadas a tierra)

## 🏗️ Estructura del Código

### **Archivos Principales**

poisson_solver/

├── include/

│ └── Poisson3D.h // Definiciones de clases

├── src/

│ └── Poisson3D.cpp // Implementación de métodos

└── main.cpp // Programa principal
|
└──graficas.ipynb // Graficación


### **Clases Implementadas**

```cpp
// 1. Grid3D: Malla computacional 3D
class Grid3D {
    double dx, dy, dz;
    std::vector<std::vector<std::vector<double>>> XYZ;
};

// 2. PoissonSolver3D: Solucionador principal  
class PoissonSolver3D {
    std::vector<std::vector<std::vector<double>>> phi; // Solución
    std::vector<std::vector<std::vector<double>>> rho; // Fuente
    void solve();        // Método iterativo
    void writeVTK();     // Exportación de resultados
};
```

### 🚀 Instrucciones de Compilación y Ejecución

# Opción 1: Compilación directa
g++ -std=c++11 -Iinclude src/Poisson3D.cpp main.cpp -o poisson3d

# Opción 2: Compilación separada
g++ -std=c++11 -Iinclude -c src/Poisson3D.cpp -o Poisson3D.o
g++ -std=c++11 -Iinclude -c main.cpp -o main.o
g++ Poisson3D.o main.o -o poisson3d

### Ejecución

./main_cylindrical.exe

### Parámetros Configurables (en main_cylindrical.cpp)

int nx = 50, ny = 50, nz = 50;       // Resolución de malla
double rho_value = -1.0;             // Densidad de carga
int max_iter = 1000;                 // Máximo de iteraciones
double tolerance = 1e-6;             // Tolerancia de convergencia

### 📊 Resultados y Salidas

Por consola: 
=== SOLUCIONADOR POISSON 3D ===
Dimensión de malla: 50x50x50
Densidad de carga: ρ = -1.0
Iteraciones realizadas: 347
Error final: 8.45e-07
Tiempo de ejecución: 2.14 segundos
Archivo de salida: poisson3d.vtk

# Archivos Generados

poisson3d.vtk: Datos en formato VTK para visualización

campos_XXX.txt: Snapshots temporales (opcional)


### Resultados Numéricos Esperados

=== VALORES CARACTERÍSTICOS ===
Potencial en centro (0.5,0.5,0.5): φ ≈ 0.0625
Potencial en borde (0.0,0.5,0.5): φ = 0.0000
Potencial en esquina (0.0,0.0,0.0): φ = 0.0000
Gradiente máximo: |∇φ| ≈ 0.125