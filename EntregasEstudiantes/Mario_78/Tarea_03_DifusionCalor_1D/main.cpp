#include <cstdio>
#include <iostream>
#include "difusion_model.h"



int main(){
    int N=50;
    double xmin=0;
    double xmax=1;   
    
    Geometria G(N, xmin, xmax);
    Condiciones C(G);
    
    
    C.condicionesIniciales();
    C.condicionesFrontera();
    C.evolucionar(50);      // Simular 20 pasos de tiempo
   
    return 0;
}