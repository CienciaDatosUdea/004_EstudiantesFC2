#include "op_complejos.h"
#include <cmath>

op_complejos::op_complejos(double x0, double y0) : complejos(x0, y0) {}

double op_complejos::magnitud_complejo() {
    return std::sqrt(real * real + imag * imag);
}

op_complejos op_complejos::operator+(complejos &ob) {
    return op_complejos(real + ob.get_real(), imag + ob.get_imag());
}
