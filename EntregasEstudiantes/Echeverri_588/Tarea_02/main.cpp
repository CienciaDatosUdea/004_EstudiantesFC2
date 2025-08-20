#include <iostream>
#include "/Users/aleja/Desktop/UdeA/FC_II/004_EstudiantesFC2/EntregasEstudiantes/Echeverri_588/Tarea 02/include/difusion_model.h"

int main() {
    // Parámetros de la simulación
    int N = 100;             // número de puntos de la malla
    double xmin = 0.0;
    double xmax = 1.0;
    double D = 0.1;          // coeficiente de difusión
    double dt = 0.0005;      // paso temporal
    double t_max = 0.1;      // tiempo total
    double alpha_ini = 50.0; // parámetro de la gaussiana inicial
    double x0 = 0.5;         // centro de la gaussiana
    double TL = 0.0;         // temperatura en el borde izquierdo
    double TR = 0.0;         // temperatura en el borde derecho

    // Crear geometría y condiciones iniciales
    Geometria geo(N, xmin, xmax);
    Condiciones cond(geo);
    DiffusionSolver solver(D, dt, t_max);

    // Verificar estabilidad antes de resolver
    if (!solver.verificarEstabilidad(geo.dx)) {
        std::cerr << "Error: Ajusta dt, dx o D para cumplir el criterio de estabilidad.\n";
        return -1;
    }

    // Aplicar condición inicial y de frontera
    cond.condicionesIniciales(alpha_ini, x0);
    cond.condicionesFrontera(TL, TR);

    std::cout << "Resolviendo el problema de difusión con FTCS...\n";

    // Resolver el problema
    solver.resolverFTCS(cond, TL, TR);

    // Guardar resultados en archivo
    guardarResultado(geo, cond, "resultados.txt");

    std::cout << "Simulación completada. Resultados guardados en 'resultados.txt'.\n";

    return 0;
}
