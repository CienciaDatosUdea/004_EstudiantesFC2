#pragma once
#include <cstddef>
#include <vector>
#include <string>
#include <cmath>

namespace fdtd {

constexpr double c = 1;

// two boundary conditions the user can choose from
enum class Boundary {
    Periodic,
    PEC,  // Perfect Electric Conductor - E = 0 at both ends
};

// A structure to hold configuration parameters for the FDTD simulation
struct Config {
    double zmax = 200.0; // spatial extent
    size_t Nz = 10000; // number of spatial divisions
    double Tmax = 5000; // time extent
    size_t steps = 10000; // number of time divisions
    double dz = zmax / static_cast<double>(2 * Nz); // spatial step
    double wavelength = 100.0; // wavelength for initial sine function
    size_t output_every = 30; // write every n steps to csv file
    Boundary bc = Boundary::Periodic;

    // Method to automatically compute stable spatial divisions
    void computeStableSpatial(double safety_factor = 0.9) {
        // From stability condition: dz <= lambda / 10
        double dz_max = wavelength / 10.0;
        double dz_stable = safety_factor * dz_max;
        Nz = static_cast<size_t>(std::ceil(zmax / dz_stable));
        dz = zmax / static_cast<double>(Nz); // recalculate dz
    }

    // Method to automatically compute stable time steps
    void computeStableSteps(double safety_factor = 0.9) {
        // From Courant condition: c * dt / dz <= 1/2
        double dt_max = (1.0 / (2.0 * c)) * dz;
        double dt_stable = safety_factor * dt_max;
        steps = static_cast<size_t>(std::ceil(Tmax / dt_stable));
    }

    // Method to automatically compute both stable spatial and temporal discretization
    void computeStableDiscretization(double spatial_safety = 0.9, double temporal_safety = 0.9) {
        computeStableSpatial(spatial_safety);
        computeStableSteps(temporal_safety);
    }
};

// Declaration of the FDTD1D class
class FDTD1D {
private:
    double zmax_;
    size_t Nz_;
    double Tmax_;
    size_t steps_;
    double dz_;
    double dt_;
    double beta_;
    double lambda_;
    size_t output_every_;
    Boundary bc_;
    bool renorm_;

    // Vector with values of E and H at a time 2n for H, 2n + 1 for E. Indices
    // of this vector are positional, odd ones are reserved for H and even ones
    // are reserved for E
    std::vector<double> EH_vector;

    void applyBoundaryConditions();

public:
    explicit FDTD1D(const Config& cfg);
    void setFieldsAtInitialTime();
    void step();
    void run();
    void write_csv(const std::string& filename, size_t tindex, bool header=false) const;

    // Accessors
    const std::vector<double> E() const {
        std::vector<double> E_field(Nz_);
        for (size_t k = 0; k < Nz_; k++){
            E_field[k] = EH_vector[2 * k];
        }
        return E_field;
    }
    const std::vector<double> H() const {
        std::vector<double> H_field(Nz_);
        for (size_t k = 0; k < Nz_; k++){
            H_field[k] = EH_vector[2 * k + 1];
        }
        return H_field;
    }
    double dz() const { return dz_; }
    double dt() const { return dt_; }
    double beta() const { return beta_; }
    size_t steps() const { return steps_; }
    size_t Nz() const { return Nz_; }

};

} //namespace fdtd
