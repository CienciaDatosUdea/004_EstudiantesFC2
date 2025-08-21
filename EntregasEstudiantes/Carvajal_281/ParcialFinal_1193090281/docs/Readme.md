# Parcial Final Física Computacional II 
# Sara Alejandra Carvajal Ramírez 
# Diferencias fínitas: Simulación FDTD de ondas electromagnéticas 


Este proyecto implementa un modelo **FDTD (Finite-Difference Time-Domain) 1D** para simular la propagación de una onda electromagnética linealmente polarizada en el vacío.

El código está estructurado de manera modular, con clases específicas para la geometría, los campos y la evolución temporal mediante FDTD. Se utiliza un **Makefile** para compilar y organizar el proyecto.


La compilación y organización del código se realiza mediante **Makefile**, por lo que las componentes se encuentran separadas en diferentes carpetas.

Durante el desarrollo se da solución a los dos puntos fundamentales correspondientes a: 
1. **Simulación de propagación de onda sinusoidal con FDTD**
2. **Estudio de condiciones de frontera y estabilidad numérica** desde donde se realizaron algunas pruebas de implementación de condiciones de frontera de Dirichlet y de tipo Periódicas ademas de evaluar la estabilidad del sistema bajo variación de parámetros


Este documento funciona como guía para entender, implementar y validar el problema de la propagación de Ondas electromagnéticas empleando el método de diferencias fínitas en el dominio del tiempo con el implemento de la malla escalonada de Yee [1.]



## Parámetros iniciales de simulación

- Número de nodos: N = 200
- Espaciado espacial inicial: dz = 0.1
- beta 
- Número de pasos temporales: steps = 200

Estos valores pueden modificarse en main.cpp.

## Estructura de carpetas

Se tienen las siguientes carpetas moduladas: 

include → Contiene los archivos de cabecera  
  - `fdtd.h`  

src - → Contiene la implementación principal y su .o asociado  
  - `fdtd.cpp`  
  - `fdtd.o`  
  
 
data - → Contiene los archivos .txt extraídos de la simulación
  - campos.txt
  - campos_Dirichlet.txt
  - camposnoestabilidad1.txt
  - camposnoestabilidad2.txt
  - campos_t0.2_z0.5.txt
  - campos_t0.2_z1.txt
  - campos_t0.2_z2.txt
  - campos_z1_t0.2.txt
  - campos_z1_t0.3.txt
  - campos_z1_t0.5.txt
  
docs - → Contiene el Readme- Documento actual de explicación general 
  - `fdtd.cpp` 
  - Teoría_parcial.pdf -En este encontrará adicionalmente algunos desarrollos teóricos
   
python - → Contiene un archivo de tipo .ipynb con la documentación correspondiente al análisis de los datos y la obtención de imagenes y simulación 
  - `AnalisisRespuestas.ipynb`

  
graphs - → Contiene las imágenes y simulaciones realizadas a través de Python con los archivos .txt de la carpeta data 

En la carpeta raíz se encuentran los siguientes archivos:  
- `Makefile` – Script de compilación modular  
- `sim_fdtd.out` – Ejecutable principal (se genera al compilar)  
- `main.cpp`

**Para compilar el programa**
Desde la terminal, ubiquese en la carpeta raíz y ejecute los siguientes comandos: 

```bash
# Compilar el programa principal
make
# Esto generará el ejecutable:
fdtd.out

# Ejecutar el programa
./sim_fdtd.out
```

# Bibliografía

[1.] Rubin H. Landau, Manuel J. Páez y Cristian C. Bordeianu. Computational Physics: Problem Solving with Python, 3a edición. Wiley-VCH, 2015.
Texto traducido y adaptado del capítulo 22 — “E&M Waves: Finite-Difference Time Domain (FDTD)” (páginas aprox. 525–)

