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

class op_complejos: public complejos{
    public:
        op_complejos(double x0, double y0);
    
    double magnitud_complejo();

    complejos operator+(complejos &ob);
    complejos operator-(complejos &ob);   
    complejos operator*(complejos &ob);
    complejos operator/(op_complejos &ob);
};   
    