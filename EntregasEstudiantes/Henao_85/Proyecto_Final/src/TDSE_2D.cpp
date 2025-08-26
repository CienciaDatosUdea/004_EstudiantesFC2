
#include "TDSE_2D.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem>

const double hbar = 1.0;
const double m = 1.0;

// Inicializar paquete gaussiano 2D
std::vector<std::vector<cdouble>> init_psi_2d(int Nx, int Ny, double dx, double dy,
                                             double x0, double y0, 
                                             double kx0, double ky0, double sigma) {
    
    std::vector<std::vector<cdouble>> psi(Nx, std::vector<cdouble>(Ny));
    double norm_factor = 1.0 / (sqrt(2 * M_PI) * sigma);
    
    for (int i = 0; i < Nx; i++) {
        double x = (i + 1) * dx;
        for (int j = 0; j < Ny; j++) {
            double y = (j + 1) * dy;
            double gauss = exp(-((x-x0)*(x-x0) + (y-y0)*(y-y0)) / (2*sigma*sigma));
            psi[i][j] = norm_factor * gauss * exp(cdouble(0, kx0*x + ky0*y));
        }
    }
    
    // Normalización
    double norm = 0.0;
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            norm += std::norm(psi[i][j]) * dx * dy;
        }
    }
    
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            psi[i][j] /= sqrt(norm);
        }
    }
    
    return psi;
}

// Algoritmo de Thomas para complejos
void thomas_tridiag_1d(const std::vector<cdouble>& a, const std::vector<cdouble>& b,
                       const std::vector<cdouble>& c, const std::vector<cdouble>& d,
                       std::vector<cdouble>& x) {
    
    int n = b.size();
    std::vector<cdouble> c_prime(n);
    std::vector<cdouble> d_prime(n);
    
    c_prime[0] = c[0] / b[0];
    d_prime[0] = d[0] / b[0];
    
    for (int i = 1; i < n; i++) {
        cdouble denom = b[i] - a[i] * c_prime[i-1];
        c_prime[i] = c[i] / denom;
        d_prime[i] = (d[i] - a[i] * d_prime[i-1]) / denom;
    }
    
    x[n-1] = d_prime[n-1];
    for (int i = n-2; i >= 0; i--) {
        x[i] = d_prime[i] - c_prime[i] * x[i+1];
    }
}

// Paso ADI para evolución 2D
void adi_step_2d(std::vector<std::vector<cdouble>>& psi, double dt, 
                double dx, double dy, int Nx, int Ny) {
    
    cdouble alpha_x = cdouble(0, dt * hbar / (4.0 * m * dx * dx));
    cdouble alpha_y = cdouble(0, dt * hbar / (4.0 * m * dy * dy));
    
    // Vectores para el sistema tridiagonal
    std::vector<cdouble> a(Nx, -alpha_x);
    std::vector<cdouble> b(Nx, 1.0 + 2.0 * alpha_x);
    std::vector<cdouble> c(Nx, -alpha_x);
    std::vector<cdouble> d(Nx);
    
    // Primera mitad: implícito en x
    for (int j = 0; j < Ny; j++) {
        for (int i = 0; i < Nx; i++) {
            d[i] = psi[i][j] + alpha_y * (psi[i][(j-1+Ny)%Ny] - 2.0*psi[i][j] + psi[i][(j+1)%Ny]);
        }
        thomas_tridiag_1d(a, b, c, d, d);
        for (int i = 0; i < Nx; i++) {
            psi[i][j] = d[i];
        }
    }
    
    // Segunda mitad: implícito en y
    a.assign(Ny, -alpha_y);
    b.assign(Ny, 1.0 + 2.0 * alpha_y);
    c.assign(Ny, -alpha_y);
    
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            d[j] = psi[i][j] + alpha_x * (psi[(i-1+Nx)%Nx][j] - 2.0*psi[i][j] + psi[(i+1)%Nx][j]);
        }
        thomas_tridiag_1d(a, b, c, d, d);
        for (int j = 0; j < Ny; j++) {
            psi[i][j] = d[j];
        }
    }
}

// Guardar función de onda 2D
void save_wavefunction_2d(const std::vector<std::vector<cdouble>>& psi, 
                         int step, double dx, double dy) {
    
    std::filesystem::create_directory("resultados_2D/TDSE");
    
    std::ofstream file("resultados_2D/TDSE/wave_" + std::to_string(step) + ".txt");
    int Nx = psi.size();
    int Ny = psi[0].size();
    
    for (int i = 0; i < Nx; i++) {
        double x = (i + 1) * dx;
        for (int j = 0; j < Ny; j++) {
            double y = (j + 1) * dy;
            file << x << " " << y << " " << std::norm(psi[i][j]) << "\n";
        }
    }
    file.close();
}


// Función principal de simulación 2D
void run_cn_simulation_2d(int Nx, int Ny, double Lx, double Ly,
                         double dt, int nsteps, double x0, double y0,
                         double kx0, double ky0, double sigma) {
    
    double dx = Lx / (Nx + 1);
    double dy = Ly / (Ny + 1);
    
    std::cout << "Inicializando paquete gaussiano 2D..." << std::endl;
    auto psi = init_psi_2d(Nx, Ny, dx, dy, x0, y0, kx0, ky0, sigma);


    //Para guardar la evolucion temporarl 

    std::ofstream full_file("resultados_2D/TDSE/evolucion_completa.txt");
    
    std::cout << "Comenzando evolución temporal 2D..." << std::endl;
    for (int step = 0; step < nsteps; step++) {
        adi_step_2d(psi, dt, dx, dy, Nx, Ny);
        
        if (step % 10 == 0) {
            save_wavefunction_2d(psi, step, dx, dy);
            
            std::cout << "Paso " << step << "/" << nsteps << " completado" << std::endl;
        }
        save_full_evolution_2d(psi, step, dx, dy, full_file);
    }
    
    full_file.close();
    std::cout << "Simulación 2D completada. Resultados en resultados_2D/TDSE/" << std::endl;
}




void save_full_evolution_2d(const std::vector<std::vector<cdouble>>& psi, 
                            int step, double dx, double dy, std::ofstream& file) {
    int Nx = psi.size();
    int Ny = psi[0].size();
    
    for (int i = 0; i < Nx; i++) {
        double x = (i + 1) * dx;
        for (int j = 0; j < Ny; j++) {
            double y = (j + 1) * dy;
            file << step << " " << x << " " << y << " " << std::norm(psi[i][j]) << "\n";
        }
    }
}

