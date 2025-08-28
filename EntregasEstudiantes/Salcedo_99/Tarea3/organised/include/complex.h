#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>

// Base class for complex numbers
class ComplexNumbers {
  protected:
    double real;
    double imag;

  public:
    ComplexNumbers(double x0 = 0.0, double y0 = 0.0);

    void get_complexNumbers() const;

    double get_real() const;
    double get_imag() const;
};

// Derived class with all the operations
class OpComplexNumbers : public ComplexNumbers {
  public:
    OpComplexNumbers(double x0 = 0.0, double y0 = 0.0);

    double complexNorm() const;

    ComplexNumbers operator+(const ComplexNumbers &ob);
    ComplexNumbers operator-(const ComplexNumbers &ob);
    ComplexNumbers operator*(const ComplexNumbers &ob);
    ComplexNumbers operator/(const OpComplexNumbers &ob);
};

#endif
