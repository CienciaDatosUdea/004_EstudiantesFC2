# include <cstdio>
# include <iostream>
# include <cmath>


class complejos{
    protected: 
        double real;
        double imag;
    public: 
        //Cosntructor de la clase 
        complejos(double x0, double y0): real(x0), imag(y0) {};
        void get_complejos(){
            std::cout<<real<<" + "<<imag<<"i"<<" \n";
        }       
        double get_real(){return real;};
        double get_imag(){return imag;};
    };

    
class op_complejos: public complejos{
    public:
        op_complejos(double x0, double y0): complejos(x0,y0) {};
    
    double magnitud_complejo(){
        return sqrt(real * real + imag * imag);
    };

    complejos operator+(complejos &ob) {
        return complejos(real + ob.get_real(), imag + ob.get_imag());    
    };   
    /*
    Construir las otras clases heredades que permita realizar la suma, resta 
    multiplcacion y division entre complejos
    */
    
};

int main(){
    complejos a(0, 0);
    complejos b(0, 1);
    complejos c(0, 0);

    c.get_complejos();  
    op_complejos pp(1,1);
    pp.magnitud_complejo();
    b = pp + c;
    pp.get_complejos();    
    return 0;
}