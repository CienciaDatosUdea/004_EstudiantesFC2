#include "fdtd.h"
#include <cmath>
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

FDTD1D_Yee::FDTD1D_Yee(int N, int nsteps, double dz_, double dt_, BCType bc_)
    : Nnodes(N), Nsteps(nsteps), dz(dz_), dt(dt_), bc(bc_) {

    // Unidades normalizadas
    eps0 = 1.0;
    mu0  = 1.0;
    c    = 1.0;

    // En unidades normalizadas: betaE = betaH = c*dt/dz
    double courant = c * dt / dz;
    betaE = courant;
    betaH = courant;
    
    std::cout << "Número de Courant: " << courant << std::endl;
    if (courant > 1.0) {
        std::cout << "Courant > 1, simulación inestable" << std::endl;
    }

    Ex.assign(Nnodes, 0.0);
    Hy.assign(Nnodes, 0.0);
}

void FDTD1D_Yee::init_sine(double amplitude, double wavelength) {
    // Ex(k) = A sin(2π k / λ)
    // Hy(k+1/2) = A sin(2π (k+0.5) / λ)
    for (int k = 0; k < Nnodes; ++k) {
        Ex[k] = amplitude * std::sin(2.0 * M_PI * (static_cast<double>(k) / wavelength));
        Hy[k] = amplitude * std::sin(2.0 * M_PI * ((static_cast<double>(k) + 0.5) / wavelength));
    }
    
}

void FDTD1D_Yee::update_E_interior() {
    // Ecuación de Maxwell: ∂E/∂t = (1/ε) ∂H/∂z
    // Discretización: Ex[k]^(n+1) = Ex[k]^n + (dt/ε₀dz)(Hy[k] - Hy[k-1])
    for (int k = 1; k <= Nnodes - 2; ++k) {
        Ex[k] += betaE * (Hy[k] - Hy[k - 1]);
    }
}

void FDTD1D_Yee::apply_E_boundaries() {
    if (bc == BCType::PERIODIC) {
        // FRONTERA IZQUIERDA: Ex[0] usa Hy[0] - Hy[N-1] (wrap around)
        Ex[0] += betaE * (Hy[0] - Hy[Nnodes - 1]);
        
        // FRONTERA DERECHA: Ex[N-1] usa Hy[N-1] - Hy[N-2]
        Ex[Nnodes - 1] += betaE * (Hy[Nnodes - 1] - Hy[Nnodes - 2]);
        
    } else { // DIRICHLET (paredes conductoras)
        Ex[0] = 0.0;
        Ex[Nnodes - 1] = 0.0;
    }
}

void FDTD1D_Yee::update_H_interior() {
    // Ecuación de Maxwell: ∂H/∂t = -(1/μ) ∂E/∂z
    // Discretización: Hy[k]^(n+1) = Hy[k]^n - (dt/μ₀dz)(Ex[k+1] - Ex[k])
    for (int k = 0; k <= Nnodes - 2; ++k) {
        Hy[k] -= betaH * (Ex[k + 1] - Ex[k]);
    }
}

void FDTD1D_Yee::apply_H_boundaries() {
    if (bc == BCType::PERIODIC) {
        // FRONTERA: Hy[N-1] está entre Ex[N-1] y Ex[0] 
        Hy[Nnodes - 1] -= betaH * (Ex[0] - Ex[Nnodes - 1]);
        
    } else { // DIRICHLET
        // En paredes conductoras, el campo magnético tangencial también es cero
        Hy[0] = 0.0;
        Hy[Nnodes - 1] = 0.0;
    }
}



void FDTD1D_Yee::save_snapshot(int step, const std::string& outdir) {
    // Guardar exactamente 10 snapshots distribuidos uniformemente
    const int max_snapshots = 10;
    const int interval = std::max(1, Nsteps / (max_snapshots));
    
    // Condiciones para guardar los csv:
    bool save_this_step = (step == 0) || 
                         (step == Nsteps) ||
                         (step % interval == 0 && step > 0);
    
    if (!save_this_step) return;

    fs::create_directories(outdir);
    std::ofstream file(outdir + "/snapshot_step_" + std::to_string(step) + ".csv");
    file << "i,z,Ex,Hy\n";
    for (int k = 0; k < Nnodes; ++k) {
        double z = k * dz;  // posición física
        file << k << "," << z << "," << Ex[k] << "," << Hy[k] << "\n";
    }
}


void FDTD1D_Yee::run(const std::string& outdir) {
    std::cout << "Condiciones de frontera: " << 
        (bc == BCType::PERIODIC ? "PERIÓDICAS" : "DIRICHLET") << std::endl;
    
    // Guardar estado inicial
    save_snapshot(0, outdir);
    
    for (int step = 1; step < Nsteps; ++step) {
        // 1) Actualiza E en tiempo n+1/2
        update_E_interior();
        apply_E_boundaries();

        // 2) Actualiza H en tiempo n+1  
        update_H_interior();
        apply_H_boundaries();

        // 3) Guarda snapshot si es necesario
        save_snapshot(step, outdir);
    }
    
    
}








