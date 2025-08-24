#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <sstream>
#include "../include/boltzmann.h"

#include <boost/math/special_functions/bessel.hpp>/*provides bessel-K function*/

// Constructor
Secante::Secante(double tol, int maxIter) : tolerancia(tol), maxIteraciones(maxIter) {}

// Implementación del método para encontrar la raíz
double Secante::encontrarRaiz(const std::function<double(double)>& f, double x0, double x1) {
    if (f(x0) == f(x1)) {
        std::cerr << "Error: f(x0) no puede ser igual a f(x1)." << std::endl;
        return NAN; // Not a Number
    }

    double x_anterior = x0;
    double x_actual = x1;
    double x_siguiente;
    int iteracion = 0;

    while (iteracion < maxIteraciones) {
        // Fórmula del método de la secante
        x_siguiente = x_actual - f(x_actual) * (x_actual - x_anterior) / (f(x_actual) - f(x_anterior));

        // Condición de parada
        if (std::abs(x_siguiente - x_actual) < tolerancia) {
            // std::cout << "\nRaíz encontrada después de " << iteracion + 1 << " iteraciones." << std::endl;
            return x_siguiente;
        }

        // Actualizar valores para la próxima iteración
        x_anterior = x_actual;
        x_actual = x_siguiente;
        iteracion++;
    }

    std::cout << "\nSe excedió el número máximo de iteraciones. No se encontró la raíz con la tolerancia dada." << std::endl;
    return x_actual;
}
