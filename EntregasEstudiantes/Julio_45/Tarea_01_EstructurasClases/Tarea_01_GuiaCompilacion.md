## Guía de compilación y ejecución de los archivos en Tarea_01_EstructurasClases

Los códigos presentados en este directorio permiten generar una distribución de `N=10` partículas distribuidas aleatoriamente en una circunferencia de radio `R=1`. Se presenta la solución al problema planteado usando `struct` y `class` en `C++`. Ambos códigos permiten:
1. Generar la distribución aleatoria de partículas.
2. Inducir una perturbación en las posiciones.
3. Calcular la distancia máxima entre las partículas del sistema y cuáles partículas la presentan.
4. Asignar una fuerza con componentes aleatorias `(Fx,Fy)` a cada partícula.
5. Calcular la magnitud de la fuerza neta sobre el sistema.

Para compilar, incluya esta línea en la terminal:
```
g++ -std=c++17 -Wall filename.cpp -o filename.out
```
Para ejecutar, incluya esta línea en la terminal:
```
./filename.out
```
donde `filename` es el nombre del archivo que desea compilar.

Una vez ejecutado, en la terminal debería ver la salida correspondiente a cada inciso así:
1. Tabla con el índice y las posiciones `(x,y)` de cada partícula.
2. Tabla con el índice y las posiciones perturbadas `(x,y)` de cada partícula.
3. "La distancia máxima es `dmax` y se da entre las partículas `i` y `j`".
4. Tabla con el índice y las fuerzas `(Fx,Fy)` de cada partícula.
5. "La magnitud de la fuerza resultante es `Fnet`".
