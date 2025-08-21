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
    PerfectConductor = PEC  // Alias for backwards compatibility
};

// A structure to hold configuration parameters for the FDTD simulation
struct Config {
    double zmax = 200.0; // spatial extent
    double Zmax = zmax;  // alias for compatibility  
    size_t Nz = 10000;   // number of spatial divisions
    size_t K = Nz;       // alias for compatibility
    double Tmax = 5000;  // time extent
    size_t steps = 10000; // number of time divisions
    size_t N = steps;     // alias for compatibility
    double dz = zmax / static_cast<double>(2 * Nz); // spatial step
    double wavelength = 100.0; // wavelength for initial sine function
    size_t output_every = 5; // write every x steps to csv file
    Boundary bc = Boundary::Periodic;
    bool renormalize_E = true; // use renormalized scheme so both updates share beta
    
    // Method to automatically compute stable time steps
    void computeStableSteps(double safety_factor = 0.9) {
        // From Courant condition: c * dt / dz <= 1/2
        double dt_max = (1.0 / (2.0 * c)) * dz;
        double dt_stable = safety_factor * dt_max;
        steps = static_cast<size_t>(std::ceil(Tmax / dt_stable));
        N = steps; // update alias
    }
    
    // Method to automatically compute stable spatial divisions
    void computeStableSpatial(double safety_factor = 0.9) {
        // From stability condition: dz <= lambda / 10
        double dz_max = wavelength / 10.0;
        double dz_stable = safety_factor * dz_max;
        Nz = static_cast<size_t>(std::ceil(zmax / dz_stable));
        K = Nz; // update alias
        dz = zmax / static_cast<double>(Nz); // recalculate dz
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
    double Zmax_;
    size_t K_;
    double Tmax_;
    size_t N_;
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
        std::vector<double> E_field(K_);
        for (size_t k = 0; k < K_; k++){
            E_field[k] = EH_vector[2 * k];
        }
        return E_field;
    }
    // Accessors
    const std::vector<double> H() const {
        std::vector<double> H_field(K_);
        for (size_t k = 0; k < K_; k++){
            H_field[k] = EH_vector[2 * k + 1];
        }
        return H_field;
    }
    double dz() const { return dz_; }
    double dt() const { return dt_; }
    double beta() const { return beta_; }
    double courant() const { return beta_; }
    size_t N() const { return N_; }
    size_t Nz() const { return K_; }  // Accessor for number of spatial divisions

};

} //namespace fdtd
