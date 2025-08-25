# Solución numérica de la ecuación de Boltzmann para materia oscura

Andrés Felipe Riaño Quintanilla

Santiago Julio Dávila


---
## Problema físico [1]
Para estudiar la evolución de los diferentes componentes de energía en el Universo es necesario considerar desviaciones del equilibrio térmico. Un criterio aproximado para establecer el momento en que una especie deja de estar en equilibrio térmico, o se "desacopla", se da en términos de la tasa de interacción de las partículas, $\Gamma$, y la tasa de expansión del universo, $H$:

$$\begin{align*}
\Gamma&\gtrsim H \text{ (acoplado)}\\
\Gamma&\lesssim H \text{ (desacoplado)},
\end{align*}$$

es decir, la especie se desacopla del baño térmico cuando la tasa de expansión de Hubble es mayor que la tasa de interacción de las partículas. Para rastrear la evolución de la densidad numérica de las partículas de interés, necesitamos una ecuación que describa la evolución de la distribución en el espacio de fases, $f(x^\mu,p^\mu)$, de la partícula. Dicha ecuación es conocida como la ecuación de Boltzmann, que en general puede escribirse como

$$
\hat{\mathcal{L}}[f]=\mathcal{C}[f],
$$

donde $\hat{\mathcal{L}}$ es el operador de Liouville y $\mathcal{C}[f]$ es el término de colisión. El operador de Liouville puede definirse como una derivada total respecto a un parámetro de una función cuyas variables pueden depender de ese parámetro de forma implícita. En mecánica clásica, el parámetro suele ser el tiempo, y el operador de Liouville se aplica generalmente sobre una función $f(x^i,v^i,t)$, por lo que el operador de Liouville toma la forma

$$
\hat{\mathcal{L}}\_{c}=\dfrac{\partial}{\partial t}+\dot{\vec{x}}\cdot\nabla+\dot{\vec{v}}\cdot\nabla_{\vec{v}}.
$$

Extender esta definición a la relatividad general es sencillo, eligiendo un parámetro $\theta$ tal que $\frac{\mathrm{d}x^\mu}{\mathrm{d}\theta}\equiv\dot{x}^\mu=p^\mu$ y considerando funciones del tipo $f(x^\mu,p^\mu)$ que no dependen explícitamente de dicho parámetro, el operador de Liouville queda

$$
\hat{\mathcal{L}}=p^\mu\dfrac{\partial}{\partial x^\mu}-\Gamma^\mu_{\alpha\beta}p^\alpha p^\beta \dfrac{\partial}{\partial p^\mu}
$$

donde se ha usado la ecuación geodésica $\dot{p}^\mu+\Gamma^\mu_{\alpha\beta}p^\alpha p^\beta=0$. Las funciones de distribución de interés son homogéneas e isotrópicas en el espacio, como determina la métrica de Friedmann-Lemaître-Robertson-Walker (FLRW): $f(x^\mu,p^\mu)=f(x^0,p^0)=f(t,E)$. Con esta métrica, es fácil verificar que el operador de Liouville es

$$
\hat{\mathcal{L}}[f]=E\dfrac{\partial f}{\partial t}-\dfrac{\dot{a}}{a}p^2\dfrac{\partial f}{\partial E}.
$$

La ecuación de Boltzmann entonces es

$$
E\dfrac{\partial f}{\partial t}-Hp^2\dfrac{\partial f}{\partial E}=\mathcal{C}[f].
$$

Integrando esta ecuación sobre $\mathrm{d}\tilde{p}=\frac{g}{(2\pi)^3}\frac{\mathrm{d}^3\vec{p}}{E}$ y usando la definición de densidad de número

$$
n(t)=\dfrac{g}{(2\pi)^3}\int\mathrm{d}^3\vec{p}f(E,t),
$$

donde $E$ está sujeto a la restricción $E²=m²+p²$, la ecuación de Boltzmann queda

$$
\dfrac{\mathrm{d}n}{\mathrm{d}t}+3Hn=\dfrac{g}{(2\pi)^3}\int\mathrm{d}^3\vec{p}\dfrac{\mathcal{C}[f]}{E}.
$$

Definiendo $Y=n/s$ y $x=m/T$, donde 

$$s=\dfrac{2\pi²}{45}h_{eff}(T)T³$$

es la densidad de entropía que satisface la conservación de la entropía $sa³=constante$, por lo tanto, ignorando la dependencia en temperatura de los grados de libertad relativistas, $h_{eff}$, $\dot{s}=-3Hs$. Diferenciando $Y$ respecto al tiempo

$$
\dot{Y}=\dfrac{\dot{n}}{s}-\dfrac{n\dot{s}}{s²}=\dfrac{\dot{n}+3Hn}{s}.
$$

A partir de la conservación de la entropía, usando la forma funcional de $s$ y despreciando la dependencia en temperatura de $h_{eff}$, también se puede deducir que $aT=constante$, y así, $\dot{T}=-HT$. Usando la regla de la cadena, se puede escribir la derivada temporal en términos de la variable $x$: $\frac{\mathrm{d}}{\mathrm{d}t}=\frac{\mathrm{d}T}{\mathrm{d}t}\frac{\mathrm{d}x}{\mathrm{d}T}\frac{\mathrm{d}}{\mathrm{d}x}=Hx\frac{\mathrm{d}}{\mathrm{d}x}$, así que la ecuación de Boltzmann puede escribirse como

$$
\dfrac{\mathrm{d}Y}{\mathrm{d}x}=\dfrac{1}{Hxs}\dfrac{g}{(2\pi)^3}\int\mathrm{d}^3\vec{p}\dfrac{\mathcal{C}[f]}{E}.
$$

Considerando una reacción $\underbrace{\psi+a+b+...}\_{in}\rightleftharpoons \underbrace{i+j+...}_{out}$, donde $\psi$ es la especie de interés. El término de colisión para un proceso como este es

$$\begin{align*}
\int\mathcal{C}[f]\mathrm{d}\tilde{p}\_\psi=&-\int\left(\prod_{in}\mathrm{d}\tilde{p}\_k\right)\left(\prod_{out}\mathrm{d}\tilde{p}\_k\right)(2\pi)^4\delta⁴(p_{in}-p_{out})\times\\
&\times\left[|M|^2\_\rightarrow\left(\prod_{in}f_k\right)\left(\prod_{out}(1\pm f_k)\right)-|M|^2_\leftarrow\left(\prod_{out}f_k\right)\left(\prod_{in}(1\pm f_k)\right)\right],
\end{align*}$$

que puede simplificarse considerando la invariancia $CP$, lo que implica que la amplitud de transición invariante para la reacción directa es igual a la de la inversa: $|M|²_\rightarrow=|M|²_\leftarrow=|M|²$, y despreciando los factores de bloqueo y emisión estimulada $1\pm f_k\simeq 1$, llevando a la ecuación de Boltzmann

$$
\dfrac{\mathrm{d}n}{\mathrm{d}t}+3Hn=-\int\left(\prod_{in}\mathrm{d}\tilde{p}\_k\right)\left(\prod_{out}\mathrm{d}\tilde{p}\_k\right)(2\pi)^4\delta^4(p_{in}-p_{out})|M|^2\left[\left(\prod_{in}f_k\right)-\left(\prod_{out}f_k\right)\right].
$$

Nos centraremos en algunos candidatos de materia oscura (DM) tipo partícula, y las soluciones a la ecuación de Boltzmann en dicho contexto. El primer modelo de DM a analizar son las _Weakly Interacting Masssive Particles_ o WIMPs, que se desacoplan del baño térmico principalmente vía aniquilaciones $2\rightarrow2$ en partículas del Modelo Estándar (SM), y satisfacen la restricción de densidad de reliquia observacional $\Omega_0 h²\simeq0.12$; existen otros mecanismos alternativos por los cuales los WIMPs se congelan, como la semi-aniquilación. Otro mecanismo que puede producir la densidad de reliquia observada es el mecanismo de "freeze-in", en el cual el acoplamiento entre el sector oscuro y el visible es lo suficientemente pequeño como para evitar que el sector oscuro esté en equilibrio térmico con el sector visible, y la abundancia de reliquia se congela a un valor constante después de que las densidades de las partículas visibles que producen las partículas oscuras se suprimen exponencialmente; las partículas oscuras producidas por este mecanismo se llaman _Frozen-In_ o _Feebly Interacting Massive Particles_, FIMPs por sus siglas en inglés. Si asumimos interacciones DM-SM muy pequeñas, las auto-interacciones dentro del sector oscuro se vuelven significativas, en particular, procesos que cambian el número de partículas, como $3\to2$ y $4\to2$, en este caso, las partículas se conocen como _Strongly_ o _Self Interacting Massive Particles_.

Consideraremos primero la aniquilación de WIMPs en partículas del Modelo Estándar (SM) $DM+DM\rightleftharpoons SM+SM$ que ocurre durante la época de dominación por radiación, descrita por la ecuación de Friedmann:

$$
H(T)=\sqrt{\dfrac{\rho_R(T)}{3M_P²}},
$$

donde $M_P\approx 2.4\times10^{18}\text{ GeV}$ es la masa de Planck reducida y la densidad de energía de radiación del SM está dada por

$$
\rho_R(T)=\dfrac{\pi²}{30}g_{eff} T⁴.
$$

El término de colisión para este proceso es

$$
-\int\mathrm{d}\tilde{p}_1\mathrm{d}\tilde{p}_2\mathrm{d}\tilde{p}_3\mathrm{d}\tilde{p}_4(2\pi)⁴\delta⁴(p_1+p_2-p_3-p_4)|M|²(f_1f_2-f_3^{eq}f_4^{eq}),
$$

donde 1 y 2 representan las partículas DM en el lado izquierdo de la reacción y 3 y 4 representan las partículas SM en el lado derecho, que están en equilibrio térmico, de ahí el superíndice "eq" en $f_3^{eq}f_4^{eq}$. El delta de Dirac asegura la conservación del momento de 4 componentes en el proceso, particularmente la conservación de la energía. Asumimos que las distribuciones de equilibrio son distribuciones de Maxwell-Boltzmann sin potencial químico: $f_i^{eq}\sim \exp(-E_i/T)$ y las distribuciones fuera de equilibrio son aproximadamente proporcionales a las de equilibrio $f_i\approx\left(\frac{n_i}{n_i^{eq}}f_i^{eq}\right)$. Las distribuciones de las partículas SM son entonces

$$
f_3^{eq}f_4^{eq}=\exp(-(E_3+E_4)/T)=\exp(-(E_1+E_2)/T)=f_1^{eq}f_2^{eq}
$$

Reemplazando en el término de colisión, obtenemos la expresión

$$
-(n_1n_2-n_1^{eq}n_2^{eq})\dfrac{1}{n_1^{eq}n_2^{eq}}\int\mathrm{d}\tilde{p}_1\mathrm{d}\tilde{p}_2\mathrm{d}\tilde{p}\_4\mathrm{d}\tilde{p}\_3(2\pi)^4\delta^4(p\_1+p\_2-p\_3-p\_4)|M|^2f\_1^{eq}f\_2^{eq}=-\langle\sigma v\rangle(n^2-n\_{eq}^2),
$$

donde la sección eficaz promediada térmicamente, $\langle\sigma v\rangle$, está definida como la integral en la ecuación anterior y hemos usado el hecho de que no hay asimetría entre las especies DM involucradas en la reacción, por lo tanto $n_1=n_2=n$. $n_{eq}$ se encuentra fácilmente considerando que las distribuciones de equilibrio son distribuciones de Maxwell-Boltzmann:

$$
n_{eq} = \dfrac{g}{2\pi^2}m^2TK_2\left(\dfrac{m}{T}\right)
$$

Usando la definición de $Y$, la ecuación de Boltzmann se convierte en

$$
\dfrac{\mathrm{d}Y}{\mathrm{d}x}=-\dfrac{\langle\sigma v\rangle s}{Hx}(Y²-Y_{eq}²)
$$

y la abundancia de reliquia $\Omega_0=mY_0s_0/3H_0²M_P²$ está dada por:

$$
\Omega_{0}h^2=\dfrac{Y_0ms_0}{3M_P^2(2.13\times 10^{-42}\text{ GeV})^2},
$$

donde el subíndice 0 representa el valor actual de la cantidad en cuestión.

Análogamente, se puede hacer este desarrollo para FIMPs y SIMPs:

**Para FIMPs:**
La ecuación de Boltzmann para FIMPs (producción por "freeze-in") es:

$$
\dfrac{dY}{dx} = \dfrac{\langle\sigma v\rangle s}{Hx} Y_{eq}^2
$$


**Para SIMPs ($3\to2$):**
La ecuación de Boltzmann para procesos de aniquilación $3\to2$ es:

$$
\dfrac{dY}{dx} = -\dfrac{\langle\sigma v^2\rangle s^2}{Hx}(Y^3 - Y^2 Y_{eq})
$$

donde $\langle\sigma v^2\rangle$ es la sección eficaz promediada térmicamente para el proceso $3\to2$.

## Implementación computacional

La ecuación de Boltzmann para la densidad de número en el universo temprano se conoce como una ecuación _rígida_ porque los términos de la ecuación pueden variar en escalas de tiempo muy diferentes:

* El término de interacción $\langle \sigma v \rangle (n^2 - n_{eq}^2)$ puede ser muy grande cuando las partículas están en equilibrio, lo que provoca cambios rápidos en $n$.
* El término de expansión $3Hn$ evoluciona más lentamente.
Esta diferencia de escalas genera que la solución cambie muy rápido en algunos intervalos y muy lento en otros. Los métodos explícitos, como Euler o Runge-Kutta, requieren pasos de integración muy pequeños para mantener la estabilidad numérica en regiones de cambio rápido, lo que los hace ineficientes o incluso inestables.

Por eso, se prefieren métodos implícitos o semi-implícitos para resolver la ecuación de Boltzmann, ya que son más adecuados para ecuaciones rígidas y permiten usar pasos de integración más grandes sin perder estabilidad [2].

El método BDF (Backward Differentiation Formula) es una familia de métodos numéricos implícitos para resolver ecuaciones diferenciales ordinarias, especialmente útiles para ecuaciones rígidas. Considérese una ecuación diferencial rígida de la forma:

$$
\dfrac{\mathrm{d}Y}{\mathrm{d}x}=F(x,Y)
$$

En el método BDF, el valor futuro de la solución se calcula usando una combinación lineal de valores anteriores y la derivada evaluada en el nuevo punto.

$$
\left(\dfrac{\mathrm{d}Y}{\mathrm{d}x}\right)\_{n+1}\simeq\alpha_1Y_{n+1}+\alpha_0Y_n+\alpha_{-1}Y_{n-1}
$$

Por ejemplo, el BDF-2 (segundo orden) usa los dos valores previos para estimar el siguiente:

$$
\alpha_1 Y_{n+1} + \alpha_0 Y_n + \alpha_{-1} Y_{n-1} = F(x_{n+1}, Y_{n+1})\quad (*)
$$

donde 

$$\begin{align*}
&\alpha_1=\dfrac{1}{\Delta x_n}\left(1+\dfrac{\Delta x_n}{\Delta x_{n-1}+\Delta x_n}\right)\\
&\alpha_{-1}=\dfrac{1}{\Delta x_{n-1}}\left(\dfrac{\Delta x_n}{\Delta x_{n-1}+\Delta x_n}\right)\\
&\alpha_0=-\alpha_1-\alpha_{-1}
\end{align*}$$

y $\Delta x_n = x_{n+1}-x_n,~\Delta x_{n-1} = x_n - x_{n-1}$, en general $\Delta x_n\neq\Delta x_{n-1}$. Así pues, la evolución de $Y$ se reduce a encontrar la raíz $Y_{n+1}$ de la ecuación $(*)$, que, sin pérdida de generalidad, habrá de resolverse numéricamente [3].

### Clases Principales

#### 1. `Cosmology`
- **Propósito:** Calcula las cantidades físicas relevantes de la cosmología, como grados de libertad, densidad de energía, densidad de entropía y la tasa de Hubble.
- **Métodos:**
  - `Cosmology(long double T_)`: Constructor. Inicializa la temperatura y las variables físicas.
  - `readDegreesOfFreedom(const std::string& path)`: Lee los grados de libertad desde un archivo de datos.
  - `calculate(const std::string& path)`: Interpola los grados de libertad y calcula las cantidades físicas para la temperatura dada.

#### 2. `DarkMatterModel`
- **Propósito:** Define el modelo de materia oscura, incluyendo el tipo de partícula y los parámetros de la reacción.
- **Métodos:**
  - `DarkMatterModel(std::string name_, int DMini_, int DMfin_, int SMfin_)`: Constructor. Inicializa el modelo con nombre y parámetros.
  - `printProcess()`: Imprime la reacción de materia oscura en formato legible.

#### 3. `BoltzmannEquation`
- **Propósito:** Representa la ecuación de Boltzmann para un modelo y partícula de DM específicos.
- **Métodos:**
  - `BoltzmannEquation(...)`: Constructor. Inicializa los parámetros y calcula constantes cosmológicas.
  - `Yeq()`: Calcula la abundancia en equilibrio.
  - `dYdx(long double Y)`: Calcula la derivada de la abundancia según la ecuación de Boltzmann.
  - `setX(long double new_x)`: Cambia el valor de la variable x y actualiza las constantes cosmológicas.

#### 4. `BEqSolver`
- **Propósito:** Integra la ecuación de Boltzmann usando métodos numéricos (RK2 y BDF-2).
- **Métodos:**
  - `BEqSolver(...)`: Constructor. Inicializa los vectores y parámetros de integración.
  - `solve()`: Resuelve la ecuación de Boltzmann y calcula la abundancia de reliquia de DM.

#### 5. `Secante`
- **Propósito:** Implementa el método de la secante para encontrar raíces de funciones.
- **Métodos:**
  - `Secante(double tol, int maxIter)`: Constructor. Define tolerancia y máximo de iteraciones.
  - `encontrarRaiz(...)`: Encuentra la raíz de una función usando el método de la secante.

#### 6. `FieldWriter`
- **Propósito:** Escribe los resultados de la integración y los parámetros del modelo en archivos de texto.
- **Métodos:**
  - `FieldWriter()`: Constructor. Abre los archivos de salida.
  - `write(BEqSolver BEQsol)`: Escribe los datos de la solución y los parámetros del modelo.

### Flujo General

1. Se define el modelo de materia oscura con `DarkMatterModel`.
2. Se inicializa la ecuación de Boltzmann con `BoltzmannEquation`.
3. Se resuelve la ecuación con `BEqSolver`, que utiliza métodos numéricos y el método de la secante.
4. Los resultados y parámetros se escriben en archivos usando `FieldWriter`.

## Instrucciones de Compilación y Ejecución

### Compilación

El proyecto utiliza varias clases en archivos `.cpp` y depende de la biblioteca Boost para funciones especiales de Bessel.  
Asegúrate de tener Boost instalado en tu sistema.

Para compilar el proyecto, puedes usar el siguiente comando desde el directorio raíz donde está el `Makefile`:

```bash
make clean
make
```

Esto generará el ejecutable principal en `bin/main.out`.

Si deseas compilar manualmente (sin Makefile), puedes usar:

```bash
g++ -std=c++17 -I/path/a/boost main.cpp src/*.cpp -o bin/main.out -lboost_math_c99
```
Asegúrate de ajustar la ruta de Boost si es necesario.

---

## Ejecución

El programa principal se ejecuta desde la terminal y requiere los siguientes argumentos:

```bash
./bin/main.out MS sigmav TR model DMini DMfin SMfin
```

**Descripción de los argumentos:**

- `MS` (float): Masa de la partícula de materia oscura (DM).
- `sigmav` (float): Sección eficaz de interacción de la DM.
- `TR` (float): Temperatura de referencia inicial.
- `model` (string): Nombre del modelo de DM (por ejemplo, `"WIMP"` o `"FIMP"`).
- `DMini` (int): Número de partículas DM en el estado inicial de la reacción.
- `DMfin` (int): Número de partículas DM en el estado final de la reacción.
- `SMfin` (int): Número de partículas del Modelo Estándar en el estado final.

**Ejemplo de ejecución:**

```bash
./bin/main.out 100.0 1e-10 1000000.0 WIMP 2 0 2
```
---
**Notas:**
- Verifica que la ruta de los archivos de datos (`data/std.tab`) y los directorios en el código del notebook `graphs.ipynb` sea correcta.
- Si usas conda o algún entorno virtual, asegúrate de tener Boost disponible en ese entorno.

---

## Salida

- El programa genera archivos de salida en la carpeta `data/`:
  - `solution.txt`: Evolución de las variables físicas relevantes.
  - `params.txt`: Parámetros del modelo y ecuación utilizada.
- Si ejecutaste el notebook `graphs.ipynb` se generarán las siguientes gráficas en la carpeta `python`:
  - `gdlr.png`: grados de libertad relativistas.
  - `wimp.png`: solución para WIMPs.
  - `fimp.png`: solución para FIMPs.
  - `simp.png`: solución para SIMPs.
 
---

## Referencias
[1] Kolb, E. W., Turner, M. S., & Silk, J. (1991). The Early Universe.

[2] Wanner, G., & Hairer, E. (1996). Solving ordinary differential equations II (Vol. 375, p. 98). New York: Springer Berlin Heidelberg.

[3] Nishikawa, H. (2024). Derivation of BDF2/BDF3 for Variable Step Size (Corrected).
