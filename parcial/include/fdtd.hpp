// Skeleton for classes
#pragma once
#include <cstddef>
#include <vector>
#include <string>

namespace fdtd {

constexpr double c = 1;

// two boundary conditions the user can choose from
enum class Boundary {
    Periodic,
    PEC // E = 0 at both ends
};

// A struct to hold configuration parameters for the FDTD simulation
struct Config {
    double Zmax = 200.0; // spatial extent
    size_t K = 10000; // number of spatial divisions
    double Tmax = 5000; // time extent
    size_t N = 10000; // number of time divisions
    double wavelength = 100.0; // wavelength for initial sine function
    size_t output_every = 5; // write every x steps to csv file
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
    const std::vector<double>& E() const { return E_; }
    const std::vector<double>& H() const { return H_; }
    double dz() const { return dz_; }
    double dt() const { return dt_; }
    double beta() const { return beta_; }
    double courant() const { return beta_; }
    size_t N() const { return N_; }

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

    std::vector<double> E_;
    std::vector<double> H_;

    void apply_boundary_conditions();
};

} //namespace fdtd
