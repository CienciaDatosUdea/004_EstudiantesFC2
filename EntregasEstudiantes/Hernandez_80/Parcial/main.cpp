#include <iostream>
#include <string>
#include "include/fdtd.hpp"

int main(int argc, char** argv) {
    // Parámetros base
    FDTDParams P;
    P.nx   = 200;      // nodos
    P.dz   = 1.0;      // paso espacial
    P.c    = 3.0e8;    // velocidad de la luz
    P.beta = 0.49;     // c*dt/dz
    P.bc   = BCType::Periodic;

    int nsteps = 2000;
    int every  = 20;
    std::string outfile = "fields.dat";


    // ./main <bc: periodic|fixed> <nsteps> <beta> <outfile> <dz>
    if (argc > 1) {
        std::string bc = argv[1];
        if (bc == "periodic") P.bc = BCType::Periodic;
        else if (bc == "fixed") P.bc = BCType::FixedZeros;
    }
    if (argc > 2) nsteps = std::stoi(argv[2]);
    if (argc > 3) P.beta = std::stod(argv[3]);
    if (argc > 4) outfile = argv[4];
    if (argc > 5) P.dz = std::stod(argv[5]);

    FDTD sim(P);
    sim.initialize_sine(0.1, 100.0); // E=H=0.1*sin(2π z / 100)

    std::cout << "nx=" << P.nx
              << " dz=" << P.dz
              << " dt=" << sim.dt()
              << " beta=" << sim.get_beta()
              << " BC=" << (P.bc==BCType::Periodic ? "Periodic" : "FixedZeros")
              << "\n";

    sim.run(nsteps, every, outfile);
    return 0;
}
