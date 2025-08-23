#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip> // Necesaria para std::fixed y std::setprecision
#include <sstream> // Necesaria para std::stringstream
#include "include/fdtd.h"

/**
 * @brief Guarda un vector de vectores de datos en un archivo de texto.
 * @param filename El nombre del archivo de salida.
 * @param data Los datos a guardar, representados como un vector de vectores.
 */
void save_data_to_file(const std::string& filename, const std::vector<std::vector<double>>& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }
    
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i] << (i == row.size() - 1 ? "" : " ");
        }
        file << "\n";
    }
    file.close();
}

/**
 * @brief Guarda el último paso de tiempo de una simulación en un archivo de texto.
 * @param filename El nombre del archivo de salida.
 * @param data El vector que contiene los datos del último paso de tiempo.
 */
void save_final_step_to_file(const std::string& filename, const std::vector<double>& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
        return;
    }
    
    for (size_t i = 0; i < data.size(); ++i) {
        file << data[i] << (i == data.size() - 1 ? "" : " ");
    }
    file << "\n";
    file.close();
}

/**
 * @brief Función principal del programa.
 *
 * Configura y ejecuta dos simulaciones FDTD principales (una periódica y una fija)
 * y un conjunto de simulaciones de exploración con diferentes valores de beta.
 * Los resultados se guardan en archivos de texto para su posterior análisis.
 */
int main() {
    int xmax = 200;
    double beta = 0.45;
    int total_steps = 1001; // Cambiado a 1001 para incluir t=1000

    // Simulación 1: Condiciones de Frontera Periódicas
    // Se crea una instancia de FDTD con el beta definido y se ejecuta con condiciones periódicas.
    FDTD sim_periodic_stable(xmax, beta);
    sim_periodic_stable.initialize_fields_sinusoidal();
    sim_periodic_stable.run_simulation(total_steps, "periodic");
    save_data_to_file("data_E_periodic_stable.txt", sim_periodic_stable.get_E_history());
    save_data_to_file("data_H_periodic_stable.txt", sim_periodic_stable.get_H_history());
    
    // Simulación 2: Condiciones de Frontera Fijas
    // Se crea una instancia de FDTD con el mismo beta y se ejecuta con condiciones fijas.
    FDTD sim_fixed_stable(xmax, beta);
    sim_fixed_stable.initialize_fields_sinusoidal();
    sim_fixed_stable.run_simulation(total_steps, "fixed");
    save_data_to_file("data_E_fixed_stable.txt", sim_fixed_stable.get_E_history());
    save_data_to_file("data_H_fixed_stable.txt", sim_fixed_stable.get_H_history());

    std::cout << "Simulaciones completas. Datos guardados en la carpeta python." << std::endl;

    // NUEVO CÓDIGO para la exploración de beta
    // Se definen los valores de dz y dt a probar.
    double dz_options[] = {0.01, 0.02, 0.03};
    double dt_options[] = {0.004, 0.01, 0.02};
    int num_dz = 3;
    int num_dt = 3;

    std::cout << "Generando datos para el explorador de beta con fronteras fijas..." << std::endl;

    // Se iteran todas las combinaciones de dz y dt para explorar la estabilidad.
    for (int i = 0; i < num_dz; ++i) {
        for (int j = 0; j < num_dt; ++j) {
            double current_dz = dz_options[i];
            double current_dt = dt_options[j];
            
            // Se crea una nueva simulación para cada combinación.
            FDTD explorer_sim(xmax, current_dz, current_dt);
            explorer_sim.initialize_fields_sinusoidal();
            explorer_sim.run_simulation(total_steps, "fixed");
            
            // Se obtiene y guarda solo el último paso de tiempo para el análisis.
            std::vector<double> E_final = explorer_sim.get_E_history().back();
            std::vector<double> H_final = explorer_sim.get_H_history().back();

            // Usar un stringstream para formatear los nombres de archivo.
            std::stringstream ss_E;
            ss_E << std::fixed << std::setprecision(2) << "E_fixed_dz_" << current_dz << "_dt_";
            // Se ajusta la precisión para el caso específico de 0.004.
            if (current_dt == 0.004) {
                ss_E << std::fixed << std::setprecision(3) << current_dt;
            } else {
                ss_E << std::fixed << std::setprecision(2) << current_dt;
            }
            ss_E << ".txt";
            std::string filename_E = ss_E.str();
            
            std::stringstream ss_H;
            ss_H << std::fixed << std::setprecision(2) << "H_fixed_dz_" << current_dz << "_dt_";
            if (current_dt == 0.004) {
                ss_H << std::fixed << std::setprecision(3) << current_dt;
            } else {
                ss_H << std::fixed << std::setprecision(2) << current_dt;
            }
            ss_H << ".txt";
            std::string filename_H = ss_H.str();
            
            // Se guardan los datos del paso final en un archivo.
            save_final_step_to_file(filename_E, E_final);
            save_final_step_to_file(filename_H, H_final);

            std::cout << "Simulación para dz=" << current_dz << ", dt=" << current_dt << ", beta=" << current_dt/current_dz << " guardada." << std::endl;
        }
    }

    std::cout << "Todos los datos de beta explorer generados. Revisa la carpeta python." << std::endl;

    return 0;
}