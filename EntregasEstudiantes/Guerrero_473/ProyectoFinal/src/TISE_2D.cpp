#include "TISE_2D.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

// Potencial 2D: Pozo infinito
double potential_2d(double x, double y, double* params) {
    if (params == nullptr) return 0.0;
    
    // Pozo infinito 2D
    if (x < 0 || x > params[0] || y < 0 || y > params[1]) {
        return 1e10; // Valor muy grande para paredes infinitas
    }
    return 0.0;
}

// Crear matriz Hamiltoniana 2D
void create_Hamiltonian_2d(int Nx, int Ny, double Lx, double Ly, 
                          double* H, double* params) {
    
    double dx = Lx / (Nx + 1);
    double dy = Ly / (Ny + 1);
    double coeff_x = 1.0 / (2.0 * dx * dx);
    double coeff_y = 1.0 / (2.0 * dy * dy);
    
    int total_points = Nx * Ny;
    
    // Inicializar matriz a cero
    for (int i = 0; i < total_points * total_points; i++) {
        H[i] = 0.0;
    }
    
    // Llenar la matriz Hamiltoniana
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            int idx = i * Ny + j;
            double x = (i + 1) * dx;
            double y = (j + 1) * dy;
            
            // Término diagonal
            H[idx * total_points + idx] = 2.0 * (coeff_x + coeff_y) + 
                                        potential_2d(x, y, params);
            
            // Vecinos en x
            if (i > 0) {
                int idx_left = (i - 1) * Ny + j;
                H[idx * total_points + idx_left] = -coeff_x;
            }
            
            if (i < Nx - 1) {
                int idx_right = (i + 1) * Ny + j;
                H[idx * total_points + idx_right] = -coeff_x;
            }
            
            // Vecinos en y
            if (j > 0) {
                int idx_down = i * Ny + (j - 1);
                H[idx * total_points + idx_down] = -coeff_y;
            }
            
            if (j < Ny - 1) {
                int idx_up = i * Ny + (j + 1);
                H[idx * total_points + idx_up] = -coeff_y;
            }
        }
    }
}

// Jacobi modificado para matrices grandes
void jacobi_eigenvalues_2d(double* A, int n, double tol, 
                          double* eigenvectors, double* eigenvalues) {
    
    // Inicializar matriz de autovectores como identidad
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            eigenvectors[i * n + j] = (i == j) ? 1.0 : 0.0;
        }
    }
    
    double* B = new double[n * n];
    for (int i = 0; i < n * n; i++) {
        B[i] = A[i];
    }
    
    double error = tol + 1.0;
    int max_iter = 1000;
    int iter = 0;
    
    while (error > tol && iter < max_iter) {
        error = 0.0;
        
        for (int p = 0; p < n - 1; p++) {
            for (int q = p + 1; q < n; q++) {
                if (fabs(B[p * n + q]) > 1e-12) {
                    error = std::max(error, fabs(B[p * n + q]));
                    
                    double phi = 0.5 * atan2(2.0 * B[p * n + q], 
                                           B[q * n + q] - B[p * n + p]);
                    double c = cos(phi), s = sin(phi);
                    
                    // Actualizar matriz B
                    for (int i = 0; i < n; i++) {
                        if (i != p && i != q) {
                            double B_ip = c * B[i * n + p] - s * B[i * n + q];
                            double B_iq = s * B[i * n + p] + c * B[i * n + q];
                            B[i * n + p] = B_ip;
                            B[p * n + i] = B_ip;
                            B[i * n + q] = B_iq;
                            B[q * n + i] = B_iq;
                        }
                    }
                    
                    double B_pp = c * c * B[p * n + p] - 2.0 * s * c * B[p * n + q] + s * s * B[q * n + q];
                    double B_qq = s * s * B[p * n + p] + 2.0 * s * c * B[p * n + q] + c * c * B[q * n + q];
                    B[p * n + p] = B_pp;
                    B[q * n + q] = B_qq;
                    B[p * n + q] = 0.0;
                    B[q * n + p] = 0.0;
                    
                    // Actualizar autovectores
                    for (int i = 0; i < n; i++) {
                        double V_ip = c * eigenvectors[i * n + p] - s * eigenvectors[i * n + q];
                        double V_iq = s * eigenvectors[i * n + p] + c * eigenvectors[i * n + q];
                        eigenvectors[i * n + p] = V_ip;
                        eigenvectors[i * n + q] = V_iq;
                    }
                }
            }
        }
        iter++;
    }
    
    // Extraer autovalores
    for (int i = 0; i < n; i++) {
        eigenvalues[i] = B[i * n + i];
    }
    
    delete[] B;
}

void normalize_and_save_wavefunctions_2d(double* eigenvectors, double* eigenvalues,
                                        int Nx, int Ny, int Nfunc, 
                                        double Lx, double Ly) {
    
    double dx = Lx / (Nx + 1);
    double dy = Ly / (Ny + 1);
    int total_points = Nx * Ny;
    
    // Normalizar cada autovector
    for (int k = 0; k < Nfunc; k++) {
        double norm = 0.0;
        for (int i = 0; i < total_points; i++) {
            double psi_val = eigenvectors[i * total_points + k];
            norm += psi_val * psi_val;
        }
        norm = sqrt(norm * dx * dy);
        
        if (norm > 1e-12) {
            for (int i = 0; i < total_points; i++) {
                eigenvectors[i * total_points + k] /= norm;
            }
        }
    }
    
    // Crear carpeta de resultados
    fs::create_directories("resultados_2D/TISE");

    // Guardar energías
    std::ofstream energy_file("resultados_2D/TISE/energies.txt");
    for (int k = 0; k < Nfunc; k++) {
        energy_file << k << " " << eigenvalues[k] << "\n";
    }
    energy_file.close();
    
    // Guardar funciones de onda individuales
    for (int k = 0; k < Nfunc; k++) {
        std::string filename = "resultados_2D/TISE/funcion_onda_" + std::to_string(k) + ".txt";
        std::ofstream wave_file(filename);
        
        for (int i = 0; i < Nx; i++) {
            double x = (i + 1) * dx;
            for (int j = 0; j < Ny; j++) {
                double y = (j + 1) * dy;
                int idx = i * Ny + j;
                double psi_val = eigenvectors[idx * total_points + k];
                wave_file << x << " " << y << " " << psi_val << "\n";
            }
            wave_file << "\n";
        }
        wave_file.close();
    }
    
    std::cout << "Funciones de onda 2D guardadas en resultados_2D/TISE/" << std::endl;
}

// Función principal TISE 2D
void run_tise_simulation_2d(int Nx, int Ny, double Lx, double Ly, 
                           int Nfunc, double* potential_params) {
    
    std::cout << "=== INICIANDO TISE 2D ===" << std::endl;
    std::cout << "Malla: " << Nx << " x " << Ny << " puntos" << std::endl;
    
    int total_points = Nx * Ny;
    
    // Reservar memoria
    double* H = new double[total_points * total_points];
    double* eigenvectors = new double[total_points * total_points];
    double* eigenvalues = new double[total_points];
    
    // Crear Hamiltoniano
    std::cout << "Construyendo Hamiltoniano 2D..." << std::endl;
    create_Hamiltonian_2d(Nx, Ny, Lx, Ly, H, potential_params);
    
    // Calcular autovalores
    std::cout << "Calculando autovalores..." << std::endl;
    jacobi_eigenvalues_2d(H, total_points, 1e-8, eigenvectors, eigenvalues);
    
    // Guardar resultados
    std::cout << "Guardando resultados..." << std::endl;
    normalize_and_save_wavefunctions_2d(eigenvectors, eigenvalues, 
                                       Nx, Ny, Nfunc, Lx, Ly);
    
    // Mostrar energías
    std::cout << "\n=== ENERGÍAS CALCULADAS ===" << std::endl;
    for (int k = 0; k < std::min(10, Nfunc); k++) {
        std::cout << "E[" << k << "] = " << eigenvalues[k] << std::endl;
    }
    
    // Liberar memoria
    delete[] H;
    delete[] eigenvectors;
    delete[] eigenvalues;
    
    std::cout << "=== TISE 2D COMPLETADO ===" << std::endl;
}

void save_all_wavefunctions_2d(
    double* eigenvectors,
    double* eigenvalues,
    int Nx, int Ny, int Nfunc,
    double Lx, double Ly,
    const std::string& folder_path) {
    
    // Crear directorio
    fs::create_directories(folder_path);
    
    double dx = Lx / (Nx + 1);
    double dy = Ly / (Ny + 1);
    int total_points = Nx * Ny;
    
    std::string filename = folder_path + "/todas_funciones_onda.txt";
    std::ofstream file(filename);
    
    for (int k = 0; k < Nfunc; k++) {
        double energy = eigenvalues[k];
        
        for (int i = 0; i < Nx; i++) {
            double x = (i + 1) * dx;
            for (int j = 0; j < Ny; j++) {
                double y = (j + 1) * dy;
                int idx = i * Ny + j;
                double psi_val = eigenvectors[idx * total_points + k];
                
                file << k << " " << x << " " << y << " " << psi_val << " " << energy << "\n";
            }
        }
        file << "\n";
    }
    
    file.close();
    std::cout << "Todas las funciones de onda guardadas en: " << filename << std::endl;
}