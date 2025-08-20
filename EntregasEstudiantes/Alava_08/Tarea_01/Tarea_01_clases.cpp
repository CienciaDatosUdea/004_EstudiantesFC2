// Tarea_01_clases.cpp
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

// Clase que representa una partícula en 2D
class Particula {
public:
    double x, y;   // Posición
    double fx, fy; // Fuerzas

    // Constructor: inicializa posición y fuerza aleatoria
    Particula(double angulo, mt19937_64& generador,
              uniform_real_distribution<double>& perturbacion,
              uniform_real_distribution<double>& fuerza) {
        x = RADIO * cos(angulo) + perturbacion(generador);
        y = RADIO * sin(angulo) + perturbacion(generador);
        fx = fuerza(generador);
        fy = fuerza(generador);
    }

    // Calcula la distancia euclidiana entre dos partículas
    static double distancia(const Particula& a, const Particula& b) {
        return hypot(a.x - b.x, a.y - b.y);
    }
};

// Clase que representa el sistema completo de partículas
class SistemaParticulas {
    vector<Particula> particulas;

public:
    // Constructor: genera las N partículas aleatoriamente
    SistemaParticulas(mt19937_64& generador) {
        uniform_real_distribution<double> distribucion_angulo(0, 2 * M_PI);
        uniform_real_distribution<double> perturbacion(-DELTA, DELTA);
        uniform_real_distribution<double> fuerza(0.0, 1.0);

        for (int i = 0; i < NUM_PARTICULAS; ++i) {
            particulas.emplace_back(distribucion_angulo(generador), generador, perturbacion, fuerza);
        }
    }

    // Ejecuta la simulación: muestra resultados y estadísticas
    void simular() const {
        double distancia_maxima = 0;
        double fuerza_total_x = 0, fuerza_total_y = 0;

        cout << fixed << setprecision(5);

        for (int i = 0; i < NUM_PARTICULAS; ++i) {
            const auto& p = particulas[i];
            cout << "Partícula " << i << ": x=" << p.x << " y=" << p.y
                 << " fx=" << p.fx << " fy=" << p.fy << endl;

            fuerza_total_x += p.fx;
            fuerza_total_y += p.fy;

            for (int j = i + 1; j < NUM_PARTICULAS; ++j) {
                distancia_maxima = max(distancia_maxima, Particula::distancia(p, particulas[j]));
            }
        }

        cout << "Distancia máxima: " << distancia_maxima << endl;
        cout << "Fuerza total: Fx=" << fuerza_total_x << " Fy=" << fuerza_total_y
             << " |F|=" << sqrt(fuerza_total_x * fuerza_total_x + fuerza_total_y * fuerza_total_y) << endl;
    }
};

int main() {
    mt19937_64 generador(SEMILLA);
    SistemaParticulas sistema(generador);
    sistema.simular();
    return 0;
}
