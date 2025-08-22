#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>

const int COUNT = 10;       // cantidad de partículas
const double R0 = 1.0;      // radio inicial
const double SHIFT = 0.1;   // perturbación máxima

// Definición de partícula
struct Particle {
    double x, y;  // posición
    double fx, fy; // fuerza
};

// Genera posiciones iniciales aleatorias en el círculo
void randomPositions(Particle arr[]) {
    for (int i = 0; i < COUNT; i++) {
        double angle = (double(rand()) / RAND_MAX) * 2.0 * M_PI;
        arr[i].x = R0 * cos(angle);
        arr[i].y = R0 * sin(angle);
    }
}

// Perturba todas las posiciones
void perturbAll(Particle arr[]) {
    for (int i = 0; i < COUNT; i++) {
        arr[i].x += (double(rand()) / RAND_MAX) * 2.0 * SHIFT - SHIFT;
        arr[i].y += (double(rand()) / RAND_MAX) * 2.0 * SHIFT - SHIFT;
    }
}

// Encuentra y muestra la distancia máxima
void findMaxDist(Particle arr[]) {
    double dmax = 0.0;
    int a = -1, b = -1;
    for (int i = 0; i < COUNT; i++) {
        for (int j = i + 1; j < COUNT; j++) {
            double dx = arr[i].x - arr[j].x;
            double dy = arr[i].y - arr[j].y;
            double d = sqrt(dx * dx + dy * dy);
            if (d > dmax) {
                dmax = d;
                a = i;
                b = j;
            }
        }
    }
    std::cout << "Distancia máxima = " << dmax 
              << " entre partículas " << a << " y " << b << "\n";
}

// Inicializa fuerzas aleatorias
void randomForces(Particle arr[]) {
    for (int i = 0; i < COUNT; i++) {
        arr[i].fx = (double(rand()) / RAND_MAX);
        arr[i].fy = (double(rand()) / RAND_MAX);
    }
}

// Calcula la fuerza neta
void totalForce(Particle arr[]) {
    double sumX = 0.0, sumY = 0.0;
    for (int i = 0; i < COUNT; i++) {
        sumX += arr[i].fx;
        sumY += arr[i].fy;
    }
    double magnitude = sqrt(sumX * sumX + sumY * sumY);
    std::cout << "Magnitud de la fuerza neta = " << magnitude << "\n";
}

int main() {
    srand(time(NULL)); // Inicializar la semilla del generador de números aleatorios
    std::cout << std::fixed << std::setprecision(6);

    Particle particles[COUNT];

    // 1. Generar posiciones iniciales
    randomPositions(particles);
    std::cout << "==================== POSICIONES INICIALES ====================\n";
    std::cout << "ID\tX\t\tY\n";
    for (int i = 0; i < COUNT; i++) {
        std::cout << i << "\t" << particles[i].x << "\t" << particles[i].y << "\n";
    }

    // 2. Calcular posiciones perturbadas
    perturbAll(particles);
    std::cout << "\n==================== POSICIONES PERTURBADAS ==================\n";
    std::cout << "ID\tX\t\tY\n";
    for (int i = 0; i < COUNT; i++) {
        std::cout << i << "\t" << particles[i].x << "\t" << particles[i].y << "\n";
    }

    // 3. Distancia máxima entre partículas
    std::cout << "\n==================== DISTANCIA MÁXIMA ========================\n";
    findMaxDist(particles);

    // 4. Asignar fuerzas aleatorias
    randomForces(particles);
    std::cout << "\n==================== FUERZAS ASIGNADAS =======================\n";
    std::cout << "ID\tFx\t\tFy\n";
    for (int i = 0; i < COUNT; i++) {
        std::cout << i << "\t" << particles[i].fx << "\t" << particles[i].fy << "\n";
    }

    // 5. Calcular fuerza neta
    std::cout << "\n==================== FUERZA NETA DEL SISTEMA =================\n";
    totalForce(particles);

    return 0;
}
