#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <random>
#include <fstream>
#include <string>
#include "system.h"

constexpr double KB = 1;
// constexpr double KB = 1.0;
// constexpr double m = 6.69e-26;
constexpr double m = .1;
constexpr double T0 = .05; //temperatura objetivo


constexpr int N = 5;
const int L = 7*sqrt(N); //esto garantiza una densidad constante de partículas
const double r_cut = L/2;
const int height = L;
const int width = L;
constexpr int BINSIZE = 30; //tamaño de los bines sobre los que dividir el espacio (para busqueda de vecinos)
constexpr double dt = 1e-3; //tamaño temporal
constexpr double Tf = 30; //tiempo final

std::string filename = "data.txt"; //no cambiar esto
int iter = Tf/dt;


int main(){
    std::ofstream file;
    file.open(filename);
    if (!file.is_open()){
        throw std::runtime_error("No se pudo abrir el archivo: " + filename);
    }

    file << "#L = "<<L<<"\n# x\t y\n";


    GridBin gridbins(height,width,BINSIZE);
    System sys(N,gridbins,T0,m,KB, r_cut);

    for(int n= 0;n<iter;n++){
        file<<"#t = "<<n*dt<<"\n";

        sys.update(dt,&file);
        sys.rescaleTemp();
        file<<"#E = "<<sys.getEnergy()<<"\n";
        file<<"#T = "<<sys.getTemperature()<<"\n";

        file << "\n";
    }
    file.close();
    std::string command = "python3 plot.py";
    system(command.c_str());
    return 0;
}
