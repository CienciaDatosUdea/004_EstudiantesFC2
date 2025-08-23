#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <iomanip>
#include "../include/fdtd.h"

Grid::Grid(double zmax, double tmax, double beta_):z_max(zmax),t_max(tmax),beta(beta_){
    // if (beta > 0.5){
    //                 throw std::runtime_error("WARNING: the parameter beta does not satisfy the stability condition. Please choose a value of beta <= 0.5.");
    //             }
    nz = 200;
    dz = z_max/(nz-1.0L);
    if (dz > 10){
                    throw std::runtime_error("WARNING: the wavelength is equal to 100, so dz must be <= 10. Please choose a value of z_max <= 1990.");
                }
    dt = dz*beta;
    nt = t_max/dt + 1;
    ZT.resize(nt, std::vector<std::vector<double>>(nz, std::vector<double>(2)));

    for(int i=0;i<nt;i++){
        for(int j=0;j<nz;j++){
            ZT[i][j][0] = j*dz;  // z's
            ZT[i][j][1] = i*dt;  // t's
        }
    }
}

CampoEM::CampoEM(Grid &G):g(G){
    nz2 = g.nz/2;
    nt2 = g.nt/2;

    E.resize(nt2, std::vector<double>(nz2));
    H.resize(nt2, std::vector<double>(nz2));
}

void CampoEM::applyInitialCondition(function<double(double)> f){
    for(int i=0;i<nz2;i++){
        E[0][i] = f(g.ZT[1][2*i][0]);
    }
    for(int i=0;i<nz2;i++){
        H[0][i] = f(g.ZT[0][2*i+1][0]);
    }
}


FieldWriter::FieldWriter(const std::string &filename){
    file.open(filename);
        if (!file.is_open()) 
            throw std::runtime_error("No se pudo abrir el archivo: " + filename);
        
        file << std::fixed << std::setprecision(6);

}

void FieldWriter::writeInitial(const Grid &G, const CampoEM &field){
    file << "# zE\t\tE\t\tzH\t\tH\n";    
    file << "# =================================\n";
    for (int i = 0; i < G.nz/2; i++) {
            file << G.ZT[1][2*i][0] << "\t"
                 << field.E[0][i] << "\t"
                 << G.ZT[0][2*i+1][0] << "\t"
                 << field.H[0][i] << "\n";
        }
}

void FieldWriter::writeField(const Grid &G, const CampoEM &field){
    for (int j=0; j < G.nt/2; j++){
        file << "# zE\t\tE\t\tzH\t\tH\n";    
        file << "# =================================\n";
        for (int i = 0; i < G.nz/2; i++) {
                file << G.ZT[2*j+1][2*i][0] << "\t"
                    << field.E[j][i] << "\t"
                    << G.ZT[2*j][2*i+1][0] << "\t"
                    << field.H[j][i] << "\n";
            }
    }
}

Evolution::Evolution(CampoEM &campo):field(campo){}

void Evolution::run(bool periodic){
    for(int i=1;i<field.g.nt/2;i++){
        for(int j=1;j<field.g.nz/2-1;j++){
            field.E[i][j] = field.E[i-1][j] + field.g.beta*(field.H[i-1][j-1]-field.H[i-1][j+1]);
            field.H[i][j] = field.H[i-1][j] + field.g.beta*(field.E[i-1][j-1]-field.E[i-1][j+1]);
        }
        if (periodic){
            field.E[i][0] = field.E[i-1][0] + field.g.beta*(field.H[i-1][field.g.nz/2-2]-field.H[i-1][1]);
            field.E[i][field.g.nz/2-1] = field.E[i-1][field.g.nz/2-1] + field.g.beta*(field.H[i-1][field.g.nz/2-2]-field.H[i-1][1]);
            field.H[i][0] = field.H[i-1][0] + field.g.beta*(field.E[i-1][field.g.nz/2-2]-field.E[i-1][1]);
            field.H[i][field.g.nz/2-1] = field.H[i-1][field.g.nz/2-1] + field.g.beta*(field.E[i-1][field.g.nz/2-2]-field.E[i-1][1]);
        }
        else{
            field.E[i][0] = 0;
            field.E[i][field.g.nz/2-1] = 0;
            field.H[i][0] = 0;
            field.H[i][field.g.nz/2-1] = 0;
        }
        }
    }
