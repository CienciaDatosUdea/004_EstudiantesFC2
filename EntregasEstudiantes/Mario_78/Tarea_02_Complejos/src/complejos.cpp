#include "complejos.h"
#include <iostream>

complejos::complejos(double x0, double y0) : real(x0), imag(y0) {}

void complejos::get_complejos() {
    std::cout << real << " + " << imag << "i\n";
}

double complejos::get_real() {
    return real;
}

double complejos::get_imag() {
    return imag;
}

