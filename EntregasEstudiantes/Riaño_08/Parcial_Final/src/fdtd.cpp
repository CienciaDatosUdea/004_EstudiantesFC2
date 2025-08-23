#include "../include/fdtd.h"
#include <iostream>
#include <cmath>
#include <vector>

/**
 * @brief Constructor de la clase FDTD que inicializa con un valor de beta.
 * @param x_max Número de puntos en el espacio.
 * @param beta_val Valor del parámetro de Courant (β = dt/dz).
 */
FDTD::FDTD(int x_max, double beta_val) : xmax(x_max), beta(beta_val) {
    Ex.resize(xmax, 0.0);
    Hy.resize(xmax, 0.0);
}

/**
 * @brief Constructor que calcula beta a partir de los pasos de tiempo y espacio.
 * @param xmax Número de puntos en el espacio.
 * @param dz Tamaño de la celda espacial (Δz).
 * @param dt Tamaño del paso de tiempo (Δt).
 */
FDTD::FDTD(int xmax, double dz, double dt) : xmax(xmax), beta(dt / dz), dz(dz), dt(dt) {
    Ex.resize(xmax, 0.0);
    Hy.resize(xmax, 0.0);
}

/**
 * @brief Inicializa los campos eléctrico (E) y magnético (H) con una onda sinusoidal.
 * La inicialización se realiza con los campos desfasados en el espacio para
 * la grilla de Yee.
 */
void FDTD::initialize_fields_sinusoidal() {
    for (int k = 0; k < xmax; ++k) {
        Ex[k] = 0.1 * std::sin(2 * M_PI * k / 100.0);
        Hy[k] = 0.1 * std::sin(2 * M_PI * (k + 0.5) / 100.0);
    }
    // Guarda el estado inicial de los campos en el historial
    E_history.push_back(Ex);
    H_history.push_back(Hy);
}

/**
 * @brief Ejecuta la simulación FDTD paso a paso.
 * @param total_steps El número total de pasos de tiempo a simular.
 * @param boundary_conditions El tipo de condiciones de frontera ("periodic" o "fixed").
 */
void FDTD::run_simulation(int total_steps, const std::string& boundary_conditions) {
    std::vector<double> Hy_temp = Hy;
    std::vector<double> Ex_temp = Ex;

    for (int t_step = 1; t_step < total_steps; ++t_step) {
        // Se actualiza el campo magnético Hy
        // Se utiliza un bucle que va desde el inicio hasta antes del último punto para evitar el borde
        for (int k = 0; k < xmax - 1; ++k) {
            Hy_temp[k] = Hy[k] + beta * (Ex[k] - Ex[k + 1]);
        }
        // Se actualiza el campo magnético en el borde para condiciones periódicas
        if (boundary_conditions == "periodic") {
            Hy_temp[xmax - 1] = Hy[xmax - 1] + beta * (Ex[xmax - 1] - Ex[0]);
        }

        // Se actualiza el campo eléctrico Ex
        // Se utiliza un bucle que va desde el segundo punto para evitar el borde
        for (int k = 1; k < xmax; ++k) {
            Ex_temp[k] = Ex[k] + beta * (Hy_temp[k-1] - Hy_temp[k]);
        }
        // Se actualiza el campo eléctrico en el borde para condiciones periódicas
        if (boundary_conditions == "periodic") {
            Ex_temp[0] = Ex[0] + beta * (Hy_temp[xmax - 1] - Hy_temp[0]);
        }
        
        // Se aplican las condiciones de frontera fijas
        // Se anulan los valores de los campos en los puntos inicial y final
        if (boundary_conditions == "fixed") {
            Ex_temp[0] = 0.0;
            Ex_temp[xmax - 1] = 0.0;
            Hy_temp[0] = 0.0;
            Hy_temp[xmax - 1] = 0.0;
        }

        // Se copian los valores temporales a los campos principales
        Ex = Ex_temp;
        Hy = Hy_temp;
        
        // Se guardan los datos del paso actual en el historial
        E_history.push_back(Ex);
        H_history.push_back(Hy);
    }
}

/**
 * @brief Obtiene el historial completo del campo eléctrico.
 * @return Una referencia constante al vector que contiene la historia del campo E.
 */
const std::vector<std::vector<double>>& FDTD::get_E_history() const {
    return E_history;
}

/**
 * @brief Obtiene el historial completo del campo magnético.
 * @return Una referencia constante al vector que contiene la historia del campo H.
 */
const std::vector<std::vector<double>>& FDTD::get_H_history() const {
    return H_history;
}
