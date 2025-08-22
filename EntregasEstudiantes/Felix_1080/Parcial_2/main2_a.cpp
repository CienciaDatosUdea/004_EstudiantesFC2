#include "fdtd.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>

int main() {
    // Parámetros
    const int Nz = 200;
    const double dz = 1.0;
    const double beta = 0.5 * 0.99;  // estable si beta <= 0.5 (c=1)
    const int nt = 2000;
    const int save_every = 5;
    const char* outfile = "output/Punto2a/em_all_dirichlet.txt";

    std::cout << "  Simulacion FDTD 1D — 1.2(a)       \n";
    std::cout << "  Frontera: Dirichlet (E=H=0)       \n";
    std::cout << "Nz         : " << Nz << "\n";
    std::cout << "dz         : " << dz << "\n";
    std::cout << "beta       : " << beta << "\n";
    std::cout << "dt         : " << (beta*dz) << "\n";
    std::cout << "nt         : " << nt << "\n";
    std::cout << "save_every : " << save_every << "\n";
    std::cout << "Archivo    : " << outfile << "\n";

    // Simulación
    Grid1D G(Nz, dz);
    FDTD1D sim(G, beta, BoundaryType::DirichletZero);  // <-- enum correcto

    sim.init_sine(0.1, 100.0);

    std::ofstream f(outfile);
    if (!f.is_open()) {
        std::cerr << "No se pudo abrir " << outfile << "\n";
        return 1;
    }

    const double dt = beta * dz;
    sim.write_all(f, 0.0);  // t=0

    for (int n = 1; n <= nt; ++n) {
        sim.step();
        if (n % save_every == 0) {
            sim.write_all(f, n * dt);
        }
    }
    f.close();

    std::cout << "Simulacion completada.\n";
    std::cout << "Resultados guardados en: " << outfile << "\n";
    std::cout << "====================================\n";
    return 0;
}
