// Test program to demonstrate the automatic stability functions
#include "include/fdtd.hpp"
#include <iostream>

int main() {
    using namespace fdtd;
    
    std::cout << "=== FDTD Stability Function Test ===\n\n";
    
    // Create a configuration
    Config cfg;
    cfg.zmax = 200.0;
    cfg.Tmax = 100.0;
    cfg.wavelength = 50.0;
    cfg.Nz = 100;  // Initial guess
    cfg.steps = 100; // Initial guess
    
    std::cout << "Initial configuration:\n";
    std::cout << "zmax = " << cfg.zmax << "\n";
    std::cout << "Tmax = " << cfg.Tmax << "\n";
    std::cout << "wavelength = " << cfg.wavelength << "\n";
    std::cout << "Nz (initial) = " << cfg.Nz << "\n";
    std::cout << "steps (initial) = " << cfg.steps << "\n";
    std::cout << "dz (initial) = " << cfg.dz << "\n\n";
    
    // Compute stable discretization
    cfg.computeStableDiscretization();
    
    std::cout << "After automatic stability computation:\n";
    std::cout << "Nz (stable) = " << cfg.Nz << "\n";
    std::cout << "steps (stable) = " << cfg.steps << "\n";
    std::cout << "dz (stable) = " << cfg.dz << "\n";
    std::cout << "dt (will be) = " << cfg.Tmax / cfg.steps << "\n";
    
    // Check stability conditions
    double dt = cfg.Tmax / cfg.steps;
    double courant = dt / cfg.dz;  // assuming c = 1
    double spatial_stability = cfg.dz / cfg.wavelength;
    
    std::cout << "\nStability checks:\n";
    std::cout << "Courant number (c*dt/dz) = " << courant << " (should be <= 0.5)\n";
    std::cout << "Spatial stability (dz/λ) = " << spatial_stability << " (should be <= 0.1)\n";
    
    // Try to create FDTD solver
    try {
        FDTD1D solver(cfg);
        std::cout << "\n✓ FDTD solver created successfully!\n";
        std::cout << "Solver parameters:\n";
        std::cout << "  Nz = " << solver.Nz() << "\n";
        std::cout << "  dz = " << solver.dz() << "\n";
        std::cout << "  dt = " << solver.dt() << "\n";
        std::cout << "  β (Courant) = " << solver.beta() << "\n";
    } catch (const std::exception& e) {
        std::cout << "\n✗ Error creating FDTD solver: " << e.what() << "\n";
    }
    
    return 0;
}
