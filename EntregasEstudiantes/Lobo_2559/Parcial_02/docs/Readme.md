# **Descripción del Proyecto**
Este proyecto implementa el método de Diferencias Finitas en el Dominio del Tiempo (FDTD) con el esquema de Yee para simular la propagación de ondas electromagnéticas en una dimensión. El código resuelve numéricamente las ecuaciones de Maxwell para estudiar el comportamiento de campos electromagnéticos bajo diferentes condiciones de frontera y parámetros de simulación.

**Estructura**
FDTD_Simulation/
├── include/
│   └── onda_em_yee.h         # Definición de la clase OndaEMYee
├── src/
│   └── onda_em_yee.cpp       # Implementación de los métodos
├── main.cpp                  # Programa principal
├── analisis_resultados.ipynb       #notebook de Jupyter para analizar los outputs de la simulación
├── animations/               # Animaciones de la propagación
└── data/                     # Datos de salida de las simulaciones

**Para compilar**
Ejecutar en ela terminal:
g++  main.cpp -o fdtd.out

**Para Ejecutar**
./fdtd.out

**INPUTS**
- Número de pasos temporales: El usuario puede escoger los pasos temporales para la evolución de la onda electromagnética

**OUTPUTS**
- En la terminal se muestra los parámetros utilizados para la evolución en unidades normalizadas 
- En la carpeta ./data se encuentrarán los siguientes archivos

1. EM_periodic.txt y EM_fixed.txt: matriz con la evolucion temporal de una onda con un beta =0.05 establecido

2. EM_periodic.beta_N.txts y . EM_fixed.beta_N.txt : matrices con la evolucion temporal de una onda con un beta = N/100
