#include "../include/functions.h"

// Wavefunction normalisation regionwise
double square_norm(double x, void* params) {
    auto* p = static_cast<WaveParams*>(params);
    if (x >= -p->b && x < -p->a) {
        return std::norm(phi_0(x, *p));
    } else if (x >= -p->a && x <= p->a) {
        return std::norm(phi_1(x, *p));
    } else if (x > p->a && x <= p->b) {
        return std::norm(phi_2(x, *p));
    }
    return 0.0;
}

// Computes the normalization constant for the wavefunction
double normalize_wavefunction(const WaveParams& p) {
    gsl_integration_workspace* w = gsl_integration_workspace_alloc(1000);
    gsl_function F;
    F.function = &square_norm;
    F.params = const_cast<WaveParams*>(&p);

    double result, error;
    gsl_integration_qag(&F, -p.b, p.b, 0, 1e-6, 1000,
                        GSL_INTEG_GAUSS61, w, &result, &error);
    gsl_integration_workspace_free(w);
    return 1.0 / std::sqrt(result);
}

// Returns the normalized wavefunction value at position x
Complex phi(double x, const WaveParams& p) {
    double norm_const = normalize_wavefunction(p);
    if (x >= -p.b && x < -p.a) {
        return norm_const * phi_0(x, p);
    } else if (x >= -p.a && x <= p.a) {
        return norm_const * phi_1(x, p);
    } else if (x > p.a && x <= p.b) {
        return norm_const * phi_2(x, p);
    }
    return Complex(0.0, 0.0);
}
