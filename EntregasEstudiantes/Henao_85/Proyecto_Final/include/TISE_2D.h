#ifndef TISE_2D_H
#define TISE_2D_H

#include <string>

// Función de potencial 2D
double potential_2d(double x, double y, double* params);

// Crear matriz Hamiltoniana 2D
void create_Hamiltonian_2d(int Nx, int Ny, double Lx, double Ly, 
                          double* H, double* params = nullptr);

// Algoritmo de Jacobi para matrices grandes (modificado para 2D)
void jacobi_eigenvalues_2d(double* A, int n, double tol, 
                          double* eigenvectors, double* eigenvalues);

// Normalizar y guardar funciones de onda 2D
void normalize_and_save_wavefunctions_2d(double* eigenvectors, double* eigenvalues,
                                        int Nx, int Ny, int Nfunc, 
                                        double Lx, double Ly);

// Función principal TISE 2D
void run_tise_simulation_2d(int Nx, int Ny, double Lx, double Ly, 
                           int Nfunc, double* potential_params = nullptr);

// Función alternativa TISE 2D
void run_tise_simulation_2d(
    int Nx, int Ny, double dx, double dy,
    double (*V)(double, double),
    int Nfunc,
    double*& eigenvectors,
    double*& eigenvalues,
    const std::string& output_folder);

// Guardar todas las funciones de onda
void save_all_wavefunctions_2d(
    double* eigenvectors,
    double* eigenvalues,
    int Nx, int Ny, int Nfunc,
    double Lx, double Ly,
    const std::string& folder_path);

#endif