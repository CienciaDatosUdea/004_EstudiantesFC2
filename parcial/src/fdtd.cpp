// In this file, we define the FDTD1D class and its methods.
#include "fdtd.h"
#include <cmath>
#include <iostream>

using namespace fdtd;

FDTD1D::FDTD1D(const Config &cfg)
    : // Space parameters
      Zmax_(cfg.Zmax), K_(cfg.K),
      dz_(cfg.Zmax / (2 * static_cast<double>(cfg.K))),
      // Time parameters
      Tmax_(cfg.Tmax), N_(cfg.N),
      dt_(cfg.Tmax / (2 * static_cast<double>(cfg.N))),
      // Other parameters
      lambda_(cfg.wavelength), output_every_(cfg.output_every), bc_(cfg.bc),
      renorm_(cfg.renormalize_E), E_(cfg.N, 0.0), H_(cfg.N, 0.0)
      {
          if (dt_ <= 0.0) {
              // Courant: c*dt/dz ≤ 0.5
              dt_ = 0.45 * dz_ / c;
          }
          beta_ = c * dt_ / dz_;

          if (beta_ > 0.5 + 1e-12) {
              throw std::runtime_error("Unstable configuration: Courant number = " + std::to_string(beta_));
          }
          reset();
      }

void FDTD1D::reset() {
    for (size_t k = 0; k < K_; ++k) {
        double z = k * dz_;
        double val = 0.1 * sin(2.0 * M_PI * z / lambda_);
        E_[k] = val;
        H_[k] = val;
    }
}

void FDTD1D::apply_boundary_conditions() {
    if (bc_ == Boundary::PEC) {
        E_.front() = 0.0;
        E_.back()  = 0.0;
        H_.front() = 0.0;
        H_.back()  = 0.0;
    }
}

void FDTD1D::step() {
    std::vector<double> Ex_old = E_;
    std::vector<double> Hy_old = H_;

    // Update Ex
    for (size_t k = 0; k < N_; ++k) {
        size_t km1 = (k == 0) ? (N_ - 1) : (k - 1);
        double diff = Hy_old[km1] - Hy_old[k];
        E_[k] = Ex_old[k] + beta_ * diff;
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
    for (size_t n = 1; n <= N_; ++n) {
        step();
        if (n % output_every_ == 0 || n == N_) {
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
