#ifndef COMPLEJOS_H
#define COMPLEJOS_H

#include <iostream>
#include <cmath>

// Clase base para representar un número complejo
class NumComplejo {
protected:
    double real;
    double imag;

public:
    // Constructor
    NumComplejo(double x0, double y0);

    // Métodos para acceder a los valores
    void imprimir() const;  // imprime el número complejo
    double realParte() const;
    double imagParte() const;
};

// Clase derivada para operaciones con complejos
class OperadorComplejo : public NumComplejo {
public:
    // Constructor
    OperadorComplejo(double x0, double y0);

    // Método para calcular magnitud
    double modulo() const;

    // Sobrecarga de operadores
    NumComplejo operator+(NumComplejo& ob);
    NumComplejo operator-(NumComplejo& ob);
    NumComplejo operator*(NumComplejo& ob);
    NumComplejo operator/(NumComplejo& ob);
};

#endif
