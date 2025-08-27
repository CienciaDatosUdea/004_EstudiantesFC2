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
- **Dominio:** Cilindro 3D \([0,1] \times [0,2]\)
- **Condiciones de frontera:** \(\phi = 0\) en todas las bordes r=1 y z=0 y z=2 (Dirichlet)
- **Densidad de carga:** \(\rho = -1.0\) constante en todo el volumen

### **Justificación del Modelo**
- **Geometría cartesiana:** Más simple para discretización inicial
- **ρ constante:** Caso analíticamente soluble para validación
- **Condiciones Dirichlet:** Físicamente relevantes (paredes conectadas a tierra)

## 🏗️ Estructura del Código

### **Archivos Principales**

ProyectoFinalCilindricas/

├── include/

│ └── PoissonCylindrical.h // Definiciones de clases

├── src/

│ └── PoissonCylindrical.cpp // Implementación de métodos

└── main_cylindrical.cpp // Programa principal
|
└──graficacion.ipynb // Graficación


### **Clases Implementadas**

```cpp
// 1. Grid3D: Malla computacional 3D
class CylindricalGrid {
public:
    CylindricalGrid(double r_max, double z_max, int nr, int nz);
    
    double dr, dz;
    double r_max, z_max;
    int nr, nz;
};

// 2. PoissonSolver3D: Solucionador principal  
class PoissonSolverCylindrical {
public:
    PoissonSolverCylindrical(CylindricalGrid &grid, double rho, int max_iter, double tol);
    
    void solve();
    void setBoundaryConditions();
    void writeVTK(const std::string &filename);

    CylindricalGrid &grid;
    std::vector<std::vector<double>> phi;  // phi[r][z]
    std::vector<std::vector<double>> rho;  // rho[r][z]

private:
    double tolerance;
    int max_iter;
};
```

### 🚀 Instrucciones de Compilación y Ejecución

# Opción 1: Compilación directa
g++ -std=c++11 -Iinclude src/PoissonCylindrical.cpp main_cylindrical.cpp -o poisson3d

# Opción 2: Compilación separada
g++ -std=c++11 -Iinclude -c src/PoissonCylindrical.cpp -o PoissonCylindrical.o
g++ -std=c++11 -Iinclude -c main_cylindrical.cpp -o main_cylindrical.o
g++ PoissonCylindrical.o main_cylindrical.o -o poisson3d

### Ejecución

./main_cylindrical.exe


### 📊 Resultados y Salidas

Por consola: 
=== SOLUCIONADOR POISSON 3D ===
Dimensión de malla: 50x100
Densidad de carga: ρ = -1.0
Iteraciones realizadas: 347
Error final: 8.45e-07
Tiempo de ejecución: 2.14 segundos
Archivo de salida: poisson_cylinder.vtk

# Archivos Generados

poisson_cylinder.vtk: Datos en formato VTK para visualización

