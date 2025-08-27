#include "include/PoissonCylindrical.h"
#include <iostream>

int main() {
    // Cilindro de radio 1, altura 2
    CylindricalGrid grid(1.0, 2.0, 50, 100);
    
    // Densidad de carga constante
    PoissonSolverCylindrical solver(grid, -1.0, 1000, 1e-6);
    
    solver.setBoundaryConditions();
    solver.solve();
    solver.writeVTK("poisson_cylinder.vtk");
    
    std::cout << "Solución completada para geometría cilíndrica!" << std::endl;
    return 0;
}