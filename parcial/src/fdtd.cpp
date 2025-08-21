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
      renorm_(cfg.renormalize_E), EH_vector(2 * cfg.K, 0.0)
      {
          // Evaluate stability condition
          if (dz_ > lambda_ / 10) {
              throw std::runtime_error("Unstable configuration: dz must be <= " + std::to_string(lambda_ / 10));
          }

          // Evaluate Courant number
          beta_ = c * dt_ / dz_;
          if (beta_ > 0.5 ) {
              throw std::runtime_error("Unstable configuration: Courant number = " + std::to_string(beta_) +
                                       " must be <= 0.5");
          }
          setFieldsAtInitialTime();
      }

void FDTD1D::setFieldsAtInitialTime() {
    for (size_t k = 0; k < K_; k++) {
        double E_value = 0.1 * sin(2.0 * M_PI * (2 * k * dz_) / lambda_); // Generalise this to have arbirtrary functions
        double H_value = 0.1 * sin(2.0 * M_PI * ((2 * k + 1) * dz_) / lambda_);
        EH_vector[2 * k] = E_value;
        EH_vector[2 * k + 1] = H_value;
    }
}

void FDTD1D::applyBoundaryConditions() {
    if (bc_ == Boundary::PerfectConductor) {
        E_.front() = 0.0;
        E_.back()  = 0.0;
        H_.front() = 0.0;
        H_.back()  = 0.0;
    }
}

// Finite differences method using the recursive formulas
void FDTD1D::step() {
    std::vector<double> EH_vector_old = EH_vector;
    // Update E over space coordinates
    for (size_t k = 0; k < K_; k++) {
        double diff = EH_vector[2 * k + 1] - EH_vector[2 * k - 1];
        EH_vector[2 * k] = EH_vector_old[2 * k] + beta_ * diff;
    }
    // Update H over space coordinates
    for (size_t k = 0; k < K_; k++) {
        double diff = EH_vector[2 * k] - EH_vector[2 * (k - 1)];
        EH_vector[2 * k + 1] = EH_vector_old[2 * k + 1] + beta_ * diff;
    }

    applyBoundaryConditions();
}

// Perform steps over the whole time domain, save the resulting EH_vectors each time
void FDTD1D::run() {
    const std::string csv = "fdtd_output.csv";
    write_csv(csv, 0, true);
    for (size_t n = 1; n <= N_; n++) {
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

    for (size_t k = 0; k < K_; ++k) {
        double z = k * dz_;
        out << tindex << "," << z << "," << E_[k] << "," << H_[k] << "\n";
    }
}
