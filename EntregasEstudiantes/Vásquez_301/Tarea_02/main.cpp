#include <iostream>
#include "include/difusion_model.h" 

int main() {

    int N = 101;         // Número de nodos (puntos en la malla)
    double x_min = -5.0; // Límite izquierdo de la barra
    double x_max = 5.0;  // Límite derecho de la barra
    double D = 0.1;      // Coeficiente de difusión
    double t_max = 2.0;  // Tiempo total de la simulación
    double dt = 0.001;   // Paso de tiempo (pequeño para asegurar estabilidad)


    Geometria geometria(N, x_min, x_max);
    DiffusionSolver solver(geometria, D, dt, t_max);

    solver.resolver();
    solver.exportarSolucion("solucion_final.txt");

    return 0; 
}