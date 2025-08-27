#include "diffusion_solver.h"
#include <iostream>

int main() {
    // Parámetros de la malla
    int N = 101;
    double xmin = 0.0, xmax = 1.0;

    // Crear geometría
    Geometria geo(N, xmin, xmax);

    // Crear condiciones
    Condiciones cond(geo);

    // Condición inicial: gaussiana centrada en 0.5
    cond.condicionesIniciales(100.0, 0.5);

    // Solver con coef. de difusión D, paso dt y tiempo máximo
    double D = 0.01;
    double dt = 1e-4;
    double t_max = 0.05;
    DiffusionSolver solver(D, dt, t_max);

    // Condiciones de frontera
    double TL = 0.0;
    double TR = 0.0;

    // Resolver
    solver.resolverFTCS(cond, TL, TR);

    // Guardar resultado
    guardarResultado(geo, cond, "resultado.dat");

    std::cout << "✅ Simulación completada. Resultados guardados en resultado.dat\n";
    return 0;
}
