#include <cstdio>
#include <iostream>
#include <cmath>

class complejos{
    protected:
        double real;
        double imaginario;  
    public:
        complejos(double x0, double y0);
        void get_complejos();
        double get_real();
        double get_imag();
};

class op_complejos : public complejos {
public:
    op_complejos(double x0 = 0, double y0 = 0);

    double magnitud_complejo() const;

    op_complejos operator+(complejos& ob);
    op_complejos operator-(complejos& ob);
    op_complejos operator*(complejos& ob);
    op_complejos operator/(complejos& ob);
};