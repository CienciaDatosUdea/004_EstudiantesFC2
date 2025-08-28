#** Comparación de un Propagador de Luz de Espectro Angular en Python vs C++**

## Descripción del Proyecto
Este proyecto presenta la comparación entre dos implementaciones de un propagador de luz basado en el método del espectro angular:  
- Una versión desarrollada en Python.  
- Una versión equivalente desarrollada en C++.  

El objetivo es evaluar la equivalencia de resultados y el rendimiento computacional en ambas plataformas.

---

##  Implementación en C++
La versión en C++ fue desarrollada a través de un notebook de Google Colaboartory. No obstante, está organizada en los siguientes archivos:

- `asm.h` → Contiene las definiciones y prototipos.  
- `asm.cpp` → Implementación del propagador.  
- `main.cpp` → Programa principal que ejecuta el propagador.  
- `Makefile` → Permite compilar y ejecutar el proyecto fácilmente.  

## Compilación
 `! cmake `..
`! make`

## Ejecución
`./main`

## Output

El programa genera como resultado archivos CSV que contienen el campo luminoso propagado para diferentes distancias de propagación.

## Resultados

 Se comprobó que ambas implementaciones (Python y C++) son equivalentes en cuanto a los resultados obtenidos. Sin embargo, se observó que la implementación en C++ es más lenta que la versión en Python. Una posible causa es que la librería LibTorch, utilizada en la versión en C++, ya no recibe actualizaciones desde hace tiempo, lo cual puede afectar su rendimiento.

##Autores

Valentina Lobo Ruiz
Camilo Londoño Vera



