# include <cstdio>
# include <iostream>
# include <cmath>

class complejos{
    protected: 
        double real;
        double imag;
    public: 
        //Cosntructor de la clase 
        complejos(double x0, double y0);
        void get_complejos();       
        double get_real();
        double get_imag();
    };

