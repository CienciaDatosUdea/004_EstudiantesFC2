#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <fstream>
#include "../include/diffusion_model.h"

using namespace std;

// Constructor de la clase Temperature
Temperature::Temperature(Geometry &g_):g(g_),T(g.N, 0.0){}

// Aplica las condiciones de frontera de Dirichlet sobre el campo de temperatura (RF3 - Historia 3)
void Temperature::applyBoundaryCondition(double TL,double TR){
    T[0] = TL;
    T[g.N-1] = TR;
}

// Aplica la condición inicial sobre el campo de temperatura (RF2 - Historia 2)
void Temperature::applyInitialCondition(std::function<double(double)> f){
    for (int i=1;i<g.N-1;i++){
        T[i] = f(g.x[i]);
    }
}

