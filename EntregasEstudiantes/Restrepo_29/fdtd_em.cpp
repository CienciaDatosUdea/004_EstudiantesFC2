

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    // Constantes físicas
    const double eps0 = 8.854e-12;
    const double mu0  = 4.0 * M_PI * 1e-7;
    const double c    = 1.0 / sqrt(eps0 * mu0);

    // Parámetros espaciales
    const int N = 200;      
    const double Lz = 1.0;   
    const double dz = Lz / (N - 1);

    // Condición de Courant
    const double dt = dz / (2*c);  

    // Factores beta para condiciones periódicas
    const double betaE = dt / (eps0 * dz);
    const double betaH = dt / (mu0 * dz);

    // Vectores de los campos
    vector<double> E(N, 0.0);
    vector<double> H(N, 0.0);

    // Condiciones iniciales
    for (int k = 0; k < N; k++) {
        double z = k * dz * 100.0; 
        E[k] = 0.1 * sin(2.0 * M_PI * z / 100.0);
        H[k] = E[k]; 
    }

    
    const int nSteps = 500;                                  //Desplazamientos temporales en la malla de Yee.
    for (int n = 0; n < nSteps; n++) {
       
        for (int k = 0; k < N-1; k++) {                       // Se realiza la evolución del campo Hy.
            H[k] = H[k] + (dt/(mu0*dz)) * (E[k+1] - E[k]);
        }

       
        for (int k = 1; k < N; k++) {                         // Se realiza la evolución del campo Ex.
            E[k] = E[k] + (dt/(eps0*dz)) * (H[k] - H[k-1]);
        }

        // Condiciones de frontera periódicas.

        E[0]     = E[0]     + betaE * (H[N-2] - H[1]);
        E[N-1]   = E[N-1]   + betaE * (H[N-2] - H[1]);

        
        H[0]     = H[0]     + betaH * (E[N-2] - E[1]);
        H[N-1]   = H[N-1]   + betaH * (E[N-2] - E[1]);

       
        for (int s= 0; s<10; s++){
            cout << "Ex["<<s<<"]=" <<E[s] << endl;
            cout << "Hy["<<s<<"]=" <<H[s] << endl;
        }


        
    }

    return 0;
}

