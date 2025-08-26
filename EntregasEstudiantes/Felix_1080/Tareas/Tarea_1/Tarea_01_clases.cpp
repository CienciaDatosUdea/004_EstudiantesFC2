#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

const int N = 10;         // Número de partículas
const double R = 1.0;     // Radio de la circunferencia
const double DELTA = 0.1; // Rango de perturbación aleatoria

// Clase para representar una partícula
class Particula {
public:
    double x, y; // Coordenadas de la partícula

    // Constructor para inicializar la partícula con un ángulo aleatorio sobre la circunferencia
    Particula() {
        double angulo = ((double) rand() / RAND_MAX) * 2 * M_PI;
        x = R * cos(angulo);
        y = R * sin(angulo);
    }

    // Función para aplicar una perturbación aleatoria
    void perturbar() {
        x += ((double) rand() / RAND_MAX) * 2 * DELTA - DELTA;
        y += ((double) rand() / RAND_MAX) * 2 * DELTA - DELTA;
    }

    // Función para calcular la distancia con otra partícula
    double calcularDistancia(const Particula &otra) const {
        return sqrt(pow(otra.x - x, 2) + pow(otra.y - y, 2));
    }
};

// Función para calcular la distancia máxima entre las partículas
double calcularDistanciaMaxima(Particula particulas[]) {
    double maxDist = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            double dist = particulas[i].calcularDistancia(particulas[j]);
            if (dist > maxDist) {
                maxDist = dist;
            }
        }
    }
    return maxDist;
}

int main() {
    srand(time(0)); // Inicializar el generador de números aleatorios

    // Crear un arreglo de partículas
    Particula particulas[N];

    // Perturbar las partículas
    for (int i = 0; i < N; i++) {
        particulas[i].perturbar();
    }

    // Calcular y mostrar la distancia máxima
    double distanciaMaxima = calcularDistanciaMaxima(particulas);
    std::cout << "Distancia máxima entre partículas: " << distanciaMaxima << std::endl;

    return 0;
}
