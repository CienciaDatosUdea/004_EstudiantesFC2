#include "fdtd.hpp"

int main() {
    // Simulación 1: Fronteras Periódicas (Problema 1.1)
    FDTDSimulator sim_periodic(200, 0.45);
    sim_periodic.set_boundary_conditions("periodic");
    sim_periodic.run(100, 10, "fdtd_periodic_data.txt");

    // Simulación 2: Fronteras Absorbentes (Problema 1.2a)
    FDTDSimulator sim_absorbing(200, 0.45);
    sim_absorbing.set_boundary_conditions("absorbing");
    sim_absorbing.run(200, 10, "fdtd_absorbing_data.txt");
    
    // Simulación 3: Prueba de Estabilidad (Problema 1.2b)
    FDTDSimulator sim_unstable(200, 1.0); 
    sim_unstable.set_boundary_conditions("periodic");
    sim_unstable.run(200, 5, "fdtd_unstable_data.txt"); 

    return 0;
}