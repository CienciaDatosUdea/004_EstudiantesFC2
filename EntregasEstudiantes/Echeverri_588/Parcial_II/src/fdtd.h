#ifndef FDTD_H
#define FDTD_H

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

class FDTD {
private:
    int nx;                    // Número de puntos espaciales
    double dx;                 // Paso espacial (Δz)
    double dt;                 // Paso temporal (Δt)
    double beta;               // Parámetro de Courant (c*Δt/Δz)
    double c;                  // Velocidad de la luz
    
    std::vector<double> Ex_old;    // Campo eléctrico en tiempo viejo
    std::vector<double> Ex_new;    // Campo eléctrico en tiempo nuevo
    std::vector<double> Hy_old;    // Campo magnético en tiempo viejo
    std::vector<double> Hy_new;    // Campo magnético en tiempo nuevo
    
    int current_step;              // Paso temporal actual

public:
    // Constructor
    FDTD(int nx = 200, double dx = 1.0, double beta = 0.4);
    
    // Destructor
    ~FDTD();
    
    // Métodos para configuración inicial
    void setInitialConditions();
    void setBeta(double new_beta);
    
    // Métodos de simulación
    void timeStepPeriodic();
    void timeStepZeroBoundary();
    void simulate(int num_steps, const std::string& boundary_type = "periodic");
    
    // Métodos de análisis
    bool isStable() const;
    double getMaxAmplitude() const;
    double getEnergy() const;
    
    // Métodos de acceso
    std::vector<double> getEx() const { return Ex_old; }
    std::vector<double> getHy() const { return Hy_old; }
    double getBeta() const { return beta; }
    double getDt() const { return dt; }
    double getDx() const { return dx; }
    int getCurrentStep() const { return current_step; }
    
    // Métodos de salida
    void saveToFile(const std::string& filename) const;
    void printParameters() const;
    void printFields(int start_idx = 0, int end_idx = -1) const;
    
    // Método para análisis de estabilidad
    void stabilityAnalysis(const std::vector<double>& beta_values, int num_steps);
};

#endif // FDTD_H