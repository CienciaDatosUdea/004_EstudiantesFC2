#include "../include/functions.h"

// Thermalized probability density function.
// Compute 1-dimensional wavefunctions over a range of temperatures and energies
std::vector<VectorXd> compute_wavefunctions_1d(
    const VectorXd& T_values,
    const VectorXd& energies,
    const VectorXd& x_values,
    double m, double V_0, double h_bar, double a, double b) {

    // Initialise parameters template with E = 0. In time, we will change the
    // energy values
    WaveParams base_params = {0, m, V_0, h_bar, a, b};
    int n_temperatures = T_values.size();
    int n_energies = energies.size();
    int n_x = x_values.size();

    // Declare the result as an (n_temperatures)-dimensional vector of real
    // n_x-dimensional vectors. n_x = amount of x values to compute
    std::vector<VectorXd> result(n_temperatures, VectorXd::Zero(n_x));

    #pragma omp parallel for collapse(1)
    for(int k = 0; k < n_temperatures; ++k) {
        for (int i = 0; i < n_energies; ++i) {
            // overwrite the base params with the correct energy
            WaveParams p = base_params; p.E = energies[i];

            for (int j = 0; j < n_x; ++j) {
                Complex psi = phi(x_values[j], p);
                result[k][j] += exp(-energies[i] / T_values[k]) * std::norm(psi);
            }
        }
    }
    return result;
}

// Returns expected values of the positional probability density
// function for either bosons (sym=1) or fermions (sym=-1) with or without
// spin.
std::vector<MatrixXd> compute_wavefunctions(
    const std::vector<std::tuple<double, double, double, double>>& energies,
    const VectorXd& x1_values,
    const VectorXd& x2_values,
    double m, double V_0, double h_bar, double a, double b,
    double T, double sym, bool spin) {

    // Initialise parameters template with E = 0, in time we will change the
    // energy values
    WaveParams base_params = {0, m, V_0, h_bar, a, b};
    int n_energies = energies.size();
    int n1 = x1_values.size();
    int n2 = x2_values.size();

    // Declare the result as an n_energies-dimensional vector of real
    // (n1xn2)-dimensional matrices
    std::vector<MatrixXd> result(n_energies, MatrixXd::Zero(n1, n2));

    #pragma omp parallel for collapse(1)
    for(int k = 0; k < n_energies; ++k) { // k is the index corresponding to the energy tuple
        // overwrite the base params with the correct energies
        auto [E1, E2, E3, E4] = energies[k];

        WaveParams p1 = base_params; p1.E = E1;
        WaveParams p2 = base_params; p2.E = E2;
        WaveParams p3 = base_params; p3.E = E3;
        WaveParams p4 = base_params; p4.E = E4;

        // populate the k-th array
        for(int i = 0; i < n1; ++i) {
            for(int j = 0; j < n2; ++j) {
                Complex psi1 = phi(x1_values[i], p1);
                Complex psi2 = phi(x2_values[j], p2);
                Complex psi3 = phi(x1_values[i], p3);
                Complex psi4 = phi(x2_values[j], p4);

                if(spin) {
                    result[k](i,j) = 0.5 * std::exp(-(E1 + E2)/T) *
                        (0.25 * std::norm(psi1 * psi2 + psi3 * psi4) +
                         0.75 * std::norm(psi1 * psi2 - psi3 * psi4));
                } else {
                    result[k](i,j) = 0.5 * std::exp(-(E1 + E2)/T) *
                        std::norm(psi1 * psi2 + sym * psi3 * psi4);
                }
            }
        }
    }
    return result;
}
