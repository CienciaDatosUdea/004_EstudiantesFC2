#include "include/classes.h"
#include <iomanip>

int main() {
    std::cout << std::setprecision(6) << std::fixed;

    Sistema s(N);

    // Posiciones iniciales
    s.initAll(R);
    std::cout << "1. Posiciones iniciales\n"
              << "---------------------------\n"
              << "i\tx\t\ty\n";
    for (int i = 0; i < N; i++) {
        std::cout << i << "\t" << s[i].x << "\t" << s[i].y << std::endl;
    }

    // 2. Posiciones perturbadas
    std::cout << "---------------------------\n"
              << "2. Posiciones perturbadas\n";
    s.pertAll(DELTA);
    std::cout << "---------------------------\n"
              << "i\tx\t\ty\n";
    for (int i = 0; i < N; i++) {
        std::cout << i << "\t" << s[i].x << "\t" << s[i].y << std::endl;
    }

    // 3. Distancia máxima
    std::cout << "---------------------------\n"
              << "3. Distancia máxima\n";
    s.distMax();

    // 4. Fuerzas
    std::cout << "---------------------------\n"
              << "4. Fuerzas\n";
    s.initForces();
    std::cout << "---------------------------\n"
              << "i\tFx\t\tFy\n";
    for (int i = 0; i < N; i++) {
        std::cout << i << "\t" << s[i].Fx << "\t" << s[i].Fy << std::endl;
    }

    // 5. Magnitud de la fuerza neta
    std::cout << "---------------------------\n"
              << "5. Magnitud de la fuerza neta\n";
    s.netForce();

    return 0;
}
