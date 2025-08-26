#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>
#include "../include/diffusion_model.h"

using namespace std;

// Gaussiana de la forma exp(-alpha*(x-x0)²/sigma²)
double gaussian(double x,double x0,double alpha,double sigma){
    return exp(-alpha*(x-x0)*(x-x0)/(sigma*sigma));
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " archivo.par" << endl;
        return 1;
    }

    // Variables de parámetros (RF7)
    double xmin = 0.0;
    double xmax = 0.0;
    int N = 0;
    double D = 0.0;
    double dt = 0.0;
    double tmax = 0.0;
    double x0 = 0.0;
    double sigma = 0.0;
    string filename;

    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Error: no se pudo abrir el archivo " << argv[1] << endl;
        return 1;
    }
    // Lee los parámetros del archivo .par
    string line;
    while (getline(infile, line)) {
        // Ignorar líneas vacías o comentarios (#)
        if (line.empty() || line[0] == '#') continue;

        string key;
        string value;

        // Partir la línea en clave=valor
        size_t eq_pos = line.find('=');
        if (eq_pos != string::npos) {
            key = line.substr(0, eq_pos);
            value = line.substr(eq_pos + 1);

            // Eliminar posibles espacios
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            // Asignar valores según la clave
            if (key == "xmin") {
                xmin = stod(value);
            } else if (key == "xmax") {
                xmax = stod(value);
            } else if (key == "N") {
                N = stoi(value);
            } else if (key == "D") {
                D = stod(value);
            } else if (key == "dt") {
                dt = stod(value);
            } else if (key == "tmax") {
                tmax = stod(value);
            } else if (key == "x0") {
                x0 = stod(value);
            }
            else if (key == "filename") {
                filename = value;
            } else if (key == "sigma") {
                sigma = stod(value);
            }
        }
    }

    infile.close();

    // Crea la geometría y el campo de temperatura
    Geometry G(xmin,xmax,N);
    Temperature T(G);

    double alp = D*dt/(G.dx*G.dx);

    // Define la condición inicial
    auto initCond = [x0,alp,sigma](double x){return gaussian(x,x0,alp,sigma);};

    // Define las condiciones de frontera
    double TL = initCond(G.x[0]);
    double TR = initCond(G.x[G.N-1]);

    // Aplica las condiciones iniciales y de frontera
    T.applyInitialCondition(initCond);
    T.applyBoundaryCondition(TL,TR);

    // Resuelve la ecuación diferencial
    DiffusionSolver eq(T,D,dt,tmax,TL,TR,initCond,filename);

    eq.run();

    return 0;
}