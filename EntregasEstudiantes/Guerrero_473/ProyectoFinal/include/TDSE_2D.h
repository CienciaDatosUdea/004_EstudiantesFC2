#ifndef TDSE_2D_H
#define TDSE_2D_H

#include <vector>
#include <complex>
using cdouble = std::complex<double>;

// Función para inicializar paquete gaussiano 2D
std::vector<std::vector<cdouble>> init_psi_2d(int Nx, int Ny, double dx, double dy,
                                             double x0, double y0, 
                                             double kx0, double ky0, double sigma);

// Algoritmo de Thomas para sistemas tridiagonales complejos
void thomas_tridiag_1d(const std::vector<cdouble>& a, const std::vector<cdouble>& b,
                       const std::vector<cdouble>& c, const std::vector<cdouble>& d,
                       std::vector<cdouble>& x);

// Paso ADI para evolución 2D
void adi_step_2d(std::vector<std::vector<cdouble>>& psi, double dt, 
                double dx, double dy, int Nx, int Ny);

// Función principal de simulación 2D
void run_cn_simulation_2d(int Nx, int Ny, double Lx, double Ly,
                         double dt, int nsteps, double x0, double y0,
                         double kx0, double ky0, double sigma);

// Guardar función de onda 2D
void save_wavefunction_2d(const std::vector<std::vector<cdouble>>& psi, 
                         int step, double dx, double dy);

void save_full_evolution_2d(const std::vector<std::vector<cdouble>>& psi, 
                            int step, double dx, double dy, std::ofstream& file);

void run_tise_simulation_2d(int Nx, int Ny, double Lx, double Ly, int Nfunc,
                            double** eigenvectors, double** eigenvalues);

void save_all_wavefunctions_2d(const double* eigenvectors, const double* eigenvalues,
                               int Nx, int Ny, int Nfunc, double Lx, double Ly);

                               

#endif


