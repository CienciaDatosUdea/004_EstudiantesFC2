#include "complejos.h"
#include <limits> // limpiar buffers

// Función para leer un número complejo (usuario)
op_complejos leerComplejo(const std::string& nombre) {
    double real, imag;
    
    std::cout << "Ingresa el número complejo " << nombre << " ===" << std::endl;
    
    // Leer parte real
    std::cout << "Parte real: ";
    while (!(std::cin >> real)) {
        std::cout << "Entrada inválida. Por favor ingrese un número: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    // Leer parte imaginaria
    std::cout << "Parte imaginaria: ";
    while (!(std::cin >> imag)) {
        std::cout << "Entrada inválida. Por favor ingrese un número: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    std::cout << std::endl;
    return op_complejos(real, imag);
}

int main() {
    std::cout << "=== CALCULADORA DE NÚMEROS COMPLEJOS ===" << std::endl;
    std::cout << "Este programa realiza todas las operaciones básicas con dos números complejos." << std::endl << std::endl;
    
    // Leer los números complejos
    op_complejos A = leerComplejo("A");
    op_complejos B = leerComplejo("B");
    
    // Mostrar los números ingresados
    std::cout << "=== NÚMEROS INGRESADOS ===" << std::endl;
    std::cout << "A = ";
    A.get_complejos();
    std::cout << "B = ";
    B.get_complejos();
    std::cout << std::endl;
    
    // Realizar y mostrar todas las operaciones
    std::cout << "=== RESULTADOS DE LAS OPERACIONES ===" << std::endl;
    
    // Suma
    op_complejos suma = A + B;
    std::cout << "SUMA: A + B = ";
    suma.get_complejos();
    
    // Resta
    op_complejos resta = A - B;
    std::cout << "RESTA: A - B = ";
    resta.get_complejos();
    
    // Multiplicación
    op_complejos multiplicacion = A * B;
    std::cout << "MULTIPLICACIÓN: A * B = ";
    multiplicacion.get_complejos();
    
    // División (con verificación)
    std::cout << "DIVISIÓN: A / B = ";
    if (B.get_real() == 0 && B.get_imag() == 0) {
        std::cout << "Error: No se puede dividir por cero" << std::endl;
    } else {
        op_complejos division = A / B;
        division.get_complejos();
    }
    
    // Magnitudes
    std::cout << std::endl;
    std::cout << "MAGNITUD (MÓDULO):" << std::endl;
    std::cout << "|A| = " << A.magnitud_complejo() << std::endl;
    std::cout << "|B| = " << B.magnitud_complejo() << std::endl;
    
    std::cout << std::endl << "=== FIN DEL PROGRAMA ===" << std::endl;
    
    return 0;
}