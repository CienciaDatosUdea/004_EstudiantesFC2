
#include <cstdio>
#include <iostream>
#include <cmath>
#include "campo_velocidades.h"

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

// Constructor modificado para aceptar tipo de problema y fuerza
Condiciones::Condiciones(Grid &G_, ProblemType ptype, ForceType ftype)
    :G(G_), problemType(ptype), forceType(ftype){}

void Condiciones::CondicionesIniciales(){
    U.resize(G.nx, std::vector<double>(G.ny, 1E-10));
    V.resize(G.nx, std::vector<double>(G.ny, 1E-10));
    P.resize(G.nx, std::vector<double>(G.ny, 10));
    
    // Inicializar fuerzas
    Fx.resize(G.nx, std::vector<double>(G.ny, 0.0));
    Fy.resize(G.nx, std::vector<double>(G.ny, 0.0));
    
    AplicarFuerza(); // Configurar fuerza según tipo
}

void Condiciones::AplicarFuerza() {
    switch(forceType) {
        case ForceType::CONSTANT_X:
            for(int i=0; i<G.nx; i++) {
                for(int j=0; j<G.ny; j++) {
                    Fx[i][j] = 1.0; // Fuerza constante en x
                }
            }
            break;
            
        case ForceType::CONSTANT_Y:
            for(int i=0; i<G.nx; i++) {
                for(int j=0; j<G.ny; j++) {
                    Fy[i][j] = 1.0; // Fuerza constante en y
                }
            }
            break;
            
        case ForceType::NONE:
        default:
            // No hacer nada, fuerzas ya están en 0
            break;
    }
}

void Condiciones::CondicionesFrontera(){   
    switch(problemType) {
        case ProblemType::CAVITY_FLOW:
            // Condiciones para Cavity Flow (tu código original)
            for(int i=0;i<G.nx;i++){
                U[i][0] = 0;
                V[i][0] = 0;
                P[i][0] = P[i][1];
            }
            
            for(int j=0;j<G.ny;j++){
                U[0][j] = 0;
                V[0][j] = 0;
                P[0][j] = P[1][j];
            }    
            
            for(int j=0;j<G.ny;j++){
                U[G.nx-1][j] = 0;
                V[G.nx-1][j] = 0;
                P[G.nx-1][j]=P[G.nx-2][j];
            }

            for(int i=0;i<G.nx;i++){
                U[i][G.ny - 1] = 1;
                V[i][G.ny - 1] = 0;
                P[i][G.ny - 1] = 0;        
            }
            break;
            
        case ProblemType::CHANNEL_FLOW:
            // Condiciones para Channel Flow
            // Fronteras periódicas en x
            for(int j=0;j<G.ny;j++){
                U[0][j] = U[G.nx-2][j]; // Periódica
                V[0][j] = V[G.nx-2][j];
                P[0][j] = P[G.nx-2][j];
                
                U[G.nx-1][j] = U[1][j];
                V[G.nx-1][j] = V[1][j];
                P[G.nx-1][j] = P[1][j];
            }
            
            // Fronteras superior e inferior con no-slip
            for(int i=0;i<G.nx;i++){
                U[i][0] = 0;
                V[i][0] = 0;
                U[i][G.ny-1] = 0;
                V[i][G.ny-1] = 0;
                
                // Condiciones de presión para Channel Flow
                P[i][0] = P[i][1]; // ∂p/∂y = 0 en y=0
                P[i][G.ny-1] = P[i][G.ny-2]; // ∂p/∂y = 0 en y=Ly
            }
            break;
    }
}

Presion::Presion(Condiciones &C_, double rho_, double dt_, int nit_)
    : C(C_), rho(rho_), dt(dt_), nit(nit_) {}

void Presion::calcularPresion(){
    int nx = C.G.nx;
    int ny = C.G.ny;
    double dx = C.G.dx;
    double dy = C.G.dy;

    std::vector<std::vector<double>> Pn = C.P;
    for (int it = 0; it < nit; ++it) {
        Pn = C.P;
        for (int i = 1; i < nx - 1; ++i) {
            for (int j = 1; j < ny - 1; ++j) {
                double dudx = (C.U[i+1][j] - C.U[i-1][j]) / (2.0 * dx);
                double dudy = (C.U[i][j+1] - C.U[i][j-1]) / (2.0 * dy);
                double dvdx = (C.V[i+1][j] - C.V[i-1][j]) / (2.0 * dx);
                double dvdy = (C.V[i][j+1] - C.V[i][j-1]) / (2.0 * dy);
                
                double b = rho * (
                    (1.0 / dt) * (dudx + dvdy)
                    - dudx * dudx
                    - 2.0 * dudy * dvdx
                    - dvdy * dvdy
                );
                
                C.P[i][j] = (
                    (Pn[i+1][j] + Pn[i-1][j]) * dy * dy +
                    (Pn[i][j+1] + Pn[i][j-1]) * dx * dx -
                    b * dx * dx * dy * dy
                ) / (2.0 * (dx * dx + dy * dy));
            }
        }
        C.CondicionesFrontera();
    }
};

Velocidades::Velocidades(Presion &omega_):omega(omega_){}

void Velocidades::calcularVelocidades() {
    int nx = omega.C.G.nx;
    int ny = omega.C.G.ny;
    double dx = omega.C.G.dx;
    double dy = omega.C.G.dy;
    double dt = omega.dt;
    double rho = omega.rho;
    double nu = 0.1;

    std::vector<std::vector<double>> Un = omega.C.U;
    std::vector<std::vector<double>> Vn = omega.C.V;
    std::vector<std::vector<double>> P = omega.C.P;

    for (int i = 1; i < nx - 1; i++) {
        for (int j = 1; j < ny - 1; j++) {
            // Términos de fuerza adicionales
            double force_x = omega.C.Fx[i][j];
            double force_y = omega.C.Fy[i][j];
            
            // Actualizar componente U  
            omega.C.U[i][j] = Un[i][j]
                - Un[i][j] * dt / dx * (Un[i][j] - Un[i - 1][j])
                - Vn[i][j] * dt / dy * (Un[i][j] - Un[i][j - 1])
                - dt / (2.0 * rho * dx) * (P[i + 1][j] - P[i - 1][j])
                + nu * dt * (
                    (Un[i + 1][j] - 2 * Un[i][j] + Un[i - 1][j]) / (dx * dx) +
                    (Un[i][j + 1] - 2 * Un[i][j] + Un[i][j - 1]) / (dy * dy)
                )
                + dt * force_x; // Agregar fuerza en x

            // Actualizar componente V
            omega.C.V[i][j] = Vn[i][j]
                - Un[i][j] * dt / dx * (Vn[i][j] - Vn[i - 1][j])
                - Vn[i][j] * dt / dy * (Vn[i][j] - Vn[i][j - 1])
                - dt / (2.0 * rho * dy) * (P[i][j + 1] - P[i][j - 1])
                + nu * dt * (
                    (Vn[i + 1][j] - 2 * Vn[i][j] + Vn[i - 1][j]) / (dx * dx) +
                    (Vn[i][j + 1] - 2 * Vn[i][j] + Vn[i][j - 1]) / (dy * dy)
                )
                + dt * force_y; // Agregar fuerza en y
        }
    }

    omega.C.CondicionesFrontera();
}

EscribirCampo::EscribirCampo(const std::string &filename) {
    std::string ruta = "python/datos/" + filename;
    file.open(ruta);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << ruta << std::endl;
    }
}



    /* 
    Forma en que se guardan los datos

            # i		j		x		y		u		v		p

        # nx		ny	 t	Tamaño de la malla 
        # 3		2
        # =================================
        0	0	0.0	0.0	0.00000001	0.00000001	10   valores para cad apunto de la mmalla
        0	1	0.0	1.0	0.00000001	0.00000001	10
        1	0	1.0	0.0	0.00000001	0.00000001	10
        1	1	1.0	1.0	0.00000001	0.00000001	10
        2	0	2.0	0.0	0.00000001	0.00000001	10
        2	1	2.0	1.0	0.00000001	0.00000001	10
    
    
    */

void EscribirCampo::PosicionCampo(const Grid &G, const Condiciones &C, double t) {
    int nx = G.nx;
    int ny = G.ny;
    
    file << "# Tiempo: " << t << "\n";
    file << "# Tipo Problema: " << (C.problemType == ProblemType::CAVITY_FLOW ? "CAVITY_FLOW" : "CHANNEL_FLOW") << "\n";
    file << "# i\tj\tx\ty\tu\tv\tp\tFx\tFy\n";
    file << "# " << nx << "\t" << ny << "\n";
    file << "# =================================\n";

    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            file << i << "\t" << j << "\t"
                 << G.XY[i][j][0] << "\t" << G.XY[i][j][1] << "\t"
                 << C.U[i][j] << "\t" << C.V[i][j] << "\t" << C.P[i][j] << "\t"
                 << C.Fx[i][j] << "\t" << C.Fy[i][j] << "\n";
        }
    }
}