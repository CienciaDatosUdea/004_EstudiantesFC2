#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>

const int TOTAL = 10;      // número de partículas
const double RADIUS = 1.0; // radio inicial
const double STEP = 0.1;   // perturbación máxima

// Clase que representa una partícula en 2D
class Particle {
public:
    double posX, posY; // coordenadas
    double forceX, forceY; // componentes de la fuerza

    // Constructor por defecto
    Particle() : posX(0.0), posY(0.0), forceX(0.0), forceY(0.0) {}

    // Inicializa una posición aleatoria en el círculo de radio R
    void setRandomPosition(double R) {
        double angle = (double(rand()) / RAND_MAX) * 2.0 * M_PI;
        posX = R * cos(angle);
        posY = R * sin(angle);
    }

    // Aplica una perturbación aleatoria en x e y
    void moveRandom(double delta) {
        double dx = (double(rand()) / RAND_MAX) * 2.0 * delta - delta;
        double dy = (double(rand()) / RAND_MAX) * 2.0 * delta - delta;
        posX += dx;
        posY += dy;
    }

    // Asigna valores aleatorios a las componentes de fuerza
    void assignRandomForce() {
        forceX = (double(rand()) / RAND_MAX);
        forceY = (double(rand()) / RAND_MAX);
    }
};

// Clase que representa el conjunto de partículas
class Simulation {
private:
    std::vector<Particle> particles;

public:
    Simulation(int N) : particles(N) {}

    // Inicializa todas las posiciones aleatorias
    void initPositions(double R) {
        for (auto &p : particles) {
            p.setRandomPosition(R);
        }
    }

    // Perturba todas las posiciones
    void perturb(double delta) {
        for (auto &p : particles) {
            p.moveRandom(delta);
        }
    }

    // Calcula y muestra la distancia máxima entre dos partículas
    void maxDistance() {
        double dmax = 0.0;
        int idx1 = -1, idx2 = -1;
        for (int i = 0; i < TOTAL; i++) {
            for (int j = i + 1; j < TOTAL; j++) {
                double dx = particles[i].posX - particles[j].posX;
                double dy = particles[i].posY - particles[j].posY;
                double dist = sqrt(dx * dx + dy * dy);
                if (dist > dmax) {
                    dmax = dist;
                    idx1 = i;
                    idx2 = j;
                }
            }
        }
        std::cout << "Distancia máxima = " << dmax << " entre las particulas " << idx1 << " y " << idx2 << "\n";
    }

    // Inicializa las fuerzas aleatorias de todas las partículas
    void initForces() {
        for (auto &p : particles) {
            p.assignRandomForce();
        }
    }

    // Calcula y muestra la fuerza neta
    void netForce() {
        double sumX = 0.0, sumY = 0.0;
        for (auto &p : particles) {
            sumX += p.forceX;
            sumY += p.forceY;
        }
        double mag = sqrt(sumX * sumX + sumY * sumY);
        std::cout << "Magnitud fuerza neta = " << mag << "\n";
    }

    // Acceso a las partículas
    Particle &operator[](int i) {
        return particles[i];
    }
};

int main() {
    srand(time(NULL)); // Inicializar la semilla del generador de números aleatorios
    std::cout << std::fixed << std::setprecision(6);

    Simulation sim(TOTAL);

    // 1. Generar posiciones iniciales
    sim.initPositions(RADIUS);
    std::cout << "==================== POSICIONES INICIALES ====================\n";
    std::cout << "ID\tX\t\tY\n";
    for (int i = 0; i < TOTAL; i++) {
        std::cout << i << "\t" << sim[i].posX << "\t" << sim[i].posY << "\n";
    }

    // 2. Calcular posiciones perturbadas
    sim.perturb(STEP);
    std::cout << "\n==================== POSICIONES PERTURBADAS ==================\n";
    std::cout << "ID\tX\t\tY\n";
    for (int i = 0; i < TOTAL; i++) {
        std::cout << i << "\t" << sim[i].posX << "\t" << sim[i].posY << "\n";
    }

    // 3. Distancia máxima entre partículas
    std::cout << "\n==================== DISTANCIA MÁXIMA ========================\n";
    sim.maxDistance();

    // 4. Asignar fuerzas aleatorias
    sim.initForces();
    std::cout << "\n==================== FUERZAS ASIGNADAS =======================\n";
    std::cout << "ID\tFx\t\tFy\n";
    for (int i = 0; i < TOTAL; i++) {
        std::cout << i << "\t" << sim[i].forceX << "\t" << sim[i].forceY << "\n";
    }

    // 5. Calcular fuerza neta
    std::cout << "\n==================== FUERZA NETA DEL SISTEMA =================\n";
    sim.netForce();

    return 0;
}