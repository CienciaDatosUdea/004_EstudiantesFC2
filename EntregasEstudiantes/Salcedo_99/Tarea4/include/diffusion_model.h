#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include <string>

class Geometry {
public:
    Geometry(double x_min, double x_max, int N);
    double dx;
    double x_min, x_max;
    int N;
    std::vector<double> x;
};

class Temperature {
public:
    Temperature(Geometry &g);
    Geometry &g;
    std::vector<double> T;
    void applyInitialCondition(std::function<double(double)> f);
    void applyBoundaryCondition(double TL, double TR);
};

class FieldWriter {
public:
    FieldWriter(const std::string &filename);
    std::ofstream file;
    void writeTemperature(const Geometry &G, const Temperature &Campo, double time=0.0);
};

class DiffusionSolver {
public:
    Temperature& field;
    double D, dt, t_max, TL, TR, alpha;
    std::function<double(double)> f;
    std::string filename;

    DiffusionSolver(Temperature& field, double D, double dt, double t_max,
                    double TL, double TR, std::function<double(double)> f,
                    const std::string &filename);

    void run();
    void step();
};
