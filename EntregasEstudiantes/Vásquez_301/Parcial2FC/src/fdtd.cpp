#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "fdtd.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

// Definición del constructor
FDTDSimulator::FDTDSimulator(int n_nodes, double beta) : N(n_nodes), BETA(beta) {
    // Redimensionamos los vectores para los campos
    Ex.assign(N, std::vector<double>(2, 0.0));
    Hy.assign(N, std::vector<double>(2, 0.0));
    boundary_type = "periodic"; // Por defecto
    initialize_fields();
}

void FDTDSimulator::initialize_fields() {
    for (int k = 0; k < N; ++k) {
        double z = k;
        Ex[k][0] = 0.1 * sin(2.0 * M_PI * z / 100.0);
        Hy[k][0] = 0.1 * sin(2.0 * M_PI * z / 100.0);
    }
}

void FDTDSimulator::set_boundary_conditions(const std::string& type) {
    if (type == "periodic" || type == "absorbing") {
        boundary_type = type;
    } else {
        throw std::invalid_argument("Tipo de frontera no válido. Use 'periodic' o 'absorbing'.");
    }
}

void FDTDSimulator::update_step() {
    // 1. Calcular los nuevos valores 
    for (int k = 1; k < N - 1; ++k) {
        Ex[k][1] = Ex[k][0] + BETA * (Hy[k - 1][0] - Hy[k + 1][0]);
        Hy[k][1] = Hy[k][0] + BETA * (Ex[k - 1][0] - Ex[k + 1][0]);
    }
    apply_boundaries();

    // Filtro de promedio para suprimir la inestabilidad
    std::vector<double> filtered_Ex(N);
    std::vector<double> filtered_Hy(N);

    // Aplicar filtro a los puntos interiores
    for (int k = 1; k < N - 1; ++k) {
        // Promedio simple de 3 puntos para suavizar el ruido
        filtered_Ex[k] = (Ex[k - 1][1] + Ex[k][1] + Ex[k + 1][1]) / 3.0;
        filtered_Hy[k] = (Hy[k - 1][1] + Hy[k][1] + Hy[k + 1][1]) / 3.0;
    }
    
    // Para los bordes, simplemente copiamos el valor sin filtrar 
    filtered_Ex[0] = Ex[0][1];
    filtered_Ex[N - 1] = Ex[N - 1][1];
    filtered_Hy[0] = Hy[0][1];
    filtered_Hy[N - 1] = Hy[N - 1][1];

    // 3. Copiar los valores FILTRADOS para el siguiente paso de tiempo
    for (int k = 0; k < N; ++k) {
        Ex[k][0] = filtered_Ex[k];
        Hy[k][0] = filtered_Hy[k];
    }
}

void FDTDSimulator::apply_boundaries() {
    if (boundary_type == "periodic") {
        // Usamos las condiciones de frontera periódicas 
        Ex[0][1] = Ex[0][0] + BETA * (Hy[N - 1][0] - Hy[1][0]);
        Ex[N - 1][1] = Ex[N - 1][0] + BETA * (Hy[N - 2][0] - Hy[0][0]);
        Hy[0][1] = Hy[0][0] + BETA * (Ex[N - 1][0] - Ex[1][0]);
        Hy[N - 1][1] = Hy[N - 1][0] + BETA * (Ex[N - 2][0] - Ex[0][0]);
    } else { // absorbing
        Ex[0][1] = 0.0;
        Hy[0][1] = 0.0;
        Ex[N - 1][1] = 0.0;
        Hy[N - 1][1] = 0.0;
    }
}

void FDTDSimulator::save_data(std::ofstream& file) {
    for (int k = 0; k < N; ++k) {
        file << Ex[k][0] << (k == N - 1 ? "" : " ");
    }
    file << "\n";
}

void FDTDSimulator::run(int num_steps, int plot_every, const std::string& output_filename) {
    std::ofstream data_file(output_filename);
    for (int t = 0; t < num_steps; ++t) {
        update_step();
        if (t % plot_every == 0) {
            save_data(data_file);
        }
    }
    data_file.close();
    std::cout << "Simulación para '" << output_filename << "' completada." << std::endl;
}