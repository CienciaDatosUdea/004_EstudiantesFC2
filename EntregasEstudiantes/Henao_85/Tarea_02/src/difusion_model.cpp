#include "difusion_model.h"
#include <cmath>
#include <fstream>
#include <iostream>

// N: Número de nodos, xmin: límite inferior, xmax: límite superior
Geometria::Geometria(int N_, double xmin_, double xmax_)
    : N(N_), xmin(xmin_), xmax(xmax_) {
    x.resize(N);
    dx = (xmax - xmin) / (N - 1);
    for (int i = 0; i < N; i++) {
        x[i] = xmin + i * dx;
    }
}


Condiciones::Condiciones(Geometria &G_)
    : G(G_), u(G_.N, 0.0) {}

 
// Condición inicial gaussiana u(x, 0) = exp(-α (x - x₀)²)

void Condiciones::condicionesIniciales(double alpha, double x0) {
    for (int i = 0; i < G.N; i++) {
        double dx_val = G.x[i] - x0;
        u[i] = std::exp(-alpha * dx_val * dx_val);
    }
}

// Condiciones de frontera Dirichlet
// u(0, t) = TL y u(L, t) = TR

void Condiciones::condicionesFrontera(double TL, double TR) {
    u[0] = TL;
    u[G.N - 1] = TR;
}


DiffusionSolver::DiffusionSolver(double D_, double dt_, double t_max_)
    : D(D_), dt(dt_), t_max(t_max_) {}

bool DiffusionSolver::verificarEstabilidad(double dx) const {
    double alpha = D * dt / (dx * dx);
    if (alpha > 0.5) {
        std::cerr << "alpha = " << alpha << " > 0.5 (posible inestabilidad)\n";
        return false;
    }
    return true;
}

// Resolver usando el método FTCS (Forward Time Centered Space)
// u[i] = u[i] + α (u[i+1] - 2 * u[i] + u[i-1])
// donde α = D * dt / dx²
void DiffusionSolver::resolverFTCS(Condiciones &cond, double TL, double TR) {
    int Nsteps = static_cast<int>(t_max / dt);
    double dx = cond.G.dx;
    double alpha = D * dt / (dx * dx);
    std::vector<double> u_new(cond.G.N, 0.0);

    for (int step = 0; step < Nsteps; step++) {
        for (int i = 1; i < cond.G.N - 1; i++) {
            u_new[i] = cond.u[i] + alpha * (cond.u[i+1] - 2.0 * cond.u[i] + cond.u[i-1]);
        }
        cond.condicionesFrontera(TL, TR);
        u_new[0] = TL;
        u_new[cond.G.N - 1] = TR;
        cond.u.swap(u_new);
    }
}


void guardarResultado(const Geometria &geo, const Condiciones &cond, const std::string &nombreArchivo) {
    std::ofstream file(nombreArchivo);
    for (int i = 0; i < geo.N; i++) {
        file << geo.x[i] << " " << cond.u[i] << "\n";
    }
    file.close();
}


