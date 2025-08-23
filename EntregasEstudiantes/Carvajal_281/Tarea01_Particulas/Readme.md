### Tarea 01: Implementación Simulación de partículas distribuidas en una circunferencia 

El presente código presenta dos formas de simular un sistema de N partículas distribuidas aleatoriamente sobre una circunferencia y que realiza las siguientes operaciones fisicas: 

- Inicialización de partículas dispuestas aleatoriamente sobre una circunferencia unitaria
- Perturbación aleatoria 
- Cálculo de distancia máxima 
- Asignación de fuerzas 
- Cálculo de la fuerza total  

Para compilar: Debe tener un compilador compatible con C++17.
Acceda a la terminal con ctrl +Alt + T, ubiquese en la carpeta que contenga los archivos y ejecute el siguiente comando: 

	g++ -std=c++17 -Wall programa.cpp -o programa.out (cambie el nombre programa por los nombres de las carpetas Tarea01_Clases o estructuras según el caso)

después, ejecute: 

	./programa.out 
	
El programa ejecutará automaticamente el resultado obtenido para las operaciones físicas dadas en un conjunto de N=10 partículas. 

La salída debe verse de la siguiente manera: 

La partícula 0 esta en posición: (x,y)=(-0.671502, 0.639754) y tiene una fuerza: (0.451629, 0.926146) asociada 
La partícula 1 esta en posición: (x,y)=(0.405569, 0.892398) y tiene una fuerza: (0.274187, 0.233204) asociada 
...

Distancia máxima entre partículas: 2.11571
Magnitud de la fuerza total: 7.32493
