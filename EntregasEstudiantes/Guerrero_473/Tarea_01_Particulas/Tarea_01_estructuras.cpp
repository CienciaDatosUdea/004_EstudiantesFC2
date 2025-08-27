#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <vector>
#include <limits>




// g++ -std=c++17 -Wall programa.cpp -o programa.out

/*
Simulación de partículas en una circunferencia 2D
- N partículas distribuidas aleatoriamente en una circunferencia de radio R
- Cada partícula tiene una perturbación aleatoria dx, dy
- Se calcula la distancia mínima entre partículas
- Cada partícula tiene un vector de fuerza fx, fy con valores aleatorios
- Se calcula la magnitud de la fuerza resultante del sistema
*/

// Parámetros por defecto
const int N = 10;
const double R = 1.0;
const double DELTA = 0.1;

// Estructura para representar una partícula
struct Particula {
    double x;
    double y;
    double fx;  // Fuerza en dirección x
    double fy;  // Fuerza en dirección y
};

// Generador de números aleatorios
std::mt19937 rng(std::time(nullptr));

// Función para generar número aleatorio en [a, b]
double random_number(double a, double b) {
    std::uniform_real_distribution<double> dist(a, b);
    return dist(rng);
}

// Inicializar posiciones de las partículas en la circunferencia
void init_position(std::vector<Particula>& particulas, double radio) {
    for (auto& p : particulas) {
        double theta = random_number(0, 2 * M_PI);
        p.x = radio * std::cos(theta);
        p.y = radio * std::sin(theta);
        
        // Inicializar fuerzas aleatorias entre 0 y 1
        p.fx = random_number(0, 1);
        p.fy = random_number(0, 1);
    }
}

// Aplicar perturbación aleatoria a las partículas
void perturbarParticulas(std::vector<Particula>& particulas, double delta) {
    for (auto& p : particulas) {
        p.x += random_number(-delta, delta);
        p.y += random_number(-delta, delta);
    }
}

// Calcular distancia mínima entre partículas
double distanciaMinima(const std::vector<Particula>& particulas) {
    if (particulas.size() < 2) return 0.0;
    
    double minDist = std::numeric_limits<double>::max();
    for (size_t i = 0; i < particulas.size(); i++) {
        for (size_t j = i + 1; j < particulas.size(); j++) {
            double dx = particulas[i].x - particulas[j].x;
            double dy = particulas[i].y - particulas[j].y;
            double dist = std::sqrt(dx*dx + dy*dy);
            
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }
    return minDist;
}

// Calcular fuerza resultante del sistema
std::pair<double, double> fuerzaResultante(const std::vector<Particula>& particulas) {
    double fx_total = 0.0;
    double fy_total = 0.0;
    
    for (const auto& p : particulas) {
        fx_total += p.fx;
        fy_total += p.fy;
    }
    
    return {fx_total, fy_total};
}

// Calcular magnitud de la fuerza resultante
double magnitudFuerzaResultante(const std::vector<Particula>& particulas) {
    auto [fx, fy] = fuerzaResultante(particulas);
    return std::sqrt(fx*fx + fy*fy);
}

// Mostrar estado del sistema
void mostrarEstado(const std::vector<Particula>& particulas) {
    std::cout << "Estado del sistema:\n";
    for (size_t i = 0; i < particulas.size(); i++) {
        std::cout << "Partícula " << i << ": (" 
                  << particulas[i].x << ", " 
                  << particulas[i].y << ") Fuerza: ("
                  << particulas[i].fx << ", " 
                  << particulas[i].fy << ")\n";
    }
    std::cout << "Distancia mínima: " << distanciaMinima(particulas) << "\n";
    std::cout << "Magnitud fuerza resultante: " << magnitudFuerzaResultante(particulas) << "\n\n";
}

int main(int argc, char* argv[]) {
    // Leer parámetros de línea de comandos o usar valores por defecto
    int n_particulas = N;
    double radio = R;
    double delta = DELTA;
    
    if (argc >= 2) n_particulas = std::atoi(argv[1]);
    if (argc >= 3) radio = std::atof(argv[2]);
    if (argc >= 4) delta = std::atof(argv[3]);
    
    std::cout << "Simulación de " << n_particulas 
              << " partículas en circunferencia de radio " << radio 
              << " con delta " << delta << "\n\n";
    
    // Crear vector de partículas
    std::vector<Particula> particulas(n_particulas);
    
    // Inicializar posiciones
    init_position(particulas, radio);
    
    // Mostrar estado inicial
    std::cout << "Estado inicial:\n";
    mostrarEstado(particulas);
    
    // Aplicar perturbaciones y mostrar resultados
    for (int paso = 1; paso <= 5; paso++) {
        perturbarParticulas(particulas, delta);
        std::cout << "Después de la perturbación " << paso << ":\n";
        mostrarEstado(particulas);
    }
    
    return 0;
}

