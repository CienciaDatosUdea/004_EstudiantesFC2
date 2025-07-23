#include<stdio.h>
#include "../include/op_complejos.h"
#include <iostream>

complejos::complejos(double x0, double y0) : real(x0), imaginario(y0) {}

void complejos::get_complejos() {
    std::cout << real << " + " << imaginario << "i\n";
}   

double complejos::get_real() {
    return real;
}   

double complejos::get_imag() {
    return imaginario;
}


op_complejos::op_complejos(double x0, double y0) : complejos(x0, y0) {}

double op_complejos::magnitud_complejo() const {
    return std::sqrt(real * real + imaginario * imaginario);
};

op_complejos op_complejos::operator+(complejos& ob) {
    return op_complejos(real - ob.get_real(), imaginario - ob.get_imag());
};

op_complejos op_complejos::operator-(complejos& ob) {
    return op_complejos(real - ob.get_real(), imaginario - ob.get_imag());
};
op_complejos op_complejos::operator*(complejos& ob) {
    return op_complejos(real * ob.get_real() - imaginario * ob.get_imag(), 
                        real * ob.get_imag() + imaginario * ob.get_real());
};
op_complejos op_complejos::operator/(complejos& ob) {
    double denom = ob.get_real() * ob.get_real() + ob.get_imag() * ob.get_imag();
    if (denom == 0) {
        throw std::runtime_error("División por cero en número complejo.");
    }
    return op_complejos((real * ob.get_real() + imaginario * ob.get_imag()) / denom, 
                        (imaginario * ob.get_real() - real * ob.get_imag()) / denom);
}       