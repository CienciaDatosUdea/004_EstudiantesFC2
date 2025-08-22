#ifndef FDTD_H
#define FDTD_H
#include <cmath>
#include <vector>
#include <string>

// Constantes físicas
const double eps0 = 8.854e-12;
const double mu0  = 4.0 * M_PI * 1e-7;
const double c    = 1.0 / sqrt(eps0 * mu0);

// Parámetros espaciales
const int xmax = 200;      
const double Lz = 1990.0;  
const double dz = Lz / (xmax - 1);
const double dt = dz / (2*c);  

// Factores constantes
const double betaE = dt / (eps0 * dz); 
const double betaH = dt / (mu0 * dz);

// Tiempo de simulación
const int nmax = 500;

// Prototipos
void condiciones_iniciales(std::vector<double> &E, std::vector<double> &H);
void frontera_periodica(std::vector<double> &E, std::vector<double> &H);
void frontera_nula(std::vector<double> &E, std::vector<double> &H);
void simular(const std::string &archivo, bool usarPeriodica);

#endif