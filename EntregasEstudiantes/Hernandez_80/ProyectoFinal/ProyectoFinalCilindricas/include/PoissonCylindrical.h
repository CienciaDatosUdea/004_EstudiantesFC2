#ifndef POISSON_CYLINDRICAL_H
#define POISSON_CYLINDRICAL_H

#include <vector>
#include <cmath>
#include <string>

class CylindricalGrid {
public:
    CylindricalGrid(double r_max, double z_max, int nr, int nz);
    
    double dr, dz;
    double r_max, z_max;
    int nr, nz;
};

class PoissonSolverCylindrical {
public:
    PoissonSolverCylindrical(CylindricalGrid &grid, double rho, int max_iter, double tol);
    
    void solve();
    void setBoundaryConditions();
    void writeVTK(const std::string &filename);

    CylindricalGrid &grid;
    std::vector<std::vector<double>> phi;  // phi[r][z]
    std::vector<std::vector<double>> rho;  // rho[r][z]

private:
    double tolerance;
    int max_iter;
};

#endif