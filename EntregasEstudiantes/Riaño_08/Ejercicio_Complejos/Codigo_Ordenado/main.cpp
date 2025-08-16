#include <iostream>
#include "complejos.h"

int main() {
    complejos b(3, -5);
    complejos c(0, 0);
    op_complejos a(2, 1);

    std::cout << "a = ";
    a.get_complejos();
    std::cout << "|a| = " << a.magnitud_complejo() << "\n\n";

    std::cout << "b = ";
    b.get_complejos();
    std::cout << "|b| = " << sqrt(b.get_real() * b.get_real() + b.get_imag() * b.get_imag()) << "\n\n";

    std::cout << "a + b =";
    c = a + b;
    c.get_complejos();
    std::cout << "|a + b| = " << sqrt(c.get_real() * c.get_real() + c.get_imag() * c.get_imag()) << "\n\n";

    std::cout << "a - b =";
    c = a - b;
    c.get_complejos();
    std::cout << "|a - b| = " << sqrt(c.get_real() * c.get_real() + c.get_imag() * c.get_imag()) << "\n\n";

    std::cout << "a * b =";
    c = a * b;
    c.get_complejos();
    std::cout << "|a * b| = " << sqrt(c.get_real() * c.get_real() + c.get_imag() * c.get_imag()) << "\n\n";

    std::cout << "a / b =";
    c = a / b;
    c.get_complejos();
    std::cout << "|a / b| = " << sqrt(c.get_real() * c.get_real() + c.get_imag() * c.get_imag()) << "\n\n";

    return 0;
}