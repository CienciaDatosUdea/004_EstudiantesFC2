#include "../include/MagneticSystem.hpp"
#include <cmath>
#include <functional>
#include <stdexcept>

// Definimos M_PI si no está disponible
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace MagSim {

// --- Funciones Numéricas Auxiliares ---

double integrate_simpson(const std::function<double(double)>& func, double a, double b, int n) {
    if (n % 2 != 0) n++;
    const double h = (b - a) / n;
    double sum = func(a) + func(b);
    for (int i = 1; i < n; i += 2) sum += 4.0 * func(a + i * h);
    for (int i = 2; i < n - 1; i += 2) sum += 2.0 * func(a + i * h);
    return sum * h / 3.0;
}



// --- Implementación de la Clase MagneticSystem ---

MagneticSystem::MagneticSystem(double M, double a, double L) : M_(M), a_(a), L_(L) {}

Vector3D MagneticSystem::calculate_B_DM(const Vector3D& pos) const {
    const double u1 = pos.z + L_ / 2.0;
    const double u2 = pos.z - L_ / 2.0;

    auto create_integrand = [&](int component) {
        return [&](double phi) -> double {
            const double cos_phi = cos(phi);
            const double sin_phi = sin(phi);
            const double s_sq = pow(pos.x - a_ * cos_phi, 2) + pow(pos.y - a_ * sin_phi, 2);
            
            if (s_sq < 1e-12) return 0.0;

            const double sqrt_u1 = sqrt(u1 * u1 + s_sq);
            const double sqrt_u2 = sqrt(u2 * u2 + s_sq);
            
            const double common_term1 = (sqrt_u1 + u1 > 1e-12) ? -cos_phi / (u1*u1 + s_sq + u1 * sqrt_u1) : 0.0;
            const double common_term2 = (sqrt_u2 + u2 > 1e-12) ?  cos_phi / (u2*u2 + s_sq + u2 * sqrt_u2) : 0.0;
            const double common_factor = common_term1 + common_term2;

            if (component == 0) return common_factor * (pos.x - a_ * cos_phi);
            if (component == 1) return common_factor * (pos.y - a_ * sin_phi);
            
            const double z_term1 = (sqrt_u1 + u1 > 1e-12) ? -cos_phi / (u1*u1 + s_sq + u1 * sqrt_u1) * (u1 + sqrt_u1) : 0.0;
            const double z_term2 = (sqrt_u2 + u2 > 1e-12) ?  cos_phi / (u2*u2 + s_sq + u2 * sqrt_u2) * (u2 + sqrt_u2) : 0.0;
            return z_term1 + z_term2;
        };
    };

    const int n_steps = 1000;
    double Bx = integrate_simpson(create_integrand(0), 0, 2 * M_PI, n_steps);
    double By = integrate_simpson(create_integrand(1), 0, 2 * M_PI, n_steps);
    double Bz = integrate_simpson(create_integrand(2), 0, 2 * M_PI, n_steps);

    const double prefactor = (MagneticSystem::MU_0 * M_ * a_) / (4.0 * M_PI);
    return {prefactor * Bx, prefactor * By, prefactor * Bz};
}

Vector3D MagneticSystem::calculate_B_total_DMP(const Vector3D& pos) const {
    Vector3D pos_rel1 = {pos.x + a_, pos.y, pos.z};
    Vector3D pos_rel2 = {pos.x - a_, pos.y, pos.z};
    Vector3D B1 = calculate_B_DM(pos_rel1);
    Vector3D B2 = calculate_B_DM(pos_rel2);
    return {B1.x + B2.x, B1.y + B2.y, B1.z + B2.z};
}

double MagneticSystem::calculate_potential_U_prime(const Vector3D& B_vector, double chi) const {
    const double B_sq = B_vector.x * B_vector.x + B_vector.y * B_vector.y + B_vector.z * B_vector.z;
    return -chi / (MagneticSystem::MU_0 * (2.0 + chi)) * B_sq;
}



// --- Implementación de la Clase RodDynamics ---

RodDynamics::RodDynamics(double rho, double chi) : rho_(rho), chi_(chi) {}

double RodDynamics::vertical_force_prime(double y, const MagneticSystem& mag_system) const {
    const double h_y = 1e-6;
    Vector3D B_plus = mag_system.calculate_B_total_DMP({0, y + h_y, 0});
    Vector3D B_minus = mag_system.calculate_B_total_DMP({0, y - h_y, 0});
    double U_plus = mag_system.calculate_potential_U_prime(B_plus, chi_);
    double U_minus = mag_system.calculate_potential_U_prime(B_minus, chi_);
    double dU_dy = (U_plus - U_minus) / (2 * h_y);
    return -dU_dy - rho_ * G;
}

double RodDynamics::find_equilibrium_height(const MagneticSystem& mag_system) const {
    double y_low = 0.2 * mag_system.get_a(); 
    double y_high = 0.98 * mag_system.get_a();
    double y_mid = y_low;

    for (int i = 0; i < 100; ++i) {
        y_mid = (y_low + y_high) / 2.0;
        if (vertical_force_prime(y_mid, mag_system) * vertical_force_prime(y_low, mag_system) > 0) {
            y_low = y_mid;
        } else {
            y_high = y_mid;
        }
    }
    return y_mid;
}

double RodDynamics::restoring_force_prime(double z, double y0, const MagneticSystem& mag_system) const {
    const double h_z = 1e-6;
    Vector3D B_plus = mag_system.calculate_B_total_DMP({0, y0, z + h_z});
    Vector3D B_minus = mag_system.calculate_B_total_DMP({0, y0, z - h_z});
    double U_plus = mag_system.calculate_potential_U_prime(B_plus, chi_);
    double U_minus = mag_system.calculate_potential_U_prime(B_minus, chi_);
    return -(U_plus - U_minus) / (2 * h_z);
}

std::vector<std::pair<double, double>> RodDynamics::simulate_oscillation(const MagneticSystem& mag_system, double y0, double z0, double beta, double total_time, int steps) const {
    std::vector<std::pair<double, double>> results;
    const double dt = total_time / steps;
    double z = z0;
    double v = 0.0;

    for (int i = 0; i <= steps; ++i) {
        double t = i * dt;
        results.push_back({t, z * 1000.0});

        auto acceleration = [&](double current_z, double current_v) {
            double force = restoring_force_prime(current_z, y0, mag_system);
            return (force - beta * current_v) / rho_;
        };

        double k1z = dt * v;
        double k1v = dt * acceleration(z, v);
        double k2z = dt * (v + 0.5 * k1v);
        double k2v = dt * acceleration(z + 0.5 * k1z, v + 0.5 * k1v);
        double k3z = dt * (v + 0.5 * k2v);
        double k3v = dt * acceleration(z + 0.5 * k2z, v + 0.5 * k2v);
        double k4z = dt * (v + k3v);
        double k4v = dt * acceleration(z + k3z, v + k3v);

        z += (k1z + 2.0 * k2z + 2.0 * k3z + k4z) / 6.0;
        v += (k1v + 2.0 * k2v + 2.0 * k3v + k4v) / 6.0;
    }
    return results;
}


// --- Implementación de la Clase SimulationController ---

SimulationController::SimulationController() {}

std::vector<CamelbackDataPoint> SimulationController::run_camelback_simulation(double M, double a, double chi) const {
    std::vector<CamelbackDataPoint> results;
    const std::vector<int> la_ratios = {16, 8, 4};
    const double y_fixed = 0.7 * a;

    for (int ratio : la_ratios) {
        MagneticSystem mag_system(M, a, static_cast<double>(ratio) * a);
        for (int i = 0; i <= 200; ++i) {
            double z_norm = -0.6 + (1.2 * i / 200.0);
            Vector3D B_vec = mag_system.calculate_B_total_DMP({0, y_fixed, z_norm * mag_system.get_L()});
            double U_prime = mag_system.calculate_potential_U_prime(B_vec, chi);
            results.push_back({z_norm, U_prime, ratio});
        }
    }
    return results;
}

double SimulationController::calculate_spring_constant(const MagneticSystem& mag_system, double y_fixed, double chi) const {
    const double h = 1e-5;
    Vector3D B_center = mag_system.calculate_B_total_DMP({0, y_fixed, 0});
    Vector3D B_plus_h = mag_system.calculate_B_total_DMP({0, y_fixed, h});
    double U_center = mag_system.calculate_potential_U_prime(B_center, chi);
    double U_plus_h = mag_system.calculate_potential_U_prime(B_plus_h, chi);
    return (2.0 * U_plus_h - 2.0 * U_center) / (h * h);
}

double SimulationController::calculate_barrier_height(const MagneticSystem& mag_system, double y_fixed, double chi) const {
    Vector3D B_center = mag_system.calculate_B_total_DMP({0, y_fixed, 0});
    double U_center = mag_system.calculate_potential_U_prime(B_center, chi);
    double U_peak = U_center;
    for (int i = 1; i < mag_system.get_L() * 500; ++i) {
        double z_search = i / 1000.0;
        if (z_search > mag_system.get_L() / 2.0) break;
        Vector3D B_vec = mag_system.calculate_B_total_DMP({0, y_fixed, z_search});
        double u_val = mag_system.calculate_potential_U_prime(B_vec, chi);
        if (u_val > U_peak) U_peak = u_val;
    }
    return U_peak - U_center;
}

std::vector<ParamSweepDataPoint> SimulationController::run_param_sweep_simulation(double M, double a, double chi) const {
    std::vector<ParamSweepDataPoint> results;
    const double y_fixed = 0.7 * a;

    for (int i = 0; i <= 50; ++i) {
        double ratio = 2.0 + (38.0 * i / 50.0);
        MagneticSystem mag_system(M, a, ratio * a);
        double barrier = calculate_barrier_height(mag_system, y_fixed, chi);
        double k_z = calculate_spring_constant(mag_system, y_fixed, chi);
        results.push_back({ratio, barrier, k_z});
    }
    return results;
}

double SimulationController::calculate_fy(double y_bar, const MagneticSystem& mag_system) const {
    const double a = mag_system.get_a();
    const double h = 1e-6;
    auto get_B_sq = [&](double y) {
        Vector3D B_vec = mag_system.calculate_B_total_DMP({0, y, 0});
        return B_vec.x*B_vec.x + B_vec.y*B_vec.y + B_vec.z*B_vec.z;
    };
    double dB2_dy = (get_B_sq(y_bar*a + h) - get_B_sq(y_bar*a - h)) / (2 * h);
    return -a / (pow(MagneticSystem::MU_0, 2) * pow(mag_system.get_M(), 2)) * dB2_dy;
}

double SimulationController::calculate_fz2(double y_bar, const MagneticSystem& mag_system) const {
    const double a = mag_system.get_a();
    const double L = mag_system.get_L();
    const double h = 1e-6;
    auto get_B_sq = [&](double z) {
        Vector3D B_vec = mag_system.calculate_B_total_DMP({0, y_bar * a, z});
        return B_vec.x*B_vec.x + B_vec.y*B_vec.y + B_vec.z*B_vec.z;
    };
    double d2B2_dz2 = (get_B_sq(h) - 2 * get_B_sq(0) + get_B_sq(-h)) / (h * h);
    return L * L / (pow(MagneticSystem::MU_0, 2) * pow(mag_system.get_M(), 2)) * d2B2_dz2;
}

std::vector<ValidationDataPoint> SimulationController::run_validation_curve_generation(double M, double a, double rho) const {
    std::vector<ValidationDataPoint> results;
    const std::vector<int> la_ratios = {8, 4};

    for (int ratio : la_ratios) {
        MagneticSystem mag_system(M, a, static_cast<double>(ratio) * a);
        for (int i = 0; i <= 50; ++i) {
            double y_bar = 0.3 + (0.65 * i / 50.0);
            double fy = calculate_fy(y_bar, mag_system);
            double fz2 = calculate_fz2(y_bar, mag_system);
            
            double radicand = (pow(mag_system.get_L(), 2) * fy) / (RodDynamics::G * a * fz2);
            double Tz_val = (radicand > 0) ? 2 * M_PI * sqrt(radicand) : NAN;
            
            const double h_y = 1e-6;
            auto get_B_sq_y = [&](double y) {
                Vector3D B_vec = mag_system.calculate_B_total_DMP({0, y, 0});
                return B_vec.x*B_vec.x + B_vec.y*B_vec.y + B_vec.z*B_vec.z;
            };
            double dB2_dy = (get_B_sq_y(y_bar*a + h_y) - get_B_sq_y(y_bar*a - h_y)) / (2 * h_y);
            double C = dB2_dy / (MagneticSystem::MU_0 * rho * RodDynamics::G);
            double chi_val = (C < -1.0) ? -2.0 / (1.0 + C) : NAN;

            results.push_back({ratio, y_bar, Tz_val, chi_val});
        }
    }
    return results;
}

} 
