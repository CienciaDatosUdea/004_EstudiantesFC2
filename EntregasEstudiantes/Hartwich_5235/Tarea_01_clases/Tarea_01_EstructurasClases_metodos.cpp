#include "Tarea_01_EstructurasClases_clases.h"

std::mt19937_64& global_rng() {
    static std::mt19937_64 rng{ /*semilla*/ }; // semilla es opcional, estará generada por el estado de la hardware si es posible
    return rng;
}

double random_number(double a, double b) {
    std::uniform_real_distribution<double> dist(a, b);
    return dist(global_rng());
}

// constructor de la clase pSystem (inicializa automáticamente las posiciones y asigna números consecutivos a las partículas)
pSystem::pSystem(const int N, const double R, const double DS, const double DF) : ps(N), radius(R), ds(DS), df(DF) {
    int n{0};
    for (auto& p : ps) {
        p.num = n++;
        double theta{random_number(0, 2*M_PI)};
        p.x = cos(theta);
        p.y = sin(theta);
    }
}

void pSystem::apply_perturbation() {
    for (auto& p : ps) {
        p.x += random_number(-ds, ds);
        p.y += random_number(-ds, ds);
    }
}

void pSystem::calculate_min_and_max_dist() {
    min_dist = std::numeric_limits<double>::infinity();
    max_dist = 0;
    double dist{0};
    for (auto& p : ps) {
        for (auto& q : ps) {
            if (p.num != q.num) {
                dist = sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2));
                max_dist = std::max(max_dist, dist);
                min_dist = std::min(min_dist, dist);
            }
        }
    }
}

void pSystem::print_min_and_max_dist() { // solo esta función estará pública, para evitar que alguién quiera imprimir las distancias sin haberlo calculado antes
    calculate_min_and_max_dist();
    std::cout << "\nThe minimum distance between any two particles is:\t" << std::fixed << std::setprecision(5) << min_dist << "\nThe maximum distance between any two particles is:\t" << std::fixed << std::setprecision(5) << max_dist << std::endl;
}

void pSystem::apply_forces() {
    for (auto& p : ps) {
        p.fx = random_number(0, df);
        p.fy = random_number(0, df);
    }
}

void pSystem::calculate_total_force() {
    double Fx{0};
    double Fy{0};
    for (auto& p : ps) {
        Fx += p.fx;
        Fy += p.fy;
    }
    total_force = sqrt(pow(Fx, 2) + pow(Fy, 2));
}

void pSystem::print_total_force() { // solo esta función estará pública, para evitar que alguién quiera imprimir las distancias sin haberlo calculado antes
    calculate_total_force();
    std::cout << "\nThe magnitude of the total force on the system is:\t" << std::fixed << std::setprecision(5) << total_force << std::endl;
}