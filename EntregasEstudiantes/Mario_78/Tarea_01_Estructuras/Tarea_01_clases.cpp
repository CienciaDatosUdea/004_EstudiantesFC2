#include <iostream>  // Librería para entrada y salida de datos (cout, cin, etc.)
#include <cmath>     // Librería matemática (cos, sin, sqrt, etc.)
#include <cstdlib>   // Librería estándar (rand, srand, etc.)
#include <ctime>     // Librería para manejar el tiempo (time)

// Constantes globales
const int N = 10;          // Número de partículas
const double R = 1.0;      // Radio inicial de la circunferenciadonde se colocan las partículas 
const double DELTA = 0.1;  // Rango de perturbación
const double PI = 3.14159265358979323846;  


// Clase que representa una partícula en 2D
class Particula {
    double x, y;   // Posición en el plano
    double fx, fy; // Componentes de la fuerza

public:
    // Constructor: inicializa la partícula en (0,0) con fuerza (0,0)
    Particula() : x(0), y(0), fx(0), fy(0) {}

    // Coloca la partícula en un punto aleatorio sobre una circunferencia de radio R
    void init() {
        double theta = ((double) rand() / RAND_MAX) * 2 *PI; 
        x = R * cos(theta); // Coordenada X
        y = R * sin(theta); // Coordenada Y
    }

    // Desplaza ligeramente la partícula en una dirección aleatoria
    void perturb_position() {
        double dx = ((double) rand() / RAND_MAX) * 2 * DELTA - DELTA;
        double dy = ((double) rand() / RAND_MAX) * 2 * DELTA - DELTA;
        x += dx; // Actualiza X
        y += dy; // Actualiza Y
    }

    // Calcula la distancia  entre esta partícula y otra
    double distancia(const Particula &p) const {
        double dx = x - p.x;
        double dy = y - p.y;
        return sqrt(dx * dx + dy * dy);
    }

    // Asigna una fuerza aleatoria en cada dirección (entre 0 y 1)
    void  assign_forces() {
        fx = (double) rand() / RAND_MAX;
        fy = (double) rand() / RAND_MAX;
    }

    // Métodos de acceso a la fuerza
    double get_fx() const { return fx; }
    double get_fy() const { return fy; }
};

// ---------- FUNCIONES AUXILIARES ----------

// Inicializa y perturba las partículas
void init_position(Particula p[]) {
    for (int i = 0; i < N; i++) {
        p[i].init();
        p[i].perturb_position();
    }
}

// Calcula la distancia máxima entre partículas
double calcular_distancia_maxima(Particula p[]) {
    double max_d = 0;
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            max_d = std::max(max_d, p[i].distancia(p[j]));
    return max_d;
}

// Calcula la fuerza total del sistema
double calcular_fuerza_total(Particula p[]) {
    double fx_total = 0, fy_total = 0;
    for (int i = 0; i < N; i++) {
        p[i].assign_forces();
        fx_total += p[i].get_fx();
        fy_total += p[i].get_fy();
    }
    return sqrt(fx_total * fx_total + fy_total * fy_total);
}

int main() {
    system("clear");      // Limpia consola (Linux/macOS)
    srand(time(NULL));    // Semilla aleatoria

    Particula p[N];       // Se crea el arreglo de partículas

    init_position(p);     // Inicializa y perturba las partículas

    double max_d = calcular_distancia_maxima(p);
    double F_total = calcular_fuerza_total(p);

    std::cout << "Distancia máxima: " << max_d << "\n";
    std::cout << "Fuerza total: " << F_total << "\n";

    return 0;
}