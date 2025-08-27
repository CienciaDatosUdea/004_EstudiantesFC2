
#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <ctime>

// Generador de números aleatorios global
std::mt19937 global_rng(std::time(nullptr));

// Función para generar números aleatorios en un rango [a, b]
double random_number(double a, double b) {
    std::uniform_real_distribution<double> dist(a, b);
    return dist(global_rng);
}

class Particula {
private:
    double x;
    double y;
    double fx;  // Fuerza en x
    double fy;  // Fuerza en y

public:
    // Constructor por defecto
    Particula() : x(0), y(0), fx(0), fy(0) {};
    
    // Constructor con parámetros
    Particula(double x0, double y0, double fx0, double fy0) 
        : x(x0), y(y0), fx(fx0), fy(fy0) {};
    
    // Métodos para acceder a las coordenadas
    double getX() const { return x; }
    double getY() const { return y; }
    double getFx() const { return fx; }
    double getFy() const { return fy; }
    
    // Métodos para modificar las coordenadas
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
    void setFx(double newFx) { fx = newFx; }
    void setFy(double newFy) { fy = newFy; }
    
    // Método para calcular la distancia a otra partícula
    double distancia(const Particula& otra) const {
        double dx = x - otra.x;
        double dy = y - otra.y;
        return std::sqrt(dx*dx + dy*dy);
    }
    
    // Método para aplicar una perturbación aleatoria
    void perturbar(double delta) {
        x += random_number(-delta, delta);
        y += random_number(-delta, delta);
    }
};

class Sistema {
private:
    std::vector<Particula> particulas;
    double radio;
    double delta;

public:
    // Constructor
    Sistema(int N = 10, double R = 1.0, double DELTA = 0.1) 
        : radio(R), delta(DELTA) {
        inicializarParticulas(N);
    }
    
    // Inicializar partículas en posiciones aleatorias dentro de la circunferencia
    void inicializarParticulas(int N) {
        particulas.clear();
        for (int i = 0; i < N; i++) {
            double theta = random_number(0, 2 * M_PI);
            double x = radio * std::cos(theta);
            double y = radio * std::sin(theta);
            
            // Fuerzas aleatorias entre 0 y 1
            double fx = random_number(0, 1);
            double fy = random_number(0, 1);
            
            particulas.emplace_back(x, y, fx, fy);
        }
    }
    
    // Calcular la distancia mínima entre partículas
    double distanciaMinima() const {
        if (particulas.size() < 2) return 0.0;
        
        double minDist = std::numeric_limits<double>::max();
        for (size_t i = 0; i < particulas.size(); i++) {
            for (size_t j = i + 1; j < particulas.size(); j++) {
                double dist = particulas[i].distancia(particulas[j]);
                if (dist < minDist) {
                    minDist = dist;
                }
            }
        }
        return minDist;
    }
    
    // Calcular la fuerza resultante del sistema
    std::pair<double, double> fuerzaResultante() const {
        double fx_total = 0.0;
        double fy_total = 0.0;
        
        for (const auto& p : particulas) {
            fx_total += p.getFx();
            fy_total += p.getFy();
        }
        
        return {fx_total, fy_total};
    }
    
    // Calcular la magnitud de la fuerza resultante
    double magnitudFuerzaResultante() const {
        auto [fx, fy] = fuerzaResultante();
        return std::sqrt(fx*fx + fy*fy);
    }
    
    // Aplicar perturbaciones a todas las partículas
    void perturbarSistema() {
        for (auto& p : particulas) {
            p.perturbar(delta);
        }
    }
    
    // Mostrar información del sistema
    void mostrarEstado() const {
        std::cout << "Sistema con " << particulas.size() << " partículas:\n";
        for (size_t i = 0; i < particulas.size(); i++) {
            std::cout << "Partícula " << i << ": (" 
                      << particulas[i].getX() << ", " 
                      << particulas[i].getY() << ")\n";
        }
        std::cout << "Distancia mínima: " << distanciaMinima() << "\n";
        std::cout << "Magnitud fuerza resultante: " << magnitudFuerzaResultante() << "\n\n";
    }
};

int main(int argc, char* argv[]) {
    // Parámetros por defecto
    int N = 10;
    double R = 1.0;
    double DELTA = 0.1;
    
    // Leer parámetros de la línea de comandos si están disponibles
    if (argc >= 2) N = std::atoi(argv[1]);
    if (argc >= 3) R = std::atof(argv[2]);
    if (argc >= 4) DELTA = std::atof(argv[3]);
    
    std::cout << "Parámetros: N=" << N << ", R=" << R << ", DELTA=" << DELTA << "\n\n";
    
    // Crear y simular el sistema
    Sistema sistema(N, R, DELTA);
    
    // Mostrar estado inicial
    std::cout << "Estado inicial:\n";
    sistema.mostrarEstado();
    
    // Aplicar algunas perturbaciones y mostrar resultados
    for (int paso = 1; paso <= 5; paso++) {
        sistema.perturbarSistema();
        std::cout << "Después de la perturbación " << paso << ":\n";
        sistema.mostrarEstado();
    }
    
    return 0;
}



