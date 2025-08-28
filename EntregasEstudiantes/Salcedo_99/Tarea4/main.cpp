#include <iostream>
#include <cmath>
#include <functional>
#include "include/diffusion_model.h"

using namespace std;

int main() {
    // Parámetros dados
    double xmin = -1.0;
    double xmax = 1.0;
    int N = 101;
    double D = 0.1;
    double dt = 0.001;
    double tmax = 1.0;
    double TL = 0.0, TR = 0.0;
    double x0 = 0.0;
    double sigma = 0.2;
    std::string filename = "output.dat";

    // Geometría
    Geometry geom(xmin, xmax, N);

    // Campo de temperatura
    Temperature Tfield(geom);

    // Condición inicial: Gaussiana centrada en x0 con desviación sigma
    auto init_cond = [x0, sigma](double x) {
        return exp(-0.5 * pow((x - x0) / sigma, 2));
    };

    Tfield.applyInitialCondition(init_cond);
    Tfield.applyBoundaryCondition(TL, TR);

    // Solver
    DiffusionSolver solver(Tfield, D, dt, tmax, TL, TR, init_cond, filename);
    solver.run();

    cout << "Simulación finalizada. Resultados en " << filename << endl;
    return 0;
}
