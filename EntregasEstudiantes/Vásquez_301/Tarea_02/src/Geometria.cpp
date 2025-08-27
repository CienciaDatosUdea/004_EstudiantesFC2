#include "../include/difusion_model.h" 
#include <iostream> 

/**
 * @brief Constructor de la clase Geometria.
 *
 * Inicializa los miembros de la clase y calcula la malla espacial.
 * @param n_nodos Número total de nodos en la malla.
 * @param x_min Límite izquierdo del dominio.
 * @param x_max Límite derecho del dominio.
 */
Geometria::Geometria(int n_nodos, double x_min, double x_max)
    : N(n_nodos) // Inicializa N usando la lista de inicializadores
{
    // Verifica que el número de nodos sea válido para evitar división por cero
    if (N < 2) {
        std::cerr << "Error: El numero de nodos (N) debe ser al menos 2." << std::endl;
        // En un programa real, aquí se podría lanzar una excepción
        dx = 0;
        return;
    }

    // Calcula el espaciamiento de la malla (dx)
    dx = (x_max - x_min) / (N - 1);

    // Asigna el tamaño correcto al vector de posiciones
    x.resize(N);

    // Calcula y almacena la posición de cada nodo en el vector x
    for (int i = 0; i < N; ++i) {
        x[i] = x_min + i * dx;
    }
}