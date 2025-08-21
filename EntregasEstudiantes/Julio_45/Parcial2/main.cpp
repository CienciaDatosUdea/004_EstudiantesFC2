#include <vector>
#include <iostream>
#include <fstream>
#include <functional>
#include <cmath>
#include <iomanip>
#include "../include/fdtd.h"


using namespace std;

double initCond(double z){
    return 0.1*sin(2.0L*M_PI*z/100.0L);
}

int main(int argc,char* argv []){
    double b = atof(argv[1]);
    double zmax = atof(argv[2]);
    double tmax = atof(argv[3]);
    bool periodic = atoi(argv[4]);
    string name = argv[5];


    Grid g(zmax,tmax,b);
    CampoEM field(g);
    field.applyInitialCondition(initCond);
    FieldWriter fileInit("initial_conds.txt");
    fileInit.writeInitial(g,field);

    Evolution solve(field);
    solve.run(periodic);

    FieldWriter fileSol(name);
    fileSol.writeField(g,solve.field);
    
    cout<<"beta = "<<b<<endl;
    cout<<"z_max = "<<zmax<<endl;
    cout<<"t_max = "<<tmax<<endl;
    cout<<"nt = "<<solve.field.g.nt<<endl;
    cout<<"nz = "<<solve.field.g.nz<<endl;
    if(periodic){
        cout<<"Condiciones de frontera periódicas"<<endl;
    }
    else{
        cout<<"Condiciones de frontera de Dirichlet"<<endl;
    }

    return 0;
}