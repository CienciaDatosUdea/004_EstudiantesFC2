#include "../include/fdtd.h"
#include <fstream>
#include <cmath>
#include <iostream>

using namespace std;

OndaEM::OndaEM(int nz, double dz, double dt,double nt, int boundary_type)
    : nz(nz), dz(dz), dt(dt), nt(nt), boundary_type(boundary_type) {
    Ex.resize(nz, vector<double>(nt, 0.0));
    Hy.resize(nz, vector<double>(nt, 0.0));
    
    // Calcular beta (c = 1 en unidades normalizadas)
    beta = dt / dz;
}

void OndaEM::Inicialization() {
    for (int k = 0; k < nz; k++) {
        double z = k * dz;
        Ex[k][0] = 0.1 * sin(2 * M_PI * z / 100.0);
        Hy[k][0] = 0.1 * sin(2 * M_PI * z / 100.0);
    }
}

void OndaEM::update() {
    for (int n = 0; n < nt - 1; n++) {
        // Actualizar campo eléctrico Ex para el siguiente paso temporal
        for (int k = 1; k < nz - 1; k++) {
            Ex[k][n + 1] = Ex[k][n] + beta * (Hy[k - 1][n] - Hy[k + 1][n]);
        }
        
        // Actualizar campo magnético Hy para el siguiente paso temporal
        for (int k = 1; k < nz - 1; k++) {
            Hy[k][n + 1] = Hy[k][n] + beta * (Ex[k - 1][n] - Ex[k + 1][n]);
        }
        
        // Aplicar condiciones de frontera para el paso n+1
        if (boundary_type == 0) {
            // Condiciones periódicas
            Ex[0][n + 1] = Ex[0][n] + beta * (Hy[nz - 2][n] - Hy[1][n]);
            Ex[nz - 1][n + 1] = Ex[nz - 1][n] + beta * (Hy[nz - 2][n] - Hy[1][n]);
            
            Hy[0][n + 1] = Hy[0][n] + beta * (Ex[nz - 2][n] - Ex[1][n]);
            Hy[nz - 1][n + 1] = Hy[nz - 1][n] + beta * (Ex[nz - 2][n] - Ex[1][n]);
        } else {
            // Condiciones fijas (E=H=0 en bordes)
            Ex[0][n + 1] = 0.0;
            Ex[nz - 1][n + 1] = 0.0;
            Hy[0][n + 1] = 0.0;
            Hy[nz - 1][n + 1] = 0.0;
        }
    }
}
void OndaEM::outputToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }
    
    
    file << "Paso;z;Ex;Hy\n";
    
    for (int t = 0; t < nt; t++) {
        for (int z = 0; z < nz; z++) {
            double pos_z = z * dz;
            double ex_val = Ex[z][t];
            double hy_val = Hy[z][t];
            
            
            file << t << ";" << pos_z << ";" << ex_val << ";" << hy_val << "\n";
        }
    }
    
    file.close();
    
    
}


