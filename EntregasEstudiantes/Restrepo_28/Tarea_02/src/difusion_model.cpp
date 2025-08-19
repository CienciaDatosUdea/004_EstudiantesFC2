#include <cstdio>
#include <iostream>
#include "difusion_model.h"
#include <iomanip>
#include <fstream>
#include <functional>

Geometry::Geometry(int N_, double xmin_, double xmax_)
    :N(N_),xmin(xmin_),xmax(xmax_)
    {
        x.resize(N);
        dx = (xmax-xmin)/(N-1);
        for(int i=0;i<N;i++){
            x[i] =xmin+i*dx;
        }
    }

Conditions::Conditions(Geometry &G_):G(G_),u(G_.N,0.0){};

void Conditions::initialConditions(std::function<double(double)> func){
    for(int i=0;i<G.N;i++){
        u[i]=func(G.xmin+i*G.dx);//rellena u con la función dada
    }

}

void Conditions::boundaryConditions(double DL){
    //Dirichlet boundary conditions
    u[0]=DL;
    u[G.N-1] = DL;
}

Solver::Solver(Conditions &C_):C(C_),t0(0.0),dx(C_.G.dx),temp(C_.u){};


void Solver::run(double tmax,double dt,double D,Writer* writer){
    for(int i =0; i<int(tmax/dt);i++){
        if (writer){//Si se proporcionó un writer, guarda toda la simulación en un archivo
            writer->writeSolution(*this);
        }
        step(dt,D);
    }
};

void Solver::step(double dt,double D){
    std::vector<double> temptemp = temp;
    for(int i=1;i<C.G.N-1;i++){//i omite punto inicial y final para conservar las boundary conditions
        temp[i] = (D*dt/(dx*dx))*(temptemp[i+1]-2*temptemp[i]+temptemp[i-1])+temptemp[i];
    }
    t0 +=dt;
};

Writer::Writer(const std::string &filename_){
    file.open(filename_);
    if (!file.is_open()){
        throw std::runtime_error("No se pudo abrir el archivo: " + filename_);}
    
        file << std::fixed << std::setprecision(6);
        file << "# pos\t temp\n";

};

void Writer::writeSolution(const Solver &S){
    std::vector<double> x = S.C.G.x; //this is horrible
    std::vector<double> temp = S.temp;
    file<<"#t = "<<S.t0<<"\n";
    for(int i=0;i<S.C.G.N;i++){
        file<<x[i]<<"\t"<<temp[i]<<"\n";
    }
    file<<"\n\n";//Does espacios en blanco para poder ser leído correcctamente por gnuplot
};

