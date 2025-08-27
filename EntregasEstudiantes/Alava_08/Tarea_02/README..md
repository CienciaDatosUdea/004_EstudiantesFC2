# **solucionador numérico de la ecuación de difusión**

Este proyecto implementa un **solucionador numérico de la ecuación de difusión** en 1D utilizando el **método de diferencias finitas explícito (FDM)**.  

La ecuación de difusión modela cómo una cantidad (por ejemplo, calor o concentración) se dispersa en el espacio con el tiempo:

\[
\frac{\partial u}{\partial t} = D \frac{\partial^2 u}{\partial x^2}
\]

donde:
- \( u(x,t) \) es la cantidad a difundir (temperatura, densidad, etc.),
- \( D \) es el coeficiente de difusión,
- \( x \) la posición,
- \( t \) el tiempo.

---

##  Características
- Discretización en **espacio y tiempo** mediante diferencias finitas.
- Condiciones de frontera y condición inicial personalizables.
- Salida en consola con los valores de la simulación.
- Código modular (separado en `.h`, `.cpp` y `main.cpp`).

---

---

### Compilar el proyecto

Para compilar el código y generar el archivo ejecutable, ubicate en la carpeta raiz del  y ejecuta el comando:

```bash
make
```

Este comando compila `diffusion_solver` y `main.cpp` y crea un ejecutable llamado `difussion_solver.out`.

### Compilacion y ejecucion

Para compilar el proyecto y ejecutar el programa en un solo paso, usa la regla `run`:

```bash
make run
```

Este comando se encarga de que el ejecutable esté actualizado y luego lo ejecuta, mostrando el resultado de las operaciones en la terminal.

### Limpiar archivos generados

Si deseas eliminar el ejecutable y los archivos objeto (`.o`) generados durante la compilación, usa la regla `clean`:

```bash
make clean
```


## 📂 Estructura del proyecto
