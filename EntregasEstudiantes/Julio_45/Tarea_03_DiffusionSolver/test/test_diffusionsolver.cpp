#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>
#include "../include/diffusion_model.h"

using namespace std;

double initCond(double x){
    double out;
    double ax = std::abs(x);
    if (ax<=0.25){out = 1.0;}
    else {out = 0.0;}
    return out;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " archivo.par" << endl;
        return 1;
    }

    // Variables de parámetros
    double xmin = 0.0;
    double xmax = 0.0;
    int N = 0;
    double D = 0.0;
    double dt = 0.0;
    double tmax = 0.0;
    string filename;

    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Error: no se pudo abrir el archivo " << argv[1] << endl;
        return 1;
    }

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
            }
            else if (key == "filename") {
                filename = value;
            }
        }
    }

    infile.close();

    Geometry G(xmin,xmax,N);
    Temperature T(G);

    double TL = initCond(G.x[0]);
    double TR = initCond(G.x[G.N-1]);

    T.applyInitialCondition(initCond);
    T.applyBoundaryCondition(TL,TR);

    DiffusionSolver eq(T,D,dt,tmax,TL,TR,initCond,filename);

    cout<<"alpha = "<<eq.alpha<<endl;
    cout<<"D = "<<eq.D<<endl;
    cout<<"dt = "<<eq.dt<<endl;
    cout<<"dx = "<<eq.field.g.dx<<endl;



    eq.run();

    return 0;
}