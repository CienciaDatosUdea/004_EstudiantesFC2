#include <cstdio>
#include <iostream>
#include "difusion_model.h"


int main(){
    int N=10;
    double xmin=0;
    double xmax=1;   
    
    Geometria G(N, xmin, xmax);
    Condiciones C(G);
    C.condicionesIniciales();
    C.condicionesFrontera();
   
    return 0;
}