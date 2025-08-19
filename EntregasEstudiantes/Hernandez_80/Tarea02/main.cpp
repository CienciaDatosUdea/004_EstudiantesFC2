#include "difusion_model.h"

int main() {
    // Parámetros del dominio
    int N = 50;
    double xmin = 0.0, xmax = 1.0;

    // Crear geometría
    Geometria G(N, xmin, xmax);

    // Condiciones iniciales y de frontera
    double TL = 0.0, TR = 0.0;
    Condiciones C(G, TL, TR);
    C.condicionesIniciales(0.02); // α para la gaussiana
    C.condicionesFrontera(G);

    // Solver de difusión
    double D = 0.1, dt = 0.0005, t_max = 0.1;
    DiffusionSolver solver(D, dt, t_max);
    solver.resolver(G, C);

    // Exportar resultados
    solver.exportarResultados(G, C, "solucion_final.txt");

    std::cout << "Simulación finalizada. Resultados en 'solucion_final.txt'\n";
    return 0;
}
