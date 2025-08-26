#include <iostream>
#include <cmath>

class complejo{
    protected:
        double real;
        double imag;
    public:
        complejo(double x0, double y0);
        void print_complejo();
        double get_real();
        double get_imag();
};
