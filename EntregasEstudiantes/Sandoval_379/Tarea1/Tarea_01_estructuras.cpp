#include <iostream>
#include <cmath>    // cos, sin, pow, acos
#include <cstdlib>  // rand, srand, RAND_MAX
#include <ctime>    // time

// ----------------------- Parámetros simples -----------------------
// N: número de partículas, R: radio, DELTA: amplitud de perturbación
const int    N     = 10;
const double R     = 1.0;
const double DELTA = 0.1;

// ----------------------- Estructura base --------------------------
// Partícula con posición (x,y) y fuerza (fx,fy)
struct Particle {
    double x, y;
    double fx, fy;
};

// ----------------------- Utilidades RNG ---------------------------
// Ángulo uniforme en [0, 2π); evita depender de M_PI
inline double randomAngle() {
    const double PI = std::acos(-1.0);
    return (static_cast<double>(std::rand()) / RAND_MAX) * (2.0 * PI);
}

// Uniforme en [a, b]
inline double uniform(double a, double b) {
    return a + (b - a) * (static_cast<double>(std::rand()) / RAND_MAX);
}

// ----------------------- Inicializa + Perturba --------------------
// Coloca cada partícula en la circunferencia y aplica perturbación (dx,dy)
void initParticles(Particle* arr, int n, double radius, double delta) {
    for (int i = 0; i < n; ++i) {
        double th = randomAngle();      // ángulo aleatorio
        double x0 = radius * std::cos(th);
        double y0 = radius * std::sin(th);

        double dx = uniform(-delta, delta);
        double dy = uniform(-delta, delta);

        arr[i].x  = x0 + dx;
        arr[i].y  = y0 + dy;
        arr[i].fx = 0.0;
        arr[i].fy = 0.0;
    }
}

// ----------------------- Fuerzas aleatorias -----------------------
// Asigna (fx,fy) en [0,1] a cada partícula
void setRandomForces(Particle* arr, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i].fx = uniform(0.0, 1.0);
        arr[i].fy = uniform(0.0, 1.0);
    }
}

// ----------------------- Distancia máxima -------------------------
// Devuelve la máxima distancia entre pares (usa pow en vez de sqrt)
double MaxDistance(const Particle* arr, int n) {
    double dmax = 0.0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dx = arr[i].x - arr[j].x;
            double dy = arr[i].y - arr[j].y;
            double d2 = dx * dx + dy * dy;
            double d  = std::pow(d2, 0.5);  // sqrt(d2)
            if (d > dmax) dmax = d;
        }
    }
    return dmax;
}

// ----------------------- Fuerza total -----------------------------
// Magnitud de la fuerza total sumando componentes
double F_Total(const Particle* arr, int n) {
    double Fx = 0.0, Fy = 0.0;
    for (int i = 0; i < n; ++i) {
        Fx += arr[i].fx;
        Fy += arr[i].fy;
    }
    double s2 = Fx * Fx + Fy * Fy;
    return std::pow(s2, 0.5);           // sqrt(Fx^2 + Fy^2)
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Particle p[N];

    // 1) Inicializar en circunferencia y perturbar
    initParticles(p, N, R, DELTA);

    // 2) Asignar fuerzas
    setRandomForces(p, N);

    

    // 3) Distancia máxima y 4) fuerza total
    double dmax   = MaxDistance(p, N);
    double ftotal = F_Total(p, N);

    std::cout << "\nMax distance: " << dmax << "\n";
    std::cout << "Total force magnitude: " << ftotal << "\n";

    return 0;
}
