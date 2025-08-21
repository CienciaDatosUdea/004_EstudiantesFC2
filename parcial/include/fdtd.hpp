// Skeleton for classes
#pragma once
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include <stdexcept>
#include <cmath>

namespace fdtd {

constexpr double c0 = 1;

// two boundary conditions the user can choose from
enum class Boundary {
    Periodic,
    PEC // E = 0 at both ends
};

// A struct to hold configuration parameters for the FDTD simulation
struct Config {
    size_t Nz = 200; // number of spatial nodes
    double zmax = 200.0; // spatial extent (arbitrary units)
    double wavelength = 100.0; // wavelength for initial sinusoid (same units as z)
    double dz = 0.0; // space step (computed if 0 from zmax/Nz)
    double dt = 0.0; // time step (must satisfy Courant)
    size_t steps = 2000; // number of time steps to simulate
    size_t output_every = 10; // write every N steps to csv
    Boundary bc = Boundary::Periodic;
    bool renormalize_E = true; // use renormalized scheme so both updates share beta
};

// Declaration of the FDTD1D class
class FDTD1D {
public:
    explicit FDTD1D(const Config& cfg);
    void reset();
    void step();
    void run();
    void write_csv(const std::string& filename, size_t tindex, bool header=false) const;

    // Accessors
    const std::vector<double>& Ex() const { return Ex_; }
    const std::vector<double>& Hy() const { return Hy_; }
    double dz() const { return dz_; }
    double dt() const { return dt_; }
    double beta() const { return beta_; }
    double courant() const { return beta_; }
    size_t Nz() const { return Nz_; }

private:
    size_t Nz_;
    double zmax_;
    double dz_;
    double dt_;
    double beta_;
    double lambda_;
    size_t steps_;
    size_t output_every_;
    Boundary bc_;
    bool renorm_;

    std::vector<double> Ex_;
    std::vector<double> Hy_;

    void apply_boundary_conditions();
};

} //namespace fdtd
