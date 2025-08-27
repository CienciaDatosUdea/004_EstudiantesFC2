#include "../include/PoissonCylindrical.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

CylindricalGrid::CylindricalGrid(double r_max, double z_max, int nr, int nz)
    : r_max(r_max), z_max(z_max), nr(nr), nz(nz) {
    dr = r_max / (nr - 1);
    dz = z_max / (nz - 1);
}

PoissonSolverCylindrical::PoissonSolverCylindrical(CylindricalGrid &grid, 
                                                 double rho_value, 
                                                 int max_iter, 
                                                 double tol)
    : grid(grid), max_iter(max_iter), tolerance(tol) {
    
    phi.resize(grid.nr, std::vector<double>(grid.nz, 0.0));
    rho.resize(grid.nr, std::vector<double>(grid.nz, rho_value));
}

void PoissonSolverCylindrical::setBoundaryConditions() {
    // Condiciones de frontera cilíndricas
    for (int iz = 0; iz < grid.nz; ++iz) {
        // Eje z (r=0) - condición de simetría
        phi[0][iz] = phi[1][iz];  // ∂φ/∂r = 0 en r=0
        
        // Pared exterior (r = r_max)
        phi[grid.nr-1][iz] = 0.0;
    }
    
    for (int ir = 0; ir < grid.nr; ++ir) {
        // Tapas del cilindro (z=0 y z=z_max)
        phi[ir][0] = 0.0;
        phi[ir][grid.nz-1] = 0.0;
    }
}

void PoissonSolverCylindrical::solve() {
    double dr2 = grid.dr * grid.dr;
    double dz2 = grid.dz * grid.dz;
    
    for (int iter = 0; iter < max_iter; ++iter) {
        double max_error = 0.0;
        
        for (int ir = 1; ir < grid.nr - 1; ++ir) {
            double r = ir * grid.dr;
            
            for (int iz = 1; iz < grid.nz - 1; ++iz) {
                double old_phi = phi[ir][iz];
                
                // Discretización en coordenadas cilíndricas (simetría axial)
                phi[ir][iz] = (
                    (1.0 + 1.0/(2*ir)) * phi[ir+1][iz] + 
                    (1.0 - 1.0/(2*ir)) * phi[ir-1][iz] +
                    (dr2/dz2) * (phi[ir][iz+1] + phi[ir][iz-1]) -
                    dr2 * rho[ir][iz]
                ) / (2.0 + 2.0 * dr2/dz2);
                
                max_error = std::max(max_error, std::abs(phi[ir][iz] - old_phi));
            }
        }
        
        setBoundaryConditions();
        if (max_error < tolerance) break;
    }
}

void PoissonSolverCylindrical::writeVTK(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error al abrir archivo VTK: " + filename);
    }

    // Convertir coordenadas cilíndricas a cartesianas para VTK
    int n_points = grid.nr * grid.nz;

    file << "# vtk DataFile Version 3.0\n";
    file << "Poisson Cylindrical Solution\nASCII\n";
    file << "DATASET STRUCTURED_GRID\n";
    file << "DIMENSIONS " << grid.nr << " 1 " << grid.nz << "\n";
    file << "POINTS " << n_points << " float\n";

    // Escribir puntos en coordenadas cartesianas
    for (int iz = 0; iz < grid.nz; ++iz) {
        double z = iz * grid.dz;
        for (int ir = 0; ir < grid.nr; ++ir) {
            double r = ir * grid.dr;
            double x = r;  // Para θ=0 (simetría axial)
            double y = 0.0;
            file << x << " " << y << " " << z << "\n";
        }
    }

    file << "POINT_DATA " << n_points << "\n";
    file << "SCALARS phi float 1\n";
    file << "LOOKUP_TABLE default\n";

    // Escribir datos de potencial
    for (int iz = 0; iz < grid.nz; ++iz) {
        for (int ir = 0; ir < grid.nr; ++ir) {
            file << phi[ir][iz] << "\n";
        }
    }

    file.close();
    std::cout << "Archivo VTK guardado: " << filename << std::endl;
}