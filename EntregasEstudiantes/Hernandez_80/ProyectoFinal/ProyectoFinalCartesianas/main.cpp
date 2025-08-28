#include "include\Poisson3D.h"
#include <iostream>

int main() {
    // Parámetros de la simulación
    int nx = 50, ny = 50, nz = 50;
    double xmin = 0.0, xmax = 1.0;
    double ymin = 0.0, ymax = 1.0;
    double zmin = 0.0, zmax = 1.0;
    double rho = -1.0;  // Fuente negativa (e.g., carga negativa)
    int max_iter = 1000;
    double tolerance = 1e-6;

    // Crear malla y solver
    Grid3D grid(xmin, xmax, ymin, ymax, zmin, zmax, nx, ny, nz);
    PoissonSolver3D solver(grid, rho, max_iter, tolerance);

    // Resolver y exportar
    solver.setBoundaryConditions();
    solver.solve();
    solver.writeVTK("poisson3d.vtk");

    std::cout << "Solución completada. Datos guardados en 'poisson3d.vtk'." << std::endl;
    return 0;
}