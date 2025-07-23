#include "../include/op_complejos.h"
#include "../src/src.cpp"
#include <iostream>
using namespace std;
int main() {
    op_complejos A(1, 1), B(2, 2);
    op_complejos C = A + B;

    C.get_complejos(); // debería imprimir 3 + 3i
    std::cout << "Magnitud: " << C.magnitud_complejo() << endl;;

    auto sum=A+B;
    return 0;
}
