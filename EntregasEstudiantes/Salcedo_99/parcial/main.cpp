#include "include/fdtd.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    using namespace fdtd;

    Config cfg;
    if (argc >= 2) cfg.Nz = std::stoul(argv[1]);
    if (argc >= 3) cfg.steps = std::stoul(argv[2]);
    if (argc >= 4) {
        std::string bc = argv[3];
        if (bc == "periodic") cfg.bc = Boundary::Periodic;
        else if (bc == "pec") cfg.bc = Boundary::PEC;
    }
    cfg.dz = cfg.zmax / static_cast<double>(cfg.Nz);

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
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
