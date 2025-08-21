# Propagación de ondas electromagnéticas con FDTD

El objetivo de este proyecto es estudiar la propagación de una onda EM polarizada linealmente y que se propaga en dirección `z`, resolviendo las ecuaciones diferenciales parciales acopladas:

$$
\dfrac{\partial E_x}{\partial t} = -\dfrac{1}{\epsilon_0}\dfrac{\partial H_y}{\partial z}
$$

$$
\dfrac{\partial H_y}{\partial t} = -\dfrac{1}{\mu_0}\dfrac{\partial E_x}{\partial z}
$$


## Clases y funciones

### `Grid(z_max, t_max, beta)`
Construye la grilla espacio-temporal usada para resolver las ecuaciones de Maxwell en 1D.  

- Divide el eje espacial $ z $ en `nz = 200` puntos, con espaciamiento
  
$$
  dz = \frac{z_{\text{max}}}{n_z - 1}.
$$
  
- Calcula el paso temporal
  
$$
  dt = dz \cdot \beta, \quad n_t = \frac{t_{\text{max}}}{dt} + 1.
$$

  con

$$
\beta=\dfrac{cdt}{ dz}
$$

- Genera la malla `ZT[nt][nz][2]` que guarda en cada punto las coordenadas $(z,t)$.
- Verifica la condición de estabilidad: si $dz > 104, lanza una advertencia.

---

### `CampoEM(G)`
Representa los campos eléctrico $E$ y magnético $H$ definidos sobre la grilla reducida.  

- Construye las matrices `E[nt/2][nz/2]` y `H[nt/2][nz/2]` para almacenar la evolución.  

**Métodos:**
- `applyInitialCondition(f)`: impone la condición inicial a partir de una función $f(z)$.
  - Eléctrico:

$$
E[0][i] = f(z_{2i}).
$$
  - Magnético:

$$
H[0][i] = f(z_{2i+1}).
$$

---

### `FieldWriter(filename)`
Se encarga de escribir los resultados en un archivo de salida.  

- Abre `filename` en formato de punto flotante con 6 decimales.  

**Métodos:**
- `writeInitial(G, field)`: escribe el estado inicial de los campos $E$ y $H$.
- `writeField(G, field)`: escribe toda la evolución temporal de los campos paso a paso.

---

### `Evolution(field)`
Resuelve la evolución temporal de los campos mediante el método FDTD.  

**Métodos:**
- `run(periodic)`:
  - Actualiza los campos en cada paso de tiempo con:

$$
E^n_j = E^{n-1}_j + \beta \big( H^{n-1}_{j-1} - H^{n-1}_{j+1} \big),
$$

$$
H^n_j = H^{n-1}_j + \beta \big( E^{n-1}_{j-1} - E^{n-1}_{j+1} \big).
$$

  - Si `periodic = true`, aplica condiciones de frontera periódicas.
  - Si `periodic = false`, aplica condiciones absorbentes (campos nulos en los bordes).

---

## Compilación y ejecución

El proyecto cuenta con un `Makefile`, de modo que basta con ejecutar

```make```

en la terminal para compilar todos los archivos necesarios.

Para ejecutar directamente el archivo principal, hágalo de esta manera:

```
./obj/main.out [beta] [zmax] [tmax] [periodic] [name]
```

donde los parámetros son:
* `beta`: parámetro de estabilidad de Courant.
* `zmax`: valor máximo de $z$.
* `tmax`: valor máximo de $t$.
* `periodic`: indica si usará condiciones periódicas o de Dirichlet.
* `name`: nombre del archivo que contendrá los datos de la evolución temporal.

Como resultado, obtendrá dos archivos en formato .txt: uno con los campos de la condición inicial, otro con la evolución temporal de estos.

También podrá hacer uso de `graficas.ipynb`, que ejecuta automáticamente el programa en `C++` y grafica y anima la propagación de las ondas, además de discutir algunos resultados.
