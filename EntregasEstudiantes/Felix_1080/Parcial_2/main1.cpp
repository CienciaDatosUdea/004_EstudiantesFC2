#include "fdtd.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

int main() {
    // ===========================
    // Parámetros de la simulación
    // ===========================
    const int Nz = 200;        // número de nodos espaciales
    const double dz = 1.0;     // espaciamiento espacial
    const double beta = 0.5 * 0.99;  // beta <= 0.5 para estabilidad
    const int nt = 2000;       // pasos de tiempo totales
    const int save_every = 5; // intervalo de guardado de datos

    // Crear malla y simulador con condiciones periódicas
    Grid1D G(Nz, dz);
    FDTD1D sim(G, beta, BoundaryType::Periodic);

    // Calcular dt (con c normalizado a 1)
    const double dt = beta * dz;

    // ===========================
    // Resumen de parámetros
    // ===========================
    std::cout << "========================================\n";
    std::cout << "   Simulación FDTD 1D - Periodic BCs    \n";
    std::cout << "========================================\n";
    std::cout << "Número de nodos Nz : " << Nz << "\n";
    std::cout << "Espaciamiento dz   : " << dz << "\n";
    std::cout << "Beta (Courant)     : " << beta << "\n";
    std::cout << "Paso de tiempo dt  : " << dt << "\n";
    std::cout << "Pasos de tiempo nt : " << nt << "\n";
    std::cout << "Guardar cada       : " << save_every << " pasos\n";
    std::cout << "----------------------------------------\n";

    // Inicializar condición inicial: seno con amplitud 0.1 y periodo 100
    sim.init_sine(0.1, 100.0);

    // Archivo de salida
    std::ofstream fout("output/Punto1/em_all_periodic.txt");
    if (!fout.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo de salida.\n";
        return 1;
    }

    // Guardar estado inicial (t = 0)
    sim.write_all(fout, 0.0);

    // ===========================
    // Bucle temporal
    // ===========================
    for (int n = 1; n <= nt; ++n) {
        sim.step();
        if (n % save_every == 0) {
            sim.write_all(fout, n * dt);
        }
    }

    fout.close();

    // Mensaje final
    std::cout << "Simulación completada con éxito.\n";
    std::cout << "Resultados guardados en: output/em_all_periodic.txt\n";
    std::cout << "========================================\n";

    return 0;
}
