#include "complejos.h"
#include <iostream>
#include <cmath>

// Implementación de la clase NumComplejo
NumComplejo::NumComplejo(double x0, double y0) : real(x0), imag(y0) {}

void NumComplejo::imprimir() const {
    std::cout << real << " + " << imag << "i" << std::endl;
}

double NumComplejo::realParte() const {
    return real;
}

double NumComplejo::imagParte() const {
    return imag;
}

// Implementación de la clase OperadorComplejo
OperadorComplejo::OperadorComplejo(double x0, double y0) : NumComplejo(x0, y0) {}

double OperadorComplejo::modulo() const {
    return std::sqrt(real * real + imag * imag);
}

// Sobrecarga de operadores
NumComplejo OperadorComplejo::operator+(NumComplejo& ob) {
    return NumComplejo(real + ob.realParte(), imag + ob.imagParte());
}

NumComplejo OperadorComplejo::operator-(NumComplejo& ob) {
    return NumComplejo(real - ob.realParte(), imag - ob.imagParte());
}

NumComplejo OperadorComplejo::operator*(NumComplejo& ob) {
    return NumComplejo(real * ob.realParte() - imag * ob.imagParte(),
                       real * ob.imagParte() + imag * ob.realParte());
}

NumComplejo OperadorComplejo::operator/(NumComplejo& ob) {
    double denominador = ob.realParte() * ob.realParte() + ob.imagParte() * ob.imagParte();
    return NumComplejo((real * ob.realParte() + imag * ob.imagParte()) / denominador,
                       (imag * ob.realParte() - real * ob.imagParte()) / denominador);
}
