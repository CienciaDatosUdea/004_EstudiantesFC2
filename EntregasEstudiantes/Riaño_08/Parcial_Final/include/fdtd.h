#ifndef FDTD_H
#define FDTD_H

#include <vector>
#include <string>

/**
 * @class FDTD
 * @brief Implementa el método de Diferencias Finitas en el Dominio del Tiempo (FDTD)
 * para simular la propagación de una onda electromagnética en 1D.
 *
 * Esta clase gestiona la inicialización de los campos, la simulación paso a paso
 * y el manejo de las condiciones de frontera.
 */
class FDTD {
public:
    /**
     * @brief Constructor que inicializa la simulación con un valor predefinido para beta.
     * @param xmax El número de puntos en la grilla espacial.
     * @param beta El valor del parámetro de Courant (β = dt/dz).
     */
    FDTD(int xmax, double beta);

    /**
     * @brief Constructor que calcula el valor de beta a partir de los pasos de tiempo y espacio.
     * @param xmax El número de puntos en la grilla espacial.
     * @param dz El tamaño de la celda espacial (Δz).
     * @param dt El tamaño del paso de tiempo (Δt).
     */
    FDTD(int xmax, double dz, double dt);

    /**
     * @brief Inicializa los campos eléctrico y magnético con una onda sinusoidal.
     */
    void initialize_fields_sinusoidal();

    /**
     * @brief Ejecuta la simulación FDTD por un número de pasos de tiempo.
     * @param total_steps El número total de pasos de tiempo a simular.
     * @param boundary_conditions Tipo de condiciones de frontera ("periodic" o "fixed").
     */
    void run_simulation(int total_steps, const std::string& boundary_conditions);

    /**
     * @brief Obtiene el historial completo de los valores del campo eléctrico.
     * @return Una referencia constante al vector que contiene la historia del campo E.
     */
    const std::vector<std::vector<double>>& get_E_history() const;

    /**
     * @brief Obtiene el historial completo de los valores del campo magnético.
     * @return Una referencia constante al vector que contiene la historia del campo H.
     */
    const std::vector<std::vector<double>>& get_H_history() const;

private:
    int xmax;                                   ///< Número de puntos de la grilla.
    double beta;                                ///< Parámetro de Courant.
    double dz;                                  ///< Paso espacial (Δz).
    double dt;                                  ///< Paso de tiempo (Δt).
    std::vector<double> Ex;                     ///< Vector para los valores del campo eléctrico E.
    std::vector<double> Hy;                     ///< Vector para los valores del campo magnético H.
    std::vector<double> Ex_new;                 ///< Vector temporal para los nuevos valores de E.
    std::vector<double> Hy_new;                 ///< Vector temporal para los nuevos valores de H.
    std::vector<std::vector<double>> E_history; ///< Historial de los valores del campo E en cada paso de tiempo.
    std::vector<std::vector<double>> H_history; ///< Historial de los valores del campo H en cada paso de tiempo.
};

#endif // FDTD_H
