// In this file, we define the FDTD1D class and its methods.
#include "fdtd.h"
#include <cmath>
#include <iostream>
#include <fstream>

using namespace fdtd;

FDTD1D::FDTD1D(const Config &cfg)
    : // Space parameters
      zmax_(cfg.zmax), Nz_(cfg.Nz),
      dz_(cfg.dz),
      // Time parameters
      Tmax_(cfg.Tmax), steps_(cfg.steps),
      dt_(cfg.Tmax / static_cast<double>(2 * cfg.steps)),
      // Other parameters
      lambda_(cfg.wavelength), output_every_(cfg.output_every), bc_(cfg.bc),
      EH_vector(2 * cfg.Nz, 0.0)
      {
          // // Evaluate stability condition
          // if (dz_ > lambda_ / 10) {
          //     throw std::runtime_error("Unstable configuration: dz must be <= " + std::to_string(lambda_ / 10));
          // }

          // // Evaluate Courant number
          beta_ = c * dt_ / dz_;
          // if (beta_ > 0.5 ) {
          //     throw std::runtime_error("Unstable configuration: Courant number = " + std::to_string(beta_) +
          //                              " must be <= 0.5");
          // }
          setFieldsAtInitialTime();
      }

void FDTD1D::setFieldsAtInitialTime() {
    for (size_t k = 0; k < Nz_; k++) {
        double z_E = 2 * k * dz_;  // Position for E field
        double z_H = (2 * k + 1) * dz_;  // Position for H field (staggered grid)

        double E_value = 0.1 * sin(2.0 * M_PI * z_E / lambda_);
        double H_value = 0.1 * sin(2.0 * M_PI * z_H / lambda_);

        EH_vector[2 * k] = E_value;
        EH_vector[2 * k + 1] = H_value;
    }
}

void FDTD1D::applyBoundaryConditions() {
    if (bc_ == Boundary::PEC) {
        // Set E at boundaries to 0 (E is at even indices: 0, 2, 4, ...)
        EH_vector[0] = 0.0;                    // E at k=0
        EH_vector[2 * (Nz_ - 1)] = 0.0;        // E at k=Nz-1
        // Set H at boundaries to 0 (H is at odd indices: 1, 3, 5, ...)
        EH_vector[1] = 0.0;                    // H at k=0
        EH_vector[2 * (Nz_ - 1) + 1] = 0.0;    // H at k=Nz-1
    }
    // For periodic boundary conditions there is no additional action needed, as
    // the step function should handle wraparound
}

// Finite differences method using the recursive formulas
void FDTD1D::step() {
    std::vector<double> EH_vector_old = EH_vector;

    // In our indexing: E is at even indices, H is at odd indices
    for (size_t k = 0; k < Nz_; k++) {
        double H_right, H_left;

        H_right = EH_vector_old[2 * k + 1]; // H at current k

        if (k == 0) {
            // At leftmost boundary
            if (bc_ == Boundary::Periodic) {
                H_left = EH_vector_old[2 * (Nz_ - 1) + 1]; // H at k=Nz-1
            } else {
                H_left = 0.0; // PEC boundary
            }
        } else {
            H_left = EH_vector_old[2 * k - 1]; // H at k-1
        }

        double dH_dz = (H_right - H_left) / dz_;
        EH_vector[2 * k] = EH_vector_old[2 * k] + dt_ * dH_dz; // Assuming c = 1, eps0 = mu0 = 1
    }

    // This one is with the current (already updated) E field values
    for (size_t k = 0; k < Nz_; k++) {
        double E_right, E_left;

        // E_right corresponds to E(k+1), E_left to E(k)
        E_left = EH_vector[2 * k]; // E at current k (already updated)

        if (k == Nz_ - 1) {
            // At rightmost boundary
            if (bc_ == Boundary::Periodic) {
                E_right = EH_vector[0]; // E at k=0
            } else {
                E_right = 0.0; // PEC boundary
            }
        } else {
            E_right = EH_vector[2 * (k + 1)]; // E at k+1
        }

        double dE_dz = (E_right - E_left) / dz_;
        EH_vector[2 * k + 1] = EH_vector_old[2 * k + 1] + dt_ * dE_dz;
    }

    applyBoundaryConditions();
}

// Perform steps over the whole time domain, save the resulting EH_vectors each time
void FDTD1D::run() {
    const std::string csv = "fdtd_output.csv";
    write_csv(csv, 0, true);
    for (size_t n = 1; n <= steps_; n++) {
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
        double E_k = EH_vector[2 * k];       // E field at position k
        double H_k = EH_vector[2 * k + 1];   // H field at position k
        out << tindex << "," << z << "," << E_k << "," << H_k << "\n";
    }
}
