# Simulación del Modelo de Ising 2D y Análisis con Machine Learning

Este proyecto implementa simulaciones del **modelo de Ising bidimensional** usando el algoritmo de **Metropolis-Hastings** y aplica técnicas de **Machine Learning** para analizar distribuciones de energía y magnetización, así como la transición de fase.

---

## 📂 Estructura del Proyecto

- **`include/Canonical.h`**  
  Contiene funciones para el cálculo de:
  - Función de partición canónica.
  - Probabilidad de un microestado dado una energía y temperatura.

- **`include/Samples_Gen.h`**  
  Define las clases principales:
  - `microstate`: representa un microestado del sistema (espines, energía, magnetización).  
  - `Samples`: genera muestras Monte Carlo a diferentes temperaturas.

- **`src/Samples_Gen.cpp`**  
  Implementación de:
  - Inicialización de microestados.  
  - Algoritmo de Metropolis con condiciones periódicas de frontera.  
  - Generación y almacenamiento de datasets con configuraciones, energías y magnetizaciones.

- **`ML.ipynb`**  
  Notebook de Python para entrenar y evaluar modelos de **aprendizaje automático** que predicen fases del sistema (ordenado/desordenado) a partir de configuraciones de espines.

- **`Distribuciones.ipynb`**  
  Notebook para el análisis estadístico de las distribuciones de energía y magnetización a diferentes temperaturas. Incluye histogramas y comparaciones con resultados teóricos.

- **`ising_magnetization_distributions_L10.png`**  
  Ejemplo de distribución de magnetización para una red de tamaño `L=10`.

---

## ⚙️ Dependencias

### C++
- Compilador compatible con C++11 o superior.  
- `g++` o `clang++`   

### Python
- Python 3.9+  
- Librerías: `numpy`, `matplotlib`, `pandas`, `scikit-learn`, `seaborn`, `torch` 

---

