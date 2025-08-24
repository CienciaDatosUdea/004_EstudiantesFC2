#include "wavepacket.h"
#include "TDSE.h"
#include "TISE.h"
#include <iostream>
using namespace std;

int main() {


    // ===============================
    // 3. Simulación TISE (pozo infinito)
    // ===============================
    cout << "=== Ejecutando simulación TISE ===" << endl;
    int n = 100;
    double R = 1.0;
    double L = 0.0;
    double *H = new double[n*n];
    double *eigenvectors = new double[n*n];
    double *eigenvalues = new double[n];

    create_Hamiltonian(n, L, R, H);
    jacobi_eigenvalues(H, n, 1e-10, eigenvectors, eigenvalues);

    cout << "Primeros 5 autovalores (E_n):" << endl;
    for(int i=0;i<5;i++)
        cout << "E["<<i+1<<"] = " << eigenvalues[i] << endl;

    normalize_and_save_wavefunctions(eigenvectors, eigenvalues, n, 5, L, R);

    delete[] H;
    delete[] eigenvectors;
    delete[] eigenvalues;

    // ===============================
    // 1. Simulación del paquete gaussiano (wavepacket)
    // ===============================
    cout << "=== Ejecutando simulación de wavepacket ===" << endl;
    run_simulation(
        5.0, 5.0, 0.25,   // x_0, k, sigma
        1.0, 1.0,         // h, m
        0.0, 20.0, 0.05,  // start_x, end_x, dx
        0.0, 1.0, 0.0025  // start_t, end_t, dt
    );

    // ===============================
    // 2. Simulación TDSE (Crank-Nicolson)
    // ===============================
    cout << "=== Ejecutando simulación TDSE ===" << endl;
    int N = 200;
    double l = 1.0;
    double dt = 0.0005;
    int nsteps = 50;
    double x0 = 0.3*l;
    double k0 = 50.0;
    double sigma = 0.05;

    run_cn_simulation(N, l, dt, nsteps, x0, k0, sigma);



    return 0;
}




