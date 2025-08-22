#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <fstream>
#include "../include/diffusion_model.h"

using namespace std;

// Clase que permite escribir los resultados del campo de temperaturas
FieldWriter::FieldWriter(const std::string &filename)    
    {
        file.open(filename);
        if (!file.is_open()) 
            throw std::runtime_error("No se pudo abrir el archivo: " + filename);
        
        //file << std::fixed << std::setprecision(6);
    }


void FieldWriter::writeTemperature(const Geometry &G, const Temperature &Campo)
{
    file << "# x\t\tT\n";    
    file << "# =================================\n";
    
    for (int i = 0; i < G.N; ++i) {
            file << G.x[i] << "\t"
                 << Campo.T[i] << "\n";
        }
}

// Constructor del integrador de la EDP
DiffusionSolver::DiffusionSolver(Temperature &Temp,double D_,double dt_,double tmax,
                double TL_,double TR_,std::function<double(double)> f_,const std::string &fn):field(Temp),D(D_),dt(dt_),t_max(tmax),TL(TL_),TR(TR_),f(f_),filename(fn){
                
                alpha = D*dt/(field.g.dx*field.g.dx);
                // Verificación de la condición de estabilidad (RF10)
                if (alpha > 0.5){
                    throw std::runtime_error("WARNING: the parameter alpha does not satisfy the stability condition. Please change the values of D, dt or dx.");
                }
}

// Evoluciona el campo de temperatura una vez usando FTCS (RF4)
void DiffusionSolver::step(){
    std::vector<double> T_new(field.g.N);


    for (int i=1; i<field.g.N-1;i++){
        T_new[i] = field.T[i] + alpha*(field.T[i+1]-2*field.T[i]+field.T[i-1]);
    }

    field.T = T_new;
    field.applyBoundaryCondition(TL,TR); // aplica las condiciones de frontera (RF5)
}

// Evoluciona el campo de temperatura hasta t=t_max
void DiffusionSolver::run(){
    FieldWriter file(filename);
    file.writeTemperature(field.g,field);
    int steps = static_cast<int>(t_max / dt);
    for (int s = 0; s < steps; s++) {
        step();
        file.writeTemperature(field.g,field);      // Escribe los resultados (RF6)
    }

}
