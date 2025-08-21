#include <iostream> 
#include "fdtd.hpp" // Se incluye el encabezado con la definición de la clase

int main() {
    std::cout << "--- Iniciando conjunto de simulaciones de propagación de ondas ---" << std::endl;

    // --- Simulación 1: Caso con fronteras periódicas ---
    // Corresponde al problema 1.1. Se espera que la onda se propague y
    // reaparezca por el lado opuesto de la malla.
    std::cout << "\n[1/3] Ejecutando simulación con bordes periódicos..." << std::endl;
    WavePropagator casoPeriodico(200, 0.45);
    casoPeriodico.definirLimites("periodic");
    casoPeriodico.iniciarSimulacion(130, 10, "resultados_periodico.txt");

    // --- Simulación 2: Caso con fronteras absorbentes ---
    // Corresponde al problema 1.2a. Se espera que la onda se disipe
    // al llegar a los extremos de la malla, simulando un espacio abierto.
    std::cout << "\n[2/3] Ejecutando simulación con bordes absorbentes..." << std::endl;
    WavePropagator casoAbsorbente(200, 0.45);
    casoAbsorbente.definirLimites("absorbing");
    casoAbsorbente.iniciarSimulacion(200, 10, "resultados_absorbente.txt");
    
    // --- Simulación 3: Prueba de inestabilidad numérica ---
    // Corresponde al problema 1.2b. Se usa un factor beta >= 1.0, lo que viola
    // la condición de estabilidad de Courant-Friedrichs-Lewy (CFL).
    // Se espera que los valores de la simulación diverjan a infinito.
    std::cout << "\n[3/3] Ejecutando prueba de inestabilidad (beta=1.0)..." << std::endl;
    WavePropagator casoInestable(200, 1.0); 
    casoInestable.definirLimites("periodic");
    casoInestable.iniciarSimulacion(200, 10, "resultados_inestable.txt"); 

    std::cout << "\n--- Todas las simulaciones han finalizado. ---" << std::endl;

    return 0;
}
