#include "include/complex.h"

int main() {
    ComplexNumbers b(0, 0);

    OpComplexNumbers w(2, 5);
    OpComplexNumbers z(4, -10);

    std::cout << "z = ";
    z.get_complexNumbers();
    std::cout << "w = ";
    w.get_complexNumbers();

    std::cout << "|z| = " << z.complexNorm() << std::endl;
    std::cout << "|w| = " << w.complexNorm() << std::endl;

    b = z + w;
    std::cout << "z + w = ";
    b.get_complexNumbers();

    b = z - w;
    std::cout << "z - w = ";
    b.get_complexNumbers();

    b = z * w;
    std::cout << "z * w = ";
    b.get_complexNumbers();

    b = z / w;
    std::cout << "z / w = ";
    b.get_complexNumbers();

    return 0;
}
