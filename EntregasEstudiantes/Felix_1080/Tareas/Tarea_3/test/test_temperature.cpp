#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <iomanip>
#include "../include/diffusion_model.h"

double initCond(double x){
    double out;
    double ax = std::abs(x);
    if (ax<=0.2){out = 1.0;}
    else {out = 0.0;}
    return out;
}

int main(int argc,char *argv []){
    std::cout<<std::setprecision(6)<<std::fixed;

    double xmin = atof(argv[1]);
    double xmax = atof(argv[2]);
    int N = atoi(argv[3]);

    Geometry G(xmin,xmax,N);

    Temperature T(G);

    T.applyBoundaryCondition(0.5,0.6);
    T.applyInitialCondition(initCond);

    int i;
    std::cout<<"x\t\tT"<<std::endl;
    for (i=0;i<N;i++){
        std::cout<<G.x[i]<<"\t"<<T.T[i]<<std::endl;
    }
    std::cout<<"---------------------------"<<std::endl;

}