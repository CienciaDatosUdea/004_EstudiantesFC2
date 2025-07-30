# Historias de Usuario – Solver de Difusión 1D

Este archivo contiene las historias de usuario que definen los requisitos funcionales del software para simular la ecuación de calor 1D usando el método explícito (FTCS).

---

## Geometría y malla

### Historia 1: Construcción del dominio espacial
**Como** desarrollador,  
**quiero** definir una clase `Geometria` que calcule las posiciones espaciales y el espaciado `dx`,  
**para** representar el dominio de simulación con una malla uniforme.

---

##  Condiciones iniciales y de frontera

### Historia 2: Aplicación de condición inicial
**Como** investigador,  
**quiero** aplicar una condición inicial tipo Gaussiana,  
**para** simular un perfil de temperatura localizado y suave en el tiempo inicial.

### Historia 3: Condiciones de frontera de Dirichlet
**Como** investigador,  
**quiero** aplicar condiciones de frontera de tipo Dirichlet (temperatura fija),  
**para** modelar extremos del dominio en contacto con un reservorio térmico.

### Historia 4: Condiciones de frontera de Neumann (futuro)
**Como** investigador,  
**quiero** poder aplicar condiciones de frontera tipo Neumann (flujo nulo),  
**para** modelar bordes aislados donde no hay transferencia de calor.

---

## Lógica del solver

### Historia 5: Implementación del esquema FTCS
**Como** desarrollador,  
**quiero** implementar el método explícito FTCS en una clase `DiffusionSolver`,  
**para** calcular la evolución temporal de la temperatura.

### Historia 6: Separación de lógica física y numérica
**Como** desarrollador,  
**quiero** que el solver use la geometría y condiciones como entrada,  
**para** mantener una arquitectura modular y escalable.

### Historia 7: Aplicación de condiciones de frontera en cada paso
**Como** desarrollador,  
**quiero** aplicar condiciones de frontera dentro del bucle temporal,  
**para** asegurar que se respeten en cada iteración.

---

##  Pruebas y validación

### Historia 8: Pruebas de construcción de la malla
**Como** desarrollador,  
**quiero** verificar que `Geometria` calcula correctamente `dx` y los valores de `x[i]`,  
**para** asegurar la coherencia de la malla espacial.

### Historia 9: Prueba de condición inicial
**Como** desarrollador,  
**quiero** validar que la condición inicial se aplica correctamente,  
**para** asegurar que el estado térmico inicial es coherente con el modelo físico.

### Historia 10: Verificación de condiciones de frontera
**Como** desarrollador,  
**quiero** comprobar que las condiciones de frontera no se alteran durante la evolución,  
**para** garantizar fidelidad física en la simulación.

### Historia 11: Validación numérica básica
**Como** desarrollador,  
**quiero** ejecutar una simulación corta y comparar con resultados esperados,  
**para** confirmar que el solver produce soluciones estables y físicas.

---

## Organización del proyecto

### Historia 12: Estructura modular de carpetas
**Como** desarrollador,  
**quiero** organizar el código en `include/`, `src/`, `tests/` y `main.cpp`,  
**para** mejorar la mantenibilidad y claridad del proyecto.

### Historia 13: Punto de entrada limpio
**Como** desarrollador,  
**quiero** definir un `main.cpp` que inicialice parámetros, configure el dominio y ejecute el solver,  
**para** centralizar el control de las simulaciones.

---

## Futuras funcionalidades

### Historia 14: Exportación gráfica
**Como** usuario,  
**quiero** generar archivos compatibles con Gnuplot o Python,  
**para** visualizar la evolución del perfil de temperatura.

### Historia 15: Extensión a 2D
**Como** investigador,  
**quiero** extender el solver a 2D,  
**para** simular difusión en superficies y geometrías más realistas.

