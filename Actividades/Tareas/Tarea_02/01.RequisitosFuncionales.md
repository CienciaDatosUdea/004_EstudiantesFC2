
✅ Requisitos Funcionales – Solver de Difusión 1D

Este documento describe los requisitos funcionales del software para simular la ecuación de calor en una dimensión utilizando el método explícito FTCS.

---

#  RF1 – Definición del dominio espacial

El sistema debe permitir definir el dominio espacial 1D mediante los siguientes parámetros de entrada:

- Número de nodos: N
- Límite izquierdo del dominio: xmin
- Límite derecho del dominio: xmax

A partir de estos valores, debe calcular automáticamente el espaciamiento uniforme:

dx = (xmax - xmin) / (N - 1)

Y generar un vector de posiciones espaciales x[i] con longitud N.

---

#  RF2 – Aplicación de la condición inicial

El sistema debe aplicar una condición inicial sobre el perfil de temperatura u(x, 0), utilizando por defecto una distribución tipo Gaussiana centrada en el dominio:

u(x, 0) = exp(-α (x - x₀)²)

Esta condición debe almacenarse como el estado inicial del sistema.

---

#  RF3 – Condiciones de frontera

El sistema debe aplicar condiciones de frontera en los extremos del dominio espacial:

- Dirichlet (por defecto): temperatura fija en los extremos:
  u[0] = TL
  u[N-1] = TR

- (Opcional en futuras versiones) Neumann: derivada fija en el borde (flujo constante o nulo):
  (u[1] - u[0]) / dx = q_left

---

#  RF4 – Evolución temporal con el método FTCS

El sistema debe resolver la ecuación de calor usando el método explícito FTCS, calculando la evolución temporal mediante:

u_i^{n+1} = u_i^n + α * (u_{i+1}^n - 2 * u_i^n + u_{i-1}^n)

donde:

α = D * dt / dx²

Debe realizar Nsteps pasos temporales definidos por:

Nsteps = int(t_max / dt)

---

#  RF5 – Aplicación de condiciones de frontera en cada iteración

Durante cada paso de tiempo, el sistema debe re-aplicar las condiciones de frontera para mantener la coherencia física del modelo durante la evolución temporal.

---

#  RF6 – Exportación de resultados

El sistema debe guardar la solución final en un archivo de texto llamado solucion_final.txt, con formato de dos columnas:

x_0    u_0
x_1    u_1
...    ...
x_N-1  u_N-1

Esto permitirá la visualización o análisis posterior en Python, Gnuplot, etc.

---

#  RF7 – Configuración de parámetros desde el programa principal

El archivo main.cpp debe permitir configurar todos los parámetros clave del sistema:

- N, xmin, xmax
- D (coeficiente de difusión)
- dt (paso de tiempo)
- t_max (tiempo máximo de simulación)

---

#  RF8 – Modularidad del código

El software debe estar organizado en componentes modulares, separados en diferentes archivos:

- Geometria: construcción del dominio espacial
- Condiciones: condición inicial y de frontera
- DiffusionSolver: lógica de resolución FTCS
- main.cpp: punto de entrada y control
- difusion_model.h: interfaz pública (headers)

---

#  RF9 – Gestión automática de memoria

El sistema debe utilizar estructuras como std::vector para manejar dinámicamente la memoria de los vectores de temperatura y coordenadas espaciales. No se deben usar new ni delete manualmente.

---

# RF10 – Verificación de estabilidad

El sistema debe verificar que el parámetro α cumple la condición de estabilidad del método FTCS:

α = D * dt / dx² ≤ 0.5

Si esta condición no se cumple, el programa debe emitir una advertencia y permitir que el usuario corrija los valores de dt, dx o D.
