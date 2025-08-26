//Include de la ecuación idependiente del tiempo------------------------------------------

#include <fstream>

// Función de potencial------------
double InfiniteWell(double x, double *par);

// Construcción de la matriz Hamiltoniana usando diferencias finitas
void create_Hamiltonian(int n, double L, double R, double *H);

// Cálculo de autovalores/autovectores usando Jacobi
void jacobi_eigenvalues(double *A, int n, double tol, double *eigenvectors, double *eigenvalues);

// Normalizar y guardar las primeras Nfunc funciones de onda
void normalize_and_save_wavefunctions(double *eigenvectors, double *eigenvalues,
                                      int n, int Nfunc, double L, double R);

void  save_energies(double *eigenvalues, int Nfunc);                                    
