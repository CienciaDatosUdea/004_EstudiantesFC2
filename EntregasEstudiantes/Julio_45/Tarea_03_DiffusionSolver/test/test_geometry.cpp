#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include "../include/diffusion_model.h"

int main(int argc,char *argv []){
    double xmin = atof(argv[1]);
    double xmax = atof(argv[2]);
    int N = atoi(argv[3]);

    Geometry G(xmin,xmax,N);

    for(int i=0;i<N;i++){
        std::cout<<G.x[i]<<"\n";
    }
    std::cout<<"------------"<<std::endl;
    std::cout<<"dx = "<<G.dx<<"\n";
    std::cout<<"N = "<<G.N<<"\n";
    std::cout<<"Tamaño de x: "<<G.x.size()<<"\n";

    return 0;
}