#include "..\include\Poisson3D.h"
#include <cmath>
#include <fstream>
#include <stdexcept>

Grid3D::Grid3D(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, 
               int nx, int ny, int nz)
    : xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax), zmin(zmin), zmax(zmax),
      nx(nx), ny(ny), nz(nz) {
    
    dx = (xmax - xmin) / (nx - 1);
    dy = (ymax - ymin) / (ny - 1);
    dz = (zmax - zmin) / (nz - 1);

    XYZ.resize(nx, std::vector<std::vector<double>>(ny, std::vector<double>(nz, 0.0)));

    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            for (int k = 0; k < nz; ++k) {
                XYZ[i][j][k] = xmin + i * dx;  // Solo coordenada x (para simplificar)
            }
        }
    }
}

PoissonSolver3D::PoissonSolver3D(Grid3D &grid, double rho, int max_iter, double tolerance)
    : grid(grid), max_iter(max_iter), tolerance(tolerance) {
    
    phi.resize(grid.nx, std::vector<std::vector<double>>(grid.ny, std::vector<double>(grid.nz, 0.0)));
    this->rho.resize(grid.nx, std::vector<std::vector<double>>(grid.ny, std::vector<double>(grid.nz, rho)));
}

void PoissonSolver3D::setBoundaryConditions() {
    // Condiciones de Dirichlet: phi = 0 en las fronteras
    for (int j = 0; j < grid.ny; ++j) {
        for (int k = 0; k < grid.nz; ++k) {
            phi[0][j][k] = 0.0;          // Frontera xmin
            phi[grid.nx-1][j][k] = 0.0;  // Frontera xmax
        }
    }
    for (int i = 0; i < grid.nx; ++i) {
        for (int k = 0; k < grid.nz; ++k) {
            phi[i][0][k] = 0.0;          // Frontera ymin
            phi[i][grid.ny-1][k] = 0.0;  // Frontera ymax
        }
    }
    for (int i = 0; i < grid.nx; ++i) {
        for (int j = 0; j < grid.ny; ++j) {
            phi[i][j][0] = 0.0;          // Frontera zmin
            phi[i][j][grid.nz-1] = 0.0;  // Frontera zmax
        }
    }
}

void PoissonSolver3D::solve() {
    double dx2 = grid.dx * grid.dx;
    double dy2 = grid.dy * grid.dy;
    double dz2 = grid.dz * grid.dz;
    double error;

    for (int iter = 0; iter < max_iter; ++iter) {
        error = 0.0;
        for (int i = 1; i < grid.nx - 1; ++i) {
            for (int j = 1; j < grid.ny - 1; ++j) {
                for (int k = 1; k < grid.nz - 1; ++k) {
                    double old_phi = phi[i][j][k];
                    phi[i][j][k] = (
                        (phi[i+1][j][k] + phi[i-1][j][k]) / dx2 +
                        (phi[i][j+1][k] + phi[i][j-1][k]) / dy2 +
                        (phi[i][j][k+1] + phi[i][j][k-1]) / dz2 -
                        rho[i][j][k]
                    ) / (2.0/dx2 + 2.0/dy2 + 2.0/dz2);

                    error += std::abs(phi[i][j][k] - old_phi);
                }
            }
        }
        setBoundaryConditions();
        if (error < tolerance) break;
    }
}

void PoissonSolver3D::writeVTK(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Error al abrir el archivo VTK.");

    file << "# vtk DataFile Version 3.0\n";
    file << "Poisson 3D Solution\nASCII\nDATASET STRUCTURED_GRID\n";
    file << "DIMENSIONS " << grid.nx << " " << grid.ny << " " << grid.nz << "\n";
    file << "POINTS " << grid.nx * grid.ny * grid.nz << " float\n";

    for (int k = 0; k < grid.nz; ++k) {
        for (int j = 0; j < grid.ny; ++j) {
            for (int i = 0; i < grid.nx; ++i) {
                file << grid.xmin + i * grid.dx << " " 
                     << grid.ymin + j * grid.dy << " " 
                     << grid.zmin + k * grid.dz << "\n";
            }
        }
    }

    file << "POINT_DATA " << grid.nx * grid.ny * grid.nz << "\n";
    file << "SCALARS phi float 1\nLOOKUP_TABLE default\n";
    for (int k = 0; k < grid.nz; ++k) {
        for (int j = 0; j < grid.ny; ++j) {
            for (int i = 0; i < grid.nx; ++i) {
                file << phi[i][j][k] << "\n";
            }
        }
    }
}