// #include <cstudio>
#include <iostream>
#include <cmath>

using namespace std;

class complejo{
    protected:
        double real;
        double imag;
    public:
        //Constructor:
        complejo(double x0, double y0): real(x0), imag(y0) {};
        void print_complejo(){
            cout<<real<<" + "<<imag<<"i"<<endl;
        }
        double get_real(){return real;};
        double get_imag(){return imag;};
};

class op_complejos: public complejo{
    public:
        op_complejos(double x0, double y0): complejo(x0, y0) {};

        double magnitud_complejo(){
            return sqrt(real*real + imag*imag);
        }

        complejo operator+(complejo &ob){
            return complejo(real + ob.get_real(), imag +ob.get_imag());
        }
        complejo operator*(double ob){
            return complejo(ob*real, ob*imag);
        }
        complejo operator*(complejo &ob){
            double im, re;
            re = real*ob.get_real() - imag*ob.get_imag();
            im = real*ob.get_imag() + imag*ob.get_real();
            return complejo(re, im);
        }
        complejo operator-(complejo &ob){
            return complejo(real - ob.get_real(), imag -ob.get_imag());
        }
        complejo operator/(complejo &ob){
            double im, re;
            double denom = ob.get_real()*ob.get_real() + ob.get_imag()*ob.get_imag();  
            re = real*ob.get_real() + imag*ob.get_imag();
            im = -real*ob.get_imag() + imag*ob.get_real();
            return complejo(re/denom, im/denom);
        }
};

int main(){
    complejo a(0,0);
    complejo b(0,0);
    complejo c(2,3);

    c.print_complejo();

    op_complejos pp(1,1);
    cout<<pp.magnitud_complejo()<<endl;
    b = pp/c;
    b.print_complejo();
    return 0;
}
