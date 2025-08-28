#pragma once
#include "boundary.hpp"
#include <functional>
#include <string>

class DiffusionSolver {
public:
    Temperature& field;
    double D, dt, t_max, TL, TR, alpha;
    std::function<double(double)> f;
    std::string filename;

    DiffusionSolver(Temperature& field,double D,double dt,double t_max,
                    double TL,double TR,std::function<double(double)> f,
                    const std::string &filename);
    void run();
    void step();
};
