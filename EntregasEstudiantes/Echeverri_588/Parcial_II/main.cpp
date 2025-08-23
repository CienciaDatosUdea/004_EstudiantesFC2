#include "fdtd.h"

int main() {
    std::cout << "=== EXAMEN FINAL FC2: DIFERENCIAS FINITAS ===" << std::endl;
    std::cout << "Simulación FDTD de Ondas Electromagnéticas\n" << std::endl;
    
    // =============================================
    // PROBLEMA 1.1: Simulación de onda sinusoidal
    // =============================================
    std::cout << "1.1 Simulación de onda sinusoidal con FDTD" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    // Crear simulador con parámetros del problema
    FDTD simulator(200, 1.0, 0.4); // nx=200, dx=1.0, beta=0.4
    
    // Establecer condiciones iniciales
    simulator.setInitialConditions();
    
    // Guardar condiciones iniciales
    simulator.saveToFile("initial_conditions.dat");
    
    // Simular evolución temporal con condiciones periódicas
    std::cout << "Ejecutando simulación con condiciones periódicas..." << std::endl;
    simulator.simulate(500, "periodic");
    
    // Guardar resultados finales
    simulator.saveToFile("final_periodic.dat");
    
    std::cout << "\nEnergía inicial vs final:" << std::endl;
    simulator.setInitialConditions();
    double initial_energy = simulator.getEnergy();
    simulator.simulate(500, "periodic");
    double final_energy = simulator.getEnergy();
    
    // =======================================================
    // PROBLEMA 1.2a: Condiciones de frontera y comparación
    // =======================================================
    std::cout << "\n\n1.2a Estudio de condiciones de frontera" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    // Simulación con condiciones de frontera cero
    FDTD simulator_zero(200, 1.0, 0.4);
    simulator_zero.setInitialConditions();
    
    std::cout << "Ejecutando simulación con condiciones de frontera cero..." << std::endl;
    simulator_zero.simulate(500, "zero");
    
    // Guardar resultados
    simulator_zero.saveToFile("final_zero_boundary.dat");
    
    std::cout << "\nComparación de energías:" << std::endl;
    double energy_zero = simulator_zero.getEnergy();
    std::cout << "Energía con fronteras periódicas: " << final_energy << std::endl;
    std::cout << "Energía con fronteras cero: " << energy_zero << std::endl;
    std::cout << "Ratio (cero/periódica): " << energy_zero/final_energy << std::endl;
    
    // Análisis del comportamiento en las fronteras
    std::cout << "\nCampos en las fronteras (condiciones cero):" << std::endl;
    std::cout << "Ex[0] = " << simulator_zero.getEx()[0] << ", Ex[199] = " << simulator_zero.getEx()[199] << std::endl;
    std::cout << "Hy[0] = " << simulator_zero.getHy()[0] << ", Hy[199] = " << simulator_zero.getHy()[199] << std::endl;
    
    // =============================================
    // PROBLEMA 1.2b: Análisis de estabilidad
    // =============================================
    std::cout << "\n\n1.2b Análisis de estabilidad numérica" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    // Crear simulador para análisis de estabilidad
    FDTD stability_sim(200, 1.0, 0.3);
    
    // Valores de beta a probar (incluyendo algunos que violan Courant)
    std::vector<double> beta_values = {0.3, 0.5, 0.6, 0.8};
    
    // Ejecutar análisis de estabilidad
    stability_sim.stabilityAnalysis(beta_values, 200);
    
    // =============================================
    // ANÁLISIS DETALLADO DE VIOLACIÓN DE COURANT
    // =============================================
    std::cout << "\n\nAnálisis detallado de violación de Courant:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    // Caso estable (beta = 0.4)
    FDTD stable_sim(200, 1.0, 0.4);
    stable_sim.setInitialConditions();
    std::cout << "Simulando caso estable (beta = 0.4)..." << std::endl;
    
    double initial_amp_stable = stable_sim.getMaxAmplitude();
    stable_sim.simulate(300, "periodic");
    double final_amp_stable = stable_sim.getMaxAmplitude();
    
    // Caso inestable (beta = 0.7)
    FDTD unstable_sim(200, 1.0, 0.7);
    unstable_sim.setInitialConditions();
    std::cout << "Simulando caso inestable (beta = 0.7)..." << std::endl;
    
    double initial_amp_unstable = unstable_sim.getMaxAmplitude();
    unstable_sim.simulate(50, "periodic"); // Menos pasos para evitar overflow
    double final_amp_unstable = unstable_sim.getMaxAmplitude();
    
    std::cout << "\nComparación de amplitudes:" << std::endl;
    std::cout << "Caso estable (beta=0.4):" << std::endl;
    std::cout << "  Amplitud inicial: " << initial_amp_stable << std::endl;
    std::cout << "  Amplitud final: " << final_amp_stable << std::endl;
    std::cout << "  Factor de crecimiento: " << final_amp_stable/initial_amp_stable << std::endl;
    
    std::cout << "Caso inestable (beta=0.7):" << std::endl;
    std::cout << "  Amplitud inicial: " << initial_amp_unstable << std::endl;
    std::cout << "  Amplitud final: " << final_amp_unstable << std::endl;
    std::cout << "  Factor de crecimiento: " << final_amp_unstable/initial_amp_unstable << std::endl;

    std::cout << "\n=== SIMULACIÓN COMPLETADA ===" << std::endl;
    
    return 0;
}