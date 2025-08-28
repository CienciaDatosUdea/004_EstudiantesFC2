#pragma once
#include "geometry.hpp"
#include <vector>
#include <functional>
#include <fstream>
#include <string>

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
    void writeTemperature(const Geometry &G, const Temperature &Campo);
};
