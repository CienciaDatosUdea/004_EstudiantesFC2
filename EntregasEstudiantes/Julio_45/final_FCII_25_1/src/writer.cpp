#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "../include/boltzmann.h"

#include <boost/math/special_functions/bessel.hpp> // provee la función K de Bessel

/*
Clase que escribe los datos del modelo y la solución de la ecuación de Boltzmann
en archivos .txt
*/

FieldWriter::FieldWriter(){
    solution.open("data/solution.txt");
    if (!solution.is_open()) 
            throw std::runtime_error("No se pudo abrir el archivo: data/solution.txt");
    params.open("data/params.txt");
    if (!params.is_open()) 
            throw std::runtime_error("No se pudo abrir el archivo: data/params.txt");
}

void FieldWriter::write(BEqSolver BEQsol){
    // Escribe los datos de la solución
    std::cout<<std::setprecision(6)<<std::fixed;
    int n = BEQsol.nxi;
    solution << "# x\t\tT\t\tY\t\tYeq\t\tgeff\t\theff\t\trho\t\ts\t\tH\n";
    solution << "# ======================================================================================================\n";
    for(int i=0;i<n;i++){
        BEQsol.BEQ.setX(BEQsol.xs[i]);
        solution << BEQsol.xs[i]
        <<"\t"<< BEQsol.BEQ.MS/BEQsol.xs[i] 
        <<"\t"<< BEQsol.Ys[i]
        <<"\t"<< BEQsol.BEQ.Yeq()
        <<"\t"<< BEQsol.BEQ.C.geff
        <<"\t"<< BEQsol.BEQ.C.heff
        <<"\t"<< BEQsol.BEQ.C.energyDensity
        <<"\t"<< BEQsol.BEQ.C.entropyDensity
        <<"\t"<< BEQsol.BEQ.C.hubbleRate<<std::endl;

    }

    // Escribe los parámetros
    params << "# PARÁMETROS DEL MODELO #\n";
    params << "=========================\n";
    params << BEQsol.BEQ.modelname << " dark matter\n";
    params << "Reacción: ";
    if (BEQsol.BEQ.modelname == "FIMP"){params<<"Y+Y";}
 
    for (int i = 0; i < BEQsol.BEQ.DMini; ++i) {
        params << "~x1";
        if (i < BEQsol.BEQ.DMini - 1) std::cout << "+";
    }
    params << " -> ";
    // X+X+...+X (DMfin veces)
    for (int i = 0; i < BEQsol.BEQ.DMfin; ++i) {
        params << "~x1";
        if (i < BEQsol.BEQ.DMfin - 1) std::cout << "+";
    }
    // Y+Y+...+Y (SMfin veces)
    if (BEQsol.BEQ.SMfin > 0) {
        if (BEQsol.BEQ.DMfin > 0) params << "+";
        for (int i = 0; i < BEQsol.BEQ.SMfin; ++i) {
            params << "Y";
            if (i < BEQsol.BEQ.SMfin - 1) params << "+";
        }
    }
    
    params << std::endl;

    params << "Ecuación de Boltzmann: ";
    if (BEQsol.BEQ.modelname == "FIMP"){params<<"dY/dx=-(<σv>*s/x*Hbar)(-Yeq^2)"<<std::endl;}
    else {params<<"dY/dx=-(<σv>*s"<<BEQsol.BEQ.DMini-1<<"/x*Hbar)("<<"Y^"<<BEQsol.BEQ.DMini<<"-Y^"<<BEQsol.BEQ.DMfin<<"*Yeq^"<<abs(BEQsol.BEQ.DMini-BEQsol.BEQ.DMfin)<<")"<<std::endl;}

    params << "M_S = "<<BEQsol.BEQ.MS<<"\n";
    params << "<σv> = "<<BEQsol.BEQ.sigmav<<"\n";
    params << "T_R = "<<BEQsol.BEQ.MS/BEQsol.xs[0]<<"\n";
    params << "Ω_0h² = "<<BEQsol.Omegah2<<"\n";
}