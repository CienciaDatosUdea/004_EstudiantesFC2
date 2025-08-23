#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <ostream>
#include <iostream>
#include <../include/fdtd.h>

//Condiciones iniciales sinusoidales con condiciones de frontera periódicas


double Smart_DeltaT(int Num_nodes);

int main(){
    int Num_nodes = 200; 
    double Integration_time = 1.0;  
    double DeltaT = Smart_DeltaT(Num_nodes); 
    std::string boundary_cond = "periodic";

    Lee_Net My_Net(Num_nodes, 0.0, 0.0); 

    // Inicializa con una onda sinusoidal en el espacio para E
    for (int k = 0; k < Num_nodes; ++k) {
        double x = k * My_Net.Delta;
        // Onda sinusoidal con longitud de onda 0.5
        My_Net.E[0][k] = 0.1 * sin(4.0 * M_PI * x);
        My_Net.H[0][k] = 0.1 * sin(4.0 * M_PI * x);
    }

    My_Net.Integrate(Integration_time, DeltaT, boundary_cond, "main1.txt", false);

    return 0;
}

double Smart_DeltaT(int Num_nodes){
    double c = 1.;
    double Delta = 1.0 / (Num_nodes - 1.);
    return 0.5 * Delta / c; }