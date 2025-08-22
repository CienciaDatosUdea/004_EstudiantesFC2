#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <vector>

const int N = 10;         // Número de partículas
const double DELTA = 0.05; // Perturbación máxima

// Generador global de números aleatorios
std::mt19937_64& global_rng() {
    static std::mt19937_64 rng{ static_cast<unsigned long long>(std::time(nullptr)) };
    return rng;
}

double random_number(double a, double b) {
    std::uniform_real_distribution<double> dist(a, b);
    return dist(global_rng());
}

// Definición de la estructura Partícula
struct Particula {
    double x, y;   // posición
    double fx, fy; // fuerza
};

// Inicializa la posición sobre la circunferencia unitaria
void init_configuracion(Particula &p) {
    double theta = random_number(0, 2 * M_PI);
    p.x = std::cos(theta);
    p.y = std::sin(theta);
}

// Aplica perturbación aleatoria
void perturbacion(Particula &p, double delta) {
    double dx = random_number(-delta, delta);
    double dy = random_number(-delta, delta);
    p.x += dx;
    p.y += dy;
}

// Asigna fuerza aleatoria en [0, 1]
void asignar_fuerza(Particula &p) {
    p.fx = random_number(0, 1);
    p.fy = random_number(0, 1);
}

// Calcula la distancia euclídea
double distancia(const Particula &a, const Particula &b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx*dx + dy*dy);
}

int main() {
    std::vector<Particula> sistema(N);

    // Inicializar partículas
    for (auto &p : sistema) {
        init_configuracion(p);
    }

    // Perturbación
    for (auto &p : sistema) {
        perturbacion(p, DELTA);
    }

    // Distancia mínima y máxima
    double dmin = 1e10;
    double dmax = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            double d = distancia(sistema[i], sistema[j]);
            if (d < dmin) dmin = d;
            if (d > dmax) dmax = d;
        }
    }

    // Asignar fuerzas
    for (auto &p : sistema) {
        asignar_fuerza(p);
    }

    // Calcular fuerza total
    double Fx_total = 0.0, Fy_total = 0.0;
    for (auto &p : sistema) {
        Fx_total += p.fx;
        Fy_total += p.fy;
    }
    double F_total = std::sqrt(Fx_total*Fx_total + Fy_total*Fy_total);

    // Resultados
    std::cout << "Distancia mínima: " << dmin << "\n";
    std::cout << "Distancia máxima: " << dmax << "\n";
    std::cout << "Fuerza total: " << F_total << "\n";

    return 0;
}
