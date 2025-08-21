# include <cstdio>
# include <iostream>
# include <cmath>
# include "include.h"

using namespace std;

complejos::complejos(double x0, double y0): real(x0), imag(y0) {};
void complejos::get_complejos(){
    cout<<real<<" + "<<imag<<"i"<<" \n";
}
double complejos::get_real(){return real;};
double complejos:: get_imag(){return imag;};
double complejos:: magnitud_complejo(){
    return sqrt(real * real + imag * imag);
}

op_complejos::op_complejos(double x0, double y0): complejos(x0,y0) {};
complejos op_complejos::operator+(complejos &ob){
    return complejos(real + ob.get_real(), imag + ob.get_imag());    
};
complejos op_complejos::operator-(complejos &ob){
    return complejos(real - ob.get_real(), imag - ob.get_imag());
}
complejos op_complejos::operator*(complejos &ob){
    return complejos(real*ob.get_real() -  imag*ob.get_imag(), real*ob.get_imag() + imag*ob.get_real());
}
complejos op_complejos::operator/(complejos &ob){
    auto factor = ob.magnitud_complejo()*ob.magnitud_complejo();
    return complejos((1/factor)*(real*ob.get_real() +  imag*ob.get_imag()),(1/factor)*(imag*ob.get_real() - real*ob.get_imag()));
}

    
