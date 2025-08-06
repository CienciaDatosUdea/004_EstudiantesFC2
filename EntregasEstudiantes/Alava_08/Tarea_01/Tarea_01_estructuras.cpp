// Tarea_01_estructuras.cpp

// Importamos librerias pertinentes
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <iomanip>
using namespace std;

// Constantes del sistema
const int NUM_PARTICULAS = 10;
const double RADIO = 1.0;
const double DELTA = 0.1;
const uint64_t SEMILLA = 42;

// Estructura que representa una partícula
struct Particula {
    double x, y;     // Posición en el plano (2D)
    double fx, fy;   // Componentes de la fuerza
};

// Calcula la distancia euclidiana entre dos partículas
double distancia(const Particula& a, const Particula& b) {
    return hypot(a.x - b.x, a.y - b.y);
}

int main() {
    // Generadores aleatorios
    mt19937_64 generador(SEMILLA);
    uniform_real_distribution<double> distribucion_angulo(0, 2 * M_PI);
    uniform_real_distribution<double> distribucion_perturbacion(-DELTA, DELTA);
    uniform_real_distribution<double> distribucion_fuerza(0.0, 1.0);

    // Vector de partículas
    vector<Particula> particulas(NUM_PARTICULAS);

    // Inicialización de partículas sobre la circunferencia + perturbación
    for (int i = 0; i < NUM_PARTICULAS; ++i) {
        double angulo = distribucion_angulo(generador);
        particulas[i].x = RADIO * cos(angulo) + distribucion_perturbacion(generador);
        particulas[i].y = RADIO * sin(angulo) + distribucion_perturbacion(generador);
        particulas[i].fx = distribucion_fuerza(generador);
        particulas[i].fy = distribucion_fuerza(generador);
    }

    // Cálculo de la distancia máxima entre cualquier par de partículas
    double distancia_maxima = 0;
    for (int i = 0; i < NUM_PARTICULAS; ++i) {
        for (int j = i + 1; j < NUM_PARTICULAS; ++j) {
            distancia_maxima = max(distancia_maxima, distancia(particulas[i], particulas[j]));
        }
    }

    // Cálculo de la fuerza total (suma vectorial)
    double fuerza_total_x = 0, fuerza_total_y = 0;
    for (const auto& p : particulas) {
        fuerza_total_x += p.fx;
        fuerza_total_y += p.fy;
    }

    // Mostrar resultados
    cout << fixed << setprecision(5);
    for (int i = 0; i < NUM_PARTICULAS; ++i) {
        cout << "Partícula " << i << ": x=" << particulas[i].x
             << " y=" << particulas[i].y
             << " fx=" << particulas[i].fx
             << " fy=" << particulas[i].fy << endl;
    }

    cout << "Distancia máxima: " << distancia_maxima << endl;
    cout << "Fuerza total: Fx=" << fuerza_total_x << " Fy=" << fuerza_total_y
         << " |F|=" << sqrt(fuerza_total_x * fuerza_total_x + fuerza_total_y * fuerza_total_y) << endl;

    return 0;
}
