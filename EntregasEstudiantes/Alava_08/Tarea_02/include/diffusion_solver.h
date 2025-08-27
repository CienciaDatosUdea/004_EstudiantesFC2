#pragma once
#include <vector>
#include <string>
#include <iostream>

// ==========================================================
// Clase que define la geometría del sistema (malla 1D)
// ==========================================================
class Geometria {
public:
    explicit Geometria(int N, double xmin, double xmax);

    int N;                 // número de puntos
    double dx;             // paso espacial
    double xmin, xmax;     // extremos de la malla
    std::vector<double> x; // posiciones espaciales
};

// ==========================================================
// Clase que maneja las condiciones iniciales y de frontera
// ==========================================================
class Condiciones {
public:
    explicit Condiciones(Geometria &geo);

    Geometria &G;           // referencia a la geometría
    std::vector<double> u;  // vector de temperaturas

    // Definir condición inicial (ej: gaussiana)
    void condicionesIniciales(double alpha, double x0);

    // Condiciones de frontera Dirichlet
    void condicionesFrontera(double TL, double TR);
};

// ==========================================================
// Clase que implementa el solver de difusión 1D
// ==========================================================
class DiffusionSolver {
public:
    explicit DiffusionSolver(double D, double dt, double t_max);

    double D;      // coeficiente de difusión
    double dt;     // paso temporal
    double t_max;  // tiempo máximo de simulación

    // Resolver usando esquema explícito FTCS
    void resolverFTCS(Condiciones &cond, double TL, double TR);

    // Verificar estabilidad (criterio de Courant)
    bool verificarEstabilidad(double dx) const;
};

// ==========================================================
// Función auxiliar para guardar resultados en un archivo
// ==========================================================
void guardarResultado(const Geometria &geo,
                      const Condiciones &cond,
                      const std::string &nombreArchivo);
