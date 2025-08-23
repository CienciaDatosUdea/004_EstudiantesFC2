#include "complejos.h"
#include <iostream>
#include <cmath>

// Implementación de la clase complejos
complejos::complejos(double x0, double y0) : real(x0), imag(y0) {}

void complejos::get_complejos() {
    std::cout << real << " + " << imag << "i" << " \n";
}

double complejos::get_real() {
    return real;
}

double complejos::get_imag() {
    return imag;
}

// Implementación de la clase op_complejos
op_complejos::op_complejos(double x0, double y0) : complejos(x0, y0) {}

double op_complejos::magnitud_complejo() {
    return sqrt(real * real + imag * imag);
}

complejos op_complejos::operator+(complejos& ob) {
    return complejos(real + ob.get_real(), imag + ob.get_imag());
}

complejos op_complejos::operator-(complejos& ob) {
    return complejos(real - ob.get_real(), imag - ob.get_imag());
}

complejos op_complejos::operator*(complejos& ob) {
    return complejos(real * ob.get_real() - imag * ob.get_imag(), real * ob.get_imag() + imag * ob.get_real());
}

complejos op_complejos::operator/(complejos& ob) {
    double denominador = ob.get_real() * ob.get_real() + ob.get_imag() * ob.get_imag();
    return complejos((real * ob.get_real() + imag * ob.get_imag()) / denominador, (imag * ob.get_real() - real * ob.get_imag()) / denominador);
}
