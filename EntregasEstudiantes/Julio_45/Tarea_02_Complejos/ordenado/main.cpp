# include <cstdio>
# include <iostream>
# include <cmath>
# include "../include/op_complejos.h"

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