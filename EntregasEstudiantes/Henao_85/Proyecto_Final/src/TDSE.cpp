
#include "TDSE.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <filesystem>

using namespace std;

const double hbar = 1.0;
const double m = 1.0;

// ==========================
// Guardar función de onda
// ==========================
void save_wavefunction(const vector<cdouble>& psi, int step, double dx) {
    namespace fs = std::filesystem;
    fs::create_directories("resultados_1D/TDSE");

    ofstream file("resultados_1D/TDSE/" + to_string(step) + ".dat");
    //ofstream file("resultados_1D/TDSE/" + filename);

    
    for (size_t i = 0; i < psi.size(); i++) {
        double x = i * dx;
        file << x << " " << norm(psi[i]) << "\n";
    }
    file.close();
}

// ==========================
// Producto matriz * vector
// ==========================
vector<cdouble> matvec(const vector<vector<cdouble>>& M, const vector<cdouble>& v) {
    size_t n = v.size();
    vector<cdouble> result(n, 0.0);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            result[i] += M[i][j] * v[j];
        }
    }
    return result;
}

// ==========================
// Simulación Crank-Nicolson
// ==========================
void run_cn_simulation(int N, double L, double dt, int nsteps,
                       double x0, double k0, double sigma) {

    double dx = L / (N + 1);

    // Inicialización de la onda (paquete gaussiano)
    vector<cdouble> psi(N, 0.0);
    for (int i = 0; i < N; i++) {
        double x = (i + 1) * dx;
        double gauss = exp(-(x - x0)*(x - x0) / (2*sigma*sigma));
        psi[i] = gauss * exp(cdouble(0, k0*x));
    }

    // Normalización
    double norm_factor = 0.0;
    for (int i = 0; i < N; i++) norm_factor += norm(psi[i]) * dx;
    for (int i = 0; i < N; i++) psi[i] /= sqrt(norm_factor);

    // Construcción de la matriz Hamiltoniana (solo cinética)
    vector<vector<cdouble>> H(N, vector<cdouble>(N, 0.0));
    double coeff = -hbar*hbar / (2*m*dx*dx);
    for (int i = 0; i < N; i++) {
        H[i][i] = -2.0*coeff;
        if (i > 0) H[i][i-1] = coeff;
        if (i < N-1) H[i][i+1] = coeff;
    }

    // Construcción de matrices A y B
    vector<vector<cdouble>> A(N, vector<cdouble>(N, 0.0));
    vector<vector<cdouble>> B(N, vector<cdouble>(N, 0.0));
    cdouble alpha = cdouble(0, dt/(2.0*hbar));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                A[i][j] = 1.0 - alpha*H[i][j];
                B[i][j] = 1.0 + alpha*H[i][j];
            } else {
                A[i][j] = -alpha*H[i][j];
                B[i][j] = alpha*H[i][j];
            }
        }
    }

    // Evolución temporal
    for (int step = 0; step < nsteps; step++) {
        vector<cdouble> rhs = matvec(B, psi);

        // Resolver A * psi_new = rhs (Gauss-Seidel)
        vector<cdouble> psi_new = psi;
        for (int iter = 0; iter < 200; iter++) {
            for (int i = 0; i < N; i++) {
                cdouble sum = rhs[i];
                for (int j = 0; j < N; j++) {
                    if (j != i) sum -= A[i][j] * psi_new[j];
                }
                psi_new[i] = sum / A[i][i];
            }
        }

        psi = psi_new;

        if (step % 5 == 0) save_wavefunction(psi, step, dx);
    }

    cout << "Simulación terminada. Archivos guardados en 'resultados_cn/wave_*.dat'\n";
}


void run_cn_simulation_evolution(int N, double L, double dt, int nsteps,
                                double x0, double k0, double sigma) {

    double dx = L / (N + 1);

    // 1. INICIALIZACIÓN del paquete gaussiano
    vector<cdouble> psi(N, 0.0);
    for (int i = 0; i < N; i++) {
        double x = (i + 1) * dx;
        double gauss = exp(-(x - x0)*(x - x0) / (2*sigma*sigma));
        psi[i] = gauss * exp(cdouble(0, k0*x));
    }

    // Normalización
    double norm_factor = 0.0;
    for (int i = 0; i < N; i++) norm_factor += norm(psi[i]) * dx;
    for (int i = 0; i < N; i++) psi[i] /= sqrt(norm_factor);

    // 2. Vectores para almacenar historia temporal
    vector<vector<cdouble>> psi_history;
    vector<double> time_points;

    // 3. Construcción matriz Hamiltoniana (código existente)
    vector<vector<cdouble>> H(N, vector<cdouble>(N, 0.0));
    double coeff = -hbar*hbar / (2*m*dx*dx);
    for (int i = 0; i < N; i++) {
        H[i][i] = -2.0*coeff;
        if (i > 0) H[i][i-1] = coeff;
        if (i < N-1) H[i][i+1] = coeff;
    }

    // 4. Matrices A y B de Crank-Nicolson
    vector<vector<cdouble>> A(N, vector<cdouble>(N, 0.0));
    vector<vector<cdouble>> B(N, vector<cdouble>(N, 0.0));
    cdouble alpha = cdouble(0, dt/(2.0*hbar));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                A[i][j] = 1.0 - alpha*H[i][j];
                B[i][j] = 1.0 + alpha*H[i][j];
            } else {
                A[i][j] = -alpha*H[i][j];
                B[i][j] = alpha*H[i][j];
            }
        }
    }

    // 5. EVOLUCIÓN TEMPORAL
    for (int step = 0; step < nsteps; step++) {
        double current_time = step * dt;

        // Guardar snapshot cada 10 pasos
        if (step % 10 == 0) {
            psi_history.push_back(psi);      // ← ¡Ahora psi está definido!
            time_points.push_back(current_time);
        }

        // ... [código de evolución existente] ...
        vector<cdouble> rhs = matvec(B, psi);
        vector<cdouble> psi_new = psi;
        
        // Resolver con Gauss-Seidel
        for (int iter = 0; iter < 200; iter++) {
            for (int i = 0; i < N; i++) {
                cdouble sum = rhs[i];
                for (int j = 0; j < N; j++) {
                    if (j != i) sum -= A[i][j] * psi_new[j];
                }
                psi_new[i] = sum / A[i][i];
            }
        }

        psi = psi_new;

        // Guardado individual tradicional
        //if (step % 50 == 0) {
          //  save_wavefunction(psi, step, dx);
       // }
    }

    // 6. Guardar evolución temporal completa
   // save_time_evolution(psi_history, time_points, dx, "evolution_full.dat");
    save_time_evolution(psi_history, time_points, dx, "evolucion_completa.txt");

    
    cout << "Simulación de evolución completada. Archivos guardados.\n";
}

void save_time_evolution(const vector<vector<cdouble>>& psi_history, 
                         const vector<double>& time_points, 
                         double dx, const string& filename) {
    
    namespace fs = std::filesystem;
    fs::create_directory("resultados_1D/TDSE/");
    
    //ofstream file("resultados/" + filename);
    ofstream file("resultados_1D/TDSE/" + filename);
    int n_points = psi_history[0].size();
    int n_times = psi_history.size();
    
    // Encabezado: tiempo0, tiempo1, tiempo2, ...
    file << "x";
    for (double t : time_points) {
        file << "\tt=" << t;
    }
    file << "\n";
    
    // Datos: para cada posición x, todas las evoluciones temporales
    for (int i = 0; i < n_points; i++) {
        double x = i * dx;
        file << x;
        
        for (int j = 0; j < n_times; j++) {
            file << "\t" << norm(psi_history[j][i]);  // |ψ(x,t)|²
        }
        file << "\n";
    }
    file.close();
    
    cout << "Evolución temporal guardada en: resultados/" << filename << endl;
}

