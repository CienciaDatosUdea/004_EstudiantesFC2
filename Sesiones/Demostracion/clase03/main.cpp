#include "op_complejos.h"

int main() {
    op_complejos A(1, 1), B(2, 2);
    op_complejos C = A + B;

    C.get_complejos(); // debería imprimir 3 + 3i
    std::cout << "Magnitud: " << C.magnitud_complejo() << "\n";

    auto sum=A+B;
    return 0;
}
