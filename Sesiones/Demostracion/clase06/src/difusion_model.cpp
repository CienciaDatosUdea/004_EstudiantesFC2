#include <cstdio>
#include <iostream>
#include "difusion_model.h"

Geometria::Geometria(int N_,double xmin_, double xmax_ )
    : N(N_), xmin(xmin_), xmax(xmax_)
    {
        x.resize(N);
        dx = (xmax-xmin)/(N-1);
        for(int i;i<N;i++){
            x[i]=xmin+i*dx;
        }

    };