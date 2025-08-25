#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <omp.h>
#include "flow.h"

int main(int argc, char* argv[]) {

    // Inicialización de la grilla y los campos
    Grid G(0.0, 1.0, 0.0, 1.0, 41, 41);
    CampoVelocidadesPresion Campo(G);
    Campo.CondicionesIniciales();
    Campo.BoundaryCondition();
    
    // Parámetros de la simulación
    double rho = 1.0;
    double dt = 0.001;
    int nit = 100;
    
    // Instancias de las clases para computar la presión y las velocidades
    ComputePresion presion(Campo, rho, dt, nit);
    ComputeCampo omega(presion);

    std::cout << "Starting simulation..." << std::endl;

    const int nt = 1000;
    
    // Bucle principal de la simulación
    // Se llama a las funciones que actualizan el campo en cada paso
    for (int i = 0; i < nt; ++i) {
        
        // Llamada a las funciones de actualización
        presion.presionUpdate();
        omega.velocidadesUpdate();

        // Código para guardar datos
        if (i % (10) == 0 && i > 500) {
            
            // Nombre del archivo de salida
            char filename[50];
            std::snprintf(filename, sizeof(filename), "data/campos_%03d.txt", i);

            // Abre el archivo y guarda la grilla y los campos
            FieldWriter writer(filename);
            writer.writePosicionCampo(G, Campo);

            std::cout << "step: " << i << " of " << nt << " | file saved" << std::endl;
        }
    }

    std::cout << "Simulation finished" << std::endl;
    return 0;
}