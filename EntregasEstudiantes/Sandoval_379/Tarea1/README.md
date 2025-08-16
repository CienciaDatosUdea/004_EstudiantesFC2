# Simulación de partículas en una circunferencia

Este programa en C++ simula un sistema de **N partículas distribuidas aleatoriamente sobre una circunferencia**.  
Cada partícula recibe una pequeña perturbación de posición y se le asigna un vector de fuerza aleatorio.  
El sistema calcula la **distancia máxima** entre partículas y la **magnitud de la fuerza total resultante**.

---

## 📌 Estructuras y utilidades

### `struct Particle`
Estructura que representa una partícula con:
- `x, y`: posición en 2D.  
- `fx, fy`: componentes de fuerza.  

Es simple y flexible: se le pueden añadir más atributos (masa, velocidad, carga) sin modificar la lógica principal.

---

### `randomAngle()`
Genera un ángulo uniforme en el rango `[0, 2π)`.  
Centraliza la lógica de muestreo angular y puede adaptarse fácilmente a otras distribuciones si se necesita.

---

### `uniform(a, b)`
Devuelve un valor aleatorio en el intervalo `[a, b]`.  
Al abstraer esta función, se puede cambiar la forma de ruido (uniforme, gaussiano, etc.) sin alterar el resto del código.

---

### `initParticles(arr, n, radius, delta)`
Inicializa las partículas:
- Coloca cada partícula sobre una circunferencia de radio `radius`.  
- Aplica perturbaciones `(dx, dy)` uniformes en `[-delta, delta]`.  

Combina inicialización y ruido en un solo paso, lo que hace el código más directo y fácil de usar.

---

### `setRandomForces(arr, n)`
Asigna a cada partícula fuerzas `(fx, fy)` en el rango `[0,1]`.  
Está desacoplada de la inicialización, lo que permite cambiar el modelo de fuerzas (uniformes, dependientes de la posición, campos externos) sin tocar el resto del programa.

---

### `MaxDistance(arr, n)`
Calcula la distancia máxima entre cualquier par de partículas.  
Es útil para verificar el efecto de la perturbación y evaluar el “tamaño” del sistema.  
Se puede reemplazar por algoritmos más eficientes si `n` es muy grande.

---

### `F_Total(arr, n)`
Suma todas las fuerzas y devuelve la magnitud del vector resultante:  

\[
F_\text{total} = \sqrt{\left(\sum_i f_{x,i}\right)^2 + \left(\sum_i f_{y,i}\right)^2}
\]

Sirve como una métrica global del sistema. Puede extenderse para devolver también el vector total o estadísticas adicionales.

---

### `main()`
Controla el flujo principal:
1. Inicializa el generador aleatorio.  
2. Coloca y perturba partículas en la circunferencia.  
3. Asigna fuerzas aleatorias.  
4. Calcula la distancia máxima y la fuerza total.  
5. Muestra los resultados por consola.  

Mantener `main` sencillo hace que el programa sea fácil de extender (entradas por línea de comandos, múltiples simulaciones, guardado de datos, etc.).

---

## ⚙️ Compilación
Compilar con g++:
```bash
g++ -std=c++17 -Wall particulas.cpp -o particulas.out
