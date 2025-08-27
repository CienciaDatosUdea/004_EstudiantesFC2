#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <fstream>
#include "../include/diffusion_model.h"

using namespace std;

// Constructor de la clase Geometry (RF1 - Historia 1)
Geometry::Geometry(double xmin,double xmax,int N_):x_min(xmin),x_max(xmax),N(N_){
    dx = (x_max-x_min)/(N-1.0L);
    x.resize(N);
    // posiciones de la barra
    for (int i=0;i<N;i++){
        x[i] = x_min + i*dx;
    }
}





