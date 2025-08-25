#include <cstdio>
#include <iostream>
#include "difusion_model.h"


int main(){
    int N=50;
    double xmin=0;
    double xmax=1;   
    
    Geometria G(N, xmin, xmax);
    
    for(int i=0;i<N;i++){
        std::cout<<G.x[i]<<"\n";
    }
    std::cout<<"-------\n";
    std::cout<<"dx = "<<G.dx<<"\n";
    std::cout<<"N = "<<G.N<<"\n";
    std::cout<<"Tamaño = "<<G.x.size()<<"\n";

    return 0;
}