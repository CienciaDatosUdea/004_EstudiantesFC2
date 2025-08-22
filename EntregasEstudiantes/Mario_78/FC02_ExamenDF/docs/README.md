---
title: FC02_EXAMENDF – Simulación FDTD 1D de Ondas Electromagnéticas

---

# FC02_EXAMENDF – Simulación FDTD 1D de Ondas Electromagnéticas

Este proyecto implementa el método **FDTD (Finite-Difference Time-Domain)** en **C++** para estudiar la propagación de ondas electromagnéticas en 1D.  
Incluye herramientas en **Python/Jupyter** para analizar y visualizar los resultados.

---

## 📂 Estructura del proyecto

```
FC02_EXAMENDF/
├── docs/
│   ├── README.md                # Documentación del proyecto
│   └── datos.txt                # Resultados de la simulación (salida)
├── include/
│   └── fdtd.h                   # Definición de la clase Campos
├── src/
│   └── fdtd.cpp                 # Implementación de la simulación FDTD
├── python/
│   ├── AnalisisRespuestas.ipynb # Notebook para análisis y visualización
│   └── sim_fdtd.py              # Script de graficación y animación
├── main.cpp                     # Programa principal
├── Makefile                     # Script de compilación
```

---

##  Descripción

- Se resuelven las **ecuaciones de Maxwell en 1D** mediante diferencias finitas.  
- Se calculan los campos:
  - `Ex` (eléctrico)
  - `Hy` (magnético)  
- Los resultados se guardan en `docs/datos.txt` en el formato:

```
# t    k    Ex    Hy
```

donde:
- `t` → tiempo
- `k` → posición espacial
- `Ex` → campo eléctrico
- `Hy` → campo magnético

---

## ▶️ Compilación y ejecución

Con **Makefile**:

```bash
make
```

Esto genera el ejecutable `fdtd.out`.

Ejecutar la simulación:

```bash
./fdtd.out
```

Los datos se guardarán en `docs/datos.txt`.

Para limpiar archivos compilados y resultados:

```bash
make clean
```

---

## 📊 Visualización en Python

### En Jupyter Notebook
Abrir el archivo:

```bash
jupyter notebook python/AnalisisRespuestas.ipynb
```

### En script Python
Ejecutar directamente:

```bash
python python/sim_fdtd.py
```

Este código permite graficar:
- Evolución temporal en un nodo fijo (`k` constante).  
- Evolución espacial en un tiempo fijo (`t` constante).  
- Animaciones GIF de la propagación de la onda.

---

## 🔄 Flujo del proyecto

```text
+------------------+       +--------------------+       +-------------------+
|    C++ (FDTD)    |  -->  |   docs/datos.txt   |  -->  |  Python/Jupyter   |
|  (main + fdtd)   |       | (resultados crudos)|       | (gráficos + GIFs) |
+------------------+       +--------------------+       +-------------------+
```

---

## Experimentos sugeridos

1. **Sin condiciones de frontera explícitas**  
   - Ondas viajan libremente (condiciones periódicas).  

2. **Con condiciones de frontera PEC (E = H = 0 en los bordes)**  
   - Aparecen ondas estacionarias.  

3. Variar:
   - Longitud de onda (`lambda`)
   - Número de nodos (`xmax`)
   - Pasos de simulación (`nsteps`)  
   para observar diferentes regímenes.

---

## ✨ Requisitos

- **C++17** o superior
- **Python 3.x** con:
  - `numpy`
  - `matplotlib`
  - `jupyter`

---

##  Autor

**Jader Enrique Mario Mendoza**

---
