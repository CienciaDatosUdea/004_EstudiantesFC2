### Compilación
Para compilar los programas, abra una terminal en la carpeta del proyecto y ejecute:

Para la versión con estructuras:
```bash
g++ Tarea_01_estructuras.cpp -o Tarea_01_estructuras.out
```

Para la versión con clases:
```bash
g++ Tarea_01_clases.cpp -o Tarea_01_clases.out
```

### Ejecución
Para ejecutar cualquiera de los programas, utilice:

```bash
./Tarea_01_estructuras.out
```
o
```bash
./Tarea_01_clases.out
```

### Funcionamiento
Ambos programas generan un sistema de 100 partículas distribuidas aleatoriamente sobre una circunferencia de radio 1. Cada partícula tiene una posición y un vector de fuerza aleatorio. El sistema permite:

- Inicializar las posiciones y fuerzas de todas las partículas.
- Perturbar aleatoriamente la posición de cada partícula dentro de un rango pequeño (`DELTA`).
- Calcular y mostrar la distancia máxima entre partículas.
- Calcular y mostrar la suma vectorial de todas las fuerzas y su magnitud.
- Imprimir por pantalla las posiciones de todas las partículas.

La diferencia entre ambos archivos es únicamente el uso de `struct` (estructuras) o `class` (clases) para definir los objetos principales.
