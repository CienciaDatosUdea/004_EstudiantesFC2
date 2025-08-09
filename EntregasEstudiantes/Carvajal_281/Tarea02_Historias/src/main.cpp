#include <cstdio>
#include <iostream>
#include <fstream>
#include "difusion_model.h"

int main() {
    //Inicializar los parámetros del dominio
    int N = 50;          // número de puntos espaciales
    double xmin = 0.0;   // límite izquierdo
    double xmax = 10.0;   // límite derecho

    //Inicializar los parámetros físicos y de simulación
    double D = 0.1;      // coeficiente de difusión
    double dt = 0.002;  // paso temporal
    double t_max = 0.05; // tiempo total de simulación

    // Construcción de la geometría y condiciones iniciales
    Geometria G(N, xmin, xmax);
    Condiciones Condiciones(G);
    Condiciones.condicionesIniciales();       // Historia 2
    Condiciones.condicionesFronteraDirichlet(); // Historia 3 (puedes cambiar por Neumann si quieres probar)
    DiffusionSolver solver(Condiciones, D, dt, t_max);

    //Aplicación de las futuras funcionalidades: Se generan archivos compatibles con Python que permitirán la visualización del perfil de temperaturas. 
    std::ofstream salida("resultados_tarea02historias.txt");  //Se crea el archivo de salida
    if (!salida) {
        std::cerr << "Error: no se pudo abrir el archivo de salida.\n"; //Caso en que el archivo no se cree
        return 1;
    }

    // Guardar estado inicial en el txt corriendo la simulación
    for (int i = 0; i < N; ++i) {
        salida << G.x[i] << " " << Condiciones.u[i] << "\n";
    }
    salida << "\n";

    //Ejecutar la simulación del difusionsolver
    solver.run();

    // Guardar estado final
    for (int i = 0; i < N; ++i) {
        salida << G.x[i] << " " << Condiciones.u[i] << "\n";
    }

    salida.close();
    std::cout << "Simulación completada exitosamente, los resultados fueron guardados en \n 'resultados_tarea02historias.txt'\n";

    return 0;
}
