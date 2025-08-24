#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <sstream>
#include "../include/boltzmann.h"

#include <boost/math/special_functions/bessel.hpp>/*provides bessel-K function*/

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

long double BoltzmannEquation::Yeq(){
    return (g*g/(2*M_PI*M_PI)*pow(MS,3)/x*boost::math::cyl_bessel_k(2,x))/C.entropyDensity;
}

long double BoltzmannEquation::dYdx(long double Y){
    long double func;
    long double Hbar = C.hubbleRate/(1.0L+(1.0L/3.0L)*C.dlnheffdlnT);
    if (modelname == "FIMP"){
        func = -sigmav*C.entropyDensity/(x*Hbar)*(-pow(Yeq(),abs(DMini-DMfin)));
    }
    else{
        func = -C.entropyDensity*sigmav/(x*Hbar)*(pow(Y,DMini)-pow(Y,DMfin)*pow(Yeq(),abs(DMini-DMfin)));
    }
    return func;
}

void BoltzmannEquation::setX(long double new_x){
    x = new_x;
    C = Cosmology(MS/x);
    C.calculate(path);
}