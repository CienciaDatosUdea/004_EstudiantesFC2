---
title: Proyecto_Filtro

---

# Proyecto: Diseño de un filtro FIR con Ventana de Hamming en C++

---

##  Descripción

Este proyecto implementa un **diseñador de filtros FIR** (Finite Impulse Response) en C++ utilizando la **ventana de Hamming**.  
El programa permite al usuario crear diferentes tipos de filtros digitales:

- **Pasa-bajas**  
- **Pasa-altas**  
- **Pasa-banda**  
- **Rechaza-banda**  

Además de mostrar los coeficientes calculados en consola, el programa exporta los datos a archivos de texto para posterior análisis y graficación en Python.

---

##  Estructura del proyecto

```
Proyecto_Filtro/
│
├── datos/                   # Archivos exportados con coeficientes y respuesta en frecuencia
│   ├── filtro_lowpass.txt
│   ├── filtro_highpass.txt
│   ├── filtro_bandpass.txt
│   └── filtro_bandstop.txt
│
├── docs/                    # Documentación
│   └── README.md
│
├── include/                 # Archivos de cabecera (.h)
│   ├── fir_filter.h
│   └── flow.h
│
├── python/                  # Scripts de análisis en Python
│   └── graficar_filtro.ipynb
│
├── src/                     # Código fuente C++
│   ├── fir_filter.cpp
│   └── flow.cpp
│
├── main.cpp                 # Programa principal
├── fir_filtro.out           # Ejecutable (se genera tras compilar)
└── Makefile                 # Script de compilación
```

---

## Instalación y compilación

###  Requisitos previos
- Compilador C++ compatible con **C++17** (ej. `g++`).
- GNU Make.
- Python 3.x (opcional, para análisis con Jupyter Notebook).
- Librerías numpy, matplotlib y scipy de Python

### Compilar el proyecto

```bash
make
```

Esto generará el ejecutable `fir_filtro.out`.

### Ejecutar el programa

```bash
./fir_filtro.out
```

### Limpiar archivos compilados y datos exportados

```bash
make clean
```

---

## Uso del programa

1. El programa solicita:
   - Número de coeficientes del filtro (**numtaps**).  
   - Frecuencia de muestreo (**fs**).  
   - Tipo de filtro a diseñar.  

2. Según el tipo de filtro, pide frecuencias de corte.  
3. Muestra los coeficientes en pantalla. 
4. Exporta un archivo .txt en datos/ que contiene:
   - Los coeficientes FIR calculados con la ventana de Hamming.
   - La respuesta en frecuencia (frecuencia en Hz vs magnitud en dB) del filtro diseñado.

Ejemplo de flujo en la terminal una vez que se ejecute el archivo .out:

```
=== Diseñador de Filtros FIR (Ventana de Hamming) ===
Ingrese número de coeficientes: 51
Ingrese frecuencia de muestreo [Hz]: 8000

Seleccione tipo de filtro:
1) Pasa-bajas
2) Pasa-altas
3) Pasa-banda
4) Rechaza-banda
Opcion: 1

Ingrese frecuencia de corte [Hz]: 1000
Coeficientes FIR:
0.00123
0.00245
...
Datos exportados a: datos/filtro_lowpass.txt

```
---

## Análisis y visualización en Python

En la carpeta `python/` se incluye el notebook `graficar_filtro.ipynb` que permite:

- Cargar los coeficientes generados en `datos/*.txt`.
- Graficar la **respuesta al impulso** generada en C++ (secuencia de coeficientes $h[n]$).
- Visualizar la **respuesta en frecuencia** de los filtros generados en C++ con ventana de Hammig y comparar con la generada usando la librería scipy de Python.
- Filtrar una señal con ruido de un proceso físico con filtros FIR de Python y con los filtros FIR C++. Comparar los resultados

##  Mejoras futuras
- Implementación de más ventanas (Blackman, Kaiser, etc.).
- Interfaz gráfica en Python para diseño interactivo.

---
## Autores
**JADER ENRIQUE MARIO MENDOZA - JHON FREDY RESTREPO HENAO**

**Cusro de Física Computacional 2**

**Universidad de Antioquia (Instituto de Física) 2025**

