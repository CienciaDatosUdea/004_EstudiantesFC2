#include "fdtd.h"
#include <iostream>

int main() {
    const int    N      = 200;      // nodos Ex
    const int    Nsteps = 150;      // pasos de tiempo
    const double dz     = 1.0;      // paso espacial (unidades arbitrarias)
    const double c      = 1.0;
    const double dt     = 0.1 * dz / c; // Courant seguro en 1D: dt <= dz/c

    // Condiciones periódicas
    {
        FDTD1D_Yee sim_periodic(N, Nsteps, dz, dt, BCType::PERIODIC);
        sim_periodic.init_sine(0.1, 50);   // amplitud y longitud de onda en nodos
        sim_periodic.run("output/periodic");
        std::cout << "[OK] Simulación periódica en carpeta output/periodic\n";
    }

    // Condiciones de Dirichlet 
    {
        FDTD1D_Yee sim_dirichlet(N, Nsteps, dz, dt, BCType::DIRICHLET);
        sim_dirichlet.init_sine(0.1, 50);
        sim_dirichlet.run("output/dirichlet");
        std::cout << "[OK] Simulación Dirichlet en carpeta output/dirichlet\n";
    }

    return 0;
}










