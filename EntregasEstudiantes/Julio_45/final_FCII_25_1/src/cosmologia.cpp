#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <sstream>
#include "../include/boltzmann.h"

#include <boost/math/special_functions/bessel.hpp> // provee la función K de Bessel

/*
Clase que calcula las cantidades físicas asociadas a la cosmología
*/

Cosmology::Cosmology(long double T_):T(T_){
    geff = 0.0;     // Grados de libertad relativistas que contribuyen a la energía
    heff = 0.0;     // Grados de libertad relativistas que contribuyen a la entropía
    // Derivadas logarítmicas
    energyDensity = 0.0;    // Densidad de energía
    entropyDensity = 0.0;   // Densidad de entropía
    hubbleRate = 0.0;       // Tasa de expansión de Hubble
}

void Cosmology::readDegreesOfFreedom(const std::string& path){
    /*
    Lee los datos de los grados de libertad
    */
    geffvec.clear(),geffvec.shrink_to_fit();
    heffvec.clear(),heffvec.shrink_to_fit();
    Tvec.clear(),Tvec.shrink_to_fit();

    std::string filename = path + "/" + "data/std.tab";

    std::ifstream file(filename);

    long double r1, r2, r3;

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;//Skip lines with '#'
            std::istringstream iss(line);
            iss >> r1 >> r2 >> r3;
            Tvec.push_back(r1);
            geffvec.push_back(r3);
            heffvec.push_back(r2);
        }
        file.close();
    }
    else {
        std::cout << "Unable to open the file:" << std::endl;
    }


}

void Cosmology::calculate(const std::string& path){
    /*
    Calcula las cantidades mencionadas anteriormente
    */
    long double MP = 2.4e18;
    readDegreesOfFreedom(path);
    // interpolación lineal de los grados de libertad
    if(T<Tvec[0]){
        geff = geffvec[0];
        heff = heffvec[0];
    }
    else if(T>Tvec[Tvec.size()-1]){
        geff = geffvec[Tvec.size()-1];
        heff = heffvec[Tvec.size()-1];
    }
    else{
        int i = 0;
        while(T>=Tvec[i]){
            i++;
        }
        geff = (geffvec[i]-geffvec[i-1])/(Tvec[i]-Tvec[i-1])*(T-Tvec[i])+geffvec[i];
        heff = (heffvec[i]-heffvec[i-1])/(Tvec[i]-Tvec[i-1])*(T-Tvec[i])+heffvec[i];
    }
    entropyDensity = 2.0L*M_PI*M_PI/45.0L*heff*pow(T,3);
    energyDensity = M_PI*M_PI/30.0L*geff*pow(T,4);
    hubbleRate = sqrt(energyDensity/(3.0L*MP*MP));
}