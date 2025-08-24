#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <sstream>
#include "../include/boltzmann.h"

#include <boost/math/special_functions/bessel.hpp>/*provides bessel-K function*/

BEqSolver::BEqSolver(long double xi0,
                    long double xif,
                    int nxi_,long double Y0_,
                    BoltzmannEquation BEQ_):
                    x0(pow(10,xi0)),nxi(nxi_),Y0(Y0_),BEQ(BEQ_){
    xs.resize(nxi);
    xis.resize(nxi);
    Ys.resize(nxi);
    delta = (xif-xi0)/(nxi-1.0L);
    for (int i=0;i<nxi;i++){
        xis[i] = xi0 + i*delta;
        xs[i] = pow(10,xis[i]);
    }
    Ys[0] = Y0;
}


void BEqSolver::solve(){
    long double k1,k2,delta,deltaPlus,deltaMinus,a1,a0,am1,Yn,Ynm1;

    delta = (xs[1]-xs[0]);
    // k1
    BEQ.setX(xs[0]);
    k1 = BEQ.dYdx(Ys[0]);
    // k2
    BEQ.setX(xs[0]+delta);
    k2 = BEQ.dYdx(Ys[0]+k1*delta);

    std::cout<<"("<<k1<<","<<k2<<")"<<std::endl;
    Ys[1] = Ys[0] + (1.0L/2.0L)*delta*(k1+k2);
    
    std::cout<<"Y_0 = "<<Ys[0]<<"\n";
    std::cout<<"Y_1 = "<<Ys[1]<<"\n";
    
    Secante sec(1e-10,200);
    if(BEQ.modelname == "FIMP"){
        for (int i=2;i<nxi;i++){
            BEQ.setX(xs[i]);
            deltaPlus = xs[i]-xs[i-1];
            deltaMinus = xs[i-1]-xs[i-2];

            a1 = (1.0L/deltaPlus)*(1.0L+deltaPlus/(deltaMinus+deltaPlus));
            am1 = (1.0L/deltaMinus)*(deltaPlus/(deltaMinus+deltaPlus));
            a0 = -a1-am1;
            Ys[i] = (BEQ.dYdx(Y0)-a0*Ys[i-1]-am1*Ys[i-2])/a1;
        }
    }
    
    else{
    for (int i=2;i<nxi;i++){
        BEQ.setX(xs[i]);
        deltaPlus = xs[i]-xs[i-1];
        deltaMinus = xs[i-1]-xs[i-2];

        a1 = (1.0L/deltaPlus)*(1.0L+deltaPlus/(deltaMinus+deltaPlus));
        am1 = (1.0L/deltaMinus)*(deltaPlus/(deltaMinus+deltaPlus));
        a0 = -a1-am1;

        Yn = Ys[i-1];
        Ynm1 = Ys[i-2];
        auto func = [a1,a0,am1,Yn,Ynm1,this](double Y){
            return a1*Y+a0*Yn+am1*Ynm1-this->BEQ.dYdx(Y);
        };

        Ys[i] = sec.encontrarRaiz(func,Yn,Ynm1);
    }}

    long double MP = 2.4e18;
    long double T0 = 2.3482233139345615e-13;
    Cosmology today(T0);
    today.calculate(BEQ.path);
    Omegah2 = Ys[nxi-1]*BEQ.MS*today.entropyDensity/(3.0L*MP*MP*pow(2.13e-42,2));
}
