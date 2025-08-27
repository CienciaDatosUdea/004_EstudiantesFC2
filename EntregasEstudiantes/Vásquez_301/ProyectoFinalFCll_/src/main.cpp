#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <tuple>
#include "../include/MagneticSystem.hpp"

// Usamos el namespace para facilitar el acceso a nuestras clases
using namespace MagSim;

// Funciones auxiliares para escribir los datos a archivos 

void write_camelback_data(const std::string& filename, const std::vector<CamelbackDataPoint>& data) {
    std::ofstream file(filename);
    file << std::fixed << std::setprecision(8);
    // Formato: z_norm U_prime la_ratio
    for (const auto& p : data) {
        file << p.z_norm << "\t" << p.U_prime << "\t" << p.la_ratio << "\n";
    }
}

void write_paramsweep_data(const std::string& filename, const std::vector<ParamSweepDataPoint>& data) {
    std::ofstream file(filename);
    file << std::fixed << std::setprecision(8);
    // Formato: la_ratio barrier_height spring_const
    for (const auto& p : data) {
        file << p.la_ratio << "\t" << p.barrier_height << "\t" << p.spring_const << "\n";
    }
}

void write_oscillation_data(const std::string& filename, const std::vector<std::pair<double, double>>& data) {
    std::ofstream file(filename);
    file << std::fixed << std::setprecision(8);
    // Formato: time position_mm
    for (const auto& p : data) {
        file << p.first << "\t" << p.second << "\n";
    }
}

void write_validation_data(const std::string& filename, const std::vector<ValidationDataPoint>& data) {
    std::ofstream file(filename);
    file << std::fixed << std::setprecision(8);
    // Formato: la_ratio y_norm T_z chi
    for (const auto& p : data) {
        file << p.la_ratio << "\t" << p.y_norm << "\t" << p.T_z << "\t" << p.chi << "\n";
    }
}


int main() {
    std::cout << "--- Inicio ---" << std::endl;

    // Parámetros de Simulación
    const double M = 1e6;
    const double a = 3.2e-3;
    const double RHO_GRAFITO = 2200.0;
    const double CHI_GRAFITO = -2.0e-4;
    const double L8 = 8.0 * a; // Longitud para L/a = 8

    // Creamos el controlador principal de simulaciones
    SimulationController controller;

    // --- 1. Simulación del Potencial Camelback ---
    std::cout << "\n[1/4] Generando datos para el potencial 'Camelback'..." << std::endl;
    auto camelback_data = controller.run_camelback_simulation(M, a, CHI_GRAFITO);
    write_camelback_data("data/camelback.txt", camelback_data);
    std::cout << " -> Datos guardados en data/camelback.txt" << std::endl;

    // --- 2. Simulación del Barrido de Parámetros ---
    std::cout << "\n[2/4] Realizando barrido de parámetros (L/a)..." << std::endl;
    auto paramsweep_data = controller.run_param_sweep_simulation(M, a, CHI_GRAFITO);
    write_paramsweep_data("data/paramsweep.txt", paramsweep_data);
    std::cout << " -> Datos guardados en data/paramsweep.txt" << std::endl;
    
    // --- 3. Simulación de la Oscilación de la Varilla ---
    std::cout << "\n[3/4] Simulando la dinámica de la oscilación..." << std::endl;
    // Necesitamos y0 para esta simulación. Lo calculamos aquí e imprimimos.
    MagneticSystem mag_system_l8(M, a, L8);
    RodDynamics dynamics(RHO_GRAFITO, CHI_GRAFITO);
    double y0 = dynamics.find_equilibrium_height(mag_system_l8);
    
    std::cout << " -> Altura de equilibrio calculada: y0 = " << y0 << " m" << std::endl;
    
    auto oscillation_data = dynamics.simulate_oscillation(mag_system_l8, y0, 2.0e-3, 500.0, 25.0, 1000);
    write_oscillation_data("data/oscillation.txt", oscillation_data);
    std::cout << " -> Datos guardados en data/oscillation.txt" << std::endl;

    // --- 4. Generación de las Curvas de Validación ---
    std::cout << "\n[4/4] Generando curvas teóricas de validación..." << std::endl;
    auto validation_data = controller.run_validation_curve_generation(M, a, RHO_GRAFITO);
    write_validation_data("data/validation_curves.txt", validation_data);
    std::cout << " -> Datos guardados en data/validation_curves.txt" << std::endl;

    std::cout << "\n--- Finalizado ---" << std::endl;
    
    return 0;
}