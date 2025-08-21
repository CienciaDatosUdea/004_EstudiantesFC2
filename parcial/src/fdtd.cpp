// In this file, we define the FDTD1D class and its methods.
#include "fdtd.h"
#include <iostream>

using namespace fdtd;

FDTD1D::FDTD1D(const Config& cfg)
: Nz_(cfg.Nz),
  zmax_(cfg.zmax),
  dz_(cfg.dz > 0 ? cfg.dz : cfg.zmax / static_cast<double>(cfg.Nz)),
  dt_(cfg.dt),
  beta_(0.0),
  lambda_(cfg.wavelength),
  steps_(cfg.steps),
  output_every_(cfg.output_every),
  bc_(cfg.bc),
  renorm_(cfg.renormalize_E),
  Ex_(cfg.Nz, 0.0),
  Hy_(cfg.Nz, 0.0)
{
    if (dt_ <= 0.0) {
        // Courant: c*dt/dz ≤ 0.5 (safe factor)
        dt_ = 0.45 * dz_ / c0;
    }
    beta_ = c0 * dt_ / dz_;

    if (beta_ > 0.5 + 1e-12) {
        throw std::runtime_error("Unstable configuration: Courant number = " + std::to_string(beta_));
    }
    reset();
}

void FDTD1D::reset() {
    for (size_t k = 0; k < Nz_; ++k) {
        double z = k * dz_;
        double val = 0.1 * std::sin(2.0 * M_PI * z / lambda_);
        Ex_[k] = val;
        Hy_[k] = val;
    }
}

void FDTD1D::apply_boundary_conditions() {
    if (bc_ == Boundary::PEC) {
        Ex_.front() = 0.0;
        Ex_.back()  = 0.0;
        Hy_.front() = 0.0;
        Hy_.back()  = 0.0;
    }
}

void FDTD1D::step() {
    std::vector<double> Ex_old = Ex_;
    std::vector<double> Hy_old = Hy_;

    // Update Ex
    for (size_t k = 0; k < Nz_; ++k) {
        size_t km1 = (k == 0) ? (Nz_ - 1) : (k - 1);
        double diff = Hy_old[km1] - Hy_old[k];
        Ex_[k] = Ex_old[k] + beta_ * diff;
    }

    apply_boundary_conditions();

    // Update Hy
    for (size_t k = 0; k < Nz_; ++k) {
        size_t kp1 = (k + 1) % Nz_;
        double diff = Ex_[k] - Ex_[kp1];
        Hy_[k] = Hy_old[k] + beta_ * diff;
    }

    apply_boundary_conditions();
}

void FDTD1D::run() {
    const std::string csv = "fdtd_output.csv";
    write_csv(csv, 0, true);
    for (size_t n = 1; n <= steps_; ++n) {
        step();
        if (n % output_every_ == 0 || n == steps_) {
            write_csv(csv, n, false);
        }
    }
}

void FDTD1D::write_csv(const std::string& filename, size_t tindex, bool header) const {
    std::ofstream out(filename, std::ios::app);
    if (!out) throw std::runtime_error("Cannot open " + filename);

    if (header) out << "t_index,z,Ex,Hy\n";

    for (size_t k = 0; k < Nz_; ++k) {
        double z = k * dz_;
        out << tindex << "," << z << "," << Ex_[k] << "," << Hy_[k] << "\n";
    }
}
