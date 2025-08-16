#include <interface.h>

#include <vector>

// constructor de la clase Grid: asigna parámetros a los valores, parcialmente usando funciones wrapper
Grid::Grid(
    double z_min,
    double z_max,
    size_t n_z
) : z_min_(z_min),
    z_max_(z_max),
    n_z_(n_z),
    dz_(DZWrapper(z_min, z_max, n_z)),
    z_(GridWrapper(z_min, z_max, n_z))
{}

// calcula dz
double Grid::DZWrapper(
    double z_min,
    double z_max,
    size_t n_z
) const {
    const double dz{(z_max - z_min) / (n_z - 1)};
    return dz;
}

// crea la red con las coordenadas espaciales (z)
std::vector<double> Grid::GridWrapper(
    double z_min,
    double z_max,
    size_t n_z
) const {
    std::vector<double> vals(n_z);
    const double dz{(z_max - z_min) / (n_z - 1)}; // calcular dz de manera separada para prevenir usar accidentalmente el miembro dz_ antes de que esté inicializado. El valor es el mismo.
    for (size_t i{0}; i < n_z; ++i) {
        vals[i] = i * dz;
    }
    return vals;
}

