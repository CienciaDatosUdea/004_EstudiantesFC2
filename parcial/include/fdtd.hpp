#pragma once
#include <cstddef>
#include <vector>
#include <string>

namespace fdtd {

constexpr double c = 1;

// two boundary conditions the user can choose from
enum class Boundary {
    Periodic,
    PerfectConductor // E = 0 at both ends
};

// A structure to hold configuration parameters for the FDTD simulation
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
        std::vector<double> E;
        for (size_t k = 0; k < K_; k++){
            E[k] = EH_vector[2 * k];
        }
        return E;
    }
    // Accessors
    const std::vector<double> H() const {
        std::vector<double> H;
        for (size_t k = 0; k < K_; k++){
            H[k] = EH_vector[2 * k + 1];
        }
        return H;
    }
    double dz() const { return dz_; }
    double dt() const { return dt_; }
    double beta() const { return beta_; }
    double courant() const { return beta_; }
    size_t N() const { return N_; }

};

} //namespace fdtd
