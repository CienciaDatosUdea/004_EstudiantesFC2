
#include "include/functions.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <complex>
#include <Eigen/Dense>
#include <gsl/gsl_integration.h>
#include <tuple>
#include <vector>

using Complex = std::complex<double>;
using MatrixXcd = Eigen::Matrix<Complex, Eigen::Dynamic, Eigen::Dynamic>;
using MatrixXd = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
using VectorXd = Eigen::VectorXd;

// Main implementation for surface plots
int main(int argc, char* argv[]) {
    if (argc < 11) {
        std::cerr << "Usage: " << argv[0] << " m V_0 h_bar a b T sym spin energy_file\n";
        return 1;
    }

    double m     = std::stod(argv[1]);
    double V_0   = std::stod(argv[2]);
    double h_bar = std::stod(argv[3]);
    double a     = std::stod(argv[4]);
    double b     = std::stod(argv[5]);
    double T     = std::stod(argv[6]);
    double sym   = std::stod(argv[7]);
    bool spin    = std::stod(argv[8]);
    double grid_num = std::stod(argv[9]);
    std::string energy_file  =  argv[10];

    std::ifstream file(energy_file);
    std::vector<std::tuple<double, double, double, double>> energies;
    double E1, E2, E3, E4;
    while (file >> E1 >> E2 >> E3 >> E4) {
        energies.emplace_back(E1, E2, E3, E4);
    }
    file.close();

    const int N = grid_num;
    VectorXd x1_values = VectorXd::LinSpaced(N, -b, b);
    VectorXd x2_values = x1_values.array() + 0.001;

    auto wavefunctions = compute_wavefunctions(energies, x1_values, x2_values,
                                            m, V_0, h_bar, a, b, T, sym, spin);

    save_to_csv(x1_values, x2_values, energies, spin, wavefunctions, "wavefunctions.csv");

    return 0;
}
