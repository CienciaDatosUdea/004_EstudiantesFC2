#include "../include/diffusion_model.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>

using namespace std;

// ============================
// FieldWriter
// ============================
FieldWriter::FieldWriter(const std::string &filename) {
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + filename);
    }
    file << std::fixed << std::setprecision(6);
}

void FieldWriter::writeTemperature(const Geometry &G, const Temperature &Campo, double time) {
    file << "# t = " << time << "\n";
    for (int i = 0; i < G.N; ++i) {
        file << G.x[i] << "\t" << Campo.T[i] << "\n";
    }
    file << "\n";
}

// ============================
// DiffusionSolver
// ============================
DiffusionSolver::DiffusionSolver(Temperature &Temp, double D_, double dt_, double tmax,
                                 double TL_, double TR_, std::function<double(double)> f_,
                                 const std::string &fn)
    : field(Temp), D(D_), dt(dt_), t_max(tmax),
      TL(TL_), TR(TR_), f(f_), filename(fn) {

    alpha = D * dt / (field.g.dx * field.g.dx);

    // Verificación de condición de estabilidad (RF10)
    if (alpha > 0.5) {
        throw std::runtime_error("ERROR: alpha = " + std::to_string(alpha) +
                                 " no satisface la condición de estabilidad (alpha <= 0.5).");
    }

    // Inicializa el campo
    field.applyInitialCondition(f);
    field.applyBoundaryCondition(TL, TR);
}

// Evoluciona el campo una vez (RF4)
void DiffusionSolver::step() {
    std::vector<double> T_new(field.g.N);

    // FTCS para nodos interiores
    for (int i = 1; i < field.g.N - 1; i++) {
        T_new[i] = field.T[i] + alpha * (field.T[i + 1] - 2 * field.T[i] + field.T[i - 1]);
    }

    // Copiamos los valores viejos en frontera (serán corregidos)
    T_new[0] = field.T[0];
    T_new[field.g.N - 1] = field.T[field.g.N - 1];

    field.T = T_new;
    field.applyBoundaryCondition(TL, TR);
}

// Evoluciona el campo hasta t_max
void DiffusionSolver::run() {
    FieldWriter writer(filename);
    writer.writeTemperature(field.g, field, 0.0);

    int steps = static_cast<int>(t_max / dt);
    double time = 0.0;

    for (int s = 1; s <= steps; s++) {
        step();
        time = s * dt;
        writer.writeTemperature(field.g, field, time);
    }
}
