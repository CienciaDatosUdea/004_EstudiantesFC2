#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

const int N = 10;          // Número de partículas
const double R = 1.0;      // Radio de la circunferencia
const double DELTA = 0.1;  // Rango de perturbación
const double PI = 3.14159265358979323846;            

// Estructura que representa una partícula en 2D
struct particula {
    double x, y;   // Posición en el plano
    double fx, fy; // Componentes de la fuerza
};

// Inicializa partículas sobre la circunferencia de radio R
void init_position(particula *p) {
    for (int i = 0; i < N; i++) {
        double theta = ((double) rand() / RAND_MAX) * 2.0 * PI;
        p[i].x = R * cos(theta);
        p[i].y = R * sin(theta);
    }
}

// Perturbación aleatoria
void perturb_position(particula *p) {
    for (int i = 0; i < N; i++) {
        double dx = ((double) rand() / RAND_MAX) * 2 * DELTA - DELTA;
        double dy = ((double) rand() / RAND_MAX) * 2 * DELTA - DELTA;
        p[i].x += dx;
        p[i].y += dy;
    }
}

// Distancia máxima entre partículas
double max_distance(particula *p) {
    double max_d = 0.0;
    double dx, dy, dij;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            dx = p[i].x - p[j].x;
            dy = p[i].y - p[j].y;
            dij = sqrt(dx * dx + dy * dy);
            if (dij > max_d) max_d = dij;
        }
    }
    return max_d;
}

// Asignar fuerzas aleatorias
void assign_forces(particula *p) {
    for (int i = 0; i < N; i++) {
        p[i].fx = (double) rand() / RAND_MAX;
        p[i].fy = (double) rand() / RAND_MAX;
    }
}

// Calcular fuerza total
double total_force(particula *p) {
    double fx_total = 0.0, fy_total = 0.0;
    for (int i = 0; i < N; i++) {
        fx_total += p[i].fx;
        fy_total += p[i].fy;
    }
    return sqrt(fx_total * fx_total + fy_total * fy_total);
}

int main() {
    system("clear");               // limpia consola (en Linux/macOS)
    srand(time(NULL));             // Inicializa la semilla aleatoria con el reloj del sistema
    particula p[N];                // Se crea el arreglo de partículas

    init_position(p);              // Inicializa las partículas
    perturb_position(p);

    std::cout << "Distancia máxima: " << max_distance(p) << "\n";

    assign_forces(p);
    std::cout << "Fuerza total: " << total_force(p) << "\n";

    return 0;
}
