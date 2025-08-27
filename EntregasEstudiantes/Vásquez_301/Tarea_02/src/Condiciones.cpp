#include "../include/difusion_model.h" 
#include <cmath> 
#include <vector>

void aplicarCondicionInicial(std::vector<double>& u, const std::vector<double>& x) {
    // Parámetros para la función Gaussiana
    double x_centro = (x.front() + x.back()) / 2.0; // Calcula el centro del dominio
    double alpha_gauss = 100.0; // Factor que controla el ancho de la campana


    u.resize(x.size());

    // Calcula el valor de la temperatura en cada nodo
    for (size_t i = 0; i < x.size(); ++i) {
        u[i] = exp(-alpha_gauss * pow(x[i] - x_centro, 2));
    }
}

void aplicarCondicionesDeFrontera(std::vector<double>& u, double T_L, double T_R) {
    if (!u.empty()) {
        u[0] = T_L;         // Fija la temperatura en el primer nodo
        u.back() = T_R;     // Fija la temperatura en el último nodo 
    }
}