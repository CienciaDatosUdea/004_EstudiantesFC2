#include "op_complejos.h"
#include <cmath>

op_complejos::op_complejos(double x0, double y0) : complejos(x0, y0) {}

double op_complejos::magnitud_complejo() {
    return std::sqrt(real * real + imag * imag);
}

// Suma
op_complejos op_complejos::operator+(complejos &ob) {
    return op_complejos(real + ob.get_real(), imag + ob.get_imag());
}

// Resta
op_complejos op_complejos::operator-(complejos &ob) {
    return op_complejos(real - ob.get_real(), imag - ob.get_imag()); 
}

// Multiplicación
op_complejos op_complejos::operator*(complejos &ob) {
     return op_complejos(real*ob.get_real() - imag*ob.get_imag(), real*ob.get_imag() + imag*ob.get_real());
}

// División
op_complejos op_complejos::operator/(complejos &ob) {
    double denom = ob.get_real() * ob.get_real() + ob.get_imag() * ob.get_imag();
    
    if (denom == 0) {
        throw std::runtime_error("Error: división entre cero");
    }

    double new_real = (real * ob.get_real() + imag * ob.get_imag()) / denom;
    double new_imag = (imag * ob.get_real() - real * ob.get_imag()) / denom;

    return op_complejos(new_real, new_imag);
}