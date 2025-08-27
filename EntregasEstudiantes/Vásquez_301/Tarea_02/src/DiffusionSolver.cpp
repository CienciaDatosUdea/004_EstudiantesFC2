#include "../include/difusion_model.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept> 

DiffusionSolver::DiffusionSolver(const Geometria& geometria, double coef_D, double paso_t, double t_max)
    : geo(geometria), D(coef_D), dt(paso_t)
{
    N_steps = static_cast<int>(t_max / dt);

    // Calcula el parámetro de estabilidad alpha
    alpha = D * dt / (geo.dx * geo.dx);

    // --- Verificación de Estabilidad (RF10) ---
    std::cout << "Parametro de estabilidad alpha = " << alpha << std::endl;
    if (alpha > 0.5) {
        std::cerr << "La simulacion es inestable (alpha > 0.5)." << std::endl;
        std::cerr << "Considere reducir dt o aumentar N para estabilizar." << std::endl;
    }

    u.resize(geo.N);
}


void DiffusionSolver::resolver() {
    aplicarCondicionInicial(u, geo.x);
    aplicarCondicionesDeFrontera(u, 0.0, 0.0); // Temperatura fija de 0 en los bordes

    std::vector<double> u_siguiente = u;

    for (int n = 0; n < N_steps; ++n) {
        for (int i = 1; i < geo.N - 1; ++i) {
            u_siguiente[i] = u[i] + alpha * (u[i+1] - 2.0 * u[i] + u[i-1]);
        }

        u = u_siguiente;

        aplicarCondicionesDeFrontera(u, 0.0, 0.0);
    }
}

void DiffusionSolver::exportarSolucion(const std::string& nombre_archivo) {
    std::ofstream archivo_salida(nombre_archivo);

    if (!archivo_salida.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de salida " << nombre_archivo << std::endl;
        return;
    }

    archivo_salida << std::fixed << std::setprecision(6);

    for (int i = 0; i < geo.N; ++i) {
        archivo_salida << geo.x[i] << "\t" << u[i] << std::endl;
    }

    archivo_salida.close();
}