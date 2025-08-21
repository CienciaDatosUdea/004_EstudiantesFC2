#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <iomanip>

// --- Constantes Globales ---
const int N = 10;          // Número de partículas
const double R = 1.0;      // Radio de la circunferencia
const double DELTA = 0.1;  // Rango de perturbación aleatoria [-DELTA, DELTA]

// --- Estructura de Datos ---
// Representa una partícula con su posición (x, y) y fuerza (fx, fy).
struct Particula {
    double x, y;
    double fx, fy;
};

// --- Funciones de Ayuda ---

// Generador de números aleatorios de alta calidad.
double generarAleatorio(double min, double max) {
    static std::mt19937 generador(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<double> distribucion(min, max);
    return distribucion(generador);
}

// --- Funciones Principales de la Simulación ---

// 1. Inicializa las partículas en una circunferencia.
void inicializarParticulas(std::vector<Particula>& particulas) {
    particulas.clear(); // Limpiamos el vector por si tuviera datos previos
    for (int i = 0; i < N; ++i) {
        double theta = generarAleatorio(0, 2 * M_PI); // Ángulo aleatorio en radianes
        double x = R * cos(theta);
        double y = R * sin(theta);
        particulas.push_back({x, y, 0.0, 0.0});
    }
}

// 2. Aplica una perturbación aleatoria a cada partícula.
void perturbarParticulas(std::vector<Particula>& particulas) {
    for (auto& p : particulas) {
        double dx = generarAleatorio(-DELTA, DELTA);
        double dy = generarAleatorio(-DELTA, DELTA);
        p.x += dx;
        p.y += dy;
    }
}

// 3. Calcula la distancia máxima entre cualquier par de partículas.
double calcularDistanciaMaxima(const std::vector<Particula>& particulas) {
    double max_dist_sq = 0.0; // Usamos distancia al cuadrado para optimizar 
    for (size_t i = 0; i < particulas.size(); ++i) {
        for (size_t j = i + 1; j < particulas.size(); ++j) {
            double dx = particulas[i].x - particulas[j].x;
            double dy = particulas[i].y - particulas[j].y;
            double dist_sq = dx * dx + dy * dy;
            if (dist_sq > max_dist_sq) {
                max_dist_sq = dist_sq;
            }
        }
    }
    return sqrt(max_dist_sq); // Calculamos la raíz cuadrada solo una vez al final
}

// 4. Asigna un vector de fuerza aleatorio a cada partícula.
void asignarFuerzas(std::vector<Particula>& particulas) {
    for (auto& p : particulas) {
        p.fx = generarAleatorio(0, 1);
        p.fy = generarAleatorio(0, 1);
    }
}

// 5. Calcula la magnitud de la fuerza total del sistema.
double calcularFuerzaTotal(const std::vector<Particula>& particulas) {
    double fuerza_total_x = 0.0;
    double fuerza_total_y = 0.0;
    for (const auto& p : particulas) {
        fuerza_total_x += p.fx;
        fuerza_total_y += p.fy;
    }
    // Magnitud del vector resultante
    return sqrt(fuerza_total_x * fuerza_total_x + fuerza_total_y * fuerza_total_y);
}

int main() {
    std::vector<Particula> sistema;

    std::cout << "--- SIMULACION CON ESTRUCTURAS ---" << std::endl;

    // Paso 1: Inicialización
    inicializarParticulas(sistema);
    std::cout << "1. Se generaron " << N << " particulas en una circunferencia de radio " << R << std::endl;

    // Paso 2: Perturbación
    perturbarParticulas(sistema);
    std::cout << "2. Se aplico una perturbacion aleatoria en el rango [-" << DELTA << ", " << DELTA << "]" << std::endl;

    // Paso 3: Cálculo de distancia máxima
    double dist_max = calcularDistanciaMaxima(sistema);
    std::cout << "3. La distancia maxima entre particulas es: " << std::fixed << std::setprecision(4) << dist_max << std::endl;

    // Paso 4: Asignación de fuerzas
    asignarFuerzas(sistema);
    std::cout << "4. Se asignaron fuerzas aleatorias a cada particula." << std::endl;

    // Paso 5: Cálculo de la fuerza total
    double fuerza_total_mag = calcularFuerzaTotal(sistema);
    std::cout << "5. La magnitud de la fuerza total del sistema es: " << fuerza_total_mag << std::endl;

    return 0;
}