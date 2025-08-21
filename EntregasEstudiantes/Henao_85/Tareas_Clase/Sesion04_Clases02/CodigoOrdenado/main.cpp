#include "op_complejos.h"
#include <iostream>

using namespace std;

int main() {
    
    op_complejos A(0, 0);            // A = 0 + 0i
    op_complejos B(0, 0);            // B = 0 + 0i
    op_complejos C(1, 2);            // C = 1 + 2i

    // Se muestra el complejo C:
    cout << "C: "; 
    C.get_complejos();

    // Se crea el complejo pp y se muestra su magnitud:
    op_complejos pp(2, 1);           // pp = 2 + 1i
    cout << "Magnitud de pp: " << pp.magnitud_complejo() << endl;
    cout << "pp: "; 
    pp.get_complejos();

    // Suma de pp + C 
    B = pp + C;
    cout << "pp + C: "; 
    B.get_complejos();

    // Resta de pp - C 
    A = pp - C;
    cout << "pp - C: "; 
    A.get_complejos();

    if (C.magnitud_complejo() == 0) {
        cerr << "Error: No se puede dividir por un número complejo de magnitud 0." << endl;
    } else {
        op_complejos resultado = pp / C;
        cout << " pp / c: ";
        resultado.get_complejos();
    }


    return 0;
}

