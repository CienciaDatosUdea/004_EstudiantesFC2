#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <omp.h>
#include "flow.h"

int main(int argc, char* argv[]) {


    Grid G(0.0, 1.0, 0.0, 1.0, 40, 40);
    CampoVelocidadesPresion Campo(G);
    Campo.CondicionesIniciales();
    Campo.BoundaryCondition();
    double rho = 1.0;
    double dt = 0.001;
    int nit = 100;
    ComputePresion presion(Campo, rho, dt, nit);
    ComputeCampo omega(presion);

    std::cout << "Starting simulation..." << std::endl;

    const int nt = 1500;
    for (int i = 0; i < nt; ++i) {
        presion.presionUpdate();
        omega.velocidadesUpdate();

        // Código para guardar datos
        if (i % (10) == 0 && i > 700) {
            char filename[50];
            std::snprintf(filename, sizeof(filename), "data/campos_%03d.txt", i);
            FieldWriter writer(filename);
            writer.writePosicionCampo(G, Campo);

            std::cout << "step: " << i << " of " << nt << " | file saved" << std::endl;
        }
    }

    std::cout << "Simulation finished" << std::endl;
    return 0;
}