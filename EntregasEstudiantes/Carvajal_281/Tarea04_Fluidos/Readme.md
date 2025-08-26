# Tarea: Simulaciónde Navier-Stokes en C++ 

Este proyecto implementa un código que soluciona numericamente las ecuaciones de Navier–Stokes bidimensionales en C++, partiendo del código trabajado en clase.

La implementación utiliza un esquema explícito tipo FTCS (Forward Time, Central Space) para la actualización de las componentes de velocidad y un método iterativo para la ecuación de presión.

En esta actividad se realizaron dos modificaciones clave respecto al código base:

* Se agregaron fuerzas externas (Fx, Fy) en las ecuaciones de momento, que permiten analizar cómo un campo externo modifica la evolución de las velocidades.

* Se modificaron las condiciones de frontera: en la frontera inferior y superior se eliminan la condición de Neumann homogénea para la presión, evitando así sobrerrestricción en el sistema.

El código está estructurado de manera modular, por lo que se utilizan archivos de cabecera para inicializar estructuras (.h), de implementación (.cpp) y un programa principal main.cpp que permite ejecutar el programa visualizar los resultados.

La compilación y organización del código se realiza mediante **Makefile**, por lo que las componentes se encuentran separadas en diferentes carpetas.
--- 

## Estructura de carpetas

Se tienen las siguientes carpetas moduladas: 

data → Contiene los archivos .txt obtenidos de la ejecución del código  

graph → contiene los archivos de .ipynb que realizan el análisis de los .txt obtenidos
  - `graficacion.ipynb`  

images → contiene las imagenes extraídas del análisis del código .ipynb 

include → Contiene los archivos de cabecera  
  - `flow.h`  

src - → Contiene la implementación principal  
  - `flow.cpp`  

En la carpeta raíz se encuentran los siguientes archivos:  
- `Makefile` – Script de compilación modular  
- `Readme.md` – Documento actual  
- `flow.out` – Ejecutable principal (se genera al compilar)  
- `main.cpp` – Archivo inicial de ejecución del proyecto 

**Para compilar el programa**
Desde la terminal, ubiquese en la carpeta raíz y ejecute los siguientes comandos: 

```bash
# Compilar el programa principal
make
# Esto generará el ejecutable:
flow.out

# Ejecutar el programa
./flow.out


