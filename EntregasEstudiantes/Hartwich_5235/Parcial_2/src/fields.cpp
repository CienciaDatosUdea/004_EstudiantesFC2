#include <interface.h>

#include <vector>
#include <cmath>
#include <numbers> // for std::numbers::pi

// Constructor de la clase Fields. Aplica condiciones iniciales automáticamente. h_ tiene una componente menos que e_ ya que está evaluado a las coordenadas intermedias.
Fields::Fields(const Grid& g) : g_(g), e_(g.n_z_), h_(g.n_z_ - 1) {
    ApplyInitialCondition(g);
}

// aplicar condiciones iniciales (en las coordenadas "normales" para el campo eléctrico, intermedias para el campo magnético)
void Fields::ApplyInitialCondition(const Grid& g) {
    constexpr double pi{std::numbers::pi};
    const double h_offset{g.dz_/2};
    for (size_t i{0}; i < e_.size(); ++i) {
        e_[i] = 0.1 * std::sin(2 * pi *  g.z_[i] / 100);
    }
    for (size_t i{0}; i < h_.size(); ++i) {
        h_[i] = 0.1 * std::sin(2 * pi * (g.z_[i] + h_offset) / 100);
    }
}

// aplicar condiciones de borde (campo eléctrico)
void Fields::ApplyEBoundaryCondition() {
    e_.front() = 0;
    e_.back()  = 0;
}   

// aplicar condiciones de borde (campo magnético)
void Fields::ApplyHBoundaryCondition() {
    h_.front() = 0;
    h_.back()  = 0;
}