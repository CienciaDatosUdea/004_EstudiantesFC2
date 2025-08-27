#ifndef POISSON3D_H
#define POISSON3D_H

#include <vector>
#include <string>

class Grid3D {
public:
    Grid3D(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, 
           int nx, int ny, int nz);
    
    double dx, dy, dz;
    double xmin, xmax, ymin, ymax, zmin, zmax;
    int nx, ny, nz;
    std::vector<std::vector<std::vector<double>>> XYZ;  // Coordenadas de los nodos
};

class PoissonSolver3D {
public:
    PoissonSolver3D(Grid3D &grid, double rho, int max_iter, double tolerance);
    
    void solve();
    void setBoundaryConditions();
    void writeVTK(const std::string &filename);

    Grid3D &grid;
    std::vector<std::vector<std::vector<double>>> phi;  // Solución (campo escalar)
    std::vector<std::vector<std::vector<double>>> rho;  // Densidad de carga/fuente

private:
    double tolerance;
    int max_iter;
};

#endif