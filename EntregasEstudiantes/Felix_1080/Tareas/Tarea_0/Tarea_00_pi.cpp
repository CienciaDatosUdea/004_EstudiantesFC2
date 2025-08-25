#include <iostream>
#include <cmath> // Para usar M_PI

// Función que calcula pi utilizando la serie de Leibniz
double calcularPiLeibniz(int n) {
    double pi = 0.0;
    for (int k = 0; k < n; k++) {
        pi += std::pow(-1, k) / (2 * k + 1);  // Suma de la serie
    }
    return 4 * pi;  // Multiplicamos por 4 para obtener el valor de pi
}

// Función que calcula pi separando términos con denominadores 4k+1 y 4k+3
double calcularPiSeparado(int n) {
    double pi = 0.0;
    for (int k = 0; k < n; k++) {
        if (k % 2 == 0) {
            pi += 1.0 / (4 * k + 1);  // Término positivo: 4k+1
        } else {
            pi -= 1.0 / (4 * k + 3);  // Término negativo: 4k+3
        }
    }
    return 4 * pi;  // Multiplicamos por 4 para obtener el valor de pi
}

int main() {
    int n;

    // Solicitar el número de términos a utilizar
    std::cout << "Ingrese el número de términos para aproximar pi: ";
    std::cin >> n;

    // Validación de entrada
    if (n <= 0) {
        std::cout << "El número de términos debe ser positivo." << std::endl;
        return 1; // Salir con error
    }

    // Calcular las aproximaciones usando ambas fórmulas
    double piLeibniz = calcularPiLeibniz(n);
    double piSeparado = calcularPiSeparado(n);

    // Obtener el valor real de pi
    double piReal = M_PI;

    // Calcular el error absoluto en ambas aproximaciones
    double errorLeibniz = std::fabs(piReal - piLeibniz);
    double errorSeparado = std::fabs(piReal - piSeparado);

    // Imprimir los resultados
    std::cout << "Aproximación de pi (Leibniz): " << piLeibniz << std::endl;
    std::cout << "Error absoluto (Leibniz): " << errorLeibniz << std::endl;

    std::cout << "Aproximación de pi (Separado): " << piSeparado << std::endl;
    std::cout << "Error absoluto (Separado): " << errorSeparado << std::endl;

    return 0;
}
