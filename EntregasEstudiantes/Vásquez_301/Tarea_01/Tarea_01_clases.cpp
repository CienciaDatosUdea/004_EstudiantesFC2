#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <iomanip>

// --- Constantes Globales ---
const int N = 10;
const double R = 1.0;
const double DELTA = 0.1;

class Particula {
public:
    double x, y;
    double fx, fy;
};

class Simulacion {
private:
    std::vector<Particula> particulas;
    std::mt19937 generador; // Generador de números aleatorios

    // Método privado para generar números aleatorios
    double generarAleatorio(double min, double max) {
        std::uniform_real_distribution<double> distribucion(min, max);
        return distribucion(generador);
    }

public:
    // Constructor: inicializa el generador y las partículas
    Simulacion() : generador(static_cast<unsigned int>(time(0))) {
        inicializar();
    }

    // 1. Inicializa las partículas en la circunferencia.
    void inicializar() {
        particulas.clear();
        for (int i = 0; i < N; ++i) {
            double theta = generarAleatorio(0, 2 * M_PI);
            Particula p;
            p.x = R * cos(theta);
            p.y = R * sin(theta);
            p.fx = 0.0;
            p.fy = 0.0;
            particulas.push_back(p);
        }
    }

    // 2. Aplica la perturbación aleatoria.
    void perturbar() {
        for (auto& p : particulas) {
            p.x += generarAleatorio(-DELTA, DELTA);
            p.y += generarAleatorio(-DELTA, DELTA);
        }
    }

    // 3. Calcula y devuelve la distancia máxima.
    double calcularDistanciaMaxima() const {
        double max_dist_sq = 0.0;
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
        return sqrt(max_dist_sq);
    }

    // 4. Asigna fuerzas aleatorias.
    void asignarFuerzas() {
        for (auto& p : particulas) {
            p.fx = generarAleatorio(0, 1);
            p.fy = generarAleatorio(0, 1);
        }
    }

    // 5. Calcula y devuelve la magnitud de la fuerza total.
    double calcularFuerzaTotal() const {
        double fuerza_total_x = 0.0;
        double fuerza_total_y = 0.0;
        for (const auto& p : particulas) {
            fuerza_total_x += p.fx;
            fuerza_total_y += p.fy;
        }
        return sqrt(fuerza_total_x * fuerza_total_x + fuerza_total_y * fuerza_total_y);
    }
};

int main() {
    std::cout << "--- SIMULACION CON CLASES ---" << std::endl;

    // Se crea un objeto Simulacion, que se inicializa automáticamente.
    Simulacion miSimulacion;
    std::cout << "1. Se generaron " << N << " particulas en una circunferencia de radio " << R << std::endl;

    // Se llaman a los métodos del objeto para ejecutar la simulación.
    miSimulacion.perturbar();
    std::cout << "2. Se aplico una perturbacion aleatoria en el rango [-" << DELTA << ", " << DELTA << "]" << std::endl;

    double dist_max = miSimulacion.calcularDistanciaMaxima();
    std::cout << "3. La distancia maxima entre particulas es: " << std::fixed << std::setprecision(4) << dist_max << std::endl;

    miSimulacion.asignarFuerzas();
    std::cout << "4. Se asignaron fuerzas aleatorias a cada particula." << std::endl;

    double fuerza_total_mag = miSimulacion.calcularFuerzaTotal();
    std::cout << "5. La magnitud de la fuerza total del sistema es: " << fuerza_total_mag << std::endl;

    return 0;
}