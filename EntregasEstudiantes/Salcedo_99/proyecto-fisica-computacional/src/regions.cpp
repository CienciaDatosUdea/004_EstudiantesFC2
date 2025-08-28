#include "../include/functions.h"

// These methods define the wavefunction in each region of the potential well,
// according to quantum mechanical computations.

// Wavefunction over region 0
Complex phi_0(double x, const WaveParams& p) {
    const Complex i(0.0, 1.0);
    const Complex k_0 = (p.E >= p.V_0) ?
        std::sqrt(2.0 * p.m * (p.E - p.V_0)) / p.h_bar :
        i * std::sqrt(2.0 * p.m * (p.V_0 - p.E)) / p.h_bar;
    return std::exp(i * k_0 * (2.0 * p.b + x)) - std::exp(-i * k_0 * x);
}

// Wavefunction over region 1
Complex phi_1(double x, const WaveParams& p) {
    const Complex i(0.0, 1.0);
    const Complex k_1 = std::sqrt(2.0 * p.m * p.E) / p.h_bar;
    const Complex k_0 = (p.E >= p.V_0) ?
        std::sqrt(2.0 * p.m * (p.E - p.V_0)) / p.h_bar :
        i * std::sqrt(2.0 * p.m * (p.V_0 - p.E)) / p.h_bar;

    const Complex alpha_0 = (-k_0 * std::exp(2.0 * i * p.a * k_0) - k_0 * std::exp(2.0 * i * p.b * k_0) +
                            k_1*std::exp(2.0*i*p.a*k_0) - k_1*std::exp(2.0*i*p.b*k_0)) *
                            std::exp(i*p.a*(-k_0 + k_1))/(2.0*k_1);

    const Complex beta_0 = (k_0*std::exp(i*p.a*(3.0*k_0 + k_1)) + k_1*std::exp(i*p.a*(3.0*k_0 + k_1)) +
                           (k_0 - k_1)*std::exp(i*(p.a*(k_0 + k_1) + 2.0*p.b*k_0))) *
                           std::exp(-2.0*i*p.a*(k_0 + k_1))/(2.0*k_1);

    return alpha_0 * std::exp(i * k_1 * x) + beta_0 * std::exp(-i * k_1 * x);
}

// Wavefunction over region 2
Complex phi_2(double x, const WaveParams& p) {
    const Complex i(0.0, 1.0);
    const Complex k_0 = (p.E >= p.V_0) ?
        std::sqrt(2.0 * p.m * (p.E - p.V_0)) / p.h_bar :
        i * std::sqrt(2.0 * p.m * (p.V_0 - p.E)) / p.h_bar;
    const Complex k_1 = std::sqrt(2.0 * p.m * p.E) / p.h_bar;

    const Complex beta_0 = (k_0*std::exp(i*p.a*(3.0*k_0 + k_1)) + k_1*std::exp(i*p.a*(3.0*k_0 + k_1)) +
                           (k_0 - k_1)*std::exp(i*(p.a*(k_0 + k_1) + 2.0*p.b*k_0))) *
                           std::exp(-2.0*i*p.a*(k_0 + k_1))/(2.0*k_1);

    const Complex beta_1 = ((k_0 - k_1)*std::exp(2.0*i*p.a*k_0) + (k_0 + k_1)*std::exp(2.0*i*p.b*k_0)) *
                          std::exp(-i*(p.a*(k_0 - k_1) + 2.0*p.b*k_0))/(2.0*k_1);

    return -(beta_0 / beta_1) * (std::exp(i * k_0 * (-2.0 * p.b + x)) - std::exp(-i * k_0 * x));
}
