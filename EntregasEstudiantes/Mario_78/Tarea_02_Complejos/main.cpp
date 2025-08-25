#include "op_complejos.h"

int main() {
    op_complejos A(-2, 8), B(8, 10);
    op_complejos SUMA = A + B;
    op_complejos RESTA = A - B;
    op_complejos MULTP = A * B;
    op_complejos DIV = A / B;
    
    std::cout<<"A = "; A.get_complejos();         // imprime valor de A
    std::cout<<"B = "; B.get_complejos();         // imprime valor de B
    std::cout<<"A + B = "; SUMA.get_complejos();  // debería imprimir A + B = 6 + 18i
    std::cout<<"A - B = "; RESTA.get_complejos(); // imprime A - B = -10 + -2i
    std::cout<<"A * B = "; MULTP.get_complejos(); // imprime A * B = -96 + 44i
    std::cout<<"A / B = "; DIV.get_complejos();   // imprime A / B = 0.390244 + 0.512195i

    std::cout << "Magnitud |SUMA|= " << SUMA.magnitud_complejo() << "\n"; // imprime la magnitud de SUMA 
    
    return 0;
}
