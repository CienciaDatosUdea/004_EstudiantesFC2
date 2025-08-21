#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include "difusion_model.h"

int main(){
    int N= 20;
    double xmin = 0;
    double xmax = 10;

    Geometry G(N,xmin,xmax);
    Conditions C(G);
    C.initialConditions([](double x){return exp(-pow((x-5.0),2));});
    C.boundaryConditions(0.0);

    std::cout<<"GEOMETRY\n";
    for(int i=0;i<N;i++){
        std::cout<<G.x[i]<<"\n";
    }
    std::cout<<"---init---\n";
    for(int i=0;i<N;i++){
        std::cout<<C.u[i]<<"\n";
    }
    Writer mysave("test.dat");
    Solver S(C);
    S.run(5,.1,1.0,&mysave);


}