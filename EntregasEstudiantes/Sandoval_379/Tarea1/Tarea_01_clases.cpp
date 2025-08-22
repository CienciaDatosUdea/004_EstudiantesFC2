#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <ctime>
#include <iomanip>

// ------------------------------------------------------------
// Simulación de partículas sobre una circunferencia (CLASES)
// - Nombres simplificados: F_total, D_max, etc.
// - Comentarios en español
// - RNG moderno (mt19937 + distribuciones)
// - init + perturb en un solo método
// - pow(..., 0.5) en lugar de sqrt
// ------------------------------------------------------------

static const int      DEF_N     = 10;
static const double   DEF_R     = 1.0;
static const double   DEF_DELTA = 0.1;
static const unsigned DEF_SEED  = 0;

// --------------------------- Clase Particle ---------------------------
// Una partícula con posición (x,y) y fuerza (fx,fy)
class Particle {
public:
    double x, y;
    double fx, fy;

    Particle() : x(0.0), y(0.0), fx(0.0), fy(0.0) {}
};

// ------------------------ Clase ParticleSystem ------------------------
// Conjunto de partículas y operaciones físicas
class ParticleSystem {
public:
    ParticleSystem(int n, double r, double delta, unsigned seed)
        : N(n), R(r), DELTA(delta) {
        unsigned s = (seed == 0) ? static_cast<unsigned>(std::time(nullptr)) : seed;
        rng.seed(s);

        dist_angle = std::uniform_real_distribution<double>(0.0, 2.0 * std::acos(-1.0));
        dist_noise = std::uniform_real_distribution<double>(-DELTA, DELTA);
        dist_force = std::uniform_real_distribution<double>(0.0, 1.0);

        particles.resize(N);
    }

    // Inicializa en circunferencia y aplica perturbación
    void init_with_noise() {
        for (auto& p : particles) {
            double th = dist_angle(rng);
            double x0 = R * std::cos(th);
            double y0 = R * std::sin(th);
            double dx = dist_noise(rng);
            double dy = dist_noise(rng);
            p.x = x0 + dx;
            p.y = y0 + dy;
            p.fx = p.fy = 0.0;
        }
    }

    // Asigna fuerzas aleatorias
    void set_random_forces() {
        for (auto& p : particles) {
            p.fx = dist_force(rng);
            p.fy = dist_force(rng);
        }
    }

    // Distancia máxima entre partículas
    double D_max() const {
        double dmax = 0.0;
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                double dx = particles[i].x - particles[j].x;
                double dy = particles[i].y - particles[j].y;
                double d2 = dx * dx + dy * dy;
                double d  = std::pow(d2, 0.5);
                if (d > dmax) dmax = d;
            }
        }
        return dmax;
    }

    // Magnitud de la fuerza total
    double F_total() const {
        double Fx = 0.0, Fy = 0.0;
        for (const auto& p : particles) {
            Fx += p.fx;
            Fy += p.fy;
        }
        double s2 = Fx * Fx + Fy * Fy;
        return std::pow(s2, 0.5);
    }

    

private:
    int N;
    double R;
    double DELTA;

    std::mt19937 rng;
    std::uniform_real_distribution<double> dist_angle;
    std::uniform_real_distribution<double> dist_noise;
    std::uniform_real_distribution<double> dist_force;

    std::vector<Particle> particles;
};

int main(int argc, char* argv[]) {
    int      N     = (argc > 1 ? std::stoi(argv[1]) : DEF_N);
    double   R     = (argc > 2 ? std::stod(argv[2]) : DEF_R);
    double   DELTA = (argc > 3 ? std::stod(argv[3]) : DEF_DELTA);
    unsigned SEED  = (argc > 4 ? static_cast<unsigned>(std::stoul(argv[4])) : DEF_SEED);

    ParticleSystem system(N, R, DELTA, SEED);

    system.init_with_noise();
    system.set_random_forces();

    double dmax = system.D_max();
    double Ftot = system.F_total();

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "N=" << N << ", R=" << R << ", DELTA=" << DELTA << "\n\n";
    
    std::cout << "\nMax distance (D_max): " << dmax << "\n";
    std::cout << "Total force (F_total): " << Ftot << "\n";

    return 0;
}
