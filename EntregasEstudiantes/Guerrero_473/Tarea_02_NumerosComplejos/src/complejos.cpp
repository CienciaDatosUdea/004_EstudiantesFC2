#include "complejos.h"

// Implementación de los métodos de la clase base complejos

// Constructor
complejos::complejos(double x0, double y0) : real(x0), imag(y0) {}

// Muestra el número complejo en formato a + bi
void complejos::get_complejos() {
    std::cout << real << " + " << imag << "i" << std::endl;
}

// Getter para la parte real
double complejos::get_real() { 
    return real; 
}

// Getter para la parte imaginaria
double complejos::get_imag() { 
    return imag; 
}

// Implementación de los métodos de la clase derivada op_complejos

// Constructor que llama al constructor de la clase base
op_complejos::op_complejos(double x0, double y0) : complejos(x0, y0) {}

// Calcula la magnitud (módulo) del número complejo
double op_complejos::magnitud_complejo() {
    return sqrt(real * real + imag * imag);
}

// Sobrecarga del operador de suma
op_complejos op_complejos::operator+(const op_complejos &ob) {
    return op_complejos(real + ob.real, imag + ob.imag);
}

// Sobrecarga del operador de resta
op_complejos op_complejos::operator-(const op_complejos &ob) {
    return op_complejos(real - ob.real, imag - ob.imag);
}

// Sobrecarga del operador de multiplicación
op_complejos op_complejos::operator*(const op_complejos &ob) {
    double nuevo_real = real * ob.real - imag * ob.imag;
    double nuevo_imag = real * ob.imag + imag * ob.real;
    return op_complejos(nuevo_real, nuevo_imag);
}

// Sobrecarga del operador de división
op_complejos op_complejos::operator/(const op_complejos &ob) {
    double denominador = ob.real * ob.real + ob.imag * ob.imag;
    double nuevo_real = (real * ob.real + imag * ob.imag) / denominador;
    double nuevo_imag = (imag * ob.real - real * ob.imag) / denominador;
    return op_complejos(nuevo_real, nuevo_imag);
}