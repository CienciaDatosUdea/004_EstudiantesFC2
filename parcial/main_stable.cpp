#include "include/fdtd.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    using namespace fdtd;

    Config cfg;

    // Parse command line arguments
    if (argc >= 2) cfg.Nz = std::stoul(argv[1]);
    if (argc >= 3) cfg.steps = std::stoul(argv[2]);
    if (argc >= 4) {
        std::string bc = argv[3];
        if (bc == "periodic") cfg.bc = Boundary::Periodic;
        else if (bc == "pec") cfg.bc = Boundary::PEC;
    }

    // Automatically compute stable discretization
    std::cout << "Computing stable discretization...\n";
    std::cout << "Original Nz: " << cfg.Nz << ", steps: " << cfg.steps << "\n";

    cfg.computeStableDiscretization(0.1, 0.25);

    std::cout << "Stable Nz: " << cfg.Nz << ", steps: " << cfg.steps << "\n";
    std::cout << "dz: " << cfg.dz << ", expected dt: " << cfg.Tmax / cfg.steps << "\n";

    try {
        FDTD1D solver(cfg);
        std::cout << "FDTD 1D\n"
                  << "Nz=" << solver.Nz()
                  << " dz=" << solver.dz()
                  << " dt=" << solver.dt()
                  << " beta=" << solver.beta()
                  << " steps=" << cfg.steps
                  << " bc=" << (cfg.bc==Boundary::Periodic? "Periodic":"PEC")
                  << "\n";
        solver.run();
        std::cout << "Simulation completed successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
