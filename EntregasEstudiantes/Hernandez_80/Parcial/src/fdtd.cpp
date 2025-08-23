#include "../include/fdtd.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>

static inline int modp(int a, int m) {
    int r = a % m;
    return (r < 0) ? r + m : r;
}

FDTD::FDTD(const FDTDParams& p) : params(p) {
    if (params.nx < 4) throw std::runtime_error("nx debe ser >= 4");
    if (params.beta <= 0.0 || params.beta > 0.5)
        std::cerr << "⚠️ Aviso: Courant (beta) = " << params.beta
                  << " (estable si <= 0.5, mejor < 0.5)\n";
    Ex_old.assign(params.nx, 0.0);
    Ex_new.assign(params.nx, 0.0);
    Hy_old.assign(params.nx, 0.0);
    Hy_new.assign(params.nx, 0.0);
}

void FDTD::initialize_sine(double amp, double lambda) {
    // E(z,0) = H(z,0) = amp * sin(2π z / lambda)
    for (int k = 0; k < params.nx; ++k) {
        double z = k * params.dz;
        double s = amp * std::sin(2.0 * M_PI * z / lambda);
        Ex_old[k] = s;
        Hy_old[k] = s;
    }
    Ex_new = Ex_old;
    Hy_new = Hy_old;
}

void FDTD::step_periodic() {
    const int nx = params.nx;
    const double B = params.beta;

    // interior
    for (int k = 1; k < nx - 1; ++k) {
        Ex_new[k] = Ex_old[k] + B * (Hy_old[k - 1] - Hy_old[k + 1]);
        Hy_new[k] = Hy_old[k] + B * (Ex_old[k - 1] - Ex_old[k + 1]);
    }

    // k = 0 -> vecinos: k-1 -> nx-1 , k+1 -> 1
    Ex_new[0]      = Ex_old[0]      + B * (Hy_old[nx - 2] - Hy_old[1]);
    Hy_new[0]      = Hy_old[0]      + B * (Ex_old[nx - 2] - Ex_old[1]);

    // k = nx-1 -> vecinos: k-1 -> nx-2, k+1 -> 0
    Ex_new[nx - 1] = Ex_old[nx - 1] + B * (Hy_old[nx - 2] - Hy_old[0]);
    Hy_new[nx - 1] = Hy_old[nx - 1] + B * (Ex_old[nx - 2] - Ex_old[0]);
}

void FDTD::step_fixed() {
    const int nx = params.nx;
    const double B = params.beta;

    for (int k = 1; k < nx - 1; ++k) {
        Ex_new[k] = Ex_old[k] + B * (Hy_old[k - 1] - Hy_old[k + 1]);
        Hy_new[k] = Hy_old[k] + B * (Ex_old[k - 1] - Ex_old[k + 1]);
    }
    // fronteras de Dirichlet: E=H=0 en z=0 y z=L
    Ex_new[0] = 0.0; Ex_new[nx - 1] = 0.0;
    Hy_new[0] = 0.0; Hy_new[nx - 1] = 0.0;
}

void FDTD::step() {
    if (params.bc == BCType::Periodic) step_periodic();
    else                                step_fixed();
    Ex_old.swap(Ex_new);
    Hy_old.swap(Hy_new);
}

void FDTD::write_frame(std::ostream& os, int tstep) const {
    os << "# t=" << tstep << "\n";
    for (int k = 0; k < params.nx; ++k) {
        double z = k * params.dz;
        os << z << " " << Ex_old[k] << " " << Hy_old[k] << "\n";
    }
    os << "\n\n";
}

void FDTD::run(int nsteps, int output_every, const std::string& outpath) {
    std::ofstream fout(outpath);
    if (!fout) throw std::runtime_error("No se pudo abrir " + outpath);

    for (int n = 0; n < nsteps; ++n) {
        step();
        if (n % output_every == 0) write_frame(fout, n);
    }
    std::cerr << "Listo: " << outpath << "\n";
}
