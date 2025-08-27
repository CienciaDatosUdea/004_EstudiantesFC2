#include <iostream>
#include <cmath>
#include "complejos.h"

int main() {
    NumComplejo b(3, -5);
    NumComplejo c(0, 0);
    OperadorComplejo a(2, 1);

    std::cout << "a = ";
    a.imprimir();
    std::cout << "|a| = " << a.modulo() << "\n\n";

    std::cout << "b = ";
    b.imprimir();
    std::cout << "|b| = " 
              << std::sqrt(b.realParte() * b.realParte() + b.imagParte() * b.imagParte()) 
              << "\n\n";

    std::cout << "a + b = ";
    c = a + b;
    c.imprimir();
    std::cout << "|a + b| = " 
              << std::sqrt(c.realParte() * c.realParte() + c.imagParte() * c.imagParte()) 
              << "\n\n";

    std::cout << "a - b = ";
    c = a - b;
    c.imprimir();
    std::cout << "|a - b| = " 
              << std::sqrt(c.realParte() * c.realParte() + c.imagParte() * c.imagParte()) 
              << "\n\n";

    std::cout << "a * b = ";
    c = a * b;
    c.imprimir();
    std::cout << "|a * b| = " 
              << std::sqrt(c.realParte() * c.realParte() + c.imagParte() * c.imagParte()) 
              << "\n\n";

    std::cout << "a / b = ";
    c = a / b;
    c.imprimir();
    std::cout << "|a / b| = " 
              << std::sqrt(c.realParte() * c.realParte() + c.imagParte() * c.imagParte()) 
              << "\n\n";

    return 0;
}
