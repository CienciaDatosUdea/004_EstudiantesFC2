# include <cstdio>
# include <iostream>
# include <cmath>

class complexNumbers{
    protected:
        double real;
        double imag;
    public:
        // Clsass cosntructor
        complexNumbers(double x0, double y0): real(x0), imag(y0) {};
        void get_complexNumbers(){

            std::cout<<real<<" + "<<imag<<"i"<<" \n";
        }
        double get_real(){return real;};
        double get_imag(){return imag;};
    };


class op_complexNumbers: public complexNumbers{
    public:
        op_complexNumbers(double x0, double y0): complexNumbers(x0,y0) {};

    double complexNorm(){
        return sqrt(real * real + imag * imag);
    };

    /*
      Inherited methods that define operations between complex numbers
    */
    complexNumbers operator+(complexNumbers &ob) {
        return complexNumbers(real + ob.get_real(), imag + ob.get_imag());
    };
    complexNumbers operator-(complexNumbers &ob) {
        return complexNumbers(real - ob.get_real(), imag - ob.get_imag());
    };
    complexNumbers operator*(complexNumbers &ob) {
        return complexNumbers(real * ob.get_real() - imag * ob.get_imag(), real * ob.get_imag() + imag * ob.get_real());
    };
    complexNumbers operator/(op_complexNumbers &ob) {
        return complexNumbers((real * ob.get_real() + imag * ob.get_imag()) / pow(ob.complexNorm(),2), (-real * ob.get_imag() + imag * ob.get_real()) / pow(ob.complexNorm(),2));
    };
};

int main(){
    complexNumbers b(0, 0);

    op_complexNumbers w(2, 5);
    op_complexNumbers z(4,-10);

    std::cout<<"z = ";
    z.get_complexNumbers();
    std::cout<<"w = ";
    w.get_complexNumbers();

    std::cout<<"|z| = "<<z.complexNorm()<<std::endl;
    std::cout<<"|w| = "<<w.complexNorm()<<std::endl;
    b = z+w;
    std::cout<<"z+w = ";
    b.get_complexNumbers();
    b = z-w;
    std::cout<<"z-w = ";
    b.get_complexNumbers();
    b = z*w;
    std::cout<<"z*w = ";
    b.get_complexNumbers();
    b = z/w;
    std::cout<<"z/w = ";
    b.get_complexNumbers();
    return 0;
}
