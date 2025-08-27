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
Clase que crea el modelo de materia oscura
*/

DarkMatterModel::DarkMatterModel(std::string name_,int DMini_,int DMfin_,int SMfin_):name(name_),DMini(DMini_),DMfin(DMfin_),SMfin(SMfin_){}

// imprime la reacción
void DarkMatterModel::printProcess(){
    std::cout<<name<<" Dark Matter"<<std::endl;
    // X+X+...+X (DMini veces)
    if (name == "FIMP"){std::cout<<"Y+Y";}
    for (int i = 0; i < DMini; ++i) {
        std::cout << "~x1";
        if (i < DMini - 1) std::cout << "+";
    }
    std::cout << " -> ";
    // X+X+...+X (DMfin veces)
    for (int i = 0; i < DMfin; ++i) {
        std::cout << "~x1";
        if (i < DMfin - 1) std::cout << "+";
    }
    // Y+Y+...+Y (SMfin veces)
    if (SMfin > 0) {
        if (DMfin > 0) std::cout << "+";
        for (int i = 0; i < SMfin; ++i) {
            std::cout << "Y";
            if (i < SMfin - 1) std::cout << "+";
        }
    }
    std::cout << std::endl;
}