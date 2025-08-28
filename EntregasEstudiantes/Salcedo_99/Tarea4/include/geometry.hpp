#pragma once
#include <vector>

class Geometry {
public:
    Geometry(double x_min, double x_max, int N);
    double dx;
    double x_min, x_max;
    int N;
    std::vector<double> x;
};
