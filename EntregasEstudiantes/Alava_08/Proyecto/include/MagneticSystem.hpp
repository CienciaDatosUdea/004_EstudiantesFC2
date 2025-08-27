#ifndef MAGNETIC_SYSTEM_HPP
#define MAGNETIC_SYSTEM_HPP

#include <vector>
#include <string>
#include <utility> 
#include <tuple>   

namespace MagSim {

    /** @struct Vector3D para manejar coordenadas y campos. */
    struct Vector3D {
        double x = 0.0, y = 0.0, z = 0.0;
    };

    /** @struct CamelbackDataPoint para los datos del potencial. */
    struct CamelbackDataPoint {
        double z_norm;      // Posición normalizada z/L
        double U_prime;     // Energía potencial por unidad de volumen
        int la_ratio;       // Relación L/a para agrupar las curvas
    };
    
    /** @struct ParamSweepDataPoint para los datos del barrido de parámetros. */
    struct ParamSweepDataPoint {
        double la_ratio;      // Relación L/a
        double barrier_height;// Altura de la barrera (ΔU'_M)
        double spring_const;  // Constante de resorte (k'_z)
    };

    /** @struct ValidationDataPoint para las curvas de validación teórica. */
    struct ValidationDataPoint {
        int la_ratio;       // Relación L/a
        double y_norm;      // Altura de equilibrio normalizada y₀/a
        double T_z;         // Período de oscilación teórico
        double chi;         // Susceptibilidad teórica
    };

    // --- Declaración de Clases ---

    class MagneticSystem; 
    
    /**
     * @class RodDynamics
     * @brief Simula la dinámica de la varilla diamagnética.
     */
    class RodDynamics {
    public:
        RodDynamics(double rho, double chi);

        double find_equilibrium_height(const MagneticSystem& mag_system) const;
        std::vector<std::pair<double, double>> simulate_oscillation(const MagneticSystem& mag_system, double y0, double z0, double beta, double total_time, int steps) const;

        static constexpr double G = 9.81;

    private:
        double rho_, chi_;
        
        double vertical_force_prime(double y, const MagneticSystem& mag_system) const;
        double restoring_force_prime(double z, double y0, const MagneticSystem& mag_system) const;
    };


    /**
     * @class MagneticSystem
     * @brief Gestiona los cálculos magnetostáticos del par de imanes.
     */
    class MagneticSystem {
    public:
        MagneticSystem(double M, double a, double L);

        Vector3D calculate_B_total_DMP(const Vector3D& pos) const;
        double calculate_potential_U_prime(const Vector3D& B_vector, double chi) const;
        
        // Métodos para obtener parámetros
        double get_a() const { return a_; }
        double get_L() const { return L_; }
        double get_M() const { return M_; }

        static constexpr double MU_0 = 4 * 3.1415926535 * 1e-7;

    private:
        double M_, a_, L_;
        
        Vector3D calculate_B_DM(const Vector3D& pos) const;
    };

    /**
     * @class SimulationController
     * @brief Diferentes simulaciones y genera los datos para las gráficas.
     */
    class SimulationController {
    public:
        SimulationController();

        // --- Funciones para cada gráfica ---
        std::vector<CamelbackDataPoint> run_camelback_simulation(double M, double a, double chi) const;
        std::vector<ParamSweepDataPoint> run_param_sweep_simulation(double M, double a, double chi) const;
        std::vector<std::pair<double, double>> run_oscillation_simulation(double M, double a, double L, double rho, double chi) const;
        std::vector<ValidationDataPoint> run_validation_curve_generation(double M, double a, double rho) const;
    
    private:
        // Métodos auxiliares para los cálculos del barrido de parámetros
        double calculate_barrier_height(const MagneticSystem& mag_system, double y_fixed, double chi) const;
        double calculate_spring_constant(const MagneticSystem& mag_system, double y_fixed, double chi) const;
        
        // Métodos auxiliares para las curvas de validación
        double calculate_fy(double y_bar, const MagneticSystem& mag_system) const;
        double calculate_fz2(double y_bar, const MagneticSystem& mag_system) const;
    };

} 

#endif 
