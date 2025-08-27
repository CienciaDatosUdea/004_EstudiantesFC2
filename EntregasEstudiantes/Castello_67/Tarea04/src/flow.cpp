# include <cstdio>
# include <iostream>
#include <iomanip>
# include "../include/flow.h"

Grid::Grid(double x_min_, double x_max_,
        double y_min_, double y_max_, int nx_, int ny_)
    :x_min(x_min_),x_max(x_max_),y_min(y_min_),y_max(y_max_),nx(nx_),ny(ny_){
        
        dx=(x_max-x_min)/(nx-1);
        dy=(y_max-y_min)/(ny-1);
        XY.resize(nx, std::vector<std::vector<double>>(ny, std::vector<double>(2)));
        
        for(int i=0;i<nx;i++){
            for(int j=0;j<ny;j++){
                XY[i][j][0] = x_min+i*dx;
                XY[i][j][1] = y_min+j*dy;
            }
        }
};

CampoVelocidadesPresion::CampoVelocidadesPresion(Grid &G_)
    :G(G_){}

void CampoVelocidadesPresion::CondicionesIniciales(){
    U.resize(G.nx, std::vector<double>(G.ny, 0.0));
    V.resize(G.nx, std::vector<double>(G.ny, 0.0));
    P.resize(G.nx, std::vector<double>(G.ny, 0.0));      
}

void CampoVelocidadesPresion::BoundaryCondition(){   
    for(int i=0; i < G.nx; i++){
        U[i][0] = 0.0;
        V[i][0] = 0.0;
        P[i][0] = P[i][1]; 
    }

    for(int i=0; i < G.nx; i++){
        U[i][G.ny - 1] = 0.0; 
        V[i][G.ny - 1] = 0.0;
        P[i][G.ny - 1] = P[i][G.ny - 2];  
    }

    for(int j=0; j < G.ny; j++){
        U[0][j] = U[G.nx - 2][j];
        V[0][j] = V[G.nx - 2][j];
        P[0][j] = P[G.nx - 2][j];

        U[G.nx - 1][j] = U[1][j];
        V[G.nx - 1][j] = V[1][j];
        P[G.nx - 1][j] = P[1][j];
    }
}
ComputePresion::ComputePresion(CampoVelocidadesPresion &Campo_, double rho_, double dt_, int nit_)
    : Campo(Campo_), rho(rho_), dt(dt_), nit(nit_) {}


void ComputePresion::presionUpdate(){
    int nx = Campo.G.nx;
    int ny = Campo.G.ny;
    double dx = Campo.G.dx;
    double dy = Campo.G.dy;
    std::vector<std::vector<double>> Pn = Campo.P;
    for (int it = 0; it < nit; ++it) {
        Pn = Campo.P;
        for (int i = 1; i < nx - 1; ++i) {
            for (int j = 1; j < ny - 1; ++j) {
                // Gradientes para el término fuente b
                double dudx = (Campo.U[i+1][j] - Campo.U[i-1][j]) / (2.0 * dx);
                double dudy = (Campo.U[i][j+1] - Campo.U[i][j-1]) / (2.0 * dy);
                double dvdx = (Campo.V[i+1][j] - Campo.V[i-1][j]) / (2.0 * dx);
                double dvdy = (Campo.V[i][j+1] - Campo.V[i][j-1]) / (2.0 * dy);
                double b = rho * (
                    (1.0 / dt) * (dudx + dvdy)
                    - dudx * dudx
                    - 2.0 * dudy * dvdx
                    - dvdy * dvdy
                );
                // Actualización presión
                Campo.P[i][j] = (
                    (Pn[i+1][j] + Pn[i-1][j]) * dy * dy +
                    (Pn[i][j+1] + Pn[i][j-1]) * dx * dx -
                    b * dx * dx * dy * dy
                ) / (2.0 * (dx * dx + dy * dy));
            }
        }
     Campo.BoundaryCondition();
    }
};

ComputeCampo::ComputeCampo(ComputePresion &omega_):omega(omega_){}

void ComputeCampo::velocidadesUpdate() {
    int nx = omega.Campo.G.nx;
    int ny = omega.Campo.G.ny;
    double dx = omega.Campo.G.dx;
    double dy = omega.Campo.G.dy;
    double dt = omega.dt;
    double rho = omega.rho;
    double nu = 0.1;


    const double Fx = 1.0;

    std::vector<std::vector<double>> Un = omega.Campo.U;
    std::vector<std::vector<double>> Vn = omega.Campo.V;
    std::vector<std::vector<double>> P = omega.Campo.P;
    for (int i = 1; i < nx - 1; i++) {
        for (int j = 1; j < ny - 1; j++) {
            // Actualizar componente U
            omega.Campo.U[i][j] = Un[i][j]
                - Un[i][j] * dt / dx * (Un[i][j] - Un[i - 1][j])
                - Vn[i][j] * dt / dy * (Un[i][j] - Un[i][j - 1])
                - dt / (2.0 * rho * dx) * (P[i + 1][j] - P[i - 1][j])
                + nu * dt * (
                    (Un[i + 1][j] - 2 * Un[i][j] + Un[i - 1][j]) / (dx * dx) +
                    (Un[i][j + 1] - 2 * Un[i][j] + Un[i][j - 1]) / (dy * dy)
                )
                + Fx * dt; 

            omega.Campo.V[i][j] = Vn[i][j]
                - Un[i][j] * dt / dx * (Vn[i][j] - Vn[i - 1][j])
                - Vn[i][j] * dt / dy * (Vn[i][j] - Vn[i][j - 1])
                - dt / (2.0 * rho * dy) * (P[i][j + 1] - P[i][j - 1])
                + nu * dt * (
                    (Vn[i + 1][j] - 2 * Vn[i][j] + Vn[i - 1][j]) / (dx * dx) +
                    (Vn[i][j + 1] - 2 * Vn[i][j] + Vn[i][j - 1]) / (dy * dy)
                );
        }
    }

}


FieldWriter::FieldWriter(const std::string &filename)    
    {
        file.open(filename);
        if (!file.is_open()) 
            throw std::runtime_error("No se pudo abrir el archivo: " + filename);
        
        file << std::fixed << std::setprecision(6);
    }


void FieldWriter::writePosicionCampo(const Grid &G, const   CampoVelocidadesPresion &Campo)
{
    int nx=G.nx;
    int ny=G.ny;
    file << "# i\t\tj\t\tx\t\ty\t\tu\t\tv\t\tp\n";    
    file << "# nx\t\tny\t\t\n";
    file << "# "<<nx<<"\t\t"<<ny<<"\n";
    file << "# =================================\n";
    
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            file << i             << "\t"
                 << j             << "\t"
                 << G.XY[i][j][0] << "\t"
                 << G.XY[i][j][1] << "\t"
                 << Campo.U[i][j] << "\t"
                 << Campo.V[i][j] << "\t"
                 << Campo.P[i][j] << "\n";
        }
    }
}