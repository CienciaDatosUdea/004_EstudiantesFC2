#include <iostream>
#include <cmath>


double energiaCinetica(double m, double v) {
    return 0.5 * m * v * v;
}

double energiaPotencial(double m, double h, double g = 9.81) {
    return m * g * h;
}

double energiaElastica(double k, double x) {
    return 0.5 * k * x * x;
}

int main() {
    double e1 = energiaCinetica(2.0, 3.0);
    double e2 = energiaPotencial(1.0, 10.0);
    double e3 = energiaElastica(100.0, 0.1);

    std::cout << "Energía cinética: " << e1 << " J\n";
    std::cout << "Energía potencial: " << e2 << " J\n";
    std::cout << "Energía elástica: " << e3 << " J\n";

    std::cout << "Total: " << (e1 + e2 + e3) << " J\n";
    return 0;
}
