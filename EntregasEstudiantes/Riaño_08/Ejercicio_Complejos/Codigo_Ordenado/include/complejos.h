#ifndef COMPLEJOS_H
#define COMPLEJOS_H

#include <iostream>
#include <cmath>

class complejos {
protected:
    double real;
    double imag;
public:
    // Constructor de la clase
    complejos(double x0, double y0);
    
    // Métodos para obtener los valores
    void get_complejos();
    double get_real();
    double get_imag();
};

class op_complejos : public complejos {
public:
    // Constructor
    op_complejos(double x0, double y0);
    
    // Método para la magnitud
    double magnitud_complejo();
    
    // Sobrecarga de operadores
    complejos operator+(complejos& ob);
    complejos operator-(complejos& ob);
    complejos operator*(complejos& ob);
    complejos operator/(complejos& ob);
};

#endif
