# include <cstdio>
# include <iostream>
# include <cmath>


class complejos{
    protected: 
        double real;
        double imag;
    public: 
        
        complejos(double x0, double y0): real(x0), imag(y0) {};//Constructor de la clase padre

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

    /*
    Construir las otras clases heredades que permita realizar la suma, resta 
    multiplcacion y division entre complejos
    */
    
};

class suma_complejos: public complejos{
    public:
        suma_complejos(double x0, double y0): complejos(x0,y0) {};

        
    complejos operator+(complejos &ob) {
        return complejos(real + ob.get_real(), imag + ob.get_imag());    
    };   



};


class resta_complejos: public complejos{
public:
    resta_complejos(double x0, double y0): complejos(x0,y0) {};

    
    complejos operator-(complejos &ob) {
        return complejos(real - ob.get_real(), imag - ob.get_imag());    
    };   

};


class multip_complejos: public complejos{
    public:
    multip_complejos(double x0, double y0): complejos(x0,y0) {};


    complejos operator*(complejos &ob) {
        return complejos(((real * ob.get_real())-(imag * ob.get_imag())),(real*ob.get_imag())+(imag*ob.get_real()));    
    };   

};


class division_complejos: public complejos{
    public:
        division_complejos(double x0, double y0): complejos(x0,y0) {};


    complejos operator/(complejos &ob) {
        return complejos(((real * ob.get_real())+(imag * ob.get_imag())),(imag*ob.get_real())-(real*ob.get_imag()));    
    };   
};





int main(){
    complejos a(0, 0);
    complejos b(0, 1);
    complejos c(0, 0);

    c.get_complejos();  
    op_complejos pp(1,1);
    pp.magnitud_complejo();
    pp.get_complejos();

    suma_complejos d(-5,2);
    complejos f = d + a;
    f.get_complejos();

    multip_complejos e(8,4);
    complejos z = e * b;
    z.get_complejos();

        
    return 0;
}