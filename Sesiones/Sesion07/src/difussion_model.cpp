
# include <cstdio>
# include <iostream>
# include "difussion_model.h"

Grid::Grid(double x_min_, double x_max_, int N_)
    :x_min(x_min_),x_max(x_max_),N(N_) {
        dx=(x_max-x_min)/(N-1);
        x.resize(N);       
        for(int i=0;i<N;i++){
            x[i]=x_min+i*dx;
        }
};

Temperature::Temperature(Grid &grid_):
    grid(grid_),u(grid_.N, 0.0){}


void Temperature::applyInitialCondition() {
    for (int i = 0; i < grid.N; ++i) {
        double x = grid.x[i];
        u[i] = std::exp(-100.0 * std::pow(x - 0.5 * (grid.x_min + grid.x_max), 2));
    }
}

void Temperature::applyBoundaryCondition() {
    u[0] = 0.0;
    u[grid.N - 1] = 0.0;
}


DiffusionSolver::DiffusionSolver(Temperature &field_, double D_, double dt_, double t_max_)
    : field(field_), D(D_), dt(dt_), t_max(t_max_) {}

// Ejecutar el solver
void DiffusionSolver::run() {
    int steps = static_cast<int>(t_max / dt);
    for (int step = 0; step < steps; ++step) {
        field.applyBoundaryCondition();
        step();
    }
}

// Paso explícito (FTCS)
void DiffusionSolver::step() {
    std::vector<double> u_new(field.grid.N);
    double alpha = D * dt / (field.grid.dx * field.grid.dx);

    for (int i = 1; i < field.grid.N - 1; ++i) {
        u_new[i] = field.u[i] + alpha * (field.u[i + 1] - 2 * field.u[i] + field.u[i - 1]);
    }

    // Aplicar condiciones de frontera de nuevo
    u_new[0] = 0.0;
    u_new[field.grid.N - 1] = 0.0;

    field.u = u_new;
}



