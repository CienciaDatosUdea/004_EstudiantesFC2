#include "fdtd.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdexcept>

int main() {
    // Parámetros base
    const int Nz = 200;
    const double dz = 1.0;
    const int nt = 1200;
    const int save_every = 5;

    // Conjunto de betas a probar (c=1 -> dt = beta*dz)
    const std::vector<double> betas = {0.20, 0.50, 0.75, 1, 1.05, 1.1}; // 0.60 viola CFL

    std::cout << "  Simulacion FDTD — 1.2(a)       \n";
    std::cout << "  Frontera: Dirichlet (E=H=0)       \n";
    std::cout << "Nz         : " << Nz << "\n";
    std::cout << "dz         : " << dz << "\n";
    std::cout << "nt         : " << nt << "\n";
    std::cout << "save_every : " << save_every << "\n";

    const std::string outdir = "output/Punto2b"; // asegurate de crear la carpeta

    // Etiquetas para nombrar los archivos
    const std::vector<std::string> etiquetas = {"beta1", "beta2", "beta3","beta4","beta5", "beta6"};

    for (size_t i = 0; i < betas.size(); ++i) {
        double beta = betas[i];
        Grid1D G(Nz, dz);

        // *** Frontera Dirichlet: E=H=0 en los bordes ***
        FDTD1D sim(G, beta, BoundaryType::DirichletZero);

        sim.init_sine(0.1, 100.0);

        // Nombre de archivo con etiqueta genérica
        std::ostringstream oss;
        oss << "Sim_Pa_" << etiquetas[i] << ".txt";
        const std::string outfile = outdir + "/" + oss.str();

        std::cout << "Caso: " << etiquetas[i]
                  << " (beta=" << beta
                  << ", dt=" << (beta * dz)
                  << ") -> archivo: " << outfile << "\n";

        std::ofstream f(outfile.c_str());
        if (!f.is_open()) {
            std::cerr << "No se pudo abrir " << outfile
                      << " (¿existe la carpeta '" << outdir << "'?)\n";
            continue;
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

        std::cout << "Estado: "
                  << (beta <= 0.5 ? "estable (CFL OK)" : "INestable (CFL violada)")
                  << "\n";
        std::cout << "Guardado en: " << outfile << "\n";
        std::cout << "------------------------------------\n";
    }

    std::cout << "Estudio completado.\n";
    std::cout << "====================================\n";
    return 0;
}
