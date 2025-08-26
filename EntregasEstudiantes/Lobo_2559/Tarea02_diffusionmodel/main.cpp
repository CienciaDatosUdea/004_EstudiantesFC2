#include "src/difusion_model.cpp"


int main(){
    // Prueba rápida
    //Definir parámetros
    int N = 8;
    double xmin = -1.0;
    double xmax = 1.0;
    double D = 1.0;
    double dt = 0.01;
    double t_max = 1.0;

    //Definir geometría
    Geometria barra(N, xmin, xmax);

    //Definir condicion inicial
    CampoInicial u(0.0, 1.0, 0.0, 1.0, barra);

    //
    DiffusionSolver solver(barra, u, D, dt);
    solver.evolucion(t_max);
    solver.save("Pasos/paso_final.csv");

    return 0;
}