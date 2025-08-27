#pragma once
#include <vector> 
#include <string>

class Geometria {
public:
    int N;       // Número de nodos
    double dx;   // Espaciamiento entre nodos
    std::vector<double> x; // Vector de posiciones espaciales

    Geometria(int n_nodos, double x_min, double x_max);
};

class DiffusionSolver {
private:
    Geometria geo; // Copia de la geometría del sistema
    double D;      // Coeficiente de difusión
    double dt;     // Paso de tiempo
    int N_steps;   // Número de pasos temporales
    double alpha;  // Parámetro de estabilidad
    
public:
    std::vector<double> u; // Perfil de temperatura u(x)

    // Constructor para configurar el solver
    DiffusionSolver(const Geometria& geometria, double coef_D, double paso_t, double t_max);

    // Método principal que ejecuta la simulación
    void resolver();
    
    // Método para guardar los resultados en un archivo
    void exportarSolucion(const std::string& nombre_archivo);
};

void aplicarCondicionInicial(std::vector<double>& u, const std::vector<double>& x);

void aplicarCondicionesDeFrontera(std::vector<double>& u, double T_L, double T_R);