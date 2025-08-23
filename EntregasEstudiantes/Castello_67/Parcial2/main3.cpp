#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <ostream>
#include <iostream>
#include <../include/fdtd.h>

// Escogencia de parametros que no cumplen Courant



int main(){
    int Num_nodes = 200;
    double E0 = 0.1 * sin(2.0 * M_PI /100.); 
    double H0 = 0.1 * sin(2.0 * M_PI /100.);
    double Integration_time = 1.;

    // Vamos a escoger un mal paso del tiempo
    double Delta = 1.0 / (Num_nodes - 1.);
    double DeltaT = 0.5 * Delta  + 0.005; // Paso del tiempo que no cumple Courant
    std::string boundary_cond = "simple"; // "simple" or "periodic"

    Lee_Net My_Net(Num_nodes, E0, H0);
    //My_Net.E[0][Num_nodes/2] = 1.; // Pulso inicial en el centro
    My_Net.Integrate(Integration_time, DeltaT, boundary_cond , "main3.txt", false);

    return 0;
}
