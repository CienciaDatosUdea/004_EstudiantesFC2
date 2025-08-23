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

    complejos operator*(complejos &ob){
        return complejos(real*ob.get_real() - imag*ob.get_imag(), real*ob.get_imag() + imag*ob.get_real());
    };

    complejos operator/(complejos &ob){
        return complejos((real*ob.get_real()+imag*ob.get_imag())/( ob.get_real()*ob.get_real() + ob.get_imag()*ob.get_imag()),(imag*ob.get_real()-real*ob.get_imag())/( ob.get_real()*ob.get_real() + ob.get_imag()*ob.get_imag()));
    };
    /*
    Construir las otras clases heredades que permita realizar la suma, resta 
    multiplcacion y division entre complejos
    */
    
};

int main(){
    complejos b(3, -5);
    complejos c(0, 0);
    op_complejos a(2,1); 
    
    std::cout<<"a = ";
    a.get_complejos();
    std::cout<<"|a| = "<<a.magnitud_complejo()<<"\n\n";    


    std::cout<<"b = ";
    b.get_complejos();
    std::cout<<"|b| = "<<sqrt(b.get_real()*b.get_real()+b.get_imag()*b.get_imag())<<"\n\n";

    std::cout<<"a + b =";
    c = a + b;
    c.get_complejos();
    std::cout<<"|a + b| = "<<sqrt(c.get_real()*c.get_real()+c.get_imag()*c.get_imag())<<"\n\n";

    std::cout<<"a - b =";
    c = a - b;
    c.get_complejos();
    std::cout<<"|a - b| = "<<sqrt(c.get_real()*c.get_real()+c.get_imag()*c.get_imag())<<"\n\n";

    std::cout<<"a * b =";
    c = a * b;
    c.get_complejos();
    std::cout<<"|a * b| = "<<sqrt(c.get_real()*c.get_real()+c.get_imag()*c.get_imag())<<"\n\n";

    std::cout<<"a / b =";
    c = a / b;
    c.get_complejos();
    std::cout<<"|a / b| = "<<sqrt(c.get_real()*c.get_real()+c.get_imag()*c.get_imag())<<"\n\n";

    return 0;
}