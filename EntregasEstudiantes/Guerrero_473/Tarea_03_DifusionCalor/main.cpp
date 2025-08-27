
#include <fstream>   // escribir archivos
#include <iostream>
#include "DifusionCalor.h"

int main() {
    const int N = 50;
    const double xmin = 0.0, xmax = 1.0;
    const double alpha = 0.01, dt = 0.001;
    const double tiempo_max = 1.0;    // tiempo total de simulación en segundos
    const double intervalo = 0.01;     // cada cuánto guardar resultados

    Geometria G(N, xmin, xmax);

    // --- Condiciones iniciales ---
    //CondicionesIniciales CI(G, ESCALON);
    //CondicionesIniciales CI(G, GAUSSIANA);
    //CondicionesIniciales CI(G, IMPULSO_CENTRAL);
    CondicionesIniciales CI(G, UNIFORME);
    CI.aplicar();

    // --- Condiciones de frontera ---
    CondicionesFrontera CF(G, NULA);

    // --- Simulador ---
    Simulador simulador(CI, CF, alpha, dt);

    std::cout << "Iniciando simulación...\n";
    simulador.imprimir( tiempo_max, intervalo);
    simulador.guardar_evolucion("uniforme.txt", tiempo_max, intervalo);
    std::cout << "Simulación finalizada.\n";

    return 0;
}
