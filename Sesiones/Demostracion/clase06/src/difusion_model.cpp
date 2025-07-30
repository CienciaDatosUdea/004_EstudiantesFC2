#include <cstdio>
#include <iostream>
#include "difusion_model.h"

Geometria::Geometria(int N_,double xmin_, double xmax_ )
    : N(N_), xmin(xmin_), xmax(xmax_)
    {
        x.resize(N);
        dx = (xmax-xmin)/(N-1);
        for(int i=0;i<N;i++){
            x[i]=xmin+i*dx;
        }
};

Condiciones::Condiciones(Geometria &G_):
    G(G_), u(G_.N, 0.0) {};

void  Condiciones::condicionesIniciales(){
    for(int i=1; i<G.N-1;i++){
        u[i]=0;
        if(i==int(G.N/2))
            u[i]=100;
    }
}

void  Condiciones::condicionesFrontera(){
    u[0]=0;
    u[G.N-1]=0;
}
