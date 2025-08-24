#ifndef DIFUSION_MODEL_H
#define DIFUSION_MODEL_H

#include <iostream>
#include <vector>
#include <cmath>

// Define una pequeñaa constante para la comparación de flotantes
const double EPSILON = 1e-9;

// Clase para definir el dominio espacial
class Geometria {
public:
    // Constructor que inicializa el dominio con N nodos, xmin y xmax
    Geometria(int N, double xmin, double xmax);
    
    // Variables miembro públicas
    int N;             // Núamero de nodos
    double dx;         // Espaciamiento uniforme
    double xmin, xmax; // Límites del dominio
    std::vector<double> x; // Vector de posiciones espaciales
};

// Clase para manejar las condiciones iniciales y de frontera
class Condiciones {
public:
    // Constructor que inicializa con una referencia a un objeto Geometria
    Condiciones(Geometria& G);
    
    // Métodos
    void condicionesIniciales(); // Aplica una distribución Gaussiana como condición inicial
    void condicionesFrontera(double TL, double TR); // Aplica condiciones de frontera de Dirichlet
    
    // Variables miembro
    Geometria& G;
    std::vector<double> u; // Vector de temperaturas
};

// Clase para resolver la ecuación de difusión usando FTCS
class DiffusionSolver {
public:
    // Constructor
    DiffusionSolver(Geometria& G, double D, double dt, double t_max);
    
    // Métodos
    void verificarEstabilidad(); // Verifica la condición de estabilidad FTCS
    void evolucionTemporal(Condiciones& C, double TL, double TR); // Resuelve la evolución temporal del sistema
    
    // Variables miembro
    Geometria& G;
    double D;         // Coeficiente de difusión
    double dt;        // Paso de tiempo
    double t_max;     // Tiempo máximo de simulación
    double alpha;     // Parámetro de estabilidad
    int Nsteps;       // Núamero de pasos de tiempo
};

#endif // DIFUSION_MODEL_H
