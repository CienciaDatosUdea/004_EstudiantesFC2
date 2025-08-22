#include "/Users/aleja/Desktop/UdeA/FC_II/004_EstudiantesFC2/EntregasEstudiantes/Echeverri_588/Tarea 02/include/difusion_model.h"
#include <cmath>
#include <fstream>
#include <iostream>

// Constructor: crea la malla espacial
Geometria::Geometria(int N_, double xmin_, double xmax_)
    : N(N_), xmin(xmin_), xmax(xmax_) {
    x.resize(N);
    dx = (xmax - xmin) / (N - 1);
    for (int i = 0; i < N; i++) {
        x[i] = xmin + i * dx;
    }
}

// Constructor: inicializa el vector de temperaturas en cero
Condiciones::Condiciones(Geometria &G_)
    : G(G_), u(G_.N, 0.0) {}

// Condición inicial gaussiana u(x,0) = exp(-α (x - x0)^2)
void Condiciones::condicionesIniciales(double alpha, double x0) {
    for (int i = 0; i < G.N; i++) {
        double dx_val = G.x[i] - x0;
        u[i] = std::exp(-alpha * dx_val * dx_val);
    }
}

// Condiciones de frontera Dirichlet: fija temperatura en extremos
void Condiciones::condicionesFrontera(double TL, double TR) {
    u[0] = TL;
    u[G.N - 1] = TR;
}

// Constructor del solver
DiffusionSolver::DiffusionSolver(double D_, double dt_, double t_max_)
    : D(D_), dt(dt_), t_max(t_max_) {}

// Verificación del criterio de estabilidad (α <= 0.5)
bool DiffusionSolver::verificarEstabilidad(double dx) const {
    double alpha = D * dt / (dx * dx);
    if (alpha > 0.5) {
        std::cerr << "Advertencia: α = " << alpha << " > 0.5 (posible inestabilidad)\n";
        return false;
    }
    return true;
}

// Resolver la ecuación de difusión con FTCS
void DiffusionSolver::resolverFTCS(Condiciones &cond, double TL, double TR) {
    int Nsteps = static_cast<int>(t_max / dt);
    double dx = cond.G.dx;
    double alpha = D * dt / (dx * dx);
    std::vector<double> u_new(cond.G.N, 0.0);

    for (int step = 0; step < Nsteps; step++) {
        for (int i = 1; i < cond.G.N - 1; i++) {
            u_new[i] = cond.u[i] + alpha * (cond.u[i+1] - 2.0 * cond.u[i] + cond.u[i-1]);
        }
        // aplicar condiciones de frontera
        u_new[0] = TL;
        u_new[cond.G.N - 1] = TR;

        cond.u.swap(u_new);
    }
}

// Guardar resultados en archivo de texto
void guardarResultado(const Geometria &geo, const Condiciones &cond, const std::string &nombreArchivo) {
    std::ofstream file(nombreArchivo);
    if (!file.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo " << nombreArchivo << "\n";
        return;
    }
    for (int i = 0; i < geo.N; i++) {
        file << geo.x[i] << " " << cond.u[i] << "\n";
    }
    file.close();
}
