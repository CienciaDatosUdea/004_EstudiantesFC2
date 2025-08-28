#include "../include/complex.h"

// ComplexNumbers methods
ComplexNumbers::ComplexNumbers(double x0, double y0) : real(x0), imag(y0) {}

void ComplexNumbers::get_complexNumbers() const {
    std::cout << real << " + " << imag << "i\n";
}

double ComplexNumbers::get_real() const { return real; }
double ComplexNumbers::get_imag() const { return imag; }

// OpComplexNumbers methods
OpComplexNumbers::OpComplexNumbers(double x0, double y0) : ComplexNumbers(x0, y0) {}

double OpComplexNumbers::complexNorm() const {
    return std::sqrt(real * real + imag * imag);
}

ComplexNumbers OpComplexNumbers::operator+(const ComplexNumbers &ob) {
    return ComplexNumbers(real + ob.get_real(), imag + ob.get_imag());
}

ComplexNumbers OpComplexNumbers::operator-(const ComplexNumbers &ob) {
    return ComplexNumbers(real - ob.get_real(), imag - ob.get_imag());
}

ComplexNumbers OpComplexNumbers::operator*(const ComplexNumbers &ob) {
    return ComplexNumbers(real * ob.get_real() - imag * ob.get_imag(),
                          real * ob.get_imag() + imag * ob.get_real());
}

ComplexNumbers OpComplexNumbers::operator/(const OpComplexNumbers &ob) {
    double denom = std::pow(ob.complexNorm(), 2);
    return ComplexNumbers((real * ob.get_real() + imag * ob.get_imag()) / denom,
                          (-real * ob.get_imag() + imag * ob.get_real()) / denom);
}
