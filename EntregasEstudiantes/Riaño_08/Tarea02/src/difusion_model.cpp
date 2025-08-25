#include "difusion_model.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

// Implementación de la clase Geometria
Geometria::Geometria(int N_, double xmin_, double xmax_)
    : N(N_), xmin(xmin_), xmax(xmax_) {
    if (N <= 1) {
        throw std::invalid_argument("El número de nodos N debe ser mayor que 1.");
    }
    dx = (xmax - xmin) / (N - 1);
    x.resize(N);
    for (int i = 0; i < N; ++i) {
        x[i] = xmin + i * dx;
    }
}

// Implementación de la clase Condiciones
Condiciones::Condiciones(Geometria& G_)
    : G(G_), u(G_.N, 0.0) {}

void Condiciones::condicionesIniciales() {
    double x0 = (G.xmin + G.xmax) / 2.0; // Centro del dominio
    double sigma = (G.xmax - G.xmin) / 8.0; // Desviación estándar para la Gaussiana
    double factor = 1.0 / (2.0 * sigma * sigma);
    for (int i = 0; i < G.N; ++i) {
        u[i] = exp(-factor * (G.x[i] - x0) * (G.x[i] - x0));
    }
}

void Condiciones::condicionesFrontera(double TL, double TR) {
    u[0] = TL;
    u[G.N - 1] = TR;
}

// Implementación de la clase DiffusionSolver
DiffusionSolver::DiffusionSolver(Geometria& G_, double D_, double dt_, double t_max_)
    : G(G_), D(D_), dt(dt_), t_max(t_max_) {
    if (dt_ <= 0 || t_max_ <= 0) {
        throw std::invalid_argument("dt y t_max deben ser valores positivos.");
    }
    alpha = D * dt / (G.dx * G.dx);
    Nsteps = static_cast<int>(t_max / dt);
}

void DiffusionSolver::verificarEstabilidad() {
    if (alpha > 0.5 + EPSILON) {
        std::cerr << "ADVERTENCIA: La condición de estabilidad no se cumple (alpha > 0.5)." << std::endl;
        std::cerr << "Alpha = " << alpha << ". Se recomienda disminuir dt o D, o aumentar dx." << std::endl;
    }
}

void DiffusionSolver::evolucionTemporal(Condiciones& C, double TL, double TR) {
    // Verificar estabilidad antes de la simulación
    verificarEstabilidad();

    // Copia del vector u para los cálculos
    std::vector<double> u_n = C.u;
    
    // Ciclo de evolución temporal
    for (int n = 0; n < Nsteps; ++n) {
        // Recorrer los nodos internos para el cálculo FTCS
        for (int i = 1; i < G.N - 1; ++i) {
            C.u[i] = u_n[i] + alpha * (u_n[i + 1] - 2 * u_n[i] + u_n[i - 1]);
        }
        
        // Re-aplicar condiciones de frontera en cada paso
        C.condicionesFrontera(TL, TR);
        
        // Actualizar el vector u_n para el siguiente paso de tiempo
        u_n = C.u;
    }
}
