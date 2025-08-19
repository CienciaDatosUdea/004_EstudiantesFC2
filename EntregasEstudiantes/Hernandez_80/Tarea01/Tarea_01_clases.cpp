#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <vector>

const int N = 10;         // Número de partículas
const double DELTA = 0.05; // Perturbación máxima

// Generador global de números aleatorios
std::mt19937_64& global_rng() {
    static std::mt19937_64 rng{ static_cast<unsigned long long>(std::time(nullptr)) };
    return rng;
}

double random_number(double a, double b) {
    std::uniform_real_distribution<double> dist(a, b);
    return dist(global_rng());
}

class Particula {
private:
    double x, y;   // posición
    double fx, fy; // fuerza
public:
    Particula(): x(0), y(0), fx(0), fy(0) {}

    void init_configuracion() {
        double theta = random_number(0, 2 * M_PI);
        x = std::cos(theta);
        y = std::sin(theta);
    }

    void perturbacion(double delta) {
        double dx = random_number(-delta, delta);
        double dy = random_number(-delta, delta);
        x += dx;
        y += dy;
    }

    void asignar_fuerza() {
        fx = random_number(0, 1);
        fy = random_number(0, 1);
    }

    double get_x() const { return x; }
    double get_y() const { return y; }
    double get_fx() const { return fx; }
    double get_fy() const { return fy; }
};

class Sistema {
private:
    std::vector<Particula> p;
public:
    Sistema(int N): p(N) {}

    void init_all_particles() {
        for (auto &v : p) v.init_configuracion();
    }

    void aplicar_perturbacion(double delta) {
        for (auto &v : p) v.perturbacion(delta);
    }

    double distancia_minima() const {
        double R = 1e10;
        int n = p.size();
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                double dx = p[i].get_x() - p[j].get_x();
                double dy = p[i].get_y() - p[j].get_y();
                double dij = std::sqrt(dx*dx + dy*dy);
                if (dij < R) R = dij;
            }
        }
        return R;
    }

    double distancia_maxima() const {
        double R = 0.0;
        int n = p.size();
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                double dx = p[i].get_x() - p[j].get_x();
                double dy = p[i].get_y() - p[j].get_y();
                double dij = std::sqrt(dx*dx + dy*dy);
                if (dij > R) R = dij;
            }
        }
        return R;
    }

    void asignar_fuerzas() {
        for (auto &v : p) v.asignar_fuerza();
    }

    double fuerza_total() const {
        double Fx_total = 0.0, Fy_total = 0.0;
        for (auto &v : p) {
            Fx_total += v.get_fx();
            Fy_total += v.get_fy();
        }
        return std::sqrt(Fx_total*Fx_total + Fy_total*Fy_total);
    }
};

int main() {
    Sistema s(N);

    s.init_all_particles();
    s.aplicar_perturbacion(DELTA);

    double dmin = s.distancia_minima();
    double dmax = s.distancia_maxima();

    s.asignar_fuerzas();
    double F_total = s.fuerza_total();

    std::cout << "Distancia mínima: " << dmin << "\n";
    std::cout << "Distancia máxima: " << dmax << "\n";
    std::cout << "Fuerza total: " << F_total << "\n";

    return 0;
}
