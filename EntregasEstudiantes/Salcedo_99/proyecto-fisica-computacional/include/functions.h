#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <complex>
#include <vector>
#include <tuple>
#include <Eigen/Dense>
#include <gsl/gsl_integration.h>

// Aliases
using Complex   = std::complex<double>;
using MatrixXcd = Eigen::Matrix<Complex, Eigen::Dynamic, Eigen::Dynamic>;
using MatrixXd  = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
using VectorXd  = Eigen::VectorXd;

// Wave parameters
struct WaveParams {
    double E, m, V_0, h_bar, a, b;
};

// Region wavefunctions
Complex phi_0(double x, const WaveParams& p);
Complex phi_1(double x, const WaveParams& p);
Complex phi_2(double x, const WaveParams& p);

// Normalization
double square_norm(double x, void* params);
double normalize_wavefunction(const WaveParams& p);
Complex phi(double x, const WaveParams& p);

// Wavefunction computations
std::vector<VectorXd> compute_wavefunctions_1d(
    const VectorXd& T_values,
    const VectorXd& energies,
    const VectorXd& x_values,
    double m, double V_0, double h_bar, double a, double b);

std::vector<MatrixXd> compute_wavefunctions(
    const std::vector<std::tuple<double, double, double, double>>& energies,
    const VectorXd& x1_values,
    const VectorXd& x2_values,
    double m, double V_0, double h_bar, double a, double b,
    double T, double sym, bool spin);

// Inpput-output
void save_to_csv_1d(const std::string& filename,
                    const VectorXd& x_values,
                    const VectorXd& T_values,
                    const std::vector<VectorXd>& wavefunctions);

void save_to_csv(const VectorXd& x1_values,
                 const VectorXd& x2_values,
                 const std::vector<std::tuple<double, double, double, double>>& energies,
                 bool spin,
                 const std::vector<MatrixXd>& wavefunctions,
                 const std::string& filename);

#endif
