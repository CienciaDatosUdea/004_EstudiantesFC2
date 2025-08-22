# Examen Final FC2: Diferencias Finitas - FDTD

**Universidad de Antioquia**  
**Facultad de Ciencias Exactas y Naturales**  
**Instituto de Física**

## Descripción

Este proyecto implementa el método FDTD (Finite-Difference Time-Domain) para simular la propagación de ondas electromagnéticas en una dimensión. El código resuelve las ecuaciones de Maxwell discretizadas usando diferencias finitas centradas con la malla escalonada de Yee.

## Estructura del Proyecto

```
fdtd_project/
├── include/
│   └── fdtd.cpp            # Implementación de métodos FDTD
├── src/
│   ├── fdtd.h              # Definiciones de la clase FDTD
├──main.cpp                 # Programa principal
├── python/
│   └── sim_fdtd.py         # Visualización con Python (opcional)
├── docs/
│   └── README.md           
└── Makefile                # Sistema de compilación
```

## Compilación

### Requisitos
- Compilador C++17 compatible (g++, clang++)
- Make

### Instrucciones de Compilación y ejecución

```bash
# Compilar el proyecto
make
```
y luego
```bash
# Compilar el proyecto
./fdtd_simulation.out
```



## Problemas

El programa ejecutará automáticamente:
1. **Problema 1.1**: Simulación de onda sinusoidal con condiciones periódicas
2. **Problema 1.2a**: Comparación de condiciones de frontera (periódicas vs iniciales)
3. **Problema 1.2b**: Análisis de estabilidad numérica para diferentes valores de β

### 1.1 Simulación de Onda Sinusoidal

**Condiciones iniciales:**
```cpp
Ex(z,t=0) = 0.1 * sin(2πz/100)
Hy(z,t=0) = 0.1 * sin(2πz/100)
```

**Parámetros:**
- Puntos espaciales: nx = 200
- Paso espacial: Δz = 1.0
- Parámetro β = 0.4 (estable)

### 1.2a Condiciones de Frontera

**Periódicas:**
```cpp
Ex[0] = Ex[0] + β(Hy[nx-2] - Hy[1])
Ex[nx-1] = Ex[nx-1] + β(Hy[nx-2] - Hy[1])
```

**Cero en fronteras:**
```cpp
Ex[0] = Ex[nx-1] = 0
Hy[0] = Hy[nx-1] = 0
```

### 1.2b Análisis de Estabilidad

El programa prueba valores de β = {0.3, 0.5, 0.6, 0.8} para verificar:
- β ≤ 0.5: Simulación estable
- β > 0.5: Crecimiento exponencial (inestabilidad)

## Archivos de Salida

El programa genera varios archivos de datos:
- `initial_conditions.dat`: Condiciones iniciales
- `final_periodic.dat`: Resultados con condiciones periódicas
- `final_zero_boundary.dat`: Resultados con condiciones de frontera

## Referencias

1. Rubin H. Landau, Manuel J. P ́aez y Cristian C. Bordeianu. Computational Physics: Problem
Solving with Python, 3a edici ́on. Wiley-VCH, 2015
