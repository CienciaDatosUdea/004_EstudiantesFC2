#include "TISE.h"
#include <cmath>
#include <filesystem>
#include <iostream>

using namespace std;

// Función de potencial: pozo infinito (0 dentro del pozo)
double InfiniteWell(double x, double *par) {
    return 0.0;
}

// Construcción de la matriz Hamiltoniana usando diferencias finitas
void create_Hamiltonian(int n, double L, double R, double *H) {
    double dx = (R - L) / (n+1);
    double coeff = 1.0 / (2*dx*dx);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                H[i*n + j] = 2.0 * coeff;
            else if (abs(i - j) == 1)
                H[i*n + j] = -1.0 * coeff;
            else
                H[i*n + j] = 0.0;
        }
    }
}

// Función para calcular autovalores/autovectores usando Jacobi
void jacobi_eigenvalues(double *A, int n, double tol, double *eigenvectors, double *eigenvalues) {
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            eigenvectors[i*n + j] = (i==j) ? 1.0 : 0.0;

    double *B = new double[n*n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            B[i*n + j] = A[i*n + j];

    double error = tol + 1;
    while(error > tol) {
        int p = 0, q = 1;
        error = fabs(B[0*n + 1]);
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
                if(fabs(B[i*n + j]) > error) {
                    error = fabs(B[i*n + j]);
                    p=i; q=j;
                }
        double phi = 0.5 * atan2(2*B[p*n + q], B[q*n + q]-B[p*n + p]);
        double c = cos(phi), s = sin(phi);

        double Bpp = c*c*B[p*n+p] - 2*s*c*B[p*n+q] + s*s*B[q*n+q];
        double Bqq = s*s*B[p*n+p] + 2*s*c*B[p*n+q] + c*c*B[q*n+q];
        double Bpq = 0.0;

        for(int i=0;i<n;i++) {
            if(i!=p && i!=q) {
                double Bip = c*B[i*n+p] - s*B[i*n+q];
                double Biq = s*B[i*n+p] + c*B[i*n+q];
                B[i*n+p] = Bip; B[p*n+i] = Bip;
                B[i*n+q] = Biq; B[q*n+i] = Biq;
            }
        }
        B[p*n+p]=Bpp; B[q*n+q]=Bqq; B[p*n+q]=Bpq; B[q*n+p]=Bpq;

        for(int i=0;i<n;i++) {
            double Vip = c*eigenvectors[i*n+p] - s*eigenvectors[i*n+q];
            double Viq = s*eigenvectors[i*n+p] + c*eigenvectors[i*n+q];
            eigenvectors[i*n+p] = Vip;
            eigenvectors[i*n+q] = Viq;
        }
    }

    for(int i=0;i<n;i++)
        eigenvalues[i] = B[i*n + i];

    delete[] B;
}

// ===========================
// Normalizar y guardar primeras Nfunc funciones de onda
// ===========================
void normalize_and_save_wavefunctions(double *eigenvectors, double *eigenvalues,
                                      int n, int Nfunc, double L, double R) {
    double dx = (R-L)/(n+1);

    // Normalización
    for(int j=0;j<Nfunc;j++){
        double norm = 0.0;
        for(int i=0;i<n;i++)
            norm += eigenvectors[i*n + j] * eigenvectors[i*n + j] * dx;
        norm = sqrt(norm);
        for(int i=0;i<n;i++)
            eigenvectors[i*n + j] /= norm;
    }

    // Guardar en archivo
    namespace fs = std::filesystem;
    fs::create_directory("resultados");

    ofstream fout("resultados/wavefunctions.dat");
    for(int i=0;i<n;i++){
        double x = L + (i+1)*dx;
        fout << x;
        for(int j=0;j<Nfunc;j++)
            fout << "\t" << eigenvectors[i*n + j];
        fout << "\n";
    }
    fout.close();

    // Liberar memoria de eigenvectors y eigenvalues si corresponde
    cout << "Funciones de onda guardadas en 'resultados/wavefunctions.dat'" << endl;
}







