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
Clase que define la ecuación de Boltzmann para un modelo en particular con una partícula de DM
de masa MS y sección eficaz sigmav
*/
BoltzmannEquation::BoltzmannEquation(long double x_,long double MS_,int g_,long double sigmav_,DarkMatterModel mod,const std::string &path_)
    : x(x_), MS(MS_), g(g_), sigmav(sigmav_), path(path_), C(MS/x){
    C.calculate(path);
    modelname = mod.name;
    DMini = mod.DMini;
    DMfin = mod.DMfin;
    SMfin = mod.SMfin;
    if (modelname == "FIMP"){std::cout<<"dY/dx=-(<σv>*s/x*Hbar)(-Yeq^2)"<<std::endl;}
    else {std::cout<<"dY/dx=-(<σv>*s"<<DMini-1<<"/x*Hbar)("<<"Y^"<<DMini<<"-Y^"<<DMfin<<"*Yeq^"<<abs(DMini-DMfin)<<")"<<std::endl;}
}

// Abundancia en el equilibrio
long double BoltzmannEquation::Yeq(){
    return (g*g/(2*M_PI*M_PI)*pow(MS,3)/x*boost::math::cyl_bessel_k(2,x))/C.entropyDensity;
}

// Ecuación diferencial
long double BoltzmannEquation::dYdx(long double Y){
    long double func;
    long double H = C.hubbleRate;
    if (modelname == "FIMP"){
        func = -sigmav*C.entropyDensity/(x*H)*(-pow(Yeq(),abs(DMini-DMfin)));
    }
    else{
        func = -C.entropyDensity*sigmav/(x*H)*(pow(Y,DMini)-pow(Y,DMfin)*pow(Yeq(),abs(DMini-DMfin)));
    }
    return func;
}

// Cambia el valor de x en la ecuación
void BoltzmannEquation::setX(long double new_x){
    x = new_x;
    C = Cosmology(MS/x);
    C.calculate(path);
}