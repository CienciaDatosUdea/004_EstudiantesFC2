#include "../include/diffusion_model.h"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

// Constructor de la clase Geometry
Geometry::Geometry(double xmin, double xmax, int N_)
    : x_min(xmin), x_max(xmax), N(N_) {

    if (N < 2) {
        throw std::runtime_error("Geometry requires at least 2 grid points.");
    }

    dx = (x_max - x_min) / (N - 1.0);
    x.resize(N);

    // posiciones de la barra
    for (int i = 0; i < N; i++) {
        x[i] = x_min + i * dx;
    }
}
