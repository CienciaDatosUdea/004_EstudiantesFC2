#include "../include/Samples_Gen.h"
#include <cmath>
#include <iostream>

int main(){
    double Tc_seed = 2.;
    int Num_Samples = 5000; // Número de muestras Monte Carlo
    int L = 10;
    Samples simulator(L,Num_Samples);
    
    // Generar muestras a diferentes temperaturas
    std::vector<double> temperatures = {0.1, 0.305263, 0.510526, 0.715789, 0.921053, 1.12632, 1.33158, 1.53684,
                                        1.74211, 1.94737, 2.15263, 2.35789, 2.56316, 2.76842, 2.97368, 3.17895,
                                        3.38421, 3.58947, 3.79474, 4.0};

    for (double T : temperatures) {
        simulator.Generate(T, Tc_seed);
        std::cout << "Muestras generadas para T = " << T << std::endl;
    }
    
    return 0;
}