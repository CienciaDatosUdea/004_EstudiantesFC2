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
    complejos operator-(complejos &ob) {
        return complejos(real - ob.get_real(), imag - ob.get_imag());    
    };   
    complejos operator*(complejos &ob) {
        return complejos(real*ob.get_real() - imag*ob.get_imag(), real*ob.get_imag() + imag*ob.get_real());    
    };
    complejos operator/(op_complejos &ob) {
        return complejos((real*ob.get_real() + imag*ob.get_imag())/pow(ob.magnitud_complejo(),2),( - real*ob.get_imag() + imag*ob.get_real())/pow(ob.magnitud_complejo(),2));    
    };   
    /*
    Construir las otras clases heredades que permita realizar la suma, resta 
    multiplcacion y division entre complejos
    */
    
};

int main(){
    complejos b(0, 0);

    op_complejos w(1, 2);
    op_complejos z(3,-4);

    std::cout<<"z = ";
    z.get_complejos();
    std::cout<<"w = ";
    w.get_complejos();

    std::cout<<"|z| = "<<z.magnitud_complejo()<<std::endl;
    std::cout<<"|w| = "<<w.magnitud_complejo()<<std::endl;
    b = z+w;
    std::cout<<"z+w = ";
    b.get_complejos();
    b = z-w;
    std::cout<<"z-w = ";
    b.get_complejos();
    b = z*w;
    std::cout<<"z*w = ";
    b.get_complejos();
    b = z/w;
    std::cout<<"z/w = ";
    b.get_complejos();
    return 0;
}