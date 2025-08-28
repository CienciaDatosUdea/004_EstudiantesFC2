#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream>

const double Kb = 1.0; // Constante de Boltzmann fijada a 1.0

long double canonical(double T, const std::string& filename) {
    if (T <= 0) {
        throw std::invalid_argument("T debe ser mayor que 0."); 
    }
    
    std::vector<double> energies;
    std::vector<long long> degeneracies;
    
    // Leer el archivo de datos
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + filename);
    }
    
    std::string header;
    std::getline(file, header); // Ignorar la cabecera
    
    double energy;
    long long degeneracy;
    while (file >> energy >> degeneracy) {
        energies.push_back(energy);
        degeneracies.push_back(degeneracy);
    }
    file.close();
    
    if (energies.empty()) {
        throw std::runtime_error("El archivo no contiene datos válidos: " + filename);
    }
    
    long double beta = 1.0 / (Kb * T);
    long double Z = 0.0;
    
    // Calcular la función de partición directamente (sin escalado)
    for (size_t i = 0; i < energies.size(); ++i) {
        Z += degeneracies[i] * std::exp(-beta * energies[i]);
    }  
    return Z;
}
long double probability(double E, double T, long double Z) {
    if (T <= 0) {
        throw std::invalid_argument("T debe ser mayor que 0.");
    }
    if (Z <= 0) {
        throw std::invalid_argument("Z debe ser mayor que 0.");
    }    
    long double beta = 1.0 / (Kb * T);
    return std::exp(-beta * E) / Z;
}