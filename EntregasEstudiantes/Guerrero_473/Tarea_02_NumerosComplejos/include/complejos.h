#ifndef COMPLEJOS_H
#define COMPLEJOS_H

#include <iostream>
#include <cmath>

// Clase base que representa números complejos
class complejos {
protected: 
    double real;    // Parte real del número complejo
    double imag;    // Parte imaginaria del número complejo
    
public: 
    // Constructor de la clase
    complejos(double x0 = 0, double y0 = 0);
    
    // Método para mostrar el número complejo en formato a + bi
    void get_complejos();
    
    // Getters para acceder a las partes real e imaginaria
    double get_real();
    double get_imag();
};

// Clase derivada que implementa operaciones con números complejos
class op_complejos : public complejos {
public:
    // Constructor que hereda de la clase base
    op_complejos(double x0 = 0, double y0 = 0);
    
    // Calcula la magnitud (módulo) del número complejo
    double magnitud_complejo();
    
    // Sobrecarga del operador de suma
    op_complejos operator+(const op_complejos &ob);
    
    // Sobrecarga del operador de resta
    op_complejos operator-(const op_complejos &ob);
    
    // Sobrecarga del operador de multiplicación
    op_complejos operator*(const op_complejos &ob);
    
    // Sobrecarga del operador de división
    op_complejos operator/(const op_complejos &ob);
};

#endif