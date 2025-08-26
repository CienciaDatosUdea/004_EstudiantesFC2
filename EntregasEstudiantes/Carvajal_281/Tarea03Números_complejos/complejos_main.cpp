#include <iostream>
#include "complejos.h"

int main() {
    double x1, y1, x2, y2;

    std::cout << "Ingrese la parte real del número complejo C1: ";
    std::cin >> x1;
    std::cout << "Ingrese la parte imaginaria del número complejo C1: ";
    std::cin >> y1;

    std::cout << "Ingrese la parte real del número complejo C2: ";
    std::cin >> x2;
    std::cout << "Ingrese la parte imaginaria del número complejo C2: ";
    std::cin >> y2;

    Complejos c1(x1, y1);
    Complejos c2(x2, y2);

    //Realizar las operaciones usando la clase
    Complejos suma = c1.suma(c2);
    Complejos resta = c1.resta(c2);
    Complejos multiplicacion = c1.multiplicar(c2);
    Complejos division = c1.dividir(c2);

    //Imprimir resultados para todas las operaciones
    Complejos::imprimirResultados(suma, resta, multiplicacion, division);

    return 0;
}

