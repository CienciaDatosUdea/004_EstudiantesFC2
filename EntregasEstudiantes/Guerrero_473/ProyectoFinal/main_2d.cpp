

#include "TISE_2D.h"
#include "TDSE_2D.h"
#include "wavepacket.h"  // Asegúrate de tener este header para run_cn_simulation_2d
#include <iostream>
#include <string>

int main() {
    std::cout << "=== SIMULACIÓN CUÁNTICA 2D ===" << std::endl;
    
    // Parámetros para simulación 2D
    int Nx = 10;
    int Ny = 10;
    double Lx = 1.0;
    double Ly = 1.0;
    double dt = 0.001;
    int nsteps = 100;
    
    // Parámetros del paquete gaussiano
    double x0 = 0.0 * Lx;
    double y0 = 0.0 * Ly;
    double kx0 = 0.5;
    double ky0 = 0.5;
    double sigma = 0.5;
    
    // Simulación TDSE -en wavepacket.h
    run_cn_simulation_2d(Nx, Ny, Lx, Ly, dt, nsteps, x0, y0, kx0, ky0, sigma);

    // Simulación TISE
    int Nfunc = 5;
    double potential_params[2] = {Lx, Ly};
   //-----------------------------------------------------------------------------

    // NOTA: La función run_tise_simulation_2d que tenemos NO devuelve eigenvectors/eigenvalues
    // por punteros, sino que los maneja internamente. Tenemos dos opciones:

    // OPCIÓN 1: Usar la versión que ya tenemos (maneja memoria internamente)
    std::cout << "\n=== EJECUTANDO TISE ===" << std::endl;
    run_tise_simulation_2d(Nx, Ny, Lx, Ly, Nfunc, potential_params);
    double* eigenvectors = nullptr;
    double* eigenvalues = nullptr;


    // Guardar resultados
    save_all_wavefunctions_2d(eigenvectors, eigenvalues, Nx, Ny, Nfunc, Lx, Ly, "resultados_2D/TISE");

    // OPCIÓN 2: Si quieres usar la versión que devuelve punteros, necesitamos implementarla
    // Por ahora comentaré esta parte ya que no está implementada en nuestro TISE_2D.cpp
    
    /*
    double* eigenvectors = nullptr;
    double* eigenvalues = nullptr;

    // Esta función necesitaría ser implementada de manera diferente
    run_tise_simulation_2d(Nx, Ny, Lx, Ly, Nfunc, potential_params, eigenvectors, eigenvalues);

    // Guardar resultados
    save_all_wavefunctions_2d(eigenvectors, eigenvalues, Nx, Ny, Nfunc, Lx, Ly, "resultados_2D/TISE");

    // Liberar memoria
    delete[] eigenvectors;
    delete[] eigenvalues;
    */

    return 0;
}