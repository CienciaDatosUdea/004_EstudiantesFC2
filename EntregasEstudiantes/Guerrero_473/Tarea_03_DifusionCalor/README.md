# Simulación de la Ecuación de Calor 1D

## Descripción del Proyecto

Este proyecto implementa una simulación numérica de la **ecuación de
calor en una dimensión (1D)** utilizando el **método de diferencias
finitas**. La ecuación de calor describe cómo se distribuye la
temperatura en un material a lo largo del tiempo.

------------------------------------------------------------------------

## Teoría Matemática

### Ecuación de Calor 1D (forma discretizada explícita)

La ecuación fundamental que gobierna la conducción de calor (esquema
FTCS) es:

$$
\frac{T_i^{n+1} - T_i^n}{\Delta t}
= \alpha \, \frac{T_{i+1}^n - 2T_i^n + T_{i-1}^n}{\Delta x^2}
$$

**Donde:** - ( T_i\^n ): temperatura en la posición (i) y tiempo (n) - (
`\Delta `{=tex}t ): paso temporal - ( `\Delta `{=tex}x ): paso
espacial - ( `\alpha `{=tex}= `\tfrac{k}{\rho c_p}`{=tex} ): difusividad
térmica

También, en forma continua:

-   (T): temperatura
-   (t): tiempo
-   (x): posición espacial
-   (`\alpha`{=tex}): difusividad térmica

------------------------------------------------------------------------

### Aproximación por Diferencias Finitas

**Derivada temporal (adelante en el tiempo):**

$$
\frac{\partial T}{\partial t}
\approx 
\frac{T_i^{n+1} - T_i^n}{\Delta t}
$$

**Derivada espacial (segunda derivada, esquema centrado de 2º orden):**

Partimos de las expansiones de Taylor alrededor de (x_i):

1)  ( u(x_i+`\Delta `{=tex}x) = u_i + `\Delta `{=tex}x,u'\_i +
    `\tfrac{\Delta x^2}{2}`{=tex},u''\_i +
    `\tfrac{\Delta x^3}{6}`{=tex},u'''\_i +
    `\tfrac{\Delta x^4}{24}`{=tex},u\^{(4)}\_i +
    `\mathcal{O}`{=tex}(`\Delta `{=tex}x\^5) )

2)  ( u(x_i-`\Delta `{=tex}x) = u_i - `\Delta `{=tex}x,u'\_i +
    `\tfrac{\Delta x^2}{2}`{=tex},u''\_i -
    `\tfrac{\Delta x^3}{6}`{=tex},u'''\_i +
    `\tfrac{\Delta x^4}{24}`{=tex},u\^{(4)}\_i +
    `\mathcal{O}`{=tex}(`\Delta `{=tex}x\^5) )

Sumando (1) y (2) se cancelan los términos impares:

( u\_{i+1} + u\_{i-1} = 2u_i + `\Delta `{=tex}x\^2,u''\_i +
`\tfrac{\Delta x^4}{12}`{=tex},u\^{(4)}\_i +
`\mathcal{O}`{=tex}(`\Delta `{=tex}x\^6) )

Despejamos (u''\_i):

( u''\_i = `\tfrac{u_{i+1} - 2u_i + u_{i-1}}{\Delta x^2}`{=tex} -
`\tfrac{\Delta x^2}{12}`{=tex},u\^{(4)}\_i +
`\mathcal{O}`{=tex}(`\Delta `{=tex}x\^4) )

Por tanto, la **aproximación centrada** de 2º orden es:

\[
`\boxed{\displaystyle u''(x_i) \;\approx\; \frac{u_{i+1} - 2u_i + u_{i-1}}{\Delta x^2}}`{=tex}
\]

------------------------------------------------------------------------

## Estructura del Proyecto

``` text
.
├── include/                 # Archivos de cabecera (.h)
│   └── DifusionCalor.h      # Definición de clases
├── src/                     # Archivos de implementación (.cpp)
│   └── DifusionCalor.cpp    # Implementación de métodos
├── main.cpp                 # Programa principal
├── python/                  # Visualización de resultados
│   └── visualizacion.ipynb  # Jupyter Notebook para gráficos
├── build/                   # Archivos objeto (generados)
├── bin/                     # Ejecutable (generado)
└── Makefile                 # Configuración de compilación
```

------------------------------------------------------------------------

## Compilación y Ejecución

**Compilar el proyecto:**

``` bash
make
```

**Ejecutar la simulación:**

``` bash
make run
```

**O directamente (el nombre puede variar según tu Makefile):**

``` bash
./bin/difusion_calor
```

**Limpiar archivos compilados:**

``` bash
make clean
```

------------------------------------------------------------------------

## Características Implementadas

**Condiciones iniciales disponibles:** - `UNIFORME`: temperatura
constante en todo el dominio - `ESCALÓN`: discontinuidad tipo escalón -
`GAUSSIANA`: distribución gaussiana de temperatura - `IMPULSO_CENTRAL`:
pico de temperatura en el centro

**Condiciones de frontera:** - `NULA`: temperatura fija en los bordes
(Dirichlet) - `PERIÓDICA`: condiciones periódicas - `AISLADA`: flujo de
calor cero en los bordes (Neumann)

------------------------------------------------------------------------

## Visualización de Resultados

Los resultados se guardan en archivos de texto y pueden visualizarse
usando el Jupyter Notebook en la carpeta `python/`:

``` bash
cd python
jupyter notebook visualizacion.ipynb
```

------------------------------------------------------------------------

## Parámetros de Simulación

En `main.cpp` puedes configurar:

-   `N`: número de puntos espaciales
-   `xmin`, `xmax`: límites del dominio
-   `alpha`: coeficiente de difusividad térmica
-   `dt`: paso temporal
-   `tiempo_max`: tiempo total de simulación
-   `intervalo`: intervalo para guardar resultados

------------------------------------------------------------------------

## Ejemplo de Uso

``` cpp
int main() {
    const int N = 50;
    const double xmin = 0.0, xmax = 1.0;
    const double alpha = 0.01, dt = 0.001;
    const double tiempo_max = 1.0;
    const double intervalo = 0.01;

    Geometria G(N, xmin, xmax);
    CondicionesIniciales CI(G, GAUSSIANA);
    CondicionesFrontera CF(G, NULA);

    Simulador simulador(CI, CF, alpha, dt);
    simulador.guardar_evolucion("resultados.txt", tiempo_max, intervalo);

    return 0;
}
```

------------------------------------------------------------------------

## Comandos Útiles

-   `make rebuild` --- limpia y recompila todo
-   `make debug` --- compila con información de depuración
-   `make clean` --- elimina archivos compilados
