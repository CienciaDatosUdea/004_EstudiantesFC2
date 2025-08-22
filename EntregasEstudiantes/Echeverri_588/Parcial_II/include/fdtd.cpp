#include "fdtd.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sys/stat.h>   // Para mkdir en Unix/Linux
#include <sys/types.h>
#ifdef _WIN32
    #include <direct.h>  // Para _mkdir en Windows
#endif

// Constructor
FDTD::FDTD(int nx, double dx, double beta) 
    : nx(nx), dx(dx), beta(beta), current_step(0) {
    
    // Velocidad de la luz (m/s)
    c = 3.0e8;
    
    // Calcular paso temporal basado en beta
    dt = beta * dx / c;
    
    // Inicializar vectores
    Ex_old.resize(nx, 0.0);
    Ex_new.resize(nx, 0.0);
    Hy_old.resize(nx, 0.0);
    Hy_new.resize(nx, 0.0);
    
    printParameters();
}

// Destructor
FDTD::~FDTD() {
    // Los vectores se destruyen automáticamente
}

// Establecer condiciones iniciales
void FDTD::setInitialConditions() {
    std::cout << "Estableciendo condiciones iniciales..." << std::endl;
    
    for (int k = 0; k < nx; k++) {
        double z = k * dx;
        // Ex(z,t=0) = 0.1 * sin(2πz/100)
        // Hy(z,t=0) = 0.1 * sin(2πz/100)
        Ex_old[k] = 0.1 * sin(2.0 * M_PI * z / 100.0);
        Hy_old[k] = 0.1 * sin(2.0 * M_PI * z / 100.0);
    }
    
    std::cout << "Condiciones iniciales establecidas." << std::endl;
}

// Cambiar parámetro beta
void FDTD::setBeta(double new_beta) {
    beta = new_beta;
    dt = beta * dx / c;
    std::cout << "Nuevo beta = " << beta << ", dt = " << dt << std::endl;
}

// Paso temporal con condiciones periódicas
void FDTD::timeStepPeriodic() {
    // Actualizar campos internos (k = 1 to nx-2)
    for (int k = 1; k < nx - 1; k++) {
        // Ecuaciones FDTD según (18) y (19)
        Ex_new[k] = Ex_old[k] + beta * (Hy_old[k-1] - Hy_old[k+1]);
        Hy_new[k] = Hy_old[k] + beta * (Ex_old[k-1] - Ex_old[k+1]);
    }
    
    // Condiciones de frontera periódicas según (20)-(23)
    // Ex en fronteras
    Ex_new[0] = Ex_old[0] + beta * (Hy_old[nx-2] - Hy_old[1]);
    Ex_new[nx-1] = Ex_old[nx-1] + beta * (Hy_old[nx-2] - Hy_old[1]);
    
    // Hy en fronteras
    Hy_new[0] = Hy_old[0] + beta * (Ex_old[nx-2] - Ex_old[1]);
    Hy_new[nx-1] = Hy_old[nx-1] + beta * (Ex_old[nx-2] - Ex_old[1]);
    
    // Copiar nuevos valores a viejos
    Ex_old = Ex_new;
    Hy_old = Hy_new;
    
    current_step++;
}

// Paso temporal con condiciones de frontera cero
void FDTD::timeStepZeroBoundary() {
    // Actualizar campos internos (k = 1 to nx-2)
    for (int k = 1; k < nx - 1; k++) {
        Ex_new[k] = Ex_old[k] + beta * (Hy_old[k-1] - Hy_old[k+1]);
        Hy_new[k] = Hy_old[k] + beta * (Ex_old[k-1] - Ex_old[k+1]);
    }
    
    // Condiciones de frontera cero: E = H = 0 en z = 0 y z = 200
    Ex_new[0] = 0.0;
    Ex_new[nx-1] = 0.0;
    Hy_new[0] = 0.0;
    Hy_new[nx-1] = 0.0;
    
    // Copiar nuevos valores a viejos
    Ex_old = Ex_new;
    Hy_old = Hy_new;
    
    current_step++;
}

// Simular evolución temporal
void FDTD::simulate(int num_steps, const std::string& boundary_type) {
    std::cout << "Iniciando simulación con " << num_steps << " pasos temporales." << std::endl;
    std::cout << "Condiciones de frontera: " << boundary_type << std::endl;
    
    current_step = 0;
    
    for (int n = 0; n < num_steps; n++) {
        if (boundary_type == "periodic") {
            timeStepPeriodic();
        } else if (boundary_type == "zero") {
            timeStepZeroBoundary();
        } else {
            std::cerr << "Error: Tipo de condición de frontera no válida." << std::endl;
            return;
        }
        
        // Verificar estabilidad cada 100 pasos
        if (n % 100 == 0) {
            if (!isStable()) {
                std::cout << "¡Advertencia! Simulación inestable en paso " << n << std::endl;
                std::cout << "Amplitud máxima: " << getMaxAmplitude() << std::endl;
                break;
            }
        }
    }
    
    std::cout << "Simulación completada. Pasos realizados: " << current_step << std::endl;
    std::cout << "Amplitud máxima final: " << getMaxAmplitude() << std::endl;
}

// Verificar estabilidad
bool FDTD::isStable() const {
    double max_amplitude = getMaxAmplitude();
    return max_amplitude < 10.0; // Criterio de estabilidad
}

// Obtener amplitud máxima
double FDTD::getMaxAmplitude() const {
    double max_Ex = 0.0, max_Hy = 0.0;
    
    for (int k = 0; k < nx; k++) {
        max_Ex = std::max(max_Ex, std::abs(Ex_old[k]));
        max_Hy = std::max(max_Hy, std::abs(Hy_old[k]));
    }
    
    return std::max(max_Ex, max_Hy);
}

// Calcular energía total
double FDTD::getEnergy() const {
    double energy = 0.0;
    
    for (int k = 0; k < nx; k++) {
        energy += Ex_old[k] * Ex_old[k] + Hy_old[k] * Hy_old[k];
    }
    
    return energy * dx / 2.0; // Factor de normalización
}

// Guardar datos a archivo
void FDTD::saveToFile(const std::string& filename) const {
    // Crear carpeta "results/" si no existe
#ifdef _WIN32
    _mkdir("results");
#else
    mkdir("results", 0777);
#endif

    std::string full_path = "results/" + filename;
    std::ofstream file(full_path);

    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << full_path << std::endl;
        return;
    }

    file << "# z Ex Hy" << std::endl;
    file << std::fixed << std::setprecision(6);

    for (int k = 0; k < nx; k++) {
        double z = k * dx;
        file << z << " " << Ex_old[k] << " " << Hy_old[k] << std::endl;
    }

    file.close();
    std::cout << "Datos guardados en: " << full_path << std::endl;
}

// Imprimir parámetros de simulación
void FDTD::printParameters() const {
    std::cout << "=== Parámetros de Simulación FDTD ===" << std::endl;
    std::cout << "Número de puntos espaciales (nx): " << nx << std::endl;
    std::cout << "Paso espacial (dx): " << dx << std::endl;
    std::cout << "Paso temporal (dt): " << dt << " s" << std::endl;
    std::cout << "Parámetro beta (c*dt/dx): " << beta << std::endl;
    std::cout << "Velocidad de la luz (c): " << c << " m/s" << std::endl;
    
    if (beta <= 0.5) {
        std::cout << "✓ Condición de Courant satisfecha (beta ≤ 0.5)" << std::endl;
    } else {
        std::cout << "✗ ¡ADVERTENCIA! Condición de Courant violada (beta > 0.5)" << std::endl;
        std::cout << "  La simulación puede ser inestable." << std::endl;
    }
    std::cout << "=====================================" << std::endl;
}

// Imprimir campos
void FDTD::printFields(int start_idx, int end_idx) const {
    if (end_idx == -1) end_idx = nx;
    
    std::cout << "=== Campos en paso temporal " << current_step << " ===" << std::endl;
    std::cout << std::setw(8) << "k" << std::setw(12) << "z" 
              << std::setw(12) << "Ex" << std::setw(12) << "Hy" << std::endl;
    std::cout << std::string(44, '-') << std::endl;
    
    std::cout << std::fixed << std::setprecision(6);
    for (int k = start_idx; k < std::min(end_idx, nx); k++) {
        double z = k * dx;
        std::cout << std::setw(8) << k << std::setw(12) << z 
                  << std::setw(12) << Ex_old[k] << std::setw(12) << Hy_old[k] << std::endl;
    }
    std::cout << std::endl;
}

// Análisis de estabilidad para diferentes valores de beta
void FDTD::stabilityAnalysis(const std::vector<double>& beta_values, int num_steps) {
    std::cout << "\n=== Análisis de Estabilidad ===" << std::endl;
    std::cout << "Probando diferentes valores de beta:" << std::endl;
    
    // Guardar estado actual
    std::vector<double> Ex_backup = Ex_old;
    std::vector<double> Hy_backup = Hy_old;
    int step_backup = current_step;
    
    std::cout << std::setw(8) << "Beta" << std::setw(15) << "Condición" 
              << std::setw(15) << "Amplitud Final" << std::setw(12) << "Estado" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    for (double test_beta : beta_values) {
        // Restaurar condiciones iniciales
        setInitialConditions();
        setBeta(test_beta);
        
        // Simular
        simulate(num_steps, "periodic");
        
        // Analizar resultado
        double final_amplitude = getMaxAmplitude();
        std::string condition = (test_beta <= 0.5) ? "beta ≤ 0.5" : "beta > 0.5";
        std::string status = (final_amplitude < 10.0) ? "Estable" : "Inestable";
        
        std::cout << std::fixed << std::setprecision(3);
        std::cout << std::setw(8) << test_beta << std::setw(15) << condition 
                  << std::setw(15) << final_amplitude << std::setw(12) << status << std::endl;
    }
    
    std::cout << "\nConclusiones:" << std::endl;
    std::cout << "- beta ≤ 0.5: Simulación estable (Condición de Courant)" << std::endl;
    std::cout << "- beta > 0.5: Simulación inestable, amplitudes divergen" << std::endl;
    
    // Restaurar estado original
    Ex_old = Ex_backup;
    Hy_old = Hy_backup;
    current_step = step_backup;
}