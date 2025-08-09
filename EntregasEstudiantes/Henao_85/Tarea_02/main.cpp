#include <iostream>
#include "difusion_model.h"

int main() {
   
    int N = 100;             // número de nodos
    double xmin = 0.0;
    double xmax = 1.0;
    double D = 0.1;         // coeficiente de difusión
    double dt = 0.0005;     // paso de tiempo
    double t_max = 0.1;     // tiempo máximo
    double alpha_ini = 50.0; // parámetro gaussiana
    double x0 = 0.5;        // centro de la gaussiana
    double TL = 0.0;        // temperatura borde izquierdo
    double TR = 0.0;        // temperatura borde derecho

    
    Geometria geo(N, xmin, xmax);
    Condiciones cond(geo);
    DiffusionSolver solver(D, dt, t_max);

    
    if (!solver.verificarEstabilidad(geo.dx)) {
        std::cerr << "Ajusta dt, dx o D.\n";
        return -1;
    }

    
    cond.condicionesIniciales(alpha_ini, x0);
    cond.condicionesFrontera(TL, TR);

    
    solver.resolverFTCS(cond, TL, TR);

    
    guardarResultado(geo, cond, "solucion_final.txt");

    std::cout << "Resultados guardados en el documento solucion_final.txt\n";
    return 0;
}
