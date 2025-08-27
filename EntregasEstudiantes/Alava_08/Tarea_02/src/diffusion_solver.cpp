#include "diffusion_solver.h"
#include <fstream>
#include <cmath>

// ==========================================================
// Implementación de Geometria
// ==========================================================
Geometria::Geometria(int N_, double xmin_, double xmax_)
    : N(N_), xmin(xmin_), xmax(xmax_) 
{
    dx = (xmax - xmin) / (N - 1);
    x.resize(N);
    for (int i = 0; i < N; i++) {
        x[i] = xmin + i * dx;
    }
}

// ==========================================================
// Implementación de Condiciones
// ==========================================================
Condiciones::Condiciones(Geometria &geo) : G(geo) {
    u.resize(G.N, 0.0);
}

void Condiciones::condicionesIniciales(double alpha, double x0) {
    for (int i = 0; i < G.N; i++) {
        double xi = G.x[i];
        u[i] = std::exp(-alpha * (xi - x0) * (xi - x0));
    }
}

void Condiciones::condicionesFrontera(double TL, double TR) {
    if (!u.empty()) {
        u.front() = TL;
        u.back()  = TR;
    }
}

// ==========================================================
// Implementación de DiffusionSolver
// ==========================================================
DiffusionSolver::DiffusionSolver(double D_, double dt_, double t_max_)
    : D(D_), dt(dt_), t_max(t_max_) {}

bool DiffusionSolver::verificarEstabilidad(double dx) const {
    return (D * dt / (dx * dx)) <= 0.5;
}

void DiffusionSolver::resolverFTCS(Condiciones &cond, double TL, double TR) {
    Geometria &G = cond.G;
    std::vector<double> u_new(G.N, 0.0);
    double r = D * dt / (G.dx * G.dx);

    if (!verificarEstabilidad(G.dx)) {
        std::cerr << "⚠️ Advertencia: el esquema FTCS es inestable con los parámetros dados.\n";
    }

    for (double t = 0; t < t_max; t += dt) {
        cond.condicionesFrontera(TL, TR);

        for (int i = 1; i < G.N - 1; i++) {
            u_new[i] = cond.u[i] + r * (cond.u[i+1] - 2*cond.u[i] + cond.u[i-1]);
        }

        u_new.front() = TL;
        u_new.back()  = TR;

        cond.u = u_new;
    }
}

// ==========================================================
// Guardar resultados en archivo de texto
// ==========================================================
void guardarResultado(const Geometria &geo,
                      const Condiciones &cond,
                      const std::string &nombreArchivo) 
{
    std::ofstream file(nombreArchivo);
    if (!file) {
        std::cerr << "❌ Error: no se pudo abrir el archivo " << nombreArchivo << "\n";
        return;
    }

    for (int i = 0; i < geo.N; i++) {
        file << geo.x[i] << " " << cond.u[i] << "\n";
    }
}

