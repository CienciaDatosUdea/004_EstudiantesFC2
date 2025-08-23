#include "difusion_model.h"

// =================== Geometria ===================
Geometria::Geometria(int N_, double xmin_, double xmax_) {
    N = N_;
    xmin = xmin_;
    xmax = xmax_;
    dx = (xmax - xmin) / (N - 1);

    x.resize(N);
    for (int i = 0; i < N; i++) {
        x[i] = xmin + i * dx;
    }
}

// =================== Condiciones ===================
Condiciones::Condiciones(Geometria &G, double TL_, double TR_) {
    u.resize(G.N, 0.0);
    TL = TL_;
    TR = TR_;
}

void Condiciones::condicionesIniciales(double alpha) {
    double x0 = 0.5 * (u.size() - 1); // centro en índices
    for (size_t i = 0; i < u.size(); i++) {
        double pos = i; // índice como posición relativa
        u[i] = std::exp(-alpha * std::pow(pos - x0, 2));
    }
}

void Condiciones::condicionesFrontera(Geometria &G) {
    u[0] = TL;
    u[G.N - 1] = TR;
}

// =================== DiffusionSolver ===================
DiffusionSolver::DiffusionSolver(double D_, double dt_, double t_max_) {
    D = D_;
    dt = dt_;
    t_max = t_max_;
}

void DiffusionSolver::verificarEstabilidad(Geometria &G) {
    alpha = D * dt / (G.dx * G.dx);
    if (alpha > 0.5) {
        std::cerr << "⚠ Advertencia: Condición de estabilidad NO cumplida. Alpha = "
                  << alpha << " > 0.5" << std::endl;
    }
}

void DiffusionSolver::resolver(Geometria &G, Condiciones &C) {
    verificarEstabilidad(G);
    Nsteps = static_cast<int>(t_max / dt);

    std::vector<double> u_new(G.N);

    for (int step = 0; step < Nsteps; step++) {
        for (int i = 1; i < G.N - 1; i++) {
            u_new[i] = C.u[i] + alpha * (C.u[i + 1] - 2 * C.u[i] + C.u[i - 1]);
        }

        // Aplicar condiciones de frontera
        u_new[0] = C.TL;
        u_new[G.N - 1] = C.TR;

        C.u = u_new;
    }
}

void DiffusionSolver::exportarResultados(Geometria &G, Condiciones &C, const std::string &nombreArchivo) {
    std::ofstream file(nombreArchivo);
    for (int i = 0; i < G.N; i++) {
        file << G.x[i] << " " << C.u[i] << "\n";
    }
    file.close();
}
