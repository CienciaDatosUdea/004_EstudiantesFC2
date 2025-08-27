# Tarea: Operaciones con números complejos en C++ 

Este programa implementa una clase en C++ para manejar números complejos y realizar operaciones básicas: suma, resta, multiplicación y división.

El código está estructurado de manera modular, por lo que se utilizan archivos de cabecera para inicializar estructuras (.h), de implementación (.cpp) y un programa principal main.cpp que permite ejecutar el programa visualizar los resultados.

La compilación y organización del código se realiza mediante **Makefile**, por lo que las componentes se encuentran separadas en diferentes carpetas.

Este documento funciona como guía básica para entender el concepto de modularización de código, el uso de clases y algo básico de teoría de operaciones básicas en números complejos.
--- 

## Estructura de carpetas

Se tienen las siguientes carpetas moduladas: 

include → Contiene los archivos de cabecera  
  - `complejos.h`  

src - → Contiene la implementación principal  
  - `complejos.cpp`  

En la carpeta raíz se encuentran los siguientes archivos:  
- `Makefile` – Script de compilación modular  
- `Readme.md` – Documento actual  
- `complejos.out` – Ejecutable principal (se genera al compilar)  
- `complejos_main.cpp` – Archivo inicial de ejecución del proyecto 

**Para compilar el programa**
Desde la terminal, ubiquese en la carpeta raíz y ejecute los siguientes comandos: 

```bash
# Compilar el programa principal
make
# Esto generará el ejecutable:
complejos.out

# Ejecutar el programa
./complejos.out


