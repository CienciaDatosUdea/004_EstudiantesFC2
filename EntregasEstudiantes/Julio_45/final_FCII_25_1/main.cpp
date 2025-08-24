#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include "../include/boltzmann.h"

int main(int argc, char *argv []){
    long double MS = atof(argv[1]);
    long double sigmav = atof(argv[2]);
    long double TR = atof(argv[3]);
    std::string name = argv[4];
    int DMini = atoi(argv[5]);
    int DMfin = atoi(argv[6]);
    int SMfin = atoi(argv[7]);

    long double T0 = 2.3482233139345615e-13;
    int nxi = 1000;

    std::string path = "/home/santiago/santiago_FCII_20251/final_FCII_25_1";
    Cosmology C(T0);
    C.calculate(path);
    std::cout<<C.geff<<"\t"<<C.heff<<"\t"<<C.energyDensity<<"\t"<<C.entropyDensity<<"\t"<<C.hubbleRate<<std::endl;

    DarkMatterModel model(name,DMini,DMfin,SMfin);
    model.printProcess();

    BoltzmannEquation BEQ(MS/TR,MS,1,sigmav,model,path);

    long double xi0 = log10(MS/TR);
    long double xif = log10(MS/T0);
    long double Y0;
    
    if (model.name == "FIMP"){Y0 = 0;}
    else {Y0 = BEQ.Yeq();}

    std::cout<<Y0<<std::endl;
    std::cout<<BEQ.dYdx(Y0)<<std::endl;

    BEqSolver sol(xi0,xif,nxi,Y0,BEQ);
    std::cout<<sol.xis[0]<<","<<sol.xis[nxi-1]<<","<<sol.delta<<std::endl;
    std::cout<<sol.xs[0]<<","<<sol.xs[1]<<","<<sol.xs[1]-sol.xs[0]<<std::endl;
    long double xp = pow(10,sol.xis[0]+sol.delta/2);
    std::cout<<xp<<std::endl;

    BEQ.setX(xp);
    std::cout<<BEQ.x<<std::endl;
    std::cout<<BEQ.C.geff<<std::endl;
    std::cout<<BEQ.C.energyDensity<<std::endl;
    std::cout<<BEQ.C.T<<std::endl;

    std::cout<<BEQ.dYdx(Y0)<<std::endl;
    std::cout<<"-------------------"<<std::endl;
    sol.solve();
    //std::cout<<"Y_0 = "<<sol.Ys[sol.nxi-1]<<std::endl;
    std::cout<<"Omega*h2 = "<<sol.Omegah2<<"\n";
    //for (int i=0;i<nxi;i++){std::cout<<sol.Ys[i]<<std::endl;}
    Cosmology today(T0);
    today.calculate(BEQ.path);
    std::cout << "s_0 = " << today.entropyDensity<<std::endl;
    
    FieldWriter file;
    file.write(sol);
    return 0;
}
