#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <random>
#include <cstdlib>
#include <ctime>
#define _USE_MATH_DEFINES

// usando un struct como tipo POD
struct particle {
    // públicos por default
    int num{};
    double x{};
    double y{};
    double fx{0};
    double fy{0};
};

// usando una clase para definir el conjunto de partículas y los métodos necesitados
class pSystem {
    private:
        std::vector<particle> ps;
        double radius{};
        double ds{};
        double df{};
        double max_dist{};
        double min_dist{};
        double total_force{};
        void calculate_min_and_max_dist();
        void calculate_total_force();
    public:
        pSystem(const int, const double, const double, const double);
        void apply_perturbation();
        void apply_forces();
        void print_min_and_max_dist();
        void print_total_force();
};