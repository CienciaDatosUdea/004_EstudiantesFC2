
#include "include/functions.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <complex>
#include <Eigen/Dense>
#include <gsl/gsl_integration.h>

using Complex = std::complex<double>;
using MatrixXcd = Eigen::Matrix<Complex, Eigen::Dynamic, Eigen::Dynamic>;
using MatrixXd = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
using VectorXd = Eigen::VectorXd;

// Main implementation for one dimensional plots
int main(int argc, char* argv[]) {
    if (argc < 9) {
        std::cerr << "Usage: " << argv[0] << " m V_0 h_bar a b T sym spin energy_file\n";
        return 1;
    }

    double m     = std::stod(argv[1]);
    double V_0   = std::stod(argv[2]);
    double h_bar = std::stod(argv[3]);
    double a     = std::stod(argv[4]);
    double b     = std::stod(argv[5]);
    double grid_num = std::stod(argv[6]);
    std::string temperature_file  =  argv[7];
    std::string energy_file  =  argv[8];

    std::ifstream T_file(temperature_file);
    VectorXd temperatures;
    double T;
    while (T_file >> T) {
        temperatures.conservativeResize(temperatures.size() + 1);
        temperatures(temperatures.size() - 1) = T;
    }
    T_file.close();

    std::ifstream E_file(energy_file);
    VectorXd energies;
    double E;
    while (E_file >> E) {
        energies.conservativeResize(energies.size() + 1);
        energies(energies.size() - 1) = E;
    }
    E_file.close();

    const int N = grid_num;
    VectorXd x_values = VectorXd::LinSpaced(N, -b, b);

    auto wavefunctions = compute_wavefunctions_1d(temperatures, energies, x_values,
                                                 m, V_0, h_bar, a, b);

    save_to_csv_1d("wavefunctions_1d.csv", x_values, temperatures, wavefunctions);

    return 0;
}
