# Tarea 02: Historias 
# Simulación 1D de la ecuación de difusión (Método FTCS)


Este programa implementa un modelo numérico en 1D para resolver la ecuación de difusión utilizando el **método explícito FTCS** (*Forward Time, Central Space*).  

El código está estructurado de manera modular, por lo que existen clases específicas para la geometría, las condiciones iniciales y de frontera, y para el solver de difusión.

La compilación y organización del código se realiza mediante **Makefile**, por lo que las componentes se encuentran separadas en diferentes carpetas.

Durante el desarrollo se da solución a las **14 historias de usuario** propuestas en la tarea, además de abordar los **10 requisitos funcionales** especificados.

Este documento funciona como guía para entender, implementar y validar el solver de difusión 1D, siguiendo las historias de usuario definidas.
---
Las historias definidas por el usuario para la realización del código propuesto fueron: 

**Historia 1: Construcción del dominio espacial**  
Como desarrollador,  
quiero definir una clase **Geometria** que calcule las posiciones espaciales y el espaciado dx para representar el dominio de simulación con una malla uniforme.

**Historia 2: Aplicación de condición inicial**  
Como investigador quiero aplicar una condición inicial tipo **Gaussiana**,  
para simular un perfil de temperatura localizado y suave en el tiempo inicial.

**Historia 3: Condiciones de frontera de Dirichlet**  
Como investigador quiero aplicar condiciones de frontera de tipo **Dirichlet** *(temperatura fija)*,para modelar extremos del dominio en contacto con un reservorio térmico.

**Historia 4: Condiciones de frontera de Neumann (futuro)**  
Como investigador quiero poder aplicar condiciones de frontera tipo **Neumann** *(flujo nulo)* para modelar bordes aislados donde no hay transferencia de calor.

**Historia 5: Implementación del esquema FTCS**  
Como desarrollador quiero implementar el método explícito **FTCS** en una clase `DiffusionSolver` para calcular la evolución temporal de la temperatura.

**Historia 6: Separación de lógica física y numérica**  
Como desarrollador quiero que el solver use la geometría y condiciones como entrada para mantener una arquitectura modular y escalable.

**Historia 7: Aplicación de condiciones de frontera en cada paso**  
Como desarrollador quiero aplicar condiciones de frontera dentro del bucle temporal para asegurar que se respeten en cada iteración.

**Historia 8: Pruebas de construcción de la malla**  
Como desarrollador quiero verificar que **Geometria** calcula correctamente `dx` y los valores de `x[i]` para asegurar la coherencia de la malla espacial.

**Historia 9: Prueba de condición inicial**  
Como desarrollador quiero validar que la condición inicial se aplica correctamente para asegurar que el estado térmico inicial es coherente con el modelo físico.

**Historia 10: Verificación de condiciones de frontera**  
Como desarrollador quiero comprobar que las condiciones de frontera no se alteran durante la evolución para garantizar fidelidad física en la simulación.

**Historia 11: Validación numérica básica**  
Como desarrollador quiero ejecutar una simulación corta y comparar con resultados esperados para confirmar que el solver produce soluciones estables y físicas.

**Historia 12: Estructura modular de carpetas**  
Como desarrollador quiero organizar el código en `include/`, `src/`, `tests/` y `main.cpp` para mejorar la mantenibilidad y claridad del proyecto.

**Historia 13: Punto de entrada limpio**  
Como desarrollador quiero definir un `main.cpp` que inicialice parámetros, configure el dominio y ejecute el solver para centralizar el control de las simulaciones.

---

## Futuras funcionalidades

**Historia 14: Exportación gráfica**  
Como usuario quiero generar archivos compatibles con **Gnuplot** o **Python**,  
para visualizar la evolución del perfil de temperatura.

**Historia 15: Extensión a 2D**  
Como investigador quiero extender el solver a **2D**,  
para simular difusión en superficies y geometrías más realistas.

## Estructura de carpetas

Se tienen las siguientes carpetas moduladas: 

include → Contiene los archivos de cabecera  
  - `difusion_model.h`  

src - → Contiene la implementación principal  
  - `difusion_model.cpp`  
  - `main.cpp`
  
test - → Contiene las pruebas de código
  - `test_geometria.cpp`  

En la carpeta raíz se encuentran los siguientes archivos:  
- `Makefile` – Script de compilación modular  
- `Readme.md` – Documento actual  
- `difusion_model.out` – Ejecutable principal (se genera al compilar)  
- `test.out` – Ejecutable de pruebas (se genera al compilar tests)  
- `resultados_tarea02historias.txt` – Resultados de simulación principal  
- `Teoriadeclase.pdf` – Documento teórico de referencia   


**Para compilar el programa**
Desde la terminal, ubiquese en la carpeta raíz y ejecute los siguientes comandos: 

```bash
# Compilar el programa principal
make
# Esto generará el ejecutable:
difusion_model.out

# Ejecutar el programa
./difusion_model.out

# Compilar los tests
make test
# Esto generará el ejecutable:
test.out

# Ejecutar los tests
./test.out

