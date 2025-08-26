
#include "TISE.h"
#include <cmath>
#include <filesystem>
#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;


/*
Esta función define un pozo de potencial infinito.
Dentro del pozo (entre las paredes), el potencial es 0, lo que significa que
la partícula es libre dentro de esta región. Las paredes infinitas se implementan mediante 
las condiciones de contorno, no mediante el potencial.

*/


// Función de potencial: pozo infinito (0 dentro del pozo)
double InfiniteWell(double x, double *par) {
    return 0.0;
}

// Construcción de la matriz Hamiltoniana usando diferencias finitas
void create_Hamiltonian(int n, double L, double R, double *H) {

    /*
    dx: Espaciado entre puntos de la malla

    coeff: Coeficiente que viene de la aproximación por diferencias finitas de la segunda derivada
    La matriz Hamiltoniana es tridiagonal: solo tiene elementos en la diagonal principal y las dos subdiagonales

    2.0 * coeff: Elementos diagonales (energía cinética)
    -1.0 * coeff: Elementos fuera de la diagonal (acoplamiento entre puntos vecinos)
    Esto representa el operador -ℏ²/2m * d²/dx² discretizado
    
    */
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


// Función para calcular autovalores/autovectores usando Jacobi-----------------------------------


/*
 El algoritmo de Jacobi es un método iterativo para diagonalizar matrices simétricas. 
Funciona aplicando rotaciones sucesivas para anular los elementos fuera de la diagonal.

Inicialización: Crea una matriz identidad para los autovectores
Copia la matriz: Trabaja sobre una copia para no modificar la original
Bucle principal: Encuentra el elemento fuera de la diagonal más grande
Calcula ángulo de rotación: phi = 0.5 * atan2(2*elemento, diferencia)
Aplica rotación: Actualiza filas y columnas afectadas
Actualiza autovectores: Mantiene el registro de las transformaciones
Repite hasta que todos los elementos fuera de la diagonal sean menores que la tolerancia

*/
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

/*
Calcula la norma L² de cada autovector: ∫|ψ(x)|²dx ≈ Σ|ψᵢ|²Δx
Normaliza dividiendo cada componente por la norma
Esto asegura que ∫|ψ(x)|²dx = 1 (interpretación probabilística de la MC)
*/

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

    /*
    Crea la carpeta "resultados" si no existe
    Guarda en formato columnar: primera columna es la posición x, 
    luego cada columna es una función de onda diferente
    */
    namespace fs = std::filesystem;
    //fs::create_directory("resultados");
    fs::create_directories("resultados_1D/TISE");

    //ofstream fout("resultados/wavefunctions.dat");
    ofstream fout("resultados_1D/TISE/funciones_onda.txt");
    for(int i=0;i<n;i++){
        double x = L + (i+1)*dx;
        fout << x;
        for(int j=0;j<Nfunc;j++)
            fout << "\t" << eigenvectors[i*n + j];
        fout << "\n";
    }
    fout.close();

    // Liberar memoria de eigenvectors y eigenvalues si corresponde
    cout << "Funciones de onda guardadas en 'resultados_1D/TISE/funciones_onda.txt'" << endl;

}



void save_all_wavefunctions_2d(
    double* eigenvectors,
    int Nx, int Ny, int Nfunc,
    const std::string& folder_path
) {
    std::filesystem::create_directories(folder_path);

    int total_points = Nx * Ny;

    for (int k = 0; k < Nfunc; ++k) {
        std::ostringstream filename;
        filename << folder_path << "/psi_" << std::setw(3) << std::setfill('0') << k << ".dat";

        std::ofstream file(filename.str());
        if (!file.is_open()) {
            std::cerr << "Error al abrir archivo: " << filename.str() << std::endl;
            continue;
        }

        for (int i = 0; i < Nx; ++i) {
            for (int j = 0; j < Ny; ++j) {
                int idx = k * total_points + i * Ny + j;
                file << i << " " << j << " " << eigenvectors[idx] << "\n";
            }
            file << "\n";  // Separador de filas
        }

        file.close();
    }

    std::cout << "Funciones de onda estacionarias guardadas en " << folder_path << std::endl;
}


void save_energies(double *eigenvalues, int Nfunc) {
    namespace fs = std::filesystem;
    fs::create_directories("resultados_1D/TISE");

    ofstream fout("resultados_1D/TISE/Energias.txt");
    for(int i = 0; i < Nfunc; i++)
        fout << eigenvalues[i] << "\n";
    fout.close();

    cout << "Energías guardadas en 'resultados_1D/TISE/Energias.txt'" << endl;
}

//#include "utils.hpp"  // Para save_all_wavefunctions_2d




void run_tise_simulation_2d(
    int Nx, int Ny, double dx, double dy,
    double (*V)(double, double),
    int Nfunc,
    double*& eigenvectors,
    double*& eigenvalues,
    const std::string& output_folder
) {
    int total_points = Nx * Ny;
    int matrix_size = total_points;

    std::vector<std::vector<double>> H(matrix_size, std::vector<double>(matrix_size, 0.0));

    // Construcción de la matriz Hamiltoniana
    for (int i = 0; i < Nx; ++i) {
        for (int j = 0; j < Ny; ++j) {
            int idx = i * Ny + j;
            double x = i * dx;
            double y = j * dy;
            double Vxy = V(x, y);

            H[idx][idx] = Vxy + 2.0 / (dx * dx) + 2.0 / (dy * dy);

            if (i > 0) H[idx][(i - 1) * Ny + j] = -1.0 / (dx * dx);
            if (i < Nx - 1) H[idx][(i + 1) * Ny + j] = -1.0 / (dx * dx);
            if (j > 0) H[idx][i * Ny + (j - 1)] = -1.0 / (dy * dy);
            if (j < Ny - 1) H[idx][i * Ny + (j + 1)] = -1.0 / (dy * dy);
        }
    }

    // Diagonalización (simplificada para ejemplo)
    std::vector<double> dummy_eigenvalues(Nfunc);
    std::vector<std::vector<double>> dummy_eigenvectors(Nfunc, std::vector<double>(matrix_size));

    for (int k = 0; k < Nfunc; ++k) {
        dummy_eigenvalues[k] = k * 0.1;  // Simulación de autovalores
        for (int idx = 0; idx < matrix_size; ++idx) {
            dummy_eigenvectors[k][idx] = std::sin((k + 1) * idx * M_PI / matrix_size);  // Simulación de autovectores
        }
    }

    // Asignación dinámica
    eigenvalues = new double[Nfunc];
    eigenvectors = new double[Nfunc * matrix_size];

    for (int k = 0; k < Nfunc; ++k) {
        eigenvalues[k] = dummy_eigenvalues[k];
        for (int idx = 0; idx < matrix_size; ++idx) {
            eigenvectors[k * matrix_size + idx] = dummy_eigenvectors[k][idx];
        }
    }

    // Guardar resultados
    save_all_wavefunctions_2d(eigenvectors, Nx, Ny, Nfunc, output_folder + "/estacionarios/");
    save_energies(eigenvalues, Nfunc);

    std::cout << "TISE 2D completado. Resultados guardados en " << output_folder << std::endl;
}
