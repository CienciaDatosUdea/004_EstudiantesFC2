#include <cstdio>
#include <iostream>
#include "difusion_model.h"


int main(){
    int N=10;
    double xmin=0;
    double xmax=1;   
    
    Geometria G(N, xmin, xmax);
    
    for(int i=0;i<N;i++){
        std::cout<<G.x[i]<<"\n";
    }
    std::cout<<"-----";
    std::cout<<G.dx<<"\n";
    std::cout<<G.N<<"\n";
    std::cout<<G.x.size()<<"\n";

    return 0;
}