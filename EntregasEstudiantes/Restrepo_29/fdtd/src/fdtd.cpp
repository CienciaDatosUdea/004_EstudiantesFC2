#include "fdtd.h"
#include <fstream>
#include <cmath>
#include <iostream>

using namespace std;

// Inicialización de los campos
void condiciones_iniciales(vector<double> &E, vector<double> &H) {
    for (int k = 0; k < xmax; k++) {
        double z = k * dz;
        E[k] = 0.1 * sin(2.0 * M_PI * z / 100.0);
        H[k] = E[k];
    }
}

// Frontera periódica
void frontera_periodica(vector<double> &E, vector<double> &H) {
    E[0]       += betaE * (H[xmax-2] - H[0]);
    E[xmax-1]  += betaE * (H[xmax-2] - H[0]);
    H[0]       += betaH * (E[xmax-2] - E[0]);
    H[xmax-1]  += betaH * (E[xmax-2] - E[0]);
}

// Frontera nula
void frontera_nula(vector<double> &E, vector<double> &H) {
    E[0] = 0.0;
    E[xmax-1] = 0.0;
    H[0] = 0.0;
    H[xmax-1] = 0.0;
}

// Simulación principal
void simular(const string &archivo, bool usarPeriodica) {
    vector<double> E(xmax, 0.0);
    vector<double> H(xmax, 0.0);

    condiciones_iniciales(E, H);

    ofstream file(archivo);
    file << "t,pos,E,H\n";

    for (int n = 0; n < nmax; n++) {
        // Guardar datos
        for (int k = 0; k < xmax; k++) {
            file << n << "," << k << "," << E[k] << "," << H[k] << "\n";
        }

        // Actualizar E
        for (int k = 1; k < xmax; k++) {
            E[k] += betaE * (H[k-1] - H[k]);
        }

        // Actualizar H
        for (int k = 0; k < xmax-1; k++) {
            H[k] += betaH * (E[k] - E[k+1]);
        }

        // Aplicar condiciones de frontera
        if (usarPeriodica) {
            frontera_periodica(E, H);
        } else {
            frontera_nula(E, H);
        }
    }

    file.close();
    cout << "Simulación terminada. Resultados en " << archivo << endl;
}