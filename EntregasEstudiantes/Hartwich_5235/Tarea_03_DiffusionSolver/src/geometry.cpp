#include "diffusion_model.h"

Geometry::Geometry(double x_start, double x_end, size_t N_x) : grid(N_x), dx((x_end - x_start)/(N_x - 1)) {
    for (size_t i{0}; i < N_x; ++i) {
        grid[i] = x_start + i * dx;
    }
}

const std::vector<double>& Geometry::get_grid() const {
    return grid;
}

const double& Geometry::operator[](size_t i) const {
    return grid.at(i);
}

const double Geometry::get_dx() const {
    return dx;
}