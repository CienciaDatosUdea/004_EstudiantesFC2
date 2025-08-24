#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include "../include/boltzmann.h"

int main(int argc, char *argv []){
    // parámetros
    long double MS = atof(argv[1]);
    long double sigmav = atof(argv[2]);
    long double TR = atof(argv[3]);
    std::string name = argv[4];
    int DMini = atoi(argv[5]);
    int DMfin = atoi(argv[6]);
    int SMfin = atoi(argv[7]);

    // Temperatura actual
    long double T0 = 2.3482233139345615e-13;
    
    // Número de pasos para el BDF
    int nxi = 1000;

    std::string path = "/home/santiago/santiago_FCII_20251/004_EstudiantesFC2/EntregasEstudiantes/Julio_45/final_FCII_25_1";

    // Cantidades termodinámicas
    Cosmology C(T0);
    C.calculate(path);
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"Cantidades termodinámicas hoy"<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"geff = "<<C.geff<<"\n";
    std::cout<<"heff = "<<C.heff<<"\n";
    std::cout<<"rho = "<<C.energyDensity<<"\n";
    std::cout<<"s = "<<C.entropyDensity<<"\n";
    std::cout<<"H = "<<C.hubbleRate<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;

    std::cout<<"Modelo de materia oscura"<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    DarkMatterModel model(name,DMini,DMfin,SMfin);
    model.printProcess();
    std::cout<<"-----------------------------"<<std::endl;
    // ecuación de Boltzmann
    BoltzmannEquation BEQ(MS/TR,MS,1,sigmav,model,path);

    // límites y condición inicial
    long double xi0 = log10(MS/TR);
    long double xif = log10(MS/T0);
    long double Y0;
    
    if (model.name == "FIMP"){Y0 = 0;}
    else {Y0 = BEQ.Yeq();}

    std::cout<<"Condición inicial"<<std::endl;
    std::cout<<"Y_0 = "<<Y0<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;

    // Solución de la ED
    BEqSolver sol(xi0,xif,nxi,Y0,BEQ);
    sol.solve();

    std::cout<<"Omega*h2 = "<<sol.Omegah2<<"\n";
    std::cout<<"-----------------------------"<<std::endl;
    
    FieldWriter file;
    file.write(sol);
    return 0;
}
