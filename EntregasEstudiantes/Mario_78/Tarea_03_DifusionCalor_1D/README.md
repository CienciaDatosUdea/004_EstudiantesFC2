---
title: Untitled

---

## Proyecto: Simulación de la difusión de calor en 1D

Este proyecto implementa una simulación numérica de la **ecuación de difusión del calor** en una barra unidimensional, utilizando el **método de diferencias finitas explícito** en C++.  

La estructura modular del proyecto permite:
- Definir la geometría del problema (`Geometria`).
- Establecer condiciones iniciales y de frontera (`Condiciones`).
- Evolucionar la temperatura en el tiempo.
- Guardar resultados en archivos de salida para su posterior análisis y graficación.

---

## 📂 Estructura del proyecto

```
Tarea_02_DifusionCalor_1D/
│── datos/                  # Carpeta donde se guardan resultados numéricos
│   └── resultados.txt
│
│── graph/                  # Carpeta para notebooks de graficación
│   └── graficar_difusion.ipynb
│
│── include/                # Archivos de cabecera (.h)
│   ├── difusion_model.h
│   └── flow.h
│
│── src/                    # Implementación de las clases
│   ├── difusion_model.cpp
│   └── flow.cpp
│
│── test/                   # Pruebas unitarias
│   └── test_geometria.cpp
│
│── main.cpp                # Programa principal
│── Makefile                # Script de compilación
│── README.md               # Documentación
```

---

## Requisitos

- Compilador C++ con soporte para **C++17** (g++, clang o MSVC).
- Sistema operativo: Linux, macOS o Windows (con MinGW o similar).
- Jupyter Notebook para graficar resultados (`graph/graficar_difusion.ipynb`).

---

## Compilación y ejecución

El proyecto incluye un **Makefile** para simplificar la compilación.

### Compilar el programa principal
```bash
make
```

### Ejecutar la simulación
```bash
./difusion_model.out
```

### Compilar y ejecutar la prueba de geometría
```bash
make test_geometria
./test_geometria.out
```

### Limpiar archivos generados
```bash
make clean
```

---

## Ejemplo de salida

Ejecución en terminal (`./difusion_model.out`):

```
Paso 0:
x	Temperatura
0	0
0.0204082	0
0.0408163	0
0.0612245	0
0.0816327	0
0.102041	0
0.122449	0
0.142857	0
0.163265	0
0.183673	0
0.204082	0
0.22449	0
0.244898	0
0.265306	0
0.285714	0
0.306122	0
0.326531	0
0.346939	0
0.367347	0
0.387755	0
0.408163	0
0.428571	0
0.44898	0
0.469388	0
0.489796	0
0.510204	100
0.530612	0
0.55102	0
0.571429	0
0.591837	0
0.612245	0
0.632653	0
0.653061	0
0.673469	0
0.693878	0
0.714286	0
0.734694	0
0.755102	0
0.77551	0
0.795918	0
0.816327	0
0.836735	0
0.857143	0
0.877551	0
0.897959	0
0.918367	0
0.938776	0
0.959184	0
0.979592	0
1	0
-------------------------
Paso 1:
x	Temperatura
0	0
...
```

Los resultados también se guardan automáticamente en `datos/resultados.txt`.

---

## Marco Teórico

La **ecuación de difusión del calor** describe cómo la temperatura evoluciona en un medio en función del tiempo y el espacio. En una dimensión (1D), se expresa como:

$$
\frac{\partial T(x,t)}{\partial t} = \frac{k}{c \ \rho} \frac{\partial^2 T(x,t)}{\partial x^2}
$$

donde:
- $T(x,t)$: temperatura en la posición $x$ y tiempo $t$,
- $k$: conductividad térmica,
- $c$: calor específico,
$\rho$: densidad del material.

---

### Método de diferencias finitas

El método de diferencias finitas aproxima derivadas mediante diferencias entre valores discretos en una malla espacial y temporal.

1. **Discretización espacial y temporal**  
   - Dividimos la barra en \(n\) puntos igualmente espaciados con paso $\Delta x$.  
   - Avanzamos en el tiempo en pasos de tamaño $\Delta t$.  

2. **Aproximaciones**  
   - Derivada temporal:  
   $$
   \frac{\partial T}{\partial t} \approx \frac{T_i^{\,t+1} - T_i^{\,t}}{\Delta t}
   $$

   - Derivada espacial segunda:  
   $$
   \frac{\partial^2 T}{\partial x^2} \approx \frac{T_{i+1}^{\,t} - 2T_i^{\,t} + T_{i-1}^{\,t}}{(\Delta x)^2}
   $$

3. **Esquema explícito**  
   Sustituyendo en la ecuación de difusión:  

   $$
   T_i^{\,t+1} = T_i^{\,t} +  \frac{k}{c \ \rho} \frac{\Delta t}{(\Delta x)^2} \left( T_{i+1}^{\,t} - 2T_i^{\,t} + T_{i-1}^{\,t} \right)
   $$

   Definimos:  
   $$
   \alpha = \frac{k}{c\rho} \frac{\Delta t}{(\Delta x)^2}
   $$

   Entonces:  
   $$
   T_i^{\,t+1} = T_i^{\,t} + \alpha \left( T_{i+1}^{\,t} - 2T_i^{\,t} + T_{i-1}^{\,t} \right)
   $$

**Nota:**
En el código c++ se utiliza  la variable $u$  en lugar de $T$; por lo tanto:  
    $$ 
    u_i^{\,t+1} = u_i^{\,t} + \alpha \left( u_{i+1}^{\,t} - 2u_i^{\,t} + u_{i-1}^{\,t} \right)
    $$

---

### Condiciones iniciales y de frontera

- **Condición inicial**: se puede imponer un perfil de temperatura, por ejemplo, un **pico de calor en el centro** de la barra: u(L/2,0)= 100 (en °C)  
- **Condiciones de frontera**: los extremos de la barra se mantienen a temperatura fija, típicamente u(0,t) = u(L,t) = 0.  

---

### Estabilidad del método
 
Para que el esquema explícito sea estable, el parámetro $\alpha$ debe cumplir:

$$
\alpha \leq \frac{1}{2}
$$

Esto limita la elección de $\Delta t$ en función de $\Delta x$ y $\alpha$.

---

### Interpretación física

El método permite simular cómo el calor se difunde con el tiempo:
- Al inicio, un punto caliente concentra la energía.  
- Con el tiempo, la temperatura se distribuye hacia los lados.  
- Finalmente, el sistema tiende a un estado de equilibrio térmico uniforme.  

---

##  Visualización

Los resultados pueden graficarse con el notebook en **`graph/graficar_difusion.ipynb`**, que lee los datos de `datos/resultados.txt` y genera gráficos de la evolución de la temperatura.

---

##  Autor

- Proyecto desarrollado en C++ para la asignatura **Física Computacional 2**.  
- Ejemplo adaptado y documentado por **Jader Enrique Mario Mendoza**.

---


