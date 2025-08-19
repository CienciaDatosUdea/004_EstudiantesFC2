#ifndef DIFUSION_MODEL_H
#define DIFUSION_MODEL_H

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

class Geometria {
public:
    int N;
    double dx, xmin, xmax;
    std::vector<double> x;

    Geometria(int N_, double xmin_, double xmax_);
};

class Condiciones {
public:
    std::vector<double> u;
    double TL, TR; // Temperaturas en los bordes

    Condiciones(Geometria &G, double TL_, double TR_);
    void condicionesIniciales(double alpha);
    void condicionesFrontera(Geometria &G);
};

class DiffusionSolver {
public:
    double D, dt, t_max;
    int Nsteps;
    double alpha; // Parámetro de estabilidad

    DiffusionSolver(double D_, double dt_, double t_max_);
    void verificarEstabilidad(Geometria &G);
    void resolver(Geometria &G, Condiciones &C);
    void exportarResultados(Geometria &G, Condiciones &C, const std::string &nombreArchivo);
};

#endif
